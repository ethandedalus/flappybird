#pragma once

#include <raylib.h>

struct Acceleration {
  float x;
  float y;

  constexpr Acceleration() noexcept : x(0), y(0) {}
  constexpr Acceleration(float x, float y) noexcept : x(x), y(y) {}
  constexpr Acceleration(const Vector2& v) noexcept { x = v.x, y = v.y; }
  constexpr explicit inline operator Vector2() const noexcept { return {x, y}; }
  constexpr Acceleration(const Acceleration&) noexcept   = default;
  constexpr Acceleration& operator=(const Acceleration&) = default;
};
