#pragma once

namespace solar
{
	
	#undef M_PI
	static const float M_PI = 3.14159265358979323846264338327950288f;
	static const float M_HALF_PI = M_PI * 0.5f;
	static const float M_DEGTORAD = M_PI / 180.0f;
	static const float M_DEGTORAD_2 = M_PI / 360.0f;    // M_DEGTORAD / 2.f
	static const float M_RADTODEG = 1.0f / M_DEGTORAD;

	template <class T>
	inline T Clamp(T value, T min, T max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;
		else
			return value;
	}
}