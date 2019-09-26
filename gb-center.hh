#pragma once

#include <geometry.hh>

using Geometry::Point3D;
using Curve = std::vector<Point3D>;

Point3D GBCenter(const std::vector<Curve> &boundaries);
