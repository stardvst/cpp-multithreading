#include <thread>
#include <mutex>
#include <iostream>

std::mutex mutex1;
std::mutex mutex2;

void f()
{
  std::cout << "f locking mutex 1 and mutex 2...\n";
  std::scoped_lock lk{mutex1, mutex2};
  std::cout << "f locked mutex 1 and mutex 2...\n";

  std::cout << "f unlocking mutex 2 and mutex 1...\n";
}

void g()
{
  std::cout << "g locking mutex 2 and mutex 1...\n";
  std::scoped_lock lk{mutex2, mutex1};
  std::cout << "g locked mutex 2 and mutex 1...\n";

  std::cout << "g unlocking mutex 1 and mutex 2...\n";
}

int main()
{
  std::thread t1{f};
  std::thread t2{g};

  t1.join();
  t2.join();
}
