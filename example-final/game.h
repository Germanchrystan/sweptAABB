#pragma once

#include <vector>
#include <memory>
#include "game_object.h"

class Game
{
public:
  Game();
  ~Game() = default;

  bool Init();
  bool Update(float dt);
  void Draw();

private:
  std::vector<std::unique_ptr<GameObject>> vRects;
  const char *sAppName;
};