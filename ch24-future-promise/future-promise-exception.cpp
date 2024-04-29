#include <iostream>
#include <thread>
#include <chrono>
#include <future>

using namespace std::literals;

void produce(std::promise<int> &promise)
{
  int x{42};
  std::cout << "The promise sets the shared state to " << x << '\n';
  std::this_thread::sleep_for(1s);

  try
  {
    throw std::out_of_range{"from producer thread"};

    promise.set_value(x);
  }
  catch (...)
  {
    // save exception in shared state
    promise.set_exception(std::current_exception());
  }
}

void consume(std::future<int> &future)
{
  try
  {
    std::cout << "The future calls get()...\n";

    int x = future.get();

    std::cout << "The future returns from get()\n";
    std::cout << "The answer is " << x << '\n';
  }
  catch (const std::exception &e)
  {
    std::cerr << "Exception caught: " << e.what() << '\n';
  }
}

int main()
{
  std::promise<int> p;
  std::future f = p.get_future();

  std::thread consumer{consume, std::ref(f)};
  std::thread producer{produce, std::ref(p)};

  consumer.join();
  producer.join();
}
