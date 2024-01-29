#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

struct Student {
  std::string name;
  std::string lastName;
  int birthDay = 0;
  int birthMonth = 0;
  int birthYear = 0;
};

int main() {
  std::vector<Student> students;
  int nStudents;
  std::cin >> nStudents;
  students.reserve(nStudents);

  for (int i = 0; i < nStudents; i++) {
    Student student;
    std::cin >> student.name >> student.lastName >> student.birthDay >> student.birthMonth >> student.birthYear;
    students.push_back(student);
  }

  int nRequests;
  std::cin >> nRequests;
  std::string typeReq;
  int studentNumber;

  for (int i = 0; i < nRequests; i++) {
    std::cin >>typeReq;
    std::cin >> studentNumber;
    if (studentNumber > nStudents || studentNumber <=0 || (typeReq != "name" && typeReq != "date")) {
      std::cout << "bad request" << "\n";
      continue;
    }
    if (typeReq == "name") {
      std::cout << students[studentNumber-1].name << " " << students[studentNumber-1].lastName << "\n";
    } else if (typeReq == "date") {
      std::cout << students[studentNumber-1].birthDay << "." << students[studentNumber-1].birthMonth << "." << students[studentNumber-1].birthYear << "\n";
    }
  }

  return 0;
}