#include <iostream>
#include <numeric>
#include <vector>
#include <execution>
#include <cmath>

int main()
{
  std::vector actual{0.09, 0.22, 0.27, 0.41, 0.52};
  std::vector expected{0.1, 0.2, 0.3, 0.4, 0.5};

  auto max_err = std::transform_reduce(
      std::execution::par_unseq,
      begin(expected), end(expected),
      begin(actual),
      0.0,
      [](auto a, auto b)
      { return std::max(a, b); },
      [](auto l, auto r)
      { return std::fabs(l - r); });

  std::cout << "The largest error is " << max_err << '\n';
}
