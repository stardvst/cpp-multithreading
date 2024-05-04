#include <iostream>
#include <future>
#include <chrono>

using namespace std::literals;

int func()
{
  std::cout << "Running in thread with ID " << std::this_thread::get_id() << '\n';
  std::this_thread::sleep_for(2s);
  return 42;
}

int main()
{
  std::cout << "Main thread with ID " << std::this_thread::get_id() << '\n';
  std::cout << "Starting tasks...\n";

  auto result = std::async(std::launch::async, func);
  //auto result = std::async(std::launch::deferred, func);

  // below two are equivalent
  //auto result = std::async(func);
  //auto result = std::async(std::launch::async | std::launch::deferred, func);

  std::this_thread::sleep_for(2s);
  std::cout << "Calling get()...\n";
  std::cout << result.get() << '\n';
}
