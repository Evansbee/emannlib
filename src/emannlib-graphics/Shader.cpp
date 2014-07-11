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
File Name     : ShaderImp.h
Purpose       :
*/

#include "Shader.hpp"
#include "../emannlib-common/AutoProfile.hpp"

#include <fstream>
#include <sstream>

#include <iostream>

namespace emannlib
{

	Shader::Shader() :
		m_ShaderID(0),
		m_ShaderCompileOutput("Shader Not Compiled"),
		m_ShaderSource(""),
		m_ShaderType(GL_VERTEX_SHADER),
		m_IsCompiled(false)
	{
		AUTO_PROFILE("Shader::Shader");
		m_ShaderID = glCreateShader(m_ShaderType);
	}

	Shader::Shader(GLuint shaderType) :
		m_ShaderID(0),
		m_ShaderCompileOutput("Shader Not Compiled"),
		m_ShaderSource(""),
		m_ShaderType(shaderType),
		m_IsCompiled(false)
	{
		AUTO_PROFILE("Shader::Shader");
		m_ShaderID = glCreateShader(m_ShaderType);
	}

	Shader::~Shader()
	{
		if (glIsShader(m_ShaderID))
		{
			glDeleteShader(m_ShaderID);
		}

		m_ShaderID = 0;
	}

	void Shader::CreateFromFile(const std::string& fileName, GLuint shaderType)
	{
		AUTO_PROFILE("Shader::CreateFromFile");
		std::ifstream f;

		f.open(fileName, std::ios::in);
		if (!f.is_open())
		{
			std::cerr<<"Could note open shaderfile: " <<  fileName.c_str() << std::endl;
			m_ShaderSource = "";
			m_ShaderType = shaderType;
			m_IsCompiled = false;
			m_ShaderCompileOutput = "Shader not compiled since last change";
			return;
		}

		std::stringstream readbuffer;
		readbuffer << f.rdbuf();

		m_ShaderSource = readbuffer.str();
		m_ShaderType = shaderType;
		m_IsCompiled = false;
		m_ShaderCompileOutput = "Shader not compiled since last change";
	}


	

	GLuint Shader::GetShaderID() const
	{
		return m_ShaderID;
	}



	bool Shader::Compile()
	{

		const GLchar *source = m_ShaderSource.c_str();

		if (glIsShader(m_ShaderID))
		{
			glDeleteShader(m_ShaderID);
		}

		m_ShaderID = glCreateShader(m_ShaderType);

		glShaderSource(m_ShaderID, 1, &source, NULL);
		glCompileShader(m_ShaderID);

		GLint status;
		glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &status);

		if (status == GL_FALSE)
		{
			GLint errorLogLength;
			glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &errorLogLength);
			m_ShaderCompileOutput.reserve(errorLogLength + 1);
			glGetShaderInfoLog(m_ShaderID, errorLogLength, NULL, (GLchar *) m_ShaderCompileOutput.c_str());
			m_IsCompiled = false;
			
		}
		else
		{
			m_ShaderCompileOutput = "Compile Success";
			m_IsCompiled = true;
		}
		return m_IsCompiled;
	}
	bool Shader::IsCompiled() const
	{
		return m_IsCompiled;
	}

	std::string Shader::GetShaderSource() const{ return m_ShaderSource; }

	void Shader::SetFromSource(const std::string& newSource)
	{
		m_ShaderSource = newSource;
		m_IsCompiled = false;
		m_ShaderCompileOutput = "Shader not recompiled since change";
	}
	void Shader::AppendSource(const std::string& newSource, bool appendNewLine)
	{
		m_ShaderSource += newSource;
		if (appendNewLine)
		{
			m_ShaderSource += "\n";
		}
		m_IsCompiled = false;
		m_ShaderCompileOutput = "Shader not recompiled since change";
	}

	std::string Shader::GetCompilerOutput() const
	{
		return m_ShaderCompileOutput;
	}











	Program::Program() :
		m_ProgramID(0)
	{}


	Program::Program(const std::vector<std::shared_ptr<Shader> >& shaderList) :
		m_ProgramID(0)
	{
		CreateProgram(shaderList);
	}


	void Program::CreateProgram(const std::vector<std::shared_ptr<Shader> >& shaderList)
	{
		AUTO_PROFILE("Program::CreateProgram");
		if (glIsProgram(m_ProgramID))
		{
			glDeleteProgram(m_ProgramID);
			m_ProgramID = 0;
		}

		m_ProgramID = glCreateProgram();

		for (auto shader : shaderList)
		{
			glAttachShader(m_ProgramID, shader->GetShaderID());
		}

		glLinkProgram(m_ProgramID);

		for (auto shader : shaderList)
		{
			glDetachShader(m_ProgramID, shader->GetShaderID());
		}

		GLint status;
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &status);

		if (status == GL_FALSE)
		{
			GLint len;
			glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &len);

			char *infoLog = new char[len + 1];
			glGetProgramInfoLog(m_ProgramID, len, NULL, infoLog);

			std::cerr << infoLog << std::endl;
			//LOG_ERROR("Failed to link program: %s", infoLog);
		}
	}

	Program::~Program()
	{
		if (glIsProgram(m_ProgramID))
		{
			glDeleteProgram(m_ProgramID);
		}
		m_ProgramID = 0;
	}

	void Program::Use() const
	{
		AUTO_PROFILE("Program::Use");
		glUseProgram(m_ProgramID);
	}

	void Program::StopUsing() const
	{
		AUTO_PROFILE("Program::StopUsing");
		if (IsInUse())
		{
			glUseProgram(0);
		}
	}


	bool Program::IsInUse() const
	{
		AUTO_PROFILE("Program::IsInUse");
		GLint currentProgram = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
		return (currentProgram == (GLint) m_ProgramID);
	}

	GLint Program::Attribute(const std::string& attrib) const
	{
		AUTO_PROFILE("Program::Attribute");
		return glGetAttribLocation(m_ProgramID, attrib.c_str());
	}

	GLint Program::Uniform(const std::string& uniform) const
	{
		AUTO_PROFILE("Program::Uniform");
		return glGetUniformLocation(m_ProgramID, uniform.c_str());
	}


	GLuint Program::GetProgramID() const
	{
		return m_ProgramID;
	}


	void Program::SetAttribute(const std::string& attributeName, const GLint& value) const{ assert(IsInUse()); glVertexAttribI1i(Attribute(attributeName), value); }
	void Program::SetAttribute(const std::string& attributeName, const GLuint& value) const{ assert(IsInUse()); glVertexAttribI1ui(Attribute(attributeName), value); }
	void Program::SetAttribute(const std::string& attributeName, const GLfloat& value) const{ assert(IsInUse()); glVertexAttrib1f(Attribute(attributeName), value); }
	void Program::SetAttribute(const std::string& attributeName, const GLdouble& value) const{ assert(IsInUse()); glVertexAttrib1d(Attribute(attributeName), value); }
												  
	void Program::SetAttribute(const std::string& attributeName, const GLint& value1, const GLint& value2) const{ assert(IsInUse()); glVertexAttribI2i(Attribute(attributeName), value1, value2); }
	void Program::SetAttribute(const std::string& attributeName, const GLuint& value1, const GLuint& value2) const{ assert(IsInUse()); glVertexAttribI2ui(Attribute(attributeName), value1, value2); }
	void Program::SetAttribute(const std::string& attributeName, const GLfloat& value1, const GLfloat& value2) const{ assert(IsInUse()); glVertexAttrib2f(Attribute(attributeName), value1, value2); }
	void Program::SetAttribute(const std::string& attributeName, const GLdouble& value1, const GLdouble& value2) const{ assert(IsInUse()); glVertexAttrib2d(Attribute(attributeName), value1, value2); }
												  
	void Program::SetAttribute(const std::string& attributeName, const GLint& value1, const GLint& value2, const GLint& value3) const{ assert(IsInUse()); glVertexAttribI3i(Attribute(attributeName), value1, value2, value3); }
	void Program::SetAttribute(const std::string& attributeName, const GLuint& value1, const GLuint& value2, const GLuint& value3) const{ assert(IsInUse()); glVertexAttribI3ui(Attribute(attributeName), value1, value2, value3); }
	void Program::SetAttribute(const std::string& attributeName, const GLfloat& value1, const GLfloat& value2, const GLfloat& value3) const{ assert(IsInUse()); glVertexAttrib3f(Attribute(attributeName), value1, value2, value3); }
	void Program::SetAttribute(const std::string& attributeName, const GLdouble& value1, const GLdouble& value2, const GLdouble& value3) const{ assert(IsInUse()); glVertexAttrib3d(Attribute(attributeName), value1, value2, value3); }

	void Program::SetAttribute(const std::string& attributeName, const GLint& value1, const GLint& value2, const GLint& value3, const GLint& value4) const{ assert(IsInUse()); glVertexAttribI4i(Attribute(attributeName), value1, value2, value3, value4); }
	void Program::SetAttribute(const std::string& attributeName, const GLuint& value1, const GLuint& value2, const GLuint& value3, const GLuint& value4) const{ assert(IsInUse()); glVertexAttribI4ui(Attribute(attributeName), value1, value2, value3, value4); }
	void Program::SetAttribute(const std::string& attributeName, const GLfloat& value1, const GLfloat& value2, const GLfloat& value3, const GLfloat& value4) const{ assert(IsInUse()); glVertexAttrib4f(Attribute(attributeName), value1, value2, value3, value4); }
	void Program::SetAttribute(const std::string& attributeName, const GLdouble& value1, const GLdouble& value2, const GLdouble& value3, const GLdouble& value4) const{ assert(IsInUse()); glVertexAttrib4d(Attribute(attributeName), value1, value2, value3, value4); }
		 										  
	void Program::SetAttribute(const std::string& attributeName, const glm::mat4& value) const{ assert(false); }
	void Program::SetAttribute(const std::string& attributeName, const glm::mat3& value) const{ assert(false); }
	void Program::SetAttribute(const std::string& attributeName, const glm::mat2& value) const{ assert(false); }
		 										  
	void Program::SetAttribute(const std::string& attributeName, const glm::vec4& value) const{ assert(IsInUse()); glVertexAttrib4fv(Attribute(attributeName), glm::value_ptr(value)); }
	void Program::SetAttribute(const std::string& attributeName, const glm::vec3& value) const{ assert(IsInUse()); glVertexAttrib3fv(Attribute(attributeName), glm::value_ptr(value)); }
	void Program::SetAttribute(const std::string& attributeName, const glm::vec2& value) const{ assert(IsInUse()); glVertexAttrib2fv(Attribute(attributeName), glm::value_ptr(value)); }
		 										  
	void Program::SetAttribute(const std::string& attributeName, const glm::ivec4& value) const{ assert(IsInUse()); glVertexAttribI4iv(Attribute(attributeName), glm::value_ptr(value)); }
	void Program::SetAttribute(const std::string& attributeName, const glm::ivec3& value) const{ assert(IsInUse()); glVertexAttribI3iv(Attribute(attributeName), glm::value_ptr(value)); }
	void Program::SetAttribute(const std::string& attributeName, const glm::ivec2& value) const{ assert(IsInUse()); glVertexAttribI2iv(Attribute(attributeName), glm::value_ptr(value)); }
		 
    
	void Program::SetUniform(const std::string& uniformName, const GLint& value) const{ assert(IsInUse()); glUniform1i(Uniform(uniformName), value); }
	void Program::SetUniform(const std::string& uniformName, const GLuint& value) const{ assert(IsInUse()); glUniform1ui(Uniform(uniformName), value); }
	void Program::SetUniform(const std::string& uniformName, const GLfloat& value) const{ assert(IsInUse()); glUniform1f(Uniform(uniformName), value); }
	void Program::SetUniform(const std::string& uniformName, const GLdouble& value) const{ assert(IsInUse()); glUniform1d(Uniform(uniformName), value); }
		 
	void Program::SetUniform(const std::string& uniformName, const GLint& value1, const GLint& value2) const{ assert(IsInUse()); glUniform2i(Uniform(uniformName), value1, value2); }
	void Program::SetUniform(const std::string& uniformName, const GLuint& value1, const GLuint& value2) const{ assert(IsInUse()); glUniform2ui(Uniform(uniformName), value1, value2); }
	void Program::SetUniform(const std::string& uniformName, const GLfloat& value1, const GLfloat& value2) const{ assert(IsInUse()); glUniform2f(Uniform(uniformName), value1, value2); }
	void Program::SetUniform(const std::string& uniformName, const GLdouble& value1, const GLdouble& value2) const{ assert(IsInUse()); glUniform2d(Uniform(uniformName), value1, value2); }
		 
	void Program::SetUniform(const std::string& uniformName, const GLint& value1, const GLint& value2, const GLint& value3) const{ assert(IsInUse()); glUniform3i(Uniform(uniformName), value1, value2, value3); }
	void Program::SetUniform(const std::string& uniformName, const GLuint& value1, const GLuint& value2, const GLuint& value3) const{ assert(IsInUse()); glUniform3ui(Uniform(uniformName), value1, value2, value3); }
	void Program::SetUniform(const std::string& uniformName, const GLfloat& value1, const GLfloat& value2, const GLfloat& value3) const{ assert(IsInUse()); glUniform3f(Uniform(uniformName), value1, value2, value3); }
	void Program::SetUniform(const std::string& uniformName, const GLdouble& value1, const GLdouble& value2, const GLdouble& value3) const{ assert(IsInUse()); glUniform3d(Uniform(uniformName), value1, value2, value3); }

	void Program::SetUniform(const std::string& uniformName, const GLint& value1, const GLint& value2, const GLint& value3, const GLint& value4) const{ assert(IsInUse()); glUniform4i(Uniform(uniformName), value1, value2, value3, value4); }
	void Program::SetUniform(const std::string& uniformName, const GLuint& value1, const GLuint& value2, const GLuint& value3, const GLuint& value4) const{ assert(IsInUse()); glUniform4ui(Uniform(uniformName), value1, value2, value3, value4); }
	void Program::SetUniform(const std::string& uniformName, const GLfloat& value1, const GLfloat& value2, const GLfloat& value3, const GLfloat& value4) const{ assert(IsInUse()); glUniform4f(Uniform(uniformName), value1, value2, value3, value4); }
	void Program::SetUniform(const std::string& uniformName, const GLdouble& value1, const GLdouble& value2, const GLdouble& value3, const GLdouble& value4) const{ assert(IsInUse()); glUniform4d(Uniform(uniformName), value1, value2, value3, value4); }

	void Program::SetUniform(const std::string& uniformName, const glm::mat4& value) const{ assert(IsInUse()); glUniformMatrix4fv(Uniform(uniformName), 1, GL_FALSE, glm::value_ptr(value)); }
	void Program::SetUniform(const std::string& uniformName, const glm::mat3& value) const{ assert(IsInUse()); glUniformMatrix3fv(Uniform(uniformName), 1, GL_FALSE, glm::value_ptr(value)); }
	void Program::SetUniform(const std::string& uniformName, const glm::mat2& value) const{ assert(IsInUse()); glUniformMatrix2fv(Uniform(uniformName), 1, GL_FALSE, glm::value_ptr(value)); }
		 
	void Program::SetUniform(const std::string& uniformName, const glm::vec4& value) const{ assert(IsInUse()); glUniform4fv(Uniform(uniformName), 1, glm::value_ptr(value)); }
	void Program::SetUniform(const std::string& uniformName, const glm::vec3& value) const{ assert(IsInUse()); glUniform3fv(Uniform(uniformName), 1, glm::value_ptr(value)); }
	void Program::SetUniform(const std::string& uniformName, const glm::vec2& value) const{ assert(IsInUse()); glUniform2fv(Uniform(uniformName), 1, glm::value_ptr(value)); }
		 
	void Program::SetUniform(const std::string& uniformName, const glm::ivec4& value) const{ assert(IsInUse());  glUniform4iv(Uniform(uniformName), 1, glm::value_ptr(value)); }
	void Program::SetUniform(const std::string& uniformName, const glm::ivec3& value) const{ assert(IsInUse()); glUniform3iv(Uniform(uniformName), 1, glm::value_ptr(value)); }
	void Program::SetUniform(const std::string& uniformName, const glm::ivec2& value) const{ assert(IsInUse()); glUniform2iv(Uniform(uniformName), 1, glm::value_ptr(value)); }





	ShaderBuilder::ShaderBuilder(uint32_t type) :
		m_ShaderType(type),
		m_ShaderSource("")
	{}

	void ShaderBuilder::AddLine(const std::string& newLine)
	{
		m_ShaderSource += newLine;
		m_ShaderSource += "\n";
	}

	std::string ShaderBuilder::GetSource() const
	{
		return m_ShaderSource;
	}

	uint32_t ShaderBuilder::GetType() const
	{
		return m_ShaderType;
	}




}