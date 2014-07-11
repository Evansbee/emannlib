#include "RenderableObject.hpp"




namespace emannlib
{
	uint32_t RenderableObject::ms_NextID = 0;

	RenderableObject::RenderableObject(std::vector<glm::vec2> vertexPositions, std::vector<glm::vec4> vertexColors) :
		m_VAO(0),
		m_ParentObject(nullptr),
		m_ChildObjects(),
		m_ID(ms_NextID++),
		m_Active(true),
		m_TypeOfElementsToDraw(GL_TRIANGLES),
		m_NumberOfElementsToDraw(0)
	{
		//glGenVertexArrays(1, &m_VAO);
		//glBindVertexArray(m_VAO);
	
		//GLuint vbo;
		//glGenBuffers(1, &vbo);
		//glBind

		//	GLuint vbo_VertexPositions;

		//glGenBuffers(1, &vbo_VertexPositions);
		//glBindBuffer(GL_ARRAY_BUFFER, vbo_VertexPositions);

		//GLfloat vertexData [] = {
		//	//  X     Y     Z
		//	0.0f, 100.f, 0.0f,
		//	-100.f, -100.f, 0.0f,
		//	100.f, -100.f, 0.0f,
		//};
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		//glVertexAttribPointer(vertAttribposition, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(vertAttribposition);

		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		//GLuint vbo_VertexColors;

		//glGenBuffers(1, &vbo_VertexColors);
		//glBindBuffer(GL_ARRAY_BUFFER, vbo_VertexColors);

		//GLfloat vertColors [] = {
		//	1.0f, 0.0f, 0.0f, 1.0f,
		//	0.0f, 1.0f, 0.0f, 1.0f,
		//	0.0f, 0.0f, 1.0f, 1.0f,
		//};
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertColors), vertColors, GL_STATIC_DRAW);

		//glVertexAttribPointer(vertAttribColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(vertAttribColor);

		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindVertexArray(0);
	
	}



	
}