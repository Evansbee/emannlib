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

#include "Math.hpp"

namespace emannlib
{
	

		template<> const long double Math<long double>::EPSILON = LDBL_EPSILON;
		template<> const long double Math<long double>::MAX_REAL = LDBL_MAX;
		template<> const long double Math<long double>::PI = 4.0*atan(1.0);
		template<> const long double Math<long double>::TWO_PI = 8.0*atan(1.0);
		template<> const long double Math<long double>::HALF_PI = 2.0*atan(1.0);
		template<> const long double Math<long double>::INV_PI = 1.0 / (4.0*atan(1.0));
		template<> const long double Math<long double>::INV_TWO_PI = 1.0 / (8.0*atan(1.0));
		template<> const long double Math<long double>::DEG_TO_RAD = (4.0*atan(1.0)) / 180.0;
		template<> const long double Math<long double>::RAD_TO_DEG = 180.0 / (4.0*atan(1.0));

		template<> const double Math<double>::EPSILON = DBL_EPSILON;
		template<> const double Math<double>::MAX_REAL = DBL_MAX;
		template<> const double Math<double>::PI = double(4.0*atan(1.0));
		template<> const double Math<double>::TWO_PI = double(8.0*atan(1.0));
		template<> const double Math<double>::HALF_PI = double(2.0*atan(1.0));
		template<> const double Math<double>::INV_PI = double(1.0 / (4.0*atan(1.0)));
		template<> const double Math<double>::INV_TWO_PI = double(1.0 / (8.0*atan(1.0)));
		template<> const double Math<double>::DEG_TO_RAD = double((4.0*atan(1.0)) / 180.0);
		template<> const double Math<double>::RAD_TO_DEG = double(180.0 / (4.0*atan(1.0)));

		template<> const float Math<float>::EPSILON = FLT_EPSILON;
		template<> const float Math<float>::MAX_REAL = FLT_MAX;
		template<> const float Math<float>::PI = float(4.0*atan(1.0));
		template<> const float Math<float>::TWO_PI = float(8.0*atan(1.0));
		template<> const float Math<float>::HALF_PI = float(2.0*atan(1.0));
		template<> const float Math<float>::INV_PI = float(1.0 / (4.0*atan(1.0)));
		template<> const float Math<float>::INV_TWO_PI = float(1.0 / (8.0*atan(1.0)));
		template<> const float Math<float>::DEG_TO_RAD = float((4.0*atan(1.0)) / 180.0);
		template<> const float Math<float>::RAD_TO_DEG = float(180.0 / (4.0*atan(1.0)));

	
}