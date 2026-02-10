#pragma once

#include <raylib.h>

#include <cmath>

// Minimal C++ helpers to use raylib's Vector2 in expressions.
// Kept as inline functions/operators so it can be included in multiple .cpp files.

inline Vector2 operator+(Vector2 a, Vector2 b) { return { a.x + b.x, a.y + b.y }; }
inline Vector2 operator-(Vector2 a, Vector2 b) { return { a.x - b.x, a.y - b.y }; }
inline Vector2 operator*(Vector2 a, float s) { return { a.x * s, a.y * s }; }
inline Vector2 operator*(float s, Vector2 a) { return { a.x * s, a.y * s }; }
inline Vector2 operator/(Vector2 a, float s) { return { a.x / s, a.y / s }; }

// Component-wise ops (needed by the collision code).
inline Vector2 operator*(Vector2 a, Vector2 b) { return { a.x * b.x, a.y * b.y }; }
inline Vector2 operator/(float s, Vector2 v) { return { s / v.x, s / v.y }; }

inline Vector2& operator+=(Vector2& a, Vector2 b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

inline float mag2(Vector2 v) { return v.x * v.x + v.y * v.y; }

inline Vector2 norm(Vector2 v)
{
	const float len2 = mag2(v);
	if (len2 <= 0.0f) return { 0.0f, 0.0f };
	const float inv_len = 1.0f / std::sqrt(len2);
	return { v.x * inv_len, v.y * inv_len };
}
