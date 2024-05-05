#include <iostream>
#include <algorithm>
#include <vector>
#include <execution>

int main()
{
  std::vector<int> v{3, 1, 4, 1, 5, 9};
  try
  {
    std::sort(begin(v), end(v), [&](int a, int b)
              { throw std::out_of_range("Oops"); return true; });
  }
  catch (const std::exception &e)
  {
    std::cerr << "Caught exception: " << e.what() << '\n';
  }

  // all below cases call terminate()

  // try
  // {
  //   std::sort(std::execution::seq, begin(v), end(v), [&](int a, int b)
  //             { throw std::out_of_range("Oops"); return true; });
  // }
  // catch (const std::exception &e)
  // {
  //   std::cerr << "Caught exception: " << e.what() << '\n';
  // }

  // try
  // {
  //   std::sort(std::execution::par, begin(v), end(v), [&](int a, int b)
  //             { throw std::out_of_range("Oops"); return true; });
  // }
  // catch (const std::exception &e)
  // {
  //   std::cerr << "Caught exception: " << e.what() << '\n';
  // }

  // try
  // {
  //   std::sort(std::execution::unseq, begin(v), end(v), [&](int a, int b)
  //             { throw std::out_of_range("Oops"); return true; });
  // }
  // catch (const std::exception &e)
  // {
  //   std::cerr << "Caught exception: " << e.what() << '\n';
  // }

  // try
  // {
  //   std::sort(std::execution::par_unseq, begin(v), end(v), [&](int a, int b)
  //             { throw std::out_of_range("Oops"); return true; });
  // }
  // catch (const std::exception &e)
  // {
  //   std::cerr << "Caught exception: " << e.what() << '\n';
  // }

  for (auto e : v)
    std::cout << e << ',';
  std::cout << '\n';
}
