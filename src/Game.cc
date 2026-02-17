#include "Game.h"

#include <raylib.h>

#include "Acceleration.h"
#include "Atlas.h"
#include "Position.h"
#include "Sprite.h"
#include "Velocity.h"

Game::Game() noexcept {
  InitWindow(450, 800, "Flappy Bird");
  SetTargetFPS(60);
}

Game::~Game() noexcept {
  UnloadTexture(m_spritesheet);
  CloseWindow();
}

void Game::Setup() noexcept {
  m_spritesheet = LoadTexture("resources/spritesheet.png");

  Entity background = m_world.CreateEntity();
  m_world.AddComponent<Position>(background, {0, 0});
  m_world.AddComponent<Sprite>(background, {.src = BACKGROUND_NIGHT, .dst = {0, 0, 450, 800}, .tint = WHITE});

  Entity ground = m_world.CreateEntity();
  m_world.AddComponent<Position>(ground, {0, 650});
  m_world.AddComponent<Sprite>(ground, {.src = GROUND});

  Entity player = m_world.CreateEntity();
  m_world.AddComponent<Position>(player, {20, 375});
  m_world.AddComponent<Velocity>(player, {0, 0});
  m_world.AddComponent<Acceleration>(player, {0, 9.81});
  m_world.AddComponent<Sprite>(player, {.src = BIRD_YELLOW_MIDSTROKE, .dst = {20, 375, 52, 36}, .tint = WHITE});
}

void Game::Update() noexcept {}

void Game::InputSystem() noexcept {
}

void Game::RenderSystem() noexcept {
  ClearBackground(RAYWHITE);
  m_world.Each<Position, Sprite>([this](Entity e, Position& pos, Sprite& sprite) {
    DrawTexturePro(m_spritesheet, sprite.src, sprite.dst, {sprite.offset_x, sprite.offset_y}, sprite.rotation, sprite.tint);
  });
}

void Game::PhysicsSystem() noexcept {
}

void Game::Run() noexcept {
  while (!WindowShouldClose()) {
    BeginDrawing();
    RenderSystem();
    EndDrawing();
  }
}
