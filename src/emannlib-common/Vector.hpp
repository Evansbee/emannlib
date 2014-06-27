#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <inttypes.h>

namespace emannlib
{
	template<typename T>
	struct VECTOR_TRAIT {
		typedef float DISTANCE_TYPE;
	};
	template<>
	struct VECTOR_TRAIT<double> {
		typedef double DISTANCE_TYPE;
	};

	template<>
	struct VECTOR_TRAIT<int32_t> {
		typedef float DISTANCE_TYPE;
	};
}

#endif