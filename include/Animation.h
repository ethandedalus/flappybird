#pragma once

#include <raylib.h>

#include <vector>

struct Animation {
  std::vector<Rectangle> frames;
  float                  frame_duration;
  float                  elapsed       = 0.0F;
  size_t                 current_frame = 0;
  bool                   loop          = false;
};
