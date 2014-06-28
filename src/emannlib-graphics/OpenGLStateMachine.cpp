#include "OpenGLStateMachine.hpp"

namespace emannlib
{
	OpenGLStateMachine::OpenGLStateMachine(GLFWwindow *activeWindow, uint32_t viewportWidth, uint32_t viewportHeight) :
		m_ViewportHeight(viewportHeight),
		m_ViewportWidth(viewportWidth),
		m_ActiveWindow(activeWindow)
	{

		if (glfwInit() == GL_TRUE)
		{

			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			glfwSwapInterval(1);
			m_ActiveWindow = glfwCreateWindow(m_ViewportWidth, m_ViewportHeight, "Rando Windo", NULL, NULL);

			if (!m_ActiveWindow) /* rgba, depth, stencil */
			{
				glfwTerminate();
				return ;
			}
			glfwMakeContextCurrent(m_ActiveWindow);

			//glfwSetInputMode(m_ActiveWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/

			GLenum err = glewInit();
			if (err != GLEW_OK)
			{
				glfwTerminate();
				return;
			}

			if (!GLEW_VERSION_3_2)
			{
				glfwTerminate();
				return;
			}


			new OpenGLStateMachine(m_ActiveWindow, m_ViewportHeight, m_ViewportWidth);

			ModelViewLoadIdentity();

			return ;
		}

		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLStateMachine::SetViewport(uint32_t width, uint32_t height)
	{
		m_ViewportHeight = height;
		m_ViewportWidth = width;
		glViewport(0,0,width, height);
	}
	uint32_t OpenGLStateMachine::GetViewportWidth() const
	{
		return m_ViewportWidth;
	}
	uint32_t OpenGLStateMachine::GetViewportHeight() const
	{
		return m_ViewportHeight;
	}
	GLFWwindow * OpenGLStateMachine::GetActiveWindow() const
	{
		return m_ActiveWindow;
	}

	void OpenGLStateMachine::SetActiveWindow(GLFWwindow *activeWindow)
	{
		m_ActiveWindow = activeWindow;
	}
	void OpenGLStateMachine::BeginDraw() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
		
	void OpenGLStateMachine::EndDraw() const
	{
		glfwSwapBuffers(m_ActiveWindow);
	}

	void OpenGLStateMachine::SetWindowPosition(uint32_t x, uint32_t y) const
	{
		glfwSetWindowPos(m_ActiveWindow, x, y);
	}
	void OpenGLStateMachine::PushModelView()
	{
		m_CurrentTransform.m_ModelViewMatrix.push(m_CurrentTransform.m_ModelViewMatrix.top());
	
	}
	void OpenGLStateMachine::PopModelView()
	{
		m_CurrentTransform.m_ModelViewMatrix.pop();
		updateMatrixState();
	}

	void OpenGLStateMachine::ModelViewLoadIdentity()
	{
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::mat4();
		updateMatrixState();
	}
	void OpenGLStateMachine::Transform(const glm::mat4& matrix)
	{
		m_CurrentTransform.m_ModelViewMatrix.top() = m_CurrentTransform.m_ModelViewMatrix.top() * matrix;
		updateMatrixState();
	}
	void OpenGLStateMachine::Transform(const GLfloat* matrix)
	{
		//glm::mat4 m = glm::mat4(matrix);
	}
	void OpenGLStateMachine::Translate(const glm::vec3& translate)
	{
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::translate(m_CurrentTransform.m_ModelViewMatrix.top(),translate);
		updateMatrixState();
	}
	void OpenGLStateMachine::Translate(const glm::vec2& translate)
	{
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::translate(m_CurrentTransform.m_ModelViewMatrix.top(), glm::vec3(translate, 0.0));
		updateMatrixState();
	}

	void OpenGLStateMachine::Scale(const glm::vec3& scale)
	{
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::scale(m_CurrentTransform.m_ModelViewMatrix.top(), scale);
		updateMatrixState();
	}
	void OpenGLStateMachine::Scale(const glm::vec2& scale)
	{
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::scale(m_CurrentTransform.m_ModelViewMatrix.top(), glm::vec3(scale,1.0));
		updateMatrixState();
	}
	void OpenGLStateMachine::Rotate(float radians, const glm::vec3& normalVector)
	{
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::rotate(m_CurrentTransform.m_ModelViewMatrix.top(), radians, normalVector);
		updateMatrixState();
	}

	void OpenGLStateMachine::Rotate(float radians)
	{
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::rotate(m_CurrentTransform.m_ModelViewMatrix.top(), radians, glm::vec3(0,0,1.0));
		updateMatrixState();
	}
	void OpenGLStateMachine::LookAt(const glm::vec3& point, const glm::vec3& viewer, const glm::vec3& up)
	{
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::lookAt(viewer, point, up);
		updateMatrixState();
	}

	void OpenGLStateMachine::PushProjection()
	{
		m_CurrentTransform.m_ProjectionMatrix.push(m_CurrentTransform.m_ProjectionMatrix.top());
	}
	void OpenGLStateMachine::PopProjection()
	{
		m_CurrentTransform.m_ProjectionMatrix.pop();
		updateMatrixState();
	}
	void OpenGLStateMachine::Ortho2D(float left, float right, float bottom, float top, float znear, float zfar)
	{
		m_CurrentTransform.m_ProjectionMatrix.top() = glm::ortho(left, right, bottom, top, znear, zfar);
		updateMatrixState();
	}
	void OpenGLStateMachine::Perspective(float fovy, float aspect, float znear, float zfar)
	{
		m_CurrentTransform.m_ProjectionMatrix.top() = glm::perspective(fovy, aspect, znear, zfar);
		updateMatrixState();
	}


	void OpenGLStateMachine::updateMatrixState()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(m_CurrentTransform.m_ProjectionMatrix.top()));
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(m_CurrentTransform.m_ModelViewMatrix.top()));
	}
}