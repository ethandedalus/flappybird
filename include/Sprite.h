#pragma once

#include "raylib.h"

struct Sprite {
  Rectangle src;
  Rectangle dst;
  float     offset_x = 0.0F;
  float     offset_y = 0.0F;
  float     rotation = 0.0F;
  Color     tint     = WHITE;
};
