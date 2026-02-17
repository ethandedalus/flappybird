#include "RaylibExt.h"

bool operator==(const Rectangle& r1, const Rectangle& r2) noexcept {
  return r1.x == r2.x && r1.y == r2.y && r1.width == r2.width && r1.height == r2.height;
}
