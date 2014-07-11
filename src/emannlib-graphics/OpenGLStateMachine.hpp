#pragma once
#ifndef __OPENGL_STATE_MACHINE_HPP__
#define __OPENGL_STATE_MACHINE_HPP__

#include <memory>
#include <stack>
#include <bitset>
#include <inttypes.h>

#include "emannlib-common/Singleton.hpp"
#include "emannlib-graphics/Area.hpp"
#include "emannlib-graphics/Shader.hpp"
#include "emannlib-graphics/OpenGL.hpp"


namespace emannlib
{

	class OpenGLStateMachine : public Singleton < OpenGLStateMachine >
	{
	private:
		//state variables
		std::stack< glm::mat4 > m_ModelViewTransform;
		std::stack< glm::mat4 > m_ProjectionTransform;
		
		std::shared_ptr< Program > m_CurrentProgram;

	public:
		OpenGLStateMachine();

		void UseProgram(std::shared_ptr<Program> newProgram);

		void PushModelView();
		void PopModelView();
		void ModelViewLoadIdentity();
		void Transform(const glm::mat4& matrix);
		void Transform(const GLfloat* matrix);

		void Translate(const glm::vec3& translate);
		void Translate(const glm::vec2& translate);

		void Scale(const glm::vec3& scale);
		void Scale(const glm::vec2& scale);

		void Rotate(float radians, const glm::vec3& normalVector);
		void Rotate(float radians);

		void LookAt(const glm::vec3& point, const glm::vec3& viewer, const glm::vec3& up);

		void PushProjection();
		void PopProjection();
		void ProjectionLoadIdentity();

		void Ortho2D(float left, float right, float bottom, float top, float znear = -1.0f, float zfar = 1.0f);
		void Ortho2DFromCenterAndExtents(const glm::vec2& center, float newWidth, float newHeight);
		void Perspective(float fovy, float aspect, float znear, float zfar);

	private:
		void updateMatrixState();
	};
}

#endif


	//public:
	//	void BeginDraw(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) const;
	//	void EndDraw();

	//	//OGL Control
	//public:
	//	void PushModelView();
	//	void PopModelView();
	//	void ModelViewLoadIdentity();
	//	void Transform(const glm::mat4& matrix);
	//	void Transform(const GLfloat* matrix);

	//	void Translate(const glm::vec3& translate);
	//	void Translate(const glm::vec2& translate);

	//	void Scale(const glm::vec3& scale);
	//	void Scale(const glm::vec2& scale);

	//	void Rotate(float radians, const glm::vec3& normalVector);
	//	void Rotate(float radians);

	//	void LookAt(const glm::vec3& point, const glm::vec3& viewer, const glm::vec3& up);

	//	void PushProjection();
	//	void PopProjection();
	//	void Ortho2D(float left, float right, float bottom, float top, float znear = -1.0f, float zfar = 1.0f);
	//	void Ortho2DFromCenterAndExtents(const Vec2f& center, float newWidth, float newHeight);
	//	void Perspective(float fovy, float aspect, float znear, float zfar);