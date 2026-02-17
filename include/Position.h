#pragma once

#include <raylib.h>

struct Position {
  constexpr Position() noexcept : x(0.0F), y(0.0F) {}
  constexpr Position(float x, float y) noexcept : x(x), y(y) {}
  constexpr Position(const Vector2& v) noexcept : x(v.x), y(v.y) {}
  constexpr Position(const Position&) noexcept         = default;
  constexpr Position&       operator=(const Position&) = default;
  constexpr explicit inline operator Vector2() const noexcept {
    return {.x = x, .y = y};
  }

  float x, y;
};
