#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

enum class Mood {
    QUIET,
    WORRYING
};

class Queue {
    std::vector<Mood> queue;

public:
    void markPerson(int position, Mood mood) {
        queue[position] = mood;
    }

    void addQuietToEnd(int k) {
        queue.insert(queue.end(), k, Mood::QUIET);
    }

    void removeFromEnd(int k) {
        queue.resize(queue.size() + k);
    }

    int countWorrying() {
        int result = 0;
        for (auto q : queue) {
            if (q == Mood::WORRYING) {
                result++;
            }
        }
        return result;
    }
};


int main()
{
    Queue queue;

    int nOperations;
    std::cin >> nOperations;

    for (int i = 0; i < nOperations; i++) {
        std::string action;
        std::cin >> action;
        if (action == "WORRY_COUNT") {
            std::cout << queue.countWorrying() << "\n";
            continue;
        }

        int actionParameter;
        std::cin >> actionParameter;
        // actionParameter--;

        if (action == "WORRY") {
            queue.markPerson(actionParameter, Mood::WORRYING);
        }
        if (action == "QUIET") {
            queue.markPerson(actionParameter, Mood::QUIET);
        }
        if (action == "COME") {
            if (actionParameter >= 0) {
                queue.addQuietToEnd(actionParameter);
            } else {
                queue.removeFromEnd(actionParameter);
            }
        }

    }

    return 0;
}