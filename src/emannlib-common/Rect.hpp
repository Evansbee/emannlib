#ifndef __RECT_HPP__
#define __RECT_HPP__

#include <inttypes.h>
#include <vector>

#include "Vector.hpp"


namespace emannlib
{

	template < typename T >
	class Rect
	{
	public:
		Rect():
		x1((T) 0),
		y1((T) 0), 
		x2((T) 0), 
		y2((T) 0)
		{}

		T GetArea() const { return (x2 - x1) * (y2 - y1); }
		T GetWidth() const { return x2 - x1; }
		T GetHeight() const { return y2 - y1; }
		T GetAspectRatio() const { return GetWidth() / GetHeight(); }

		void Include(T x, T y){
			if (x1 > x) x1 = x;
			if (x2 < x) x2 = x;
			if (y1 > y) y1 = y;
			if (y2 < y) y2 = y;
		}
		void Include(Vec2<T> point)
		{
			Include((T)point.x, (T)point.y)
		}

		void Include(const std::vector<Vec2<T>>& points)
		{
			for (auto p : points)
			{
				Include(p);
			}
		}

		void Normalize()
		{
			if (x1>x2)
			{
				T x = x1;
				x1 = x2;
				x2 = x;
			}

			if (y1>y2)
			{
				T x = y1;
				y1 = y2;
				y2 = y;
			}
		}

		Rect<T> Normalize() const
		{
			Rect<T> result(*this);
			result.Normalize();
			return result;
		}

	public:
		T x1;
		T y1;
		T x2;
		T y2;
	};

	typedef Rect<float> Rectf;
	typedef Rect<double> Rectd;
	typedef Rect<int32_t> Recti;
}

#endif