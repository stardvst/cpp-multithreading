#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <vector>

using namespace std::literals;

std::shared_timed_mutex shmut;
std::mutex printMutex;

void write(int threadNumber)
{
  std::unique_lock lk{printMutex};
  std::cout << "\tWriter thread " << threadNumber << " trying to lock\n";
  lk.unlock();

  std::lock_guard lg{shmut};

  lk.lock();
  std::cout << "\tWriter thread " << threadNumber << " has exclusive lock\n";
  lk.unlock();

  std::this_thread::sleep_for(2s);
  std::cout << "\tWriter thread " << threadNumber << " releasing exclusive lock\n";
}

void read(int threadNumber)
{
  std::unique_lock lg{printMutex};
  std::cout << "Reader thread " << threadNumber << " trying to lock\n";
  lg.unlock();

  std::shared_lock sl{shmut};

  lg.lock();
  std::cout << "Reader thread " << threadNumber << " has shared lock\n";
  lg.unlock();

  std::cout << "Reader thread " << threadNumber << " releasing shared lock\n";
}

int main()
{
  std::vector<std::thread> threads;

  for (auto i = 0; i < 5;++i)
    threads.push_back(std::thread{read, i});

  threads.push_back(std::thread{write, 5});
  threads.push_back(std::thread{write, 6});

  for (auto i = 7; i < 15; ++i)
    threads.push_back(std::thread{read, i});

  for (auto &thread : threads)
    thread.join();
}
