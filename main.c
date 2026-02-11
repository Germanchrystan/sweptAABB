// #include<raylib.h>
// #include"collisionManager.h"

// int main()
// {
//   InitWindow(600, 480, "Collision");
//   SetTargetFPS(60);

//   // Line
//   Vector2 mousePos;
//   Line line;
//   line.origin = (Vector2){20,20};
//   // Rectangle
//   Rectangle block = { 100, 100, 50, 50 };
//   // Vectors
//   Vector2 contactPoint;
//   Vector2 contactNormal;
//   Vector2 lineDir;
//   // Update
//   while(!WindowShouldClose())
//   {
//     float tTime = 0;
//     Vector2 mousePos = GetMousePosition();
//     lineDir = (Vector2){ mousePos.x - line.origin.x, mousePos.y - line.origin.y };
//     bool drawCircle = RayVsRect(line.origin, lineDir, block, &contactPoint, &contactNormal, &tTime);
//     // Draw
//     BeginDrawing();
//     ClearBackground(BLACK);
//     DrawRectangleRec(block, BLUE);
//     if (drawCircle)
//     {
//       DrawCircle(contactPoint.x, contactPoint.y, 3, RED);
//     }
//     DrawLineV(line.origin, (Vector2){line.origin.x + lineDir.x, line.origin.y + lineDir.y}, WHITE);
//     EndDrawing();
//   }

//   CloseWindow();
//   return 0;
// }

#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "collisionManager.h"

#define SPEED 105.0f

int main()
{
  InitWindow(600, 480, "Collision");
  SetTargetFPS(60);

  // Block
  Rectangle block = {200, 200, 100, 100};
  // Moving Rectangle
  MovingRect movingRect;
  movingRect.width = 50;
  movingRect.height = 50;
  movingRect.pos = (Vector2){20, 20};

  float dt;
  Vector2 contactPoint;
  Vector2 contactNormal;
  float fTime;
  while (!WindowShouldClose())
  {
    dt = GetFrameTime();
    bool mouseButton = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    // Update Moving Rectangle Velocity
    if (mouseButton)
    {
      Vector2 mousePos = GetMousePosition();
      Vector2 direction = Vector2Normalize(Vector2Subtract(mousePos, movingRect.pos));
      Vector2 newVelocity = (Vector2){direction.x * SPEED * dt, direction.y * SPEED * dt};
      movingRect.velocity = (newVelocity);
    }
    else
    {
      movingRect.velocity = (Vector2){0, 0};
    }

    if (DynamicRectVsRect(movingRect, block, &contactPoint, &contactNormal, &fTime, dt))
    {
      movingRect.velocity.x += contactNormal.x * fabs(movingRect.velocity.x) * (1.0f - fTime);
      movingRect.velocity.y += contactNormal.y * fabs(movingRect.velocity.y) * (1.0f - fTime);
    }

    ResolveRectVelocity(&movingRect);

    // Draw
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(block, BLUE);
    char* text = TextFormat("%.2f %.2f", movingRect.velocity.x, movingRect.velocity.y);
    DrawText(text, 500, 10, 20, RAYWHITE);
    DrawRectangleV(movingRect.pos, (Vector2){movingRect.width, movingRect.height}, GREEN);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}