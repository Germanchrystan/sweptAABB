#include <raylib.h>
#include <math.h>
#include "collisionManager.h"

bool RayVsRect(Vector2 rayOrigin, Vector2 rayDir, Rectangle target, Vector2* contactPoint,Vector2* contactNormal, float *tHitNear)
{
  if (rayDir.x == 0 && rayDir.y == 0) return false;

  Vector2 tNear = (Vector2)
  {
    (rayDir.x != 0) ? (target.x - rayOrigin.x) / rayDir.x : -1e30f,
    (rayDir.y != 0) ? (target.y - rayOrigin.y) / rayDir.y : -1e30f,
  };
  Vector2 tFar = (Vector2)
  {
    (rayDir.x != 0) ? (target.x + target.width - rayOrigin.x) / rayDir.x : 1e30f,
    (rayDir.y != 0) ? (target.y + target.height - rayOrigin.y) / rayDir.y : 1e30f,
  };

  // Swapping
  if (tNear.x > tFar.x)
  {
    float temp = tNear.x;
    tNear.x = tFar.x;
    tFar.x = temp;
  }
  if(tNear.y > tFar.y)
  {
    float temp = tNear.y;
    tNear.y = tFar.y;
    tFar.y = temp;
  }

  // Check Collision
  if (tNear.x > tFar.y || tNear.y > tFar.x) return false;

  float tHitNearTemp = (float)fmax(tNear.x, tNear.y);
  tHitNear = &tHitNearTemp;
  if(*tHitNear > 1.0) return false;
  float tHitFar = fmax(tFar.x, tFar.y);

  if (tHitFar < 0) return 0;


  contactPoint -> x = rayOrigin.x + (*tHitNear) * rayDir.x;
  contactPoint -> y = rayOrigin.y + (*tHitNear) * rayDir.y;
  
  contactNormal -> x = 0;
  contactNormal -> y = 0;

  if (tNear.x > tNear.y)
  {
    if(rayDir.x < 0)
      contactNormal -> x = 1;
    else
      contactNormal -> x = -1;
  }
  else if (tNear.x < tNear.y)
  {
    if(rayDir.y < 0)
    {
      contactNormal -> y = 1;
    }
    else
    {
      contactNormal -> y = -1;
    }
  }

  return true;
};


bool DynamicRectVsRect(MovingRect sourceRect, Rectangle targetRect, Vector2* contactPoint, Vector2* contactNormal, float* fTime, float dt)
{
  if (sourceRect.velocity.x == 0 && sourceRect.velocity.y == 0) return false;

  Rectangle expandedRect;
  expandedRect.x = targetRect.x - sourceRect.width / 2;
  expandedRect.y = targetRect.y - sourceRect.height / 2;
  expandedRect.width = targetRect.width + sourceRect.width;
  expandedRect.height = targetRect.height + sourceRect.height;

  Vector2 velocityDelta = (Vector2)
  {
    sourceRect.velocity.x * dt,
    sourceRect.velocity.y * dt
  };

  if(RayVsRect((Vector2){sourceRect.pos.x + sourceRect.width/2, sourceRect.pos.y + sourceRect.height/2}, velocityDelta, expandedRect, contactPoint, contactNormal, fTime))
  {
    if((*fTime) <= 1.0f) return true;
  }

  return false;
}

void ResolveRectVelocity(MovingRect *rect)
{
  rect -> pos.x += rect -> velocity.x;
  rect -> pos.y += rect -> velocity.y;
}