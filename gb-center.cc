#include <cassert>

#include "gb-center.hh"

static std::vector<double>
bernstein(size_t n, double u) {
  std::vector<double> coeff;
  coeff.reserve(n + 1);
  coeff.push_back(1.0);
  double u1 = 1.0 - u;
  for (size_t j = 1; j <= n; ++j) {
    double saved = 0.0;
    for (size_t k = 0; k < j; ++k) {
      double tmp = coeff[k];
      coeff[k] = saved + tmp * u1;
      saved = tmp * u;
    }
    coeff.push_back(saved);
  }
  return coeff;
}

Point3D
GBCenter(const std::vector<Curve> &boundaries) {
  auto n = boundaries.size();
  Point3D result(0, 0, 0), center(0, 0, 0);
  auto coeff_s = bernstein(3, 0.5);
  auto coeff_h = bernstein(3, (double)(n - 2) / n);
  double weight_sum = 0.0;
  for (size_t i = 0; i < n; ++i) {
    size_t im = (i + n - 1) % n, ip = (i + 1) % n;
    assert(boundaries[i].size() == 4 && "This function works only for cubic boundaries");
    Curve second_row = {
      boundaries[im][2],
      boundaries[im][2] + boundaries[i][1] - boundaries[i][0],
      boundaries[ip][1] + boundaries[i][2] - boundaries[i][3],
      boundaries[ip][1]
    };
    center += second_row[1];
    for (size_t j = 0; j <= 3; ++j)
      for (size_t k = 0; k < 2; ++k) {
        double weight = 0.5 * coeff_s[j] * coeff_h[k];
        result += (k == 0 ? boundaries[i][j] : second_row[j]) * weight;
        weight_sum += weight;
      }
  }
  center /= n;
  result += center * (1.0 - weight_sum);
  return result;
}
