#include "block.h"
#include "constants.h"

Block::Block(Vector2 pos) : GameObject(Rect(pos, Vector2{BLOCK_SIZE, BLOCK_SIZE}))
{
  sprite = LoadTexture("assets/tileset.png");
  source = {0, 16, 100, 100};
}

Block::~Block()
{
}

void Block::Update(float deltaTime)
{
}

void Block::Draw()
{
  Rectangle source = {0, 16, 16, 16};
  Rectangle destination = {rect.pos.x, rect.pos.y, (float)rect.size.x, (float)rect.size.y};
  DrawTexturePro(sprite, source, destination, {0, 0}, 0.0f, WHITE);
}