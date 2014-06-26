/*
Copyright (c) 2013 Evan Ackmann

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:
1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Creator(s)    : Evan Ackmann
File Name     : Math.h
Purpose       :
*/

#pragma once

#include <math.h>
#include <float.h>
#include <inttypes.h>

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_precision.hpp>
//#include <glm/gtc/type_ptr.hpp>

namespace emannlib
{
	inline uint32_t NextPowerOf2(uint32_t v)
	{
		v--;
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		v++;
		return v;
	}

	template <class Real>
	class Math
	{
	public:
		static Real GetGreaterValue(Real v1, Real v2);
		static Real GetLesserValue(Real v1, Real v2);
	//trig
	public:
		static Real ACos(Real fValue);
		static Real ASin(Real fValue);
		static Real ATan(Real fValue);
		static Real ATan2(Real fY, Real fX);
		static Real Ceil(Real fValue);
		static Real Cos(Real fValue);
		static Real Exp(Real fValue);
		static Real FAbs(Real fValue);
		static Real Floor(Real fValue);
		static Real FMod(Real fX, Real fY);
		static Real InvSqrt(Real fValue);
		static Real Log(Real fValue);
		static Real Pow(Real fBase, Real fExponent);
		static Real Sin(Real fValue);
		static Real Sqr(Real fValue);
		static Real Sqrt(Real fValue);
		static Real Tan(Real fValue);

		static Real DegToRad(Real degrees); 
		static Real RadToDeg(Real radians);
		//static Real Determinant(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2);

	public:
		static const Real EPSILON;
		static const Real MAX_REAL;
		static const Real PI;
		static const Real TWO_PI;
		static const Real HALF_PI;
		static const Real INV_PI;
		static const Real INV_TWO_PI;
		static const Real DEG_TO_RAD;
		static const Real RAD_TO_DEG;
	};

	template <class Real>
	Real Math<Real>::GetGreaterValue(Real v1, Real v2)
	{
		if (v1 > v2)
		{
			return v1;
		}
		return v2;
	}

	template <class Real>
	Real Math<Real>::GetLesserValue(Real v1, Real v2)
	{
		if (v1 > v2)
		{
			return v2;
		}
		return v1;
	}

	template <class Real>
	Real Math<Real>::ACos(Real fValue)
	{
		if (Real(-1.0) < fValue)
		{
			if (Real(1.0) > fValue)
			{
				return Real(acos((long double) fValue));
			}
			else
			{
				assert(Real(1.0) < fValue);
				return Real(acos((long double) 1.0));
			}
		}
		else
		{
			assert(Real(-1.0) > fValue);
			return Real(acos((long double) -1.0));
		}

	}

	template <class Real>
	Real Math<Real>::ASin(Real fValue)
	{
		if (Real(-1.0) < fValue)
		{
			if (Real(1.0) > fValue)
			{
				return Real(asin((long double) fValue));
			}
			else
			{
				assert(Real(1.0) < fValue);
				return Real(asin((long double) 1.0));
			}
		}
		else
		{
			assert(Real(-1.0) > fValue);
			return Real(asin((long double) -1.0));
		}
	}

	template <class Real>
	Real Math<Real>::ATan(Real fValue)
	{
		return Real(atan((long double) fValue));
	}

	template <class Real>
	Real Math<Real>::ATan2(Real fY, Real fX)
	{
		return Real(atan2((long double) fY, (long double) fX));
	}

	template <class Real>
	Real Math<Real>::Ceil(Real fValue)
	{
		return Real(ceil((long double) fValue));
	}

	template <class Real>
	Real Math<Real>::Cos(Real fValue)
	{
		return Real(cos((long double) fValue));
	}

	template <class Real>
	Real Math<Real>::Exp(Real fValue)
	{
		return Real(exp((long double) fValue));
	}

	template <class Real>
	Real Math<Real>::FAbs(Real fValue)
	{
		return Real(fabs((long double) fValue));
	}

	template <class Real>
	Real Math<Real>::Floor(Real fValue)
	{
		return Real(floor((long double) fValue));
	}

	template <class Real>
	Real Math<Real>::FMod(Real fX, Real fY)
	{
		return Real(fmod((long double) fX, (long double) fY));
	}

	template <class Real>
	Real Math<Real>::InvSqrt(Real fValue)
	{
		return Real(1.0 / Math<Real>::Sqrt(fValue));
	}

	template <class Real>
	Real Math<Real>::Log(Real fValue)
	{
		return Real(log((long double) fValue));
	}

	template <class Real>
	Real Math<Real>::Pow(Real fBase, Real fExponent)
	{
		return Real(pow((long double) fBase, (long double) fExponent));
	}

	template <class Real>
	Real Math<Real>::Sin(Real fValue)
	{
		return Real(sin((long double) fValue));
	}

	template <class Real>
	Real Math<Real>::Sqr(Real fValue)
	{
		return (fValue * fValue);
	}

	template <class Real>
	Real Math<Real>::Sqrt(Real fValue)
	{
		return Real(sqrt((long double) fValue));
	}

	template <class Real>
	Real Math<Real>::Tan(Real fValue)
	{
		return Real(tan((long double) fValue));
	}

	template <class Real>
	Real Math<Real>::DegToRad(Real degrees)
	{
		return degrees * DEG_TO_RAD;
	}

	template <class Real>
	Real Math<Real>::RadToDeg(Real radians)
	{
		return radians * RAD_TO_DEG;
	}

	/*template <class Real>
	Real Math<Real>::Determinant(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2)
	{
	glm::vec2 v0(p1 - p0);
	glm::vec2 v1(p2 - p1);
	return (Real) (v0.x * v1.y - v1.x - v0.y);
	}*/


}
