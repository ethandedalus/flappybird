#pragma once

#include <raylib.h>

#include <array>

// background
static constexpr Rectangle BACKGROUND_DAY   = {0, 0, 144, 256};
static constexpr Rectangle BACKGROUND_NIGHT = {146, 0, 144, 256};
static constexpr Rectangle GROUND           = {292, 0, 168, 56};

// pipes
static constexpr Rectangle BRONZE_PIPE = {0, 323, 26, 160};
static constexpr Rectangle GREEN_PIPE  = {84, 323, 26, 160};

// player
static constexpr Rectangle BIRD_RED_UPSTROKE   = {115, 381, 17, 12};
static constexpr Rectangle BIRD_RED_MIDSTROKE  = {115, 407, 17, 12};
static constexpr Rectangle BIRD_RED_DOWNSTROKE = {115, 433, 17, 12};

static constexpr Rectangle BIRD_YELLOW_UPSTROKE   = {3, 491, 17, 12};
static constexpr Rectangle BIRD_YELLOW_MIDSTROKE  = {31, 491, 17, 12};
static constexpr Rectangle BIRD_YELLOW_DOWNSTROKE = {59, 491, 17, 12};

static constexpr Rectangle BIRD_BLUE_UPSTROKE   = {87, 491, 17, 12};
static constexpr Rectangle BIRD_BLUE_MIDSTROKE  = {115, 329, 17, 12};
static constexpr Rectangle BIRD_BLUE_DOWNSTROKE = {115, 355, 17, 12};

static constexpr std::array<Rectangle, 3> BIRD_RED    = {{BIRD_YELLOW_UPSTROKE, BIRD_YELLOW_MIDSTROKE, BIRD_YELLOW_DOWNSTROKE}};
static constexpr std::array<Rectangle, 3> BIRD_YELLOW = {{BIRD_YELLOW_UPSTROKE, BIRD_YELLOW_MIDSTROKE, BIRD_YELLOW_DOWNSTROKE}};
static constexpr std::array<Rectangle, 3> BIRD_BLUE   = {{BIRD_YELLOW_UPSTROKE, BIRD_YELLOW_MIDSTROKE, BIRD_YELLOW_DOWNSTROKE}};

static constexpr std::array<std::array<Rectangle, 3>, 3> BIRDS = {{BIRD_RED, BIRD_YELLOW, BIRD_BLUE}};

// hud
static constexpr Rectangle SCORE        = {3, 259, 113, 57};
static constexpr Rectangle SILVER_MEDAL = {121, 258, 22, 22};
static constexpr Rectangle GOLD_MEDAL   = {121, 282, 22, 22};
