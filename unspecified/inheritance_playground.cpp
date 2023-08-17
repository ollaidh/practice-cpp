#include <vector>
#include <string>
#include <gtest/gtest.h>

std::vector<std::string> output;

// fixture clears the vector of results:
class InheritanceVirtualFuncTesting : public testing::Test {
protected:
    void SetUp() override {
        output.clear();
    }
};

// CASE 1: non-virtual destructor, non-virtual class method ------------------------------
class Base {
public:
    Base() { output.emplace_back("Base"); };
    ~Base() { output.emplace_back("~Base"); };

    void foo() { output.emplace_back("Base::foo"); }
};

class A : public Base {
public:
    A() { output.emplace_back("A"); };
    ~A() { output.emplace_back("~A"); };

    void foo() { output.emplace_back("A::foo"); }
};

class B : public A {
public:
    B() { output.emplace_back("B"); };
    ~B() { output.emplace_back("~B"); };

    void foo() { output.emplace_back("B::foo"); }
};

TEST_F(InheritanceVirtualFuncTesting, ctorDtorOrder) {
    {
        B b;
    }
    std::vector<std::string> expected = {"Base", "A", "B", "~B", "~A", "~Base"};
    ASSERT_EQ(expected, output);
}

TEST_F(InheritanceVirtualFuncTesting, functionCall) {
    {
        B b;
        b.foo();
    }
    std::vector<std::string> expected = {"Base", "A", "B", "B::foo", "~B", "~A", "~Base"};
    ASSERT_EQ(expected, output);
}

TEST_F(InheritanceVirtualFuncTesting, nonVirtualFunctionCall) {
    {
        // create object p of parent type Base pointing on child type B, then calling foo() func on p object
        // Though pointing on child type B, as functions and dtors are not virtual,
        // foo func is called on obj of parent Base type
        // and only Base type dtors is called, causing a potential memory leak
        std::unique_ptr<Base> p = std::make_unique<B>();
        p->foo();
    }
    std::vector<std::string> expected = {"Base", "A", "B", "Base::foo", "~Base"};
    ASSERT_EQ(expected, output);
}

// CASE 2: non-virtual destructor, virtual class method ------------------------------
class BaseVM {
public:
    BaseVM() { output.emplace_back("BaseVM"); };
    ~BaseVM() { output.emplace_back("~BaseVM"); };

    virtual void foo() { output.emplace_back("BaseVM::foo"); }
};

class AVM : public BaseVM {
public:
    AVM() { output.emplace_back("AVM"); };
    ~AVM() { output.emplace_back("~AVM"); };

    void foo() { output.emplace_back("AVM::foo"); }
};

class BVM : public AVM {
public:
    BVM() { output.emplace_back("BVM"); };
    ~BVM() { output.emplace_back("~BVM"); };

    void foo() { output.emplace_back("BVM::foo"); }
};

TEST_F(InheritanceVirtualFuncTesting, virtualFunctionCall) {
    // create object p of parent type Base pointing on child type B with virtual foo(),
    // Since foo is virtual B::foo is called when calling foo() on p object,
    // Bit dtors are not virtual, so only parent Base type dtor is called
    // causing a potential memory leak
    {
        std::unique_ptr<BaseVM> p = std::make_unique<BVM>();
        p->foo();
    }
    std::vector<std::string> expected = {"BaseVM", "AVM", "BVM", "BVM::foo", "~BaseVM"};
    ASSERT_EQ(expected, output);
}

// CASE 3: virtual destructor, virtual class method ------------------------------
class BaseVV {
public:
    BaseVV() { output.emplace_back("BaseVV"); };
    virtual ~BaseVV() { output.emplace_back("~BaseVV"); };

    virtual void foo() { output.emplace_back("BaseVV::foo"); }
};

class AVV : public BaseVV {
public:
    AVV() { output.emplace_back("AVV"); };
    ~AVV() override { output.emplace_back("~AVV"); };

    void foo() { output.emplace_back("AVV::foo"); }
};

class BVV : public AVV {
public:
    BVV() { output.emplace_back("BVV"); };
    ~BVV() override { output.emplace_back("~BVV"); };

    void foo() { output.emplace_back("BVV::foo"); }
};

TEST_F(InheritanceVirtualFuncTesting, virtualDtorDestruction) {
    {
        BVV p;
        p.foo();
    }
    std::vector<std::string> expected = {"BaseVV", "AVV", "BVV", "BVV::foo", "~BVV", "~AVV", "~BaseVV"};
    ASSERT_EQ(expected, output);
}

TEST_F(InheritanceVirtualFuncTesting, virtualFunctionCallVirtualDtor) {
    // In this case both foo and Base dtor are virtual
    // so a correct (BVV) foo is called when calling foo on p
    // And all dtors are called properly

    {
        std::unique_ptr<BaseVV> p = std::make_unique<BVV>();
        p->foo();
    }
    std::vector<std::string> expected = {"BaseVV", "AVV", "BVV", "BVV::foo", "~BVV", "~AVV", "~BaseVV"};
    ASSERT_EQ(expected, output);
}

void fooValue(BaseVV obj) {
    output.emplace_back("extFooVal");
    obj.foo();
}

TEST_F(InheritanceVirtualFuncTesting, ExternalFuncValue) {
    {
        // Create a BVV object, store it in BaseVV pointer, pass
        // it to an external function by value. In this case
        // BaseVV::foo will be called because we pass a copy
        // of the p object thus cleaning all info about virtual types
        std::unique_ptr<BaseVV> p = std::make_unique<BVV>();
        fooValue(*p);
    }
    std::vector<std::string> expected = {"BaseVV", "AVV", "BVV", "extFooVal", "BaseVV::foo", "~BaseVV", "~BVV", "~AVV", "~BaseVV"};
    ASSERT_EQ(expected, output);
}

void fooReference(BaseVV& ref) {
    output.emplace_back("extFooRef");
    ref.foo();
}

TEST_F(InheritanceVirtualFuncTesting, ExternalFuncReference) {
    {
        // Passing object to a function by reference preserves
        // info about the original type causing fooReference
        // to call BVV::foo
        std::unique_ptr<BaseVV> p = std::make_unique<BVV>();
        fooReference(*p);
    }
    std::vector<std::string> expected = {"BaseVV", "AVV", "BVV", "extFooRef", "BVV::foo", "~BVV", "~AVV", "~BaseVV"};
    ASSERT_EQ(expected, output);
}

void fooPointer(std::shared_ptr<BaseVV> ref) {
    output.emplace_back("extFooPtr");
    ref->foo();
}

TEST_F(InheritanceVirtualFuncTesting, ExternalFuncPointer) {
    {
        // Passing object to a function by pointer is the same
        // as reference and also causes fooPointer
        // to call BVV::foo
        std::shared_ptr<BaseVV> p = std::make_shared<BVV>();
        fooPointer(p);
    }
    std::vector<std::string> expected = {"BaseVV", "AVV", "BVV", "extFooPtr", "BVV::foo", "~BVV", "~AVV", "~BaseVV"};
    ASSERT_EQ(expected, output);
}
