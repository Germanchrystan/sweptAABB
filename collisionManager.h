#pragma once
#include <raylib.h>

typedef struct 
{
  Vector2 origin;
  Vector2 end;
} Line;

typedef struct
{
  float width;
  float height;
  Vector2 pos;
  Vector2 velocity;
} MovingRect;

bool RayVsRect(Vector2 rayOrigin, Vector2 rayDir, Rectangle target, Vector2* contactPoint,Vector2* contactNormal, float *tHitNear);
bool DynamicRectVsRect(MovingRect sourceRect, Rectangle targetRect, Vector2* contactPoint, Vector2* contactNormal, float* fTime, float dt);

// Moving Rect Method
void ResolveRectVelocity(MovingRect *rect);