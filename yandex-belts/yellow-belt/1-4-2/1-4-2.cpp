#include <algorithm>
#include <ostream>
#include <tuple>
#include <map>
#include <string>
#include <iostream>

#ifdef LOCAL_RUN

enum class TaskStatus {
  NEW,
  IN_PROGRESS,
  TESTING,
  DONE
};

std::ostream& operator<<(std::ostream& stream, const TaskStatus& date) {
  if (date == TaskStatus::NEW) {
    stream << "NEW";
  } else if  (date == TaskStatus::IN_PROGRESS) {
    stream << "IN_PROGRESS";
  } else if  (date == TaskStatus::TESTING) {
    stream << "TESTING";
  } else if  (date == TaskStatus::DONE) {
    stream << "DONE";
  }
  return stream;
}

using TasksInfo = std::map<TaskStatus, int>;

#endif

std::map<TaskStatus, int> makeNonZeroStatusCopy(const std::map<TaskStatus, int>& stats) {
  std::map<TaskStatus, int> result;
  for (auto& [key, value] : stats) {
    if (value != 0) {
      result[key] = value;
    }
  }
  return result;
}

class TeamTasks {
public:
  TasksInfo GetPersonTasksInfo(const std::string& person) const {
    auto result = makeNonZeroStatusCopy(m_persons.at(person));
    return result;
  }

  void AddNewTask(const std::string& person) {
    m_persons[person][TaskStatus::NEW] += 1;

  }

  std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count) {
    auto& tasks = m_persons[person];

    std::map<TaskStatus, int> updTasks;
    std::map<TaskStatus, int> notUpdTasks = tasks;
    notUpdTasks[TaskStatus::DONE] = 0;

    for (auto& [status, count]: tasks) {
        if (status == TaskStatus::DONE)
          continue;
        while (tasks[status] > 0 && task_count > 0) {
            tasks[status]--;

            updTasks[tasksUpgradeLaw[status]]++;
            notUpdTasks[status]--;
            if (notUpdTasks[status] < 0)
                notUpdTasks[status] = 0;

            task_count--;
        }
        if (task_count == 0) {
            break;
        }
    }

    for (auto status: {TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, TaskStatus::DONE}) {
      tasks[status] += updTasks[status];
    }

    updTasks = makeNonZeroStatusCopy(updTasks);
    notUpdTasks = makeNonZeroStatusCopy(notUpdTasks);

    return std::tuple(updTasks, notUpdTasks);
  }

private:
    std::map<std::string, TasksInfo> m_persons;

    std::map<TaskStatus, TaskStatus> tasksUpgradeLaw = {
      {TaskStatus::NEW, TaskStatus::IN_PROGRESS},
      {TaskStatus::IN_PROGRESS, TaskStatus::TESTING},
      {TaskStatus::TESTING, TaskStatus::DONE}
    };
};


#ifdef LOCAL_RUN

void printStatusInfo(const std::map<TaskStatus, int>& status) {
  for (const auto& [status, count] : status) {
      std::cout << status << ": " << count << " ";
  }
}

void PrintTasksInfo(TasksInfo tasks_info1, TasksInfo tasks_info2) {
   std::cout << "Updated : [";
  for (const auto& [status, count] : tasks_info1) {
      std::cout << status << ": " << count << " ";
  }
  std::cout << "] Untouched : [";
  for (const auto& [status, count] : tasks_info2) {
    std::cout << status << ": " << count << " ";
  }
  std::cout << "]\n";

}


int main() {
  TeamTasks tasks;

   std::cout << "\nJack" << std::endl;

  TasksInfo updated_tasks, untouched_tasks;


  tasks.AddNewTask("Jack");

  tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
  PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

  tasks.AddNewTask("Jack");

  tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
  PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]

  tasks.AddNewTask("Jack");

  printStatusInfo(tasks.GetPersonTasksInfo("Jack"));  // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
  std::cout << std::endl;

  tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
  PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]

  printStatusInfo(tasks.GetPersonTasksInfo("Jack"));  // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
  std::cout << std::endl;

  return 0;
}

#endif
