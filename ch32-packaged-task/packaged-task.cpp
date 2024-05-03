#include <iostream>
#include <future>

int main()
{
  // function isn't executed immediately
  std::packaged_task pkg{
      [](int a, int b)
      { return a + b; }};

  // get the future associated with task's promise
  std::future f = pkg.get_future();

  // create a thread to run the task
  // function is executed here
  std::thread t{std::move(pkg), 6, 7};

  // get the result of the task
  std::cout << "The result is: " << f.get() << '\n';

  t.join();
}
