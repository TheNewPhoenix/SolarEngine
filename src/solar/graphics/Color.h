#pragma once

#include "..\math\Math.h"

#include <glm\glm.hpp>
#include <sstream>

namespace solar
{

	class Color
	{
	public:

		Color() :
			m_r(1.0f),
			m_g(1.0f),
			m_b(1.0f),
			m_a(1.0f)
		{
		}

		Color(const Color& other) :
			m_r(other.m_r),
			m_g(other.m_g),
			m_b(other.m_b),
			m_a(other.m_a)
		{
		}

		Color(float r, float g, float b) :
			m_r(r),
			m_g(g),
			m_b(b),
			m_a(1.0f)
		{
		}

		Color(float r, float g, float b, float a) :
			m_r(r),
			m_g(g),
			m_b(b),
			m_a(a)
		{
		}

		Color& operator =(const Color& rhs)
		{
			m_r = rhs.m_r;
			m_g = rhs.m_g;
			m_b = rhs.m_b;
			m_a = rhs.m_a;
			return *this;
		}

		bool operator ==(const Color& rhs) const { return m_r == rhs.m_r && m_g == rhs.m_g && m_b == rhs.m_b && m_a == rhs.m_a; }

		bool operator !=(const Color& rhs) const { return m_r != rhs.m_r || m_g != rhs.m_g || m_b != rhs.m_b || m_a != rhs.m_a; }

		Color operator *(float rhs) const { return Color(m_r * rhs, m_g * rhs, m_b * rhs, m_a * rhs); }

		Color operator +(const Color& rhs) const { return Color(m_r + rhs.m_r, m_g + rhs.m_g, m_b + rhs.m_b, m_a + rhs.m_a); }

		Color operator -() const { return Color(-m_r, -m_g, -m_b, -m_a); }

		Color operator -(const Color& rhs) const { return Color(m_r - rhs.m_r, m_g - rhs.m_g, m_b - rhs.m_b, m_a - rhs.m_a); }

		Color& operator +=(const Color& rhs)
		{
			m_r += rhs.m_r;
			m_g += rhs.m_g;
			m_b += rhs.m_b;
			m_a += rhs.m_a;
			return *this;
		}

		unsigned toUInt() const
		{
			unsigned r = (unsigned)Clamp(((int)(m_r * 255.0f)), 0, 255);
			unsigned g = (unsigned)Clamp(((int)(m_g * 255.0f)), 0, 255);
			unsigned b = (unsigned)Clamp(((int)(m_b * 255.0f)), 0, 255);
			unsigned a = (unsigned)Clamp(((int)(m_a * 255.0f)), 0, 255);
			return (a << 24) | (b << 16) | (g << 8) | r;
		}

		std::string toString() const
		{
			std::stringstream ss;
			ss << "R: " << m_r << ", G: " << m_g << ", B: " << m_b << ", A: " << m_a;
			return ss.str();
		}

		glm::vec4 toVector4() const { return glm::vec4(m_r, m_g, m_b, m_a); }

		float m_r;
		float m_g;
		float m_b;
		float m_a;

		static const Color WHITE;
		static const Color GRAY;
		static const Color BLACK;
		static const Color RED;
		static const Color GREEN;
		static const Color BLUE;
		static const Color CYAN;
		static const Color MAGENTA;
		static const Color YELLOW;
		static const Color TRANSPARENT;
	};

	inline Color operator *(float lhs, const Color& rhs) { return rhs * lhs; }

}