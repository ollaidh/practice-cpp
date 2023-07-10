// Overload the << operator for Person class


#include <iostream>
#include <gtest/gtest.h>
#include <sstream>

class Person {
public:
    Person(const std::string& fn, const std::string& ln) {
        first_name_ = fn;
        last_name_ = ln;
    }

    std::string firstName() const{
        return first_name_;
    }

    std::string lastName() const{
        return last_name_;
    }

private:
    std::string first_name_;
    std::string last_name_;
};

std::ostream& operator << (std::ostream& stream, const Person& p) {
    stream << "first_name="<< p.firstName() << "," << "last_name=" << p.lastName();
    return stream;
}

TEST(overloadOstream, overload) {
    Person p("Piu", "Miu");
    std::cout << p << std::endl;

    std::stringstream stream;
    stream << p << std::endl;

    std::string expected = "first_name=Piu,last_name=Miu\n";

    ASSERT_EQ(expected, stream.str());
}

