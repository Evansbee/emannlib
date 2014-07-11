#ifndef __RENDERABLE_OBJECT_HPP__
#define __RENDERABLE_OBJECT_HPP__

#include <memory>
#include <vector>
#include <bitset>
#include <inttypes.h>
#include <string>



#include "Shader.hpp"

namespace emannlib
{
	class RenderableObject
	{
	private:
		GLuint m_VAO;
		
		std::shared_ptr<RenderableObject> m_ParentObject;
		std::vector<std::shared_ptr<RenderableObject > > m_ChildObjects;
		uint32_t m_ID;
		std::string m_Name;
		bool m_Active;
		uint8_t m_TypeOfElementsToDraw;
		uint32_t m_NumberOfElementsToDraw;

		GLuint m_PositionVBO;
		GLuint m_ColorVBO;


		
	public:
		RenderableObject(std::vector<glm::vec2> vertexPositions, std::vector<glm::vec4> vertexColors);


	public:
		static uint32_t ms_NextID;


	};
}

#endif