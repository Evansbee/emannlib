#ifndef __OPEN_GL_WINDOW_HPP__
#define __OPEN_GL_WINDOW_HPP__

#include "../emannlib-common/Singleton.hpp"
#include "Texture.hpp"
#include "Area.hpp"

#include "../emannlib-common/Vector.hpp"

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

class emannlib
{
	class Transform
	{
	public:
		std::stack<glm::mat4> m_ModelViewMatrix;
		std::stack<glm::mat4> m_ProjectionMatrix;
	};


	class OpenGLWindow : public Singleton < OpenGLWindow >
	{
	public:
		OpenGLWindow(float width, float height, std::string& name);

		//window Management
	public:
		void SetWindowSize(float width, float height);
		void SetWindowName(const std::string& name);
		void SetViewportSize(float width, float height);
		void SetWindowPosition(float x, float y);
		void SetFullscreen(bool fullScreen = true);

		float GetWindowWidth() const;
		float GetWindowHeight() const;

		std::string GetWindowName() const;

		float GetViewportWidth() const;
		float GetViewportHeight() const;

		float GetWindowXPosition() const;
		float GetWindowYPosition() const;

		bool GetFullscreen() const;

		//window status
	public:
		bool GetWindowCloseClicked() const;

	public:
		void BeginDraw(float r=0.0f, float g=0.0f, float b=0.0f, float a=1.0f) const;
		void EndDraw();

		//OGL Control
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

		void MessagePump() const;

	private:
		void updateMatrixState();

	private:
		emannlib::Transform m_CurrentTransform;
		float m_ViewportWidth;
		float m_ViewPortHeight;
		float m_WindowWidth;
		float m_WindowHeight;
		bool m_FullScreen;

		GLFWwindow *m_ActiveWindow;


		//drawing
	public:
		void Draw(std::shared_ptr<Texture> texture, Area area);
		void DrawLine(const Vec2f& start, const Vec2f& stop, float strokeWidth = 1.0);
		void DrawRect(const Area& sq);
		void DrawRectStroke(const Area& sq, float strokeWidth = 1.0);
		void DrawCirle(const Vec2f& center, float radius, int numSides = 360);
		void DrawCirleStroke(const Vec2f& center, float radius, float strokeWidth = 1.0f, int numSides = 360);
		void DrawCoordinateFrame(const Vec2f& center, float axisLength, float headLength, float headWidth);
		void DrawVector(const Vec2f& start, const Vec2f& target, float vectorLength, float vectorWidth, float headLength, float headWidth);
		void DrawPolyLine(const std::vector<Vec2f>& line);
		void DrawClosedPolyLine(const std::vector<Vec2f>& line);
		void DrawPoint(const Vec2f& location, float size=1.0);
		void Color(float r, float g, float b, float a = 1.0);


	public:

	}
}

#endif