#include <iostream>
#include <thread>
#include <string>

int main(int argc, const char *argv[])
{
  std::thread t1([]
  {
    std::cout << "Hello, Thread!\n";
  });
  t1.join();

  std::string str{"Hello, World!"};
  std::cout << "str before thread: " << str << '\n';
  std::thread t2([&]
  {
    str = "Hello, Thread!";
  });
  t2.join();
  std::cout << "str after thread: " << str << '\n';

  return 0;
}
