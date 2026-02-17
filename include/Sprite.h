#pragma once

#include "raylib.h"

struct Sprite {
  Rectangle src;
  Rectangle dst;
  float     offset_x;
  float     offset_y;
  float     rotation;
  Color     tint;
};
