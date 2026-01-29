#include<raylib.h>
#include"../collisionManager.h"

int main()
{
  InitWindow(600, 480, "Collision");
  SetTargetFPS(60);
  
  // Line
  Vector2 mousePos;
  Line line;
  line.origin = (Vector2){20,20};
  // Rectangle
  Rectangle block = { 100, 100, 50, 50 };
  // Vectors
  Vector2 contactPoint;
  Vector2 contactNormal;
  Vector2 lineDir;
  // Update
  while(!WindowShouldClose())
  {
    float tTime = 0;
    Vector2 mousePos = GetMousePosition();
    lineDir = (Vector2){ mousePos.x - line.origin.x, mousePos.y - line.origin.y };
    bool drawCircle = RayVsRect(line.origin, lineDir, block, &contactPoint, &contactNormal, &tTime);
    // Draw
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(block, BLUE);
    if (drawCircle)
    {
      DrawCircle(contactPoint.x, contactPoint.y, 3, RED);
    }
    DrawLineV(line.origin, (Vector2){line.origin.x + lineDir.x, line.origin.y + lineDir.y}, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}