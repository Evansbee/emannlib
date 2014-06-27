#ifndef __AREA_HPP__
#define __AREA_HPP__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace emannlib
{
	class Area
	{
	public:
		glm::vec2 m_UpperLeft;
		glm::vec2 m_LowerRight;
	};
}

#endif