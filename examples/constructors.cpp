#include <complex>
#include <functional>
#include <iostream>
#include <vector>

#include "lib.hpp"

int main() {
  lazy_priority_queue<int> pq1;
  pq1.push(5);
  std::cout << "pq1.size() = " << pq1.size() << '\n';

  lazy_priority_queue<int> pq2{pq1};
  std::cout << "pq2.size() = " << pq2.size() << '\n';

  std::vector<int> vec{3, 1, 4, 1, 5};
  lazy_priority_queue<int> pq3{std::less<int>(), vec};
  std::cout << "pq3.size() = " << pq3.size() << '\n';

  for (std::cout << "pq3 : "; !pq3.empty(); pq3.pop()) {
    std::cout << pq3.top() << ' ';
  }
  std::cout << '\n';

  // Demo With Custom Comparator:

  using my_value_t = std::complex<double>;
  using my_container_t = std::vector<my_value_t>;

  auto my_comp = [](const my_value_t& z1, const my_value_t& z2) {
    return z2.real() < z1.real();
  };

  lazy_priority_queue<my_value_t, my_container_t, decltype(my_comp)> pq4{
      my_comp};

  using namespace std::complex_literals;
  pq4.push(5.0 + 1i);
  pq4.push(3.0 + 2i);
  pq4.push(7.0 + 3i);

  for (; !pq4.empty(); pq4.pop()) {
    const auto& z = pq4.top();
    std::cout << "pq4.top() = " << z << '\n';
  }

  return 0;
}