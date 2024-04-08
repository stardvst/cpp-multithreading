#include <iostream>
#include <thread>
#include <string>

class greeter
{
public:
  void hello()
  {
    std::cout << "Hello, Thread!\n";
  }
};

int main(int argc, const char *argv[])
{
  greeter g;

  std::thread t(&greeter::hello, &g);
  t.join();

  return 0;
}
