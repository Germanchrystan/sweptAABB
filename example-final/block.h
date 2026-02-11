#pragma once

#include "game_object.h"

class Block : public GameObject
{
  private:
  Texture2D sprite;
  Rectangle source;
public:
  Block(Vector2 pos);
  ~Block();
  void Update(float deltaTime);
  void Draw();
};