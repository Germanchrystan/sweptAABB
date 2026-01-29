#include <raylib.h>
#include "../collisionManager.h"

int main()
{
  InitWindow(600, 480, "Collision");
  SetTargetFPS(60);
  
  // Block
  Rectangle block = { 200, 200, 100, 100 };
  // Moving Rectangle
  MovingRect movingRect;
  movingRect.width = 50;
  movingRect.height = 50;
  movingRect.pos = (Vector2){ 20, 20 };
  
  while(!WindowShouldClose())
  {
    // Update Moving Rectangle Velocity
    movingRect.velocity = (Vector2){ 2.0f, 1.5f };
    ResolveRectVelocity(&movingRect);
    
    // Draw
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(block, BLUE);
    DrawRectangleV(movingRect.pos, (Vector2){ movingRect.width, movingRect.height }, GREEN);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}