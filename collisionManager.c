#include <raylib.h>
#include <math.h>

bool RayVsRect(Vector2 rayOrigin, Vector2 rayEnd, Rectangle target, Vector2* contactPoint,Vector2* contactNormal, float *tHitNear)
{
  Vector2 rayDir = (Vector2){ rayEnd.x - rayOrigin.x, rayEnd.y - rayOrigin.y };

  Vector2 tNear = (Vector2)
  {
    (target.x - rayOrigin.x) / rayDir.x,
    (target.y - rayOrigin.y) / rayDir.y,
  };
  Vector2 tFar = (Vector2)
  {
    (target.x + target.width - rayOrigin.x) / rayDir.x,
    (target.y + target.height - rayOrigin.y) / rayDir.y,
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