#include "Game.h"

#include <raylib.h>

#include <utility>

#include "Acceleration.h"
#include "Atlas.h"
#include "Debug.h"
#include "Gravity.h"
#include "Hitbox.h"
#include "Marker.h"
#include "Position.h"
#include "RaylibExt.h"
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
  m_world.AddComponent<Background>(background, {});
  m_world.AddComponent<Position>(background, {0, 0});
  m_world.AddComponent<Sprite>(background, {.src = BACKGROUND_NIGHT, .dst = {0, 0, 450, 800}});

  Entity ground = m_world.CreateEntity();
  m_world.AddComponent<Ground>(ground, {});
  m_world.AddComponent<Position>(ground, {0, 650});
  m_world.AddComponent<Sprite>(ground, {.src = GROUND, .dst = {0, 650, 450, 150}});
  m_world.AddComponent<Collider>(ground, {.bounds = {0, 650, 450, 150}});

  Entity player = m_world.CreateEntity();
  m_world.AddComponent<Player>(player, {});
  m_world.AddComponent<Position>(player, {20, 0});
  m_world.AddComponent<Velocity>(player, {0, 0});
  m_world.AddComponent<Acceleration>(player, {0, 0});
  m_world.AddComponent<Sprite>(player, {.src = BIRD_YELLOW_MIDSTROKE, .dst = {20, 0, 52, 36}});
  m_world.AddComponent<Gravity>(player, {.g = 400});
  m_world.AddComponent<Collider>(player, {.bounds = {20, 0, 52, 36}});
  m_world.AddComponent<Debug>(player, {.show_hitbox = true});
}

bool Game::IsKeyPressedThrottled(int key, float cooldown, float dt) noexcept {
  m_key_cooldowns[key] -= dt;
  if (IsKeyPressed(key) && m_key_cooldowns[key] <= 0) {
    m_key_cooldowns[key] = cooldown;
    return true;
  }
  return false;
}

void Game::Update() noexcept {}

void Game::InputSystem(float dt) noexcept {
  if (IsKeyPressedThrottled(KEY_B, 0.250, dt)) {
    m_world.Each<Background, Sprite>([](Entity e, Background& bg, Sprite& sprite) {
      if (sprite.src == BACKGROUND_DAY) {
        sprite.src = BACKGROUND_NIGHT;
      } else {
        sprite.src = BACKGROUND_DAY;
      }
    });
  }
  if (IsKeyPressedThrottled(KEY_SPACE, 0.100F, dt)) {
    m_world.Each<Player, Velocity>([](Entity e, Player& p, Velocity& v) {
      v.y = -200;
    });
  }
}

void Game::CollisionSystem() noexcept {
  std::vector<std::pair<Entity, Collider>> collidables{};
  m_world.Each<Position, Collider>([&collidables](Entity e, Position& pos, Collider& hitbox) {
    // if (!hitbox.use_sprite_rec) {
    // } else {
    //   collidables.push_back({e, hitbox});
    // }
  });

  for (size_t i = 0; i < collidables.size(); i++) {
    for (size_t j = 0; j < collidables.size(); j++) {
    }
  }
}

void Game::RenderSystem() noexcept {
  ClearBackground(RAYWHITE);
  m_world.Each<Position, Sprite>([this](Entity e, Position& pos, Sprite& sprite) {
    DrawTexturePro(m_spritesheet, sprite.src, sprite.dst, {sprite.offset_x, sprite.offset_y}, sprite.rotation, sprite.tint);
    if (m_world.HasComponent<Collider>(e) && m_world.HasComponent<Debug>(e)) {
      Collider& c = m_world.GetComponent<Collider>(e);
      DrawRectangleLinesEx(c.bounds, 2.0F, RED);
      // DrawTexturePro(m_spritesheet, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint)
    }
  });
}

void Game::PhysicsSystem(float dt) noexcept {
  m_world.Each<Position, Velocity, Acceleration>([dt, this](Entity e, Position& pos, Velocity& vel, Acceleration& accel) {
    if (m_world.HasComponent<Gravity>(e)) {
      float gravity = m_world.GetComponent<Gravity>(e);
      vel.y += gravity * dt;
      pos.y += vel.y * dt;
    }
    vel.y += accel.y * dt;
    pos.y += vel.y * dt;
    vel.x += accel.x * dt;
    pos.x += vel.x * dt;

    if (m_world.HasComponent<Sprite>(e)) {
      Sprite& sprite = m_world.GetComponent<Sprite>(e);
      sprite.dst.x   = pos.x;
      sprite.dst.y   = pos.y;
    }

    if (m_world.HasComponent<Collider>(e)) {
      Collider& collider = m_world.GetComponent<Collider>(e);
      collider.bounds.x  = pos.x;
      collider.bounds.y  = pos.y;
    }
  });
}

void Game::Run() noexcept {
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    InputSystem(dt);
    PhysicsSystem(dt);

    BeginDrawing();
    RenderSystem();
    EndDrawing();
  }
}
