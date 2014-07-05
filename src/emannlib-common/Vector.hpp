#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <inttypes.h>

#include "../emannlib-math/Math.hpp"

namespace emannlib
{
	template<typename T>
	struct VECTOR_TRAIT {
		typedef float DISTANCE_TYPE;
	};
	
	template<>
	struct VECTOR_TRAIT < double > {
		typedef double DISTANCE_TYPE;
	};

	template<>
	struct VECTOR_TRAIT < long double > {
		typedef long double DISTANCE_TYPE;
	};


	template <typename T>
	class Vec2
	{
	public:
		T x;
		T y;

		//For Return Type Junk
	public:
		typedef typename VECTOR_TRAIT<T>::DISTANCE_TYPE DISTANCE_TYPE;


	public:
		Vec2() : x((T) 0), y(T(0)){}
		Vec2(T nx, T ny) : x(nx), y(ny){}
		Vec2(const Vec2<T>& src) :x(src.x), y(src.y){}
		explicit Vec2(const T* d) : x(d[0]), y(d[1]){}

		template <typename FromT>
		Vec2(const Vec2<FromT>& src) : x(static_cast<T>(src.x)), y(static_cast<T>(src.y)) {}

		//operators
	public:
		template <typename FromT>
		Vec2<T>& operator=(const Vec2<FromT>& rhs)
		{
			x = static_cast<T>(rhs.x);
			y = static_cast<T>(rhs.y);
			return *this;
		}

		Vec2<T>& operator=(const Vec2<T>& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		T& operator[](int n)
		{
			if (n > 1)
			{
				n = 1;
			}
			return (&x)[n];
		}

		const T& operator[](int n) const
		{
			if (n > 1)
			{
				n = 1;
			}
			return (&x)[n];
		}

		T* Data() const { return &(const_cast<Vec2*>(this)->x); }

		const Vec2<T>	operator+(const Vec2<T>& rhs) const { return Vec2<T>(x + rhs.x, y + rhs.y); }
		const Vec2<T>	operator-(const Vec2<T>& rhs) const { return Vec2<T>(x - rhs.x, y - rhs.y); }
		const Vec2<T>	operator*(const Vec2<T>& rhs) const { return Vec2<T>(x * rhs.x, y * rhs.y); }
		const Vec2<T>	operator/(const Vec2<T>& rhs) const { return Vec2<T>(x / rhs.x, y / rhs.y); }
		Vec2<T>&	operator+=(const Vec2<T>& rhs) { x += rhs.x; y += rhs.y; return *this; }
		Vec2<T>&	operator-=(const Vec2<T>& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
		Vec2<T>&	operator*=(const Vec2<T>& rhs)	{ x *= rhs.x; y *= rhs.y; return *this; }
		Vec2<T>&	operator/=(const Vec2<T>& rhs) { x /= rhs.x; y /= rhs.y; return *this; }
		const Vec2<T>	operator/(T rhs) const { return Vec2<T>(x / rhs, y / rhs); }
		Vec2<T>&	operator+=(T rhs)	{ x += rhs;	y += rhs; return *this; }
		Vec2<T>&	operator-=(T rhs) { x -= rhs; y -= rhs; return *this; }
		Vec2<T>&	operator*=(T rhs) { x *= rhs; y *= rhs; return *this; }
		Vec2<T>&	operator/=(T rhs) { x /= rhs; y /= rhs; return *this; }

		Vec2<T>		operator-() const { return Vec2<T>(-x, -y); } // unary negation

		bool operator==(const Vec2<T> &rhs) const
		{
			return (x == rhs.x) && (y == rhs.y);
		}

		bool operator!=(const Vec2<T> &rhs) const
		{
			return !(*this == rhs);
		}

		//operations and junk
	public:
		T Dot(const Vec2<T> &rhs) const
		{
			return x * rhs.x + y * rhs.y;
		}
		T Cross(const Vec2<T> &rhs) const
		{
			return x * rhs.y - y * rhs.x;
		}

		DISTANCE_TYPE Length() const
		{
			return Math<DISTANCE_TYPE>::Sqrt(x*x + y*y);
		}

		DISTANCE_TYPE Distance(const Vec2<T>& rhs) const
		{
			return (*this - rhs).Length();
		}

		void Normalize()
		{
			DISTANCE_TYPE inv = 1 / Length();
			x *= inv;
			y *= inv;
		}

		Vec2<T> GetNormalized() const
		{
			Vec2<T> result = *this;
			result.Normalize();
			return result;
		}

		void Rotate(DISTANCE_TYPE radians)
		{
			T tCos = Math<DISTANCE_TYPE>::Cos(radians);
			T tSin = Math<DISTANCE_TYPE>::Sin(radians);
			T rx = x * tCos - y * tSin;
			y = x*tSin + y*tCos;
			x = rx;
		}

		Vec2<T> xx() const { return Vec2<T>(x, x); }
		Vec2<T> xy() const { return Vec2<T>(x, y); }
		Vec2<T> yx() const { return Vec2<T>(y, x); }
		Vec2<T> yy() const { return Vec2<T>(y, y); }

		static Vec2<T> MakeXAxis() { return Vec2<T>(1, 0); }
		static Vec2<T> MakeYAxis() { return Vec2<T>(0, 1); }
	};

	typedef Vec2<int32_t> Vec2i;
	typedef Vec2<float> Vec2f;
	typedef Vec2<double> Vec2d;
	typedef Vec2<uint32_t> Vec2u;

}

#endif