#pragma once

#include <raylib.h>

#include <chrono>
#include <unordered_map>

#include "World.h"

class Game {
public:
  using SteadyClock = std::chrono::steady_clock;

  Game() noexcept;
  ~Game() noexcept;

  void Setup() noexcept;
  void Run() noexcept;

private:
  void AddPipes() noexcept;
  void InputSystem(float dt) noexcept;
  void RenderSystem() noexcept;
  void PhysicsSystem(float dt) noexcept;
  void CollisionSystem() noexcept;
  void Update() noexcept;
  bool IsKeyPressedThrottled(int key, float cooldown, float dt) noexcept;

  World                          m_world;
  Texture2D                      m_spritesheet;
  std::unordered_map<int, float> m_key_cooldowns;
};
