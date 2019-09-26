#include <cassert>

#include "c0-center.hh"

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

static Point3D
eval(const Curve &curve, const std::vector<double> &coeffs) {
  Point3D result(0, 0, 0);
  for (size_t i = 0; i < coeffs.size(); ++i)
    result += curve[i] * coeffs[i];
  return result;
}

static Curve
generateOppositeCurve(const std::vector<Curve> &boundaries, size_t i) {
  size_t n = boundaries.size();
  size_t im = (i + n - 1) % n;
  if (n == 3)
    return { boundaries[im][0], boundaries[im][0], boundaries[im][0], boundaries[im][0] };
  size_t ip = (i + 1) % n, imm = (im + n - 1) % n, ipp = (ip + 1) % n;
  auto P0 = boundaries[ip][3];
  auto P1 = P0 + (boundaries[ipp][1] - boundaries[ipp][0]);
  auto P3 = boundaries[im][0];
  auto P2 = P3 + (boundaries[imm][2] - boundaries[imm][3]);
  return { P0, P1, P2, P3 };
}

Point3D
C0Center(const std::vector<Curve> &boundaries) {
  auto n = boundaries.size();
  double x = (double)(n - 2) / n;
  auto coeff_s = bernstein(3, 0.5);
  auto coeff_h1 = bernstein(3, 1 - x);
  auto coeff_h2 = bernstein(3, x);

  Point3D result(0, 0, 0);
  for (size_t i = 0; i < n; ++i) {
    assert(boundaries[i].size() == 4 && "This function works only for cubic boundaries");
    size_t im = (i + n - 1) % n, ip = (i + 1) % n;
    auto opp = generateOppositeCurve(boundaries, i);
    auto S1 = eval(boundaries[i], coeff_s) * (1 - x) + eval(opp, coeff_s) * x;
    auto S2 = eval(boundaries[im], coeff_h1) * 0.5 + eval(boundaries[ip], coeff_h2) * 0.5;
    auto C =
      (boundaries[i][0] + boundaries[i][3]) * 0.5 * (1 - x) +
      (boundaries[im][0] + boundaries[ip][3]) * 0.5 * x;
    result += S1 + S2 - C;
  }
  result /= n;
  return result;
}
