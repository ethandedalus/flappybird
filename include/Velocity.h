#pragma once

#include <raylib.h>

struct Velocity {
  float x;
  float y;

  constexpr Velocity() noexcept : x(0), y(0) {}
  constexpr Velocity(float x, float y) noexcept : x(x), y(y) {}
  constexpr Velocity(const Vector2& v) noexcept { x = v.x, y = v.y; }
  constexpr explicit inline operator Vector2() const noexcept { return {x, y}; }
  constexpr Velocity(const Velocity&) noexcept   = default;
  constexpr Velocity& operator=(const Velocity&) = default;
};
