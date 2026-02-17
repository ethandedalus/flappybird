#pragma once

#include <raylib.h>

#include "World.h"

class Game {
public:
  Game() noexcept;
  ~Game() noexcept;

  void Setup() noexcept;
  void Run() noexcept;

private:
  void InputSystem() noexcept;
  void RenderSystem() noexcept;
  void PhysicsSystem() noexcept;
  void Update() noexcept;

  World     m_world;
  Texture2D m_spritesheet;
};
