#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex shared_counter_mutex;
std::mutex print_mutex;
int shared_counter = 1;

void increment_with_try_lock()
{
  for (int i = 0; i < 100; ++i)
  {
    if (!shared_counter_mutex.try_lock())
    {
      // Mutex acquired successfully
      ++shared_counter;

      print_mutex.lock();
      std::cout << "Thread " << std::this_thread::get_id() << " incremented the counter\n";
      print_mutex.unlock();

      shared_counter_mutex.unlock();
    }
    else
    {
      // Mutex is busy, do a quick task
      print_mutex.lock();
      std::cout << "Thread " << std::this_thread::get_id() << " found the mutex busy...\n";
      print_mutex.unlock();

      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }
}

int main()
{
  std::thread t1(increment_with_try_lock);
  std::thread t2(increment_with_try_lock);

  t1.join();
  t2.join();

  std::cout << "Final value of shared_counter: " << shared_counter << std::endl;
  return 0;
}
