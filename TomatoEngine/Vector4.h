#pragma once

template<typename T>
class Vector4
{
public:
	T x, y, w, h;

	Vector4(T _x = 0, T _y = 0, T _w = 0, T _h = 0) : x(_x), y(_y), w(_w), h(_h) {}

private:
	// operator + - * /
	inline Vector4 operator +(const Vector4 &v4) const
	{
		return Vector4(x + v4.x, y + v4.y, w + v4.w, h + v4.h);
	}
	inline Vector4 operator -(const Vector4 &v4) const
	{
		return Vector4(x - v4.x, y - v4.y, w - v4.w, h - v4.h);
	}
	inline Vector4 operator *(const float scale) const
	{
		return Vector4(x * scale, y * scale, w * scale, h * scale);
	}
	inline Vector4 operator /(const float scale) const
	{
		return Vector4(x / scale, y / scale, w / scale, h / scale);
	}

};