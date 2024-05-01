#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

using namespace std::literals;

std::atomic_flag atomicLock = ATOMIC_FLAG_INIT;

void task(int n)
{
  while (atomicLock.test_and_set())
    ;

  std::this_thread::sleep_for(50ms);
  std::cout << "I'm the task " << n << '\n';
  atomicLock.clear();
}

int main()
{
  std::vector<std::thread> tasks;

  for (auto i = 0; i < 10; ++i)
    tasks.push_back(std::thread{task, i});

  for (auto &task : tasks)
    task.join();
}
