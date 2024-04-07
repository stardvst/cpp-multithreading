#include <iostream>
#include <thread>
#include <string>

void hello(const std::string &str)
{
  std::cout << str << '\n';
}

int main(int argc, const char *argv[])
{
  std::thread t(hello, "Hello, Thread!");
  t.join();
  return 0;
}
