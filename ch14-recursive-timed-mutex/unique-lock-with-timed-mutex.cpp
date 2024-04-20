#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>

using namespace std::literals;

std::timed_mutex mutex;

void task1()
{
  std::cout << "task1 trying to get lock" << std::endl;
  std::unique_lock lk(mutex);
  std::cout << "task1 has lock" << std::endl;

  // pretend to be busy
  std::this_thread::sleep_for(500ms);

  std::cout << "task1 releasing lock" << std::endl;
}

void task2()
{
  std::this_thread::sleep_for(100ms);

  std::cout << "task2 trying to get lock" << std::endl;
  auto timePoint = std::chrono::steady_clock::now() + 100ms;
  std::unique_lock lk(mutex, timePoint);

  while (!lk.owns_lock())
  {
    std::cout << "task2 couldn't get lock" << std::endl;
    timePoint += 100ms;
    lk.try_lock_until(timePoint);
  }

  std::cout << "task2 has lock" << std::endl;

  // pretend to be busy
  std::this_thread::sleep_for(200ms);

  std::cout << "task2 releasing lock" << std::endl;
  mutex.unlock();
}

int main()
{
  std::thread t1{task1}, t2{task2};

  t1.join();
  t2.join();
}
