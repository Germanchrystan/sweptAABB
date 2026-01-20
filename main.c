#include<raylib.h>
#include"collisionManager.h"

typedef struct 
{
  Vector2 origin;
  Vector2 end;
} Line;

int main()
{
  InitWindow(600, 480, "Collision");
  SetTargetFPS(60);
  
  // Line
  Vector2 mousePos;
  Line line;
  line.origin = (Vector2){250,250};
  // Rectangle
  Rectangle block = { 100, 100, 50, 50 };
  // Vectors
  Vector2 contactPoint;
  Vector2 contactNormal;
  
  // Update
  while(!WindowShouldClose())
  {
    line.end = GetMousePosition();
    bool drawCircle = RayVsRect(line.origin, line.end, block, &contactPoint, &contactNormal);
    // Draw
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(block, BLUE);
    if (drawCircle)
    {
      DrawCircle(contactPoint.x, contactPoint.y, 3, RED);
    }
    DrawLineV(line.origin, line.end, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}