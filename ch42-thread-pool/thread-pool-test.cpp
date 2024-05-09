#include <iostream>
#include "thread-pool.h"

void task()
{
  std::cout << "Thread ID: " << std::this_thread::get_id() << '\n';
}

int main()
{
  threadPool pool;
  pool.submit(task);
  pool.submit(task);
  pool.submit(task);
  pool.submit(task);
}

