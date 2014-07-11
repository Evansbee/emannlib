#ifndef __RENDERABLE_OBJECT_HPP__
#define __RENDERABLE_OBJECT_HPP__

#include <memory>
#include <vector>
#include <bitset>
#include <inttypes.h>
#include <string>

#define GLFW_INCLUDE_GLU
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

namespace emannlib
{
	class RenderableObject
	{
	private:
		GLuint m_VAO;
		std::bitset<16> m_FeaturesSupported;
		glm::mat4 m_Transform;
		std::shared_ptr<RenderableObject> m_ParentObject;
		std::vector<std::shared_ptr<RenderableObject > > m_ChildObjects;
		uint32_t m_ID;
		std::string m_Name;
		bool m_Active;
		uint8_t m_TypeOfElementsToDraw;
		uint32_t m_NumberOfElementsToDraw;


		//block generic construction....
	public:
		RenderableObject();


	public:
		static uint32_t ms_NextID;

	public:
		static std::shared_ptr<RenderableObject> GenerateCircle();

	};
}

#endif