#include "RenderableObject.hpp"




namespace emannlib
{
	uint32_t RenderableObject::ms_NextID = 0;

	RenderableObject::RenderableObject() :
		m_VAO(0),
		m_FeaturesSupported(0),
		m_Transform(glm::mat4()),
		m_ParentObject(nullptr),
		m_ChildObjects(),
		m_ID(ms_NextID++),
		m_Name("Unnamed Object"),
		m_Active(true),
		m_TypeOfElementsToDraw(GL_TRIANGLES),
		m_NumberOfElementsToDraw(0)
	{}


	std::shared_ptr<RenderableObject> RenderableObject::GenerateCircle()
	{
		std::shared_ptr<RenderableObject> obj = std::make_shared<RenderableObject>();

		typedef struct { float x; float y; float z; } VERTEX;
		std::vector<VERTEX> vertexArray;
		
		
		glGenVertexArrays(1, &(obj->m_VAO));
		
		return obj;
	}
}