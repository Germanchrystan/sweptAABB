#include <raylib.h>
#include "collision_manager.h"
#include "game_object.h"
#include "vector2_utils.h"

bool PointVsRect(const Vector2 &p, const Rect *r)
{
  return (p.x >= r->pos.x && p.y >= r->pos.y && p.x < r->pos.x + r->size.x && p.y < r->pos.y + r->size.y);
}

bool RectVsRect(const Rect *r1, const Rect *r2)
{
  return (r1->pos.x < r2->pos.x + r2->size.x && r1->pos.x + r1->size.x > r2->pos.x && r1->pos.y < r2->pos.y + r2->size.y && r1->pos.y + r1->size.y > r2->pos.y);
}

bool RayVsRect(const Vector2 &ray_origin, const Vector2 &ray_dir, const Rect *target, Vector2 &contact_point, Vector2 &contact_normal, float &t_hit_near)
{
  contact_normal = {0, 0};
  contact_point = {0, 0};

  // Cache division
  Vector2 invdir = 1.0f / ray_dir;

  // Calculate intersections with rectangle bounding axes
  Vector2 t_near = (target->pos - ray_origin) * invdir;
  Vector2 t_far = (target->pos + target->size - ray_origin) * invdir;

  if (std::isnan(t_far.y) || std::isnan(t_far.x))
    return false;
  if (std::isnan(t_near.y) || std::isnan(t_near.x))
    return false;

  // Sort distances
  if (t_near.x > t_far.x)
    std::swap(t_near.x, t_far.x);
  if (t_near.y > t_far.y)
    std::swap(t_near.y, t_far.y);

  // Early rejection
  if (t_near.x > t_far.y || t_near.y > t_far.x)
    return false;

  // Closest 'time' will be the first contact
  t_hit_near = std::max(t_near.x, t_near.y);

  // Furthest 'time' is contact on opposite side of target
  float t_hit_far = std::min(t_far.x, t_far.y);

  // Reject if ray direction is pointing away from object
  if (t_hit_far < 0)
    return false;

  // Contact point of collision from parametric line equation
  contact_point = ray_origin + t_hit_near * ray_dir;

  if (t_near.x > t_near.y)
  {
    if (invdir.x < 0)
      contact_normal = {1, 0};
    else
      contact_normal = {-1, 0};
  }
  else if (t_near.x < t_near.y)
  {
    if (invdir.y < 0)
      contact_normal = {0, 1};
    else
      contact_normal = {0, -1};
  }

  // Note if t_near == t_far, collision is principly in a diagonal
  // so pointless to resolve. By returning a CN={0,0} even though its
  // considered a hit, the resolver wont change anything.
  return true;
}

bool DynamicRectVsRect(const Rect *r_dynamic, const float fTimeStep, const Rect &r_static,
                       Vector2 &contact_point, Vector2 &contact_normal, float &contact_time)
{
  // Check if dynamic rectangle is actually moving - we assume rectangles are NOT in collision to start
  if (r_dynamic->vel.x == 0 && r_dynamic->vel.y == 0)
    return false;

  // Expand target rectangle by source dimensions
  Rect expanded_target;
  expanded_target.pos = r_static.pos - r_dynamic->size / 2;
  expanded_target.size = r_static.size + r_dynamic->size;

  if (RayVsRect(r_dynamic->pos + r_dynamic->size / 2, r_dynamic->vel * fTimeStep, &expanded_target, contact_point, contact_normal, contact_time))
    return (contact_time >= 0.0f && contact_time < 1.0f);
  else
    return false;
}

bool ResolveDynamicRectVsRect(Rect *r_dynamic, const float fTimeStep, Rect *r_static)
{
  Vector2 contact_point, contact_normal;
  float contact_time = 0.0f;
  if (DynamicRectVsRect(r_dynamic, fTimeStep, *r_static, contact_point, contact_normal, contact_time))
  {
    if (contact_normal.y > 0)
      r_dynamic->contact[0] = r_static;
    if (contact_normal.x < 0)
      r_dynamic->contact[1] = r_static;
    if (contact_normal.y < 0)
      r_dynamic->contact[2] = r_static;
    if (contact_normal.x > 0)
      r_dynamic->contact[3] = r_static;

    r_dynamic->vel += contact_normal * Vector2{std::abs(r_dynamic->vel.x), std::abs(r_dynamic->vel.y)} * (1 - contact_time);
    return true;
  }

  return false;
}

bool CollisionResolver(std::vector<std::unique_ptr<GameObject>> &vRects, float deltaTime)
{
  // Sort collisions in order of distance
  Vector2 cp, cn;
  float t = 0.0f;
  std::vector<std::pair<int, float>> z;

  // Work out collision point, add it to vector along with rect ID
  for (size_t i = 1; i < vRects.size(); i++)
  {
    if (DynamicRectVsRect(&vRects[0]->rect, deltaTime, vRects[i]->rect, cp, cn, t))
    {
      z.push_back({i, t});
    }
  }

  // Do the sort
  std::sort(z.begin(), z.end(), [](const std::pair<int, float> &a, const std::pair<int, float> &b)
            { return a.second < b.second; });

  // Now resolve the collision in correct order
  for (auto j : z)
    ResolveDynamicRectVsRect(&vRects[0]->rect, deltaTime, &vRects[j.first]->rect);

  for (int i = 0; i < 4; i++)
  {
    vRects[0]->rect.contact[i] = nullptr;
  }

  // UPdate the player rectangles position, with its modified velocity
  vRects[0]->rect.pos += vRects[0]->rect.vel * deltaTime;

  return true;
}