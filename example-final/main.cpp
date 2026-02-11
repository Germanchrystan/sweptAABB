#include <raylib.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "game.h"
#include "constants.h"

int main()
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mario");
	SetTargetFPS(60);
	Game game;
	game.Init();

	while (!WindowShouldClose())
	{
		game.Update(GetFrameTime());
		// Draw
		BeginDrawing();
		ClearBackground(Color{0x61, 0x85, 0xf8, 0xff});
		game.Draw();
		EndDrawing();
	}
	return 0;
}