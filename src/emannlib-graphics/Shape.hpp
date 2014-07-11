#pragma once
#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include "emannlib-graphics/OpenGL.hpp"

#include <vector>

namespace emannlib
{
	class Shape
	{
	public:
		float *GetVertexPositions() const;
		float *GetVertexColors() const;
		float *GetVertexNormals() const;
		float *GetVertexTextureCoords() const;
		GLshort *GetVertexIndices() const;

		bool HasVertexColors() const;
		bool HasVertexNormals() const;
		bool HasVertexTextureCoords() const;
	
		int GetNumVertices() const;

	private:
		std::vector<glm::vec3> m_VertexPositions;
		std::vector<glm::vec4> m_VertexColors;
		std::vector<glm::vec3> m_VertexNormals;
		std::vector<glm::vec2> m_vertexTextureCoords;
		std::vector<GLshort> m_VertexIndices;



	};
}

#endif