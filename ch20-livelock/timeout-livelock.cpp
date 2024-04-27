#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>

using namespace std::literals;

std::timed_mutex mutex1, mutex2;

void task1()
{
  std::this_thread::sleep_for(10ms);

  bool locked{false};
  while (!locked)
  {
    std::unique_lock lk{mutex1};
    std::this_thread::sleep_for(1s);
    std::cout << "After you, Claude!\n";

    locked = mutex2.try_lock_for(5ms);
  }

  if (locked)
    std::cout << "Thread 1 has locked both mutexes\n";
}

void task2()
{
  bool locked{false};
  while (!locked)
  {
    std::unique_lock lk{mutex2};
    std::this_thread::sleep_for(1s);
    std::cout << "No, after you, Cecil!\n";

    locked = mutex1.try_lock_for(5ms);
  }

  if (locked)
    std::cout << "Thread 2 has locked both mutexes\n";
}

int main()
{
  std::thread t1{task1};

  std::this_thread::sleep_for(10ms);

  std::thread t2{task2};

  t1.join();
  t2.join();
}
