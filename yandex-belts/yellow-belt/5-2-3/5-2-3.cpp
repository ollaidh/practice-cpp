#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
  virtual void Walk(const string& destintion) const = 0;
};

class Student : public Person {
public:

    Student(const string& name, const string& favouriteSong)
    : Name(name)
    , FavouriteSong(favouriteSong)
    {
    }

    void Learn() const{
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() const {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

public:
    string Name;
    string FavouriteSong;
};


class Teacher : public Person {
public:

    Teacher(const string& name, const string& subject)
    : Name(name)
    , Subject(subject)
    {}

    void Teach() const {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Teacher: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
    string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name)
    : Name(name)
    {}

    void Check(const Teacher& t) const {
        cout << "Policeman: " << Name << " checks Teacher. Teacher's name is: " << t.Name << endl;
    }

    void Check(const Student& s) const {
        cout << "Policeman: " << Name << " checks Student. Student's name is: " << s.Name << endl;
    }

    void Check(const Policeman& p) const {
        cout << "Policeman: " << Name << " checks Policeman. Policeman's name is: " << p.Name << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Policeman: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
};

void VisitPlaces(const Person& person, const vector<string>& places) {
    for (auto p : places) {
        person.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}