#pragma once

#include "game_object.h"

class Player : public GameObject
{
public:
  bool isGrounded;
  Player(Vector2 pos);
  ~Player();

  void Update(float deltaTime) override;
  void Draw() override;

private:
  float speed;
  float gravity;
  Color color; // TODO: Remove this

  const float JUMP_DURATION = 0.5f;
  float jumpTimer;
  void Jump(float dt);
};