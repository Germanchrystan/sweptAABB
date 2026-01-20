#pragma once
#include <raylib.h>
bool RayVsRect(Vector2 rayOrigin, Vector2 rayEnd, Rectangle target, Vector2* contactPoint,Vector2* contactNormal);