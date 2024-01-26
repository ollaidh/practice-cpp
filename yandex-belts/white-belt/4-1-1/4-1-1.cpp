#include <iostream>
#include <string>

struct Specialization {
  std::string value;
  explicit Specialization(std::string new_value)
  : value(std::move(new_value)) {  }
};

struct Course {
  std::string value;
  explicit Course(std::string new_value)
  : value(std::move(new_value)) {  }
};

struct Week {
  std::string value;
  explicit Week(std::string new_value)
  : value(std::move(new_value)) {  }
};

struct LectureTitle {
  std::string specialization;
  std::string course;
  std::string week;

public:
  LectureTitle(Specialization specialization, Course course, Week week) {
    this->specialization = specialization.value;
    this->course = course.value;
    this->week = week.value;
  }
};

int main() {
  LectureTitle title(
    Specialization("C++"),
    Course("White belt"),
    Week("4th")
  );
  return 0;
}