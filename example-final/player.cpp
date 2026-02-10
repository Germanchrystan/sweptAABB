#include "player.h"
#include "vector2_utils.h"
#include "constants.h"

Player::Player(Vector2 pos) : GameObject(Rect(pos, Vector2{BLOCK_SIZE, BLOCK_SIZE}))
{
  speed = 500.0f;
  gravity = speed;
}

Player::~Player()
{
}

void Player::Update(float dt)
{
    bool prevGrounded = isGrounded;
    isGrounded = rect.vel.y == 0;
    if (!prevGrounded && isGrounded)
    {
      jumpTimer = JUMP_DURATION;
    }
    color = isGrounded ? RED : BLUE;
		rect.vel = { 0.0f, 0.0f };
		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) rect.vel.x = -speed;
		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) rect.vel.x = +speed;

    rect.vel.y = gravity;
    if ((isGrounded || jumpTimer > 0) && IsKeyDown(KEY_SPACE))
    {
      Jump(dt);
    } 
}

void Player::Jump(float dt)
{
  if (jumpTimer > 0 && !IsKeyReleased(KEY_SPACE))
  {
    rect.vel.y = -speed * (jumpTimer / JUMP_DURATION);
    jumpTimer -= dt;
    return;
  }
}

void Player::Draw()
{
  DrawRectangleV(rect.pos, rect.size, color);
}