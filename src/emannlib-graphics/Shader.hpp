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
File Name     : Shader.h
Purpose       :
*/

#pragma once

#include <inttypes.h>
#include <vector>
#include <string>
#include <memory>

#define GLFW_INCLUDE_GLU
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace emannlib
{
	class Shader
	{


		//construction
	public:
		Shader();
		Shader(const std::string& fileName, uint32_t shaderType);
		~Shader();

		void CreateFromFile(const std::string& fileName, uint32_t shaderType);
		void CreateFromSource(const std::string& source, uint32_t shaderType);

		GLuint GetShaderID() const;
	private:
		GLuint m_ShaderID;
	};


	class Program 
	{


		//construction
	public:
		Program();
		Program(const std::vector<std::shared_ptr<Shader> >& shaderList);
		~Program();

		//Helper
		void CreateProgram(const std::vector<std::shared_ptr<Shader> >& shaderList);

		void Use() const;
		void StopUsing() const;
		bool IsInUse() const;

		//Uniforms and Attributes
		GLint Attribute(const std::string& attrib) const;
		GLint Uniform(const std::string& uniform) const;


		void SetAttribute(const std::string& attributeName, const GLint& value) const;
		void SetAttribute(const std::string& attributeName, const GLuint& value) const;
		void SetAttribute(const std::string& attributeName, const GLfloat& value) const;
		void SetAttribute(const std::string& attributeName, const GLdouble& value) const;
											 
		void SetAttribute(const std::string& attributeName, const GLint& value1, const GLint& value2) const;
		void SetAttribute(const std::string& attributeName, const GLuint& value1, const GLuint& value2) const;
		void SetAttribute(const std::string& attributeName, const GLfloat& value1, const GLfloat& value2) const;
		void SetAttribute(const std::string& attributeName, const GLdouble& value1, const GLdouble& value2) const;
											 
		void SetAttribute(const std::string& attributeName, const GLint& value1, const GLint& value2, const GLint& value3) const;
		void SetAttribute(const std::string& attributeName, const GLuint& value1, const GLuint& value2, const GLuint& value3) const;
		void SetAttribute(const std::string& attributeName, const GLfloat& value1, const GLfloat& value2, const GLfloat& value3) const;
		void SetAttribute(const std::string& attributeName, const GLdouble& value1, const GLdouble& value2, const GLdouble& value3) const;

		void SetAttribute(const std::string& attributeName, const GLint& value1, const GLint& value2, const GLint& value3, const GLint& value4) const;
		void SetAttribute(const std::string& attributeName, const GLuint& value1, const GLuint& value2, const GLuint& value3, const GLuint& value4) const;
		void SetAttribute(const std::string& attributeName, const GLfloat& value1, const GLfloat& value2, const GLfloat& value3, const GLfloat& value4) const;
		void SetAttribute(const std::string& attributeName, const GLdouble& value1, const GLdouble& value2, const GLdouble& value3, const GLdouble& value4) const;

		void SetAttribute(const std::string& attributeName, const glm::mat4& value) const;
		void SetAttribute(const std::string& attributeName, const glm::mat3& value) const;
		void SetAttribute(const std::string& attributeName, const glm::mat2& value) const;
											
		void SetAttribute(const std::string& attributeName, const glm::vec4& value) const;
		void SetAttribute(const std::string& attributeName, const glm::vec3& value) const;
		void SetAttribute(const std::string& attributeName, const glm::vec2& value) const;
											 
		void SetAttribute(const std::string& attributeName, const glm::ivec4& value) const;
		void SetAttribute(const std::string& attributeName, const glm::ivec3& value) const;
		void SetAttribute(const std::string& attributeName, const glm::ivec2& value) const;


		void SetUniform(const std::string& uniformName, const GLint& value) const;
		void SetUniform(const std::string& uniformName, const GLuint& value) const;
		void SetUniform(const std::string& uniformName, const GLfloat& value) const;
		void SetUniform(const std::string& uniformName, const GLdouble& value) const;

		void SetUniform(const std::string& uniformName, const GLint& value1, const GLint& value2) const;
		void SetUniform(const std::string& uniformName, const GLuint& value1, const GLuint& value2) const;
		void SetUniform(const std::string& uniformName, const GLfloat& value1, const GLfloat& value2) const;
		void SetUniform(const std::string& uniformName, const GLdouble& value1, const GLdouble& value2) const;

		void SetUniform(const std::string& uniformName, const GLint& value1, const GLint& value2, const GLint& value3) const;
		void SetUniform(const std::string& uniformName, const GLuint& value1, const GLuint& value2, const GLuint& value3) const;
		void SetUniform(const std::string& uniformName, const GLfloat& value1, const GLfloat& value2, const GLfloat& value3) const;
		void SetUniform(const std::string& uniformName, const GLdouble& value1, const GLdouble& value2, const GLdouble& value3) const;

		void SetUniform(const std::string& uniformName, const GLint& value1, const GLint& value2, const GLint& value3, const GLint& value4) const;
		void SetUniform(const std::string& uniformName, const GLuint& value1, const GLuint& value2, const GLuint& value3, const GLuint& value4) const;
		void SetUniform(const std::string& uniformName, const GLfloat& value1, const GLfloat& value2, const GLfloat& value3, const GLfloat& value4) const;
		void SetUniform(const std::string& uniformName, const GLdouble& value1, const GLdouble& value2, const GLdouble& value3, const GLdouble& value4) const;

		void SetUniform(const std::string& uniformName, const glm::mat4& value) const;
		void SetUniform(const std::string& uniformName, const glm::mat3& value) const;
		void SetUniform(const std::string& uniformName, const glm::mat2& value) const;

		void SetUniform(const std::string& uniformName, const glm::vec4& value) const;
		void SetUniform(const std::string& uniformName, const glm::vec3& value) const;
		void SetUniform(const std::string& uniformName, const glm::vec2& value) const;

		void SetUniform(const std::string& uniformName, const glm::ivec4& value) const;
		void SetUniform(const std::string& uniformName, const glm::ivec3& value) const;
		void SetUniform(const std::string& uniformName, const glm::ivec2& value) const;



		GLuint GetProgramID() const;
	private:
		GLuint m_ProgramID;
	};

}
