#pragma once

struct Gravity {
  float g;

  constexpr inline operator float() const noexcept { return g; }
};
