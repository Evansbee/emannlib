#include "OpenGLStateMachine.hpp"

#include "../emannlib-common/AutoProfile.hpp"

namespace emannlib
{
	

	OpenGLStateMachine::OpenGLStateMachine(uint32_t viewportWidth, uint32_t viewportHeight) :
		m_ViewportHeight(viewportHeight),
		m_ViewportWidth(viewportWidth)
	{
		m_CurrentTransform.m_ModelViewMatrix.push(glm::mat4());
		m_CurrentTransform.m_ProjectionMatrix.push(glm::mat4());

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
				return;
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

			ModelViewLoadIdentity();

			SetViewport(m_ViewportWidth, m_ViewportHeight);
			Ortho2D(-m_ViewportWidth / 2., m_ViewportWidth / 2., -m_ViewportHeight / 2., m_ViewportHeight / 2., 1.f, -1.f);
		}


		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	bool OpenGLStateMachine::WindowShouldClose() const
	{
		AUTO_PROFILE("OpenGLStateMachine::WindowShouldClose");
		return glfwWindowShouldClose(m_ActiveWindow);
	}
	void OpenGLStateMachine::MessagePump() const
	{
		AUTO_PROFILE("OpenGLStateMachine::MessagePump");
		glfwPollEvents();
	}
	void OpenGLStateMachine::SetViewport(uint32_t width, uint32_t height)
	{
		AUTO_PROFILE("OpenGLStateMachine::SetViewport");
		m_ViewportHeight = height;
		m_ViewportWidth = width;
		glViewport(0,0,width, height);
	}
	uint32_t OpenGLStateMachine::GetViewportWidth() const
	{
		AUTO_PROFILE("OpenGLStateMachine::GetViewportWidth");
		return m_ViewportWidth;
	}
	uint32_t OpenGLStateMachine::GetViewportHeight() const
	{
		AUTO_PROFILE("OpenGLStateMachine::GetViewportHeight");
		return m_ViewportHeight;
	}
	GLFWwindow * OpenGLStateMachine::GetActiveWindow() const
	{
		AUTO_PROFILE("OpenGLStateMachine::GetActiveWindow");
		return m_ActiveWindow;
	}

	void OpenGLStateMachine::SetActiveWindow(GLFWwindow *activeWindow)
	{
		AUTO_PROFILE("OpenGLStateMachine::SetActiveWindow");
		m_ActiveWindow = activeWindow;
	}
	void OpenGLStateMachine::BeginDraw() const
	{

		AUTO_PROFILE("OpenGLStateMachine::BeginDraw");
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
		
	void OpenGLStateMachine::BeginDraw(float r, float g, float b) const
	{
		
		AUTO_PROFILE("OpenGLStateMachine::BeginDraw");
		
		glClearColor(r, g, b, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	void OpenGLStateMachine::EndDraw() const
	{
		AUTO_PROFILE("OpenGLStateMachine::EndDraw");
		glfwSwapBuffers(m_ActiveWindow);
	}

	void OpenGLStateMachine::SetWindowPosition(uint32_t x, uint32_t y) const
	{
		AUTO_PROFILE("OpenGLStateMachine::SetWindowPosition");
		glfwSetWindowPos(m_ActiveWindow, x, y);
	}
	void OpenGLStateMachine::PushModelView()
	{
		AUTO_PROFILE("OpenGLStateMachine::PushModelView");
		m_CurrentTransform.m_ModelViewMatrix.push(m_CurrentTransform.m_ModelViewMatrix.top());
	
	}
	void OpenGLStateMachine::PopModelView()
	{
		AUTO_PROFILE("OpenGLStateMachine::PopModelView");
		m_CurrentTransform.m_ModelViewMatrix.pop();
		updateMatrixState();
	}

	void OpenGLStateMachine::ModelViewLoadIdentity()
	{
		AUTO_PROFILE("OpenGLStateMachine::ModelViewLoadIdentity");
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::mat4();
		updateMatrixState();
	}
	void OpenGLStateMachine::Transform(const glm::mat4& matrix)
	{
		AUTO_PROFILE("OpenGLStateMachine::Transform");
		m_CurrentTransform.m_ModelViewMatrix.top() = m_CurrentTransform.m_ModelViewMatrix.top() * matrix;
		updateMatrixState();
	}
	void OpenGLStateMachine::Transform(const GLfloat* matrix)
	{
		AUTO_PROFILE("OpenGLStateMachine::Transform");
		//glm::mat4 m = glm::mat4(matrix);
	}
	void OpenGLStateMachine::Translate(const glm::vec3& translate)
	{
		AUTO_PROFILE("OpenGLStateMachine::Translate");
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::translate(m_CurrentTransform.m_ModelViewMatrix.top(),translate);
		updateMatrixState();
	}
	void OpenGLStateMachine::Translate(const glm::vec2& translate)
	{
		AUTO_PROFILE("OpenGLStateMachine::Translate");
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::translate(m_CurrentTransform.m_ModelViewMatrix.top(), glm::vec3(translate, 0.0));
		updateMatrixState();
	}

	void OpenGLStateMachine::Scale(const glm::vec3& scale)
	{
		AUTO_PROFILE("OpenGLStateMachine::Scale");
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::scale(m_CurrentTransform.m_ModelViewMatrix.top(), scale);
		updateMatrixState();
	}
	void OpenGLStateMachine::Scale(const glm::vec2& scale)
	{
		AUTO_PROFILE("OpenGLStateMachine::Scale");
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::scale(m_CurrentTransform.m_ModelViewMatrix.top(), glm::vec3(scale,1.0));
		updateMatrixState();
	}
	void OpenGLStateMachine::Rotate(float radians, const glm::vec3& normalVector)
	{
		AUTO_PROFILE("OpenGLStateMachine::Rotate");
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::rotate(m_CurrentTransform.m_ModelViewMatrix.top(), radians, normalVector);
		updateMatrixState();
	}

	void OpenGLStateMachine::Rotate(float radians)
	{
		AUTO_PROFILE("OpenGLStateMachine::Rotate");
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::rotate(m_CurrentTransform.m_ModelViewMatrix.top(), radians, glm::vec3(0,0,1.0));
		updateMatrixState();
	}
	void OpenGLStateMachine::LookAt(const glm::vec3& point, const glm::vec3& viewer, const glm::vec3& up)
	{
		AUTO_PROFILE("OpenGLStateMachine::LookAt");
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::lookAt(viewer, point, up);
		updateMatrixState();
	}

	void OpenGLStateMachine::PushProjection()
	{
		AUTO_PROFILE("OpenGLStateMachine::PushProjection");
		m_CurrentTransform.m_ProjectionMatrix.push(m_CurrentTransform.m_ProjectionMatrix.top());
	}
	void OpenGLStateMachine::PopProjection()
	{
		AUTO_PROFILE("OpenGLStateMachine::PopProjection");
		m_CurrentTransform.m_ProjectionMatrix.pop();
		updateMatrixState();
	}
	void OpenGLStateMachine::Ortho2D(float left, float right, float bottom, float top, float znear, float zfar)
	{
		AUTO_PROFILE("OpenGLStateMachine::Ortho2D");
		m_CurrentTransform.m_ProjectionMatrix.top() = glm::ortho(left, right, bottom, top, znear, zfar);
		updateMatrixState();
	}
	void OpenGLStateMachine::Perspective(float fovy, float aspect, float znear, float zfar)
	{
		AUTO_PROFILE("OpenGLStateMachine::Perspective");
		m_CurrentTransform.m_ProjectionMatrix.top() = glm::perspective(fovy, aspect, znear, zfar);
		updateMatrixState();
	}
	uint32_t OpenGLStateMachine::GetFrameTriangleCount() const
	{
		AUTO_PROFILE("OpenGLStateMachine::GetFrameTriangleCount");
		return m_FrameTriangleCount;
	}
	void OpenGLStateMachine::AddTrianglesToFrameCount(uint32_t tris)
	{
		AUTO_PROFILE("OpenGLStateMachine::AddTrianglesToFrameCount");
		m_FrameTriangleCount += tris;
	}

	void OpenGLStateMachine::ClearFrameTriangleCount()
	{
		AUTO_PROFILE("OpenGLStateMachine::ClearFrameTriangleCount");
		m_FrameTriangleCount = 0;
	}

	void OpenGLStateMachine::updateMatrixState()
	{
		AUTO_PROFILE("OpenGLStateMachine::updateMatrixState");
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(m_CurrentTransform.m_ProjectionMatrix.top()));
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(m_CurrentTransform.m_ModelViewMatrix.top()));
	}
}