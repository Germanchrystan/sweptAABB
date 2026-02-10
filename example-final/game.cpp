#include "game.h"
#include "player.h"
#include "block.h"
#include "constants.h"
#include "collision_manager.h"

Game::Game()
{
  sAppName = "Mario";
}

bool Game::Init()
{
  vRects.emplace_back(std::make_unique<Player>(Vector2{300.0f, 0.0f}));
  for (int i = 0; i < WINDOW_WIDTH / BLOCK_SIZE; i++)
  {
    vRects.emplace_back(std::make_unique<Block>(Vector2{(float)i * BLOCK_SIZE, WINDOW_HEIGHT - BLOCK_SIZE * 3}));
    vRects.emplace_back(std::make_unique<Block>(Vector2{360.0f, (float)i * BLOCK_SIZE}));
  }

  return true;
}

bool Game::Update(float dt)
{
  vRects[0]->Update(dt);

  CollisionResolver(vRects, dt);
}

void Game::Draw()
{
  for (auto &r : vRects)
    r->Draw();
}
