#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>

using namespace std::literals;

std::mutex mutex;

void task1()
{
  std::cout << "task1 trying to get lock" << std::endl;
  mutex.lock();
  std::cout << "task1 has lock" << std::endl;

  // pretend to be busy
  std::this_thread::sleep_for(500ms);

  std::cout << "task1 releasing lock" << std::endl;
  mutex.unlock();
}

void task2()
{
  std::this_thread::sleep_for(100ms);

  std::cout << "task2 trying to get lock" << std::endl;
  while (!mutex.try_lock())
  {
    std::cout << "task2 couldn't get lock" << std::endl;
    std::this_thread::sleep_for(100ms);
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
