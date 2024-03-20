#include "test_runner.h"
#include <sstream>
#include <string>
using namespace std;

class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }

  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file= value; }

  void Log(const string& message) {
    os << message;
  }

  bool getLogLine() {
    return log_line;
  }

  bool getLogFile() {
    return log_file;
  }

ostream& getStream() {
  return os;
}

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
};

#define LOG(logger, message) {                              \
  string msg;                                               \
  if (logger.getLogLine()) {                                \
    if (logger.getLogFile()) {                                \
      logger.getStream() << __FILE_NAME__<< ":" << __LINE__ << " " << message << endl; \
    } else {                                                \
      logger.getStream() << "Line "  << __LINE__ << " " << message << endl;                   \
    }                                                       \
  } else {  \
    if (logger.getLogFile()) { \
      logger.getStream() << __FILE_NAME__ << " " <<  message << endl;                    \
    } else {  \
      logger.getStream() << message << endl;    \
    }                                                  \
  }                                                         \
  logger.Log(msg);                                          \
}

void TestLog() {
/* Для написания юнит-тестов в этой задаче нам нужно фиксировать конкретные
 * номера строк в ожидаемом значении (см. переменную expected ниже). Если
 * мы добавляем какой-то код выше функции TestLog, то эти номера строк меняются,
 * и наш тест начинает падать. Это неудобно.
 *
 * Чтобы этого избежать, мы используем специальный макрос #line
 * (http://en.cppreference.com/w/cpp/preprocessor/line), который позволяет
 * переопределить номер строки, а также имя файла. Благодаря ему, номера
 * строк внутри функции TestLog будут фиксированы независимо от того, какой
 * код мы добавляем перед ней*/
#line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}
