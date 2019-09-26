#include <iostream>

#include "gb-center.hh"
#include "c0-center.hh"

int main() {
  const std::vector<std::vector<std::vector<double>>> boundaries_ =
    {
      { { 0, 0, 0 }, { 2, 2, 0 }, { 8, 2, 1 }, { 10, 0, 0 } },
      { { 10, 0, 0 }, { 10, 3, 2 }, { 10, 7, 2 }, { 10, 10, 3 } },
      { { 10, 10, 3 }, { 8, 11, 1 }, { 6, 12, 1 }, { 5, 13, 0 } },
      { { 5, 13, 0 }, { 3, 11, 0 }, { 1, 10, -1 }, { -1, 9, -1 } },
      { { -1, 9 -1 }, { 0, 7, 2 }, { 0, 3, 3 }, { 0, 0, 0 } }
    };
  std::vector<Curve> boundaries;
  for (const auto &c_ : boundaries_) {
    Curve c;
    for (const auto &p : c_)
      c.emplace_back(p[0], p[1], p[2]);
    boundaries.push_back(c);
  }
  auto p = GBCenter(boundaries);
  std::cout << p[0] << ' ' << p[1] << ' ' << p[2] << std::endl;
  p = C0Center(boundaries);
  std::cout << p[0] << ' ' << p[1] << ' ' << p[2] << std::endl;
}
