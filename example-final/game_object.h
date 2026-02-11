#pragma once

#include <raylib.h>
#include <array>
#include <vector>

struct Rect
{
  Vector2 pos;
  Vector2 size;
  Vector2 vel;

  std::array<Rect *, 4> contact;

  Rect() : pos{0.0f, 0.0f}, size{0.0f, 0.0f}, vel{0.0f, 0.0f}, contact{nullptr, nullptr, nullptr, nullptr} {}
  Rect(Vector2 p, Vector2 s) : pos(p), size(s), vel{0.0f, 0.0f}, contact{nullptr, nullptr, nullptr, nullptr} {}
};

class GameObject
{
public:
  GameObject() = default;
  GameObject(Rect r) : rect(r) {}
  virtual ~GameObject() = default;

  virtual void Update(float deltaTime) = 0;
  virtual void Draw() = 0;

  Rect rect;
};


