#include <iostream>
#include <thread>
#include <string>

void hello(std::string str)
{
  try
  {
    throw std::exception();
  }
  catch(const std::exception& e)
  {
    std::cerr << "e from thread: " << e.what() << '\n';
  }
}

void world(std::string str)
{
  throw std::exception();
}

int main(int argc, const char *argv[])
{
  // the correct way to handle exceptions from threads
  // a thread function should itself catch the thread's exceptions
  std::thread t1(hello, "Hello, Thread!");
  t1.join();

  // below code won't catch exception from thread, and the program will terminate
  try
  {
    std::thread t2(world, "Hello, Thread!");
    t2.join();
  }
  catch (const std::exception &e)
  {
    std::cerr << "e from main: " << e.what() << '\n';
  }

  return 0;
}
