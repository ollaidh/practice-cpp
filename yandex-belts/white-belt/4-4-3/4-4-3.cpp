#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <system_error>

std::string AskTimeServer() {
    // throw std::system_error(std::error_code());
    // return "11:22:33";
    throw std::invalid_argument("pooooooooo");
}

class TimeServer {
public:
    std::string GetCurrentTime() {
      try {
        last_fetched_time = AskTimeServer();
        return last_fetched_time;
      } catch (std::system_error& err) {
        return last_fetched_time;
      } catch (std::exception& ex) {
        throw;
      }
    }

private:
    std::string last_fetched_time = "00:00:00";
};

int main() {
    // Меняя реализацию функции AskTimeServer, убедитесь, что это код работает корректно
    TimeServer ts;
    try {
        std::cout << ts.GetCurrentTime() << std::endl;
    } catch (std::exception& e) {
        std::cout << "Exception got: " << e.what() << std::endl;
    }
    return 0;
}