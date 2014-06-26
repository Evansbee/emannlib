#ifndef __OPEN_GL_STATE_MACHINE_HPP__
#define __OPEN_GL_STATE_MACHINE_HPP__

#include "../emannlib-utility/Singleton.hpp"

#include <stack>
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
	class Transform
	{
	public:
		std::stack<glm::mat4> m_ModelViewMatrix;
		std::stack<glm::mat4> m_ProjectionMatrix;
	};


	class OpenGLStateMachine : public Singleton < OpenGLStateMachine >
	{
	public:
		OpenGLStateMachine(GLFWwindow *activeWindow, uint32_t viewportWidth, uint32_t viewportHeight);

		//higher level stuff
	public:
		void SetViewport(uint32_t width, uint32_t height);
		uint32_t GetViewportWidth() const;
		uint32_t GetViewportHeight() const;

		GLFWwindow * GetActiveWindow() const;
		void SetActiveWindow(GLFWwindow *activeWindow);

		void ClearBuffers() const;
		//transforms:
	public:
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
		void Ortho2D(float left, float right, float bottom, float top, float znear = -1.0f, float zfar = 1.0f);
		void Perspective(float fovy, float aspect, float znear, float zfar);

	private:
		void updateMatrixState();
	private:
		emannlib::Transform m_CurrentTransform;
		uint32_t m_ViewportWidth;
		uint32_t m_ViewportHeight;
		GLFWwindow *m_ActiveWindow;
	};
}

#endif