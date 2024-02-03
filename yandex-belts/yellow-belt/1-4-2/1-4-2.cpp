#include <algorithm>
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
    std::map<TaskStatus, int> updTasks;
    std::map<TaskStatus, int> notUpdTasks;

    std::map<TaskStatus, int> newStatus = m_persons[person];


    m_persons[person][TaskStatus::DONE] = 0;
    // std::cout << m_persons[person][TaskStatus::NEW] << " " << m_persons[person][TaskStatus::IN_PROGRESS] << " " << m_persons[person][TaskStatus::TESTING] << " " << m_persons[person][TaskStatus::DONE] << "\n";

    int upgraded = 0;
    auto& tasks = m_persons[person];
    for (auto& [status, count]: tasks) {
        upgraded = 0;
        int notUpgraded = newStatus[status];
        while (tasks[status] > 0 && task_count > 0) {
            tasks[status]--;
            task_count--;
            upgraded++;
            updTasks[tasksUpgradeLaw[status]]++;
        }
        tasks[tasksUpgradeLaw[status]] += upgraded;
        notUpdTasks[status] = notUpgraded - upgraded;
        if (task_count == 0) {
            break;
        }
    }

    // std::cout << m_persons[person][TaskStatus::NEW] << " " << m_persons[person][TaskStatus::IN_PROGRESS] << " " << m_persons[person][TaskStatus::TESTING] << " " << m_persons[person][TaskStatus::DONE] << "\n";

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

void PrintTasksInfo(TasksInfo tasks_info) {
  std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  std::cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  std::cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
  tasks.PerformPersonTasks("Ivan", 2);
  std::cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  std::cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  std::cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  std::cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  for (int i = 0; i < 5; ++i) {
    tasks.AddNewTask("Ivan");
  }
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  tasks.PerformPersonTasks("Ivan", 2);
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));


  return 0;
}



#endif
