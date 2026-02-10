#pragma once

#include "game_object.h"

bool PointVsRect(const Vector2 &p, const Rect *r);
bool RectVsRect(const Rect *r1, const Rect *r2);
bool RayVsRect(const Vector2 &ray_origin, const Vector2 &ray_dir, const Rect *target, Vector2 &contact_point, Vector2 &contact_normal, float &t_hit_near);
bool DynamicRectVsRect(const Rect *r_dynamic, const float fTimeStep, const Rect &r_static, Vector2 &contact_point, Vector2 &contact_normal, float &contact_time);
bool ResolveDynamicRectVsRect(Rect *r_dynamic, const float fTimeStep, Rect *r_static);

bool CollisionResolver(std::vector<std::unique_ptr<GameObject>> &vRects, float deltaTime);