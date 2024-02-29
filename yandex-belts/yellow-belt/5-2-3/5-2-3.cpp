#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
  virtual void Walk(const string& destintion) = 0;
};

class Student : Human{
public:

    Student(const string& name, const string& favouriteSong)
    : Name(name)
    , FavouriteSong(favouriteSong)
    {
    }

    void Learn() {
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(const string& destination) override {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

public:
    string Name;
    string FavouriteSong;
};


class Teacher : Human{
public:

    Teacher(const string& name, const string& subject)
    : Name(name)
    , Subject(subject)
    {}

    void Teach() {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }

    void Walk(const string& destination) override {
        cout << "Teacher: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
    string Subject;
};


class Policeman : Human {
public:
    Policeman(const string& name)
    : Name(name)
    {}

    void Check(Teacher t) {
        cout << "Policeman: " << Name << " checks Teacher. Teacher's name is: " << t.Name << endl;
    }

    void Check(Student s) {
        cout << "Policeman: " << Name << " checks Student. Student's name is: " << s.Name << endl;
    }

    void Check(Policeman p) {
        cout << "Policeman: " << Name << " checks Policeman. Policeman's name is: " << p.Name << endl;
    }

    void Walk(const string& destination) override {
        cout << "Policeman: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
};


void VisitPlaces(Teacher t, vector<string> places) {
    for (auto p : places) {
        t.Walk(p);
    }
}

void VisitPlaces(Student s, vector<string> places) {
    for (auto p : places) {
        s.Walk(p);
    }
}

void VisitPlaces(Policeman pol, vector<string> places) {
    for (auto p : places) {
        pol.Walk(p);
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