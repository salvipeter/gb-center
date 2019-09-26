#pragma once

#include <geometry.hh>

using Geometry::Point3D;
using Curve = std::vector<Point3D>;

Point3D C0Center(const std::vector<Curve> &boundaries);
