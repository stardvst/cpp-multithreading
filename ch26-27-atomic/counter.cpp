#include <thread>
#include <iostream>
#include <vector>
#include <atomic>

// not thread-safe
// int counter{0};

// thread-safe
std::atomic counter{0};

void task()
{
  for (auto i = 0; i < 100'000; ++i)
    counter.fetch_add(1); // same as counter++
}

int main()
{
  std::vector<std::thread> tasks;

  for (auto i = 0; i < 10; ++i)
    tasks.push_back(std::thread{task});

  for (auto &task : tasks)
    task.join();

  std::cout << "counter: " << counter << '\n';
}
