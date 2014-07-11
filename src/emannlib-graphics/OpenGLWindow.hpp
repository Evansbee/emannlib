#ifndef __OPEN_GL_WINDOW_HPP__
#define __OPEN_GL_WINDOW_HPP__

#include "../emannlib-common/Singleton.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Area.hpp"

#include "../emannlib-math/Vector.hpp"

#include <stack>
#include <memory>
#include <string>
#include <inttypes.h>

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
	class OpenGLWindow : public Singleton < OpenGLWindow >
	{
	public:
		OpenGLWindow(int newWidth, float newHeight, const std::string& name);

		//window Management
	public:
		void SetWindowSize(int newWidth, int newHeight);
		void SetWindowName(const std::string& newName);
		void SetViewportSize(int newWidth, int newHeight);
		void SetWindowPosition(float x, float y);
		void SetFullscreen(bool fullScreen = true);

		int GetWindowWidth() const;
		int GetWindowHeight() const;

		std::string GetWindowName() const;

		int GetViewportWidth() const;
		int GetViewportHeight() const;

		float GetWindowXPosition() const;
		float GetWindowYPosition() const;

		bool GetFullscreen() const;

		//window status
	public:
		bool GetWindowCloseClicked() const;


		void MessagePump() const;



	private:
	
		int m_ViewportWidth;
		int m_ViewportHeight;
		int m_WindowWidth;
		int m_WindowHeight;
		float m_ViewableWidth;
		float m_ViewableHeight;
		Vec2f m_CenterPoint;
		bool m_FullScreen;
		std::string m_WindowName;

		bool m_DebugCallbackActive;
		

		GLFWwindow *m_ActiveWindow;


		//static callbacks
	public:
		static void FrameBufferSizeCallback(GLFWwindow *activeWindow, int newWidth, int newHeight);
		static void WindowSizeCallback(GLFWwindow *activeWindow, int newWidth, int newHeight);
	};
}

#endif