#pragma once
template<typename T>
class Vector2
{
public:
	T x, y;

	Vector2(T _x = 0, T _y = 0) : x(_x), y(_y) {}

private:
	// operator + - * /
	inline Vector2 operator +(const Vector2 &v2) const
	{
		return Vector2(x + v2.x, y + v2.y);
	}
	inline Vector2 operator -(const Vector2 &v2) const
	{
		return Vector2(x - v2.x, y - v2.y);
	}
	inline Vector2 operator *(const float scale) const
	{
		return Vector2(x * scale, y * scale);
	}
	inline Vector2 operator /(const float scale) const
	{
		return Vector2(x / scale, y / scale);
	}

};