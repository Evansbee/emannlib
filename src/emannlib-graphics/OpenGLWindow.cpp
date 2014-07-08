#include "OpenGLWindow.hpp"

#include <iostream>

#include "../emannlib-common/AutoProfile.hpp"

namespace emannlib
{
	
	void APIENTRY OpenGLErrorCallback(GLenum _source,
							 GLenum _type, GLuint _id, GLenum _severity,
							 GLsizei _length, const char* _message,
							 void* _userParam);

	

	OpenGLWindow::OpenGLWindow(int newWidth, float newHeight, const std::string& name) :
		m_ViewportWidth(newWidth),
		m_ViewportHeight(newHeight),
		m_WindowHeight(newHeight),
		m_WindowWidth(newWidth),
		m_ViewableHeight((float) newHeight),
		m_ViewableWidth((float) newWidth),
		m_CenterPoint(Vec2f(0.0f, 0.0f)),
		m_DebugCallbackActive(false)
	{
		m_CurrentTransform.m_ModelViewMatrix.push(glm::mat4());
		m_CurrentTransform.m_ProjectionMatrix.push(glm::mat4());

		if (glfwInit() == GL_TRUE)
		{
		
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            
			
			//glfwSwapInterval(1);
			m_ActiveWindow = glfwCreateWindow(newWidth, newHeight, name.c_str(), NULL, NULL);

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

			SetViewportSize(newWidth, newHeight);
			Ortho2D(-newWidth / 2., newWidth / 2., -newHeight / 2., newHeight / 2., 1.f, -1.f);

			glfwSetWindowSizeCallback(m_ActiveWindow, WindowSizeCallback);
			glfwSetFramebufferSizeCallback(m_ActiveWindow, FrameBufferSizeCallback);

		}
		//need to check if hardware supports this
		
		if (GLEW_ARB_debug_output)
		{
			glDebugMessageCallbackARB(OpenGLErrorCallback, NULL);
			glEnable(GL_DEBUG_OUTPUT);
			m_DebugCallbackActive = true;
		}

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	//window Management

	void OpenGLWindow::SetWindowSize(int newWidth, int newHeight)
	{
		glfwSetWindowSize(m_ActiveWindow, newWidth, newHeight);
		SetViewportSize(newWidth, newHeight);
	}

	void OpenGLWindow::SetWindowName(const std::string& newName){}
	void OpenGLWindow::SetViewportSize(int newWidth, int newHeight)
	{
		glViewport(0, 0, newWidth, newHeight);
	}
	void OpenGLWindow::SetWindowPosition(float x, float y){}
	void OpenGLWindow::SetFullscreen(bool fullScreen){}

	int OpenGLWindow::GetWindowWidth() const{ return m_WindowWidth; }
	int OpenGLWindow::GetWindowHeight() const{ return m_WindowHeight; }

	std::string OpenGLWindow::GetWindowName() const
	{
		return "hello";
	}

	int OpenGLWindow::GetViewportWidth() const{ return m_ViewportWidth; }
	int OpenGLWindow::GetViewportHeight() const{ return m_ViewportHeight; }

	float OpenGLWindow::GetWindowXPosition() const{ return 0; }
	float OpenGLWindow::GetWindowYPosition() const{ return 0; }

	bool OpenGLWindow::GetFullscreen() const{ return false; }

	//window status

	bool OpenGLWindow::GetWindowCloseClicked() const
	{
		return glfwWindowShouldClose(m_ActiveWindow);
	}


	void OpenGLWindow::BeginDraw(float r, float g, float b, float a) const
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLWindow::EndDraw()
	{
		if (!m_DebugCallbackActive)
		{
			GLenum err;

			static char* errorMsg [] = {
				"GL_INVALID_ENUM",
				"GL_INVALID_VALUE",
				"GL_INVALID_OPERATION",
				"GL_INVALID_FRAMEBUFFER_OPERATION",
				"GL_OUT_OF_MEMORY",
				"GL_STACK_UNDERFLOW",
				"GL_STACK_OVERFLOW"

			};
			while ((err = glGetError()) != GL_NO_ERROR) {
				auto idx = err - GL_INVALID_ENUM;
				std::cerr << "OpenGL error: " << errorMsg[idx] << std::endl;
			}

		}
		glfwSwapBuffers(m_ActiveWindow);
		glfwPollEvents();
		
	}

	//OGL Control

	void OpenGLWindow::PushModelView(){ m_CurrentTransform.m_ModelViewMatrix.push(m_CurrentTransform.m_ModelViewMatrix.top()); }
	void OpenGLWindow::PopModelView(){
		m_CurrentTransform.m_ModelViewMatrix.pop();
		updateMatrixState();
	}
	void OpenGLWindow::ModelViewLoadIdentity(){
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::mat4();
		updateMatrixState();
	}
	void OpenGLWindow::Transform(const glm::mat4& matrix){
		m_CurrentTransform.m_ModelViewMatrix.top() = m_CurrentTransform.m_ModelViewMatrix.top() * matrix;
		updateMatrixState();
	}
	void OpenGLWindow::Transform(const GLfloat* matrix){}

	void OpenGLWindow::Translate(const glm::vec3& translate){
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::translate(m_CurrentTransform.m_ModelViewMatrix.top(), translate);
		updateMatrixState();
	}
	void OpenGLWindow::Translate(const glm::vec2& translate){
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::translate(m_CurrentTransform.m_ModelViewMatrix.top(), glm::vec3(translate, 0.0));
		updateMatrixState();
	}

	void OpenGLWindow::Scale(const glm::vec3& scale){
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::scale(m_CurrentTransform.m_ModelViewMatrix.top(), scale);
		updateMatrixState();
	}
	void OpenGLWindow::Scale(const glm::vec2& scale){
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::scale(m_CurrentTransform.m_ModelViewMatrix.top(), glm::vec3(scale, 1.0));
		updateMatrixState();
	}

	void OpenGLWindow::Rotate(float radians, const glm::vec3& normalVector)
	{
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::rotate(m_CurrentTransform.m_ModelViewMatrix.top(), radians, normalVector);
		updateMatrixState();
	}
	void OpenGLWindow::Rotate(float radians)
	{
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::rotate(m_CurrentTransform.m_ModelViewMatrix.top(), radians, glm::vec3(0, 0, 1.0));
		updateMatrixState();
	}

	void OpenGLWindow::LookAt(const glm::vec3& point, const glm::vec3& viewer, const glm::vec3& up)
	{
		m_CurrentTransform.m_ModelViewMatrix.top() = glm::lookAt(viewer, point, up);
		updateMatrixState();
	}

	void OpenGLWindow::PushProjection()
	{ 
		m_CurrentTransform.m_ProjectionMatrix.push(m_CurrentTransform.m_ProjectionMatrix.top()); 
	}
	void OpenGLWindow::PopProjection()
	{
		m_CurrentTransform.m_ProjectionMatrix.pop();
		updateMatrixState();
	}
	void OpenGLWindow::Ortho2D(float left, float right, float bottom, float top, float znear , float zfar)
	{
		m_CurrentTransform.m_ProjectionMatrix.top() = glm::ortho(left, right, bottom, top, znear, zfar);
		updateMatrixState();
	}
	void OpenGLWindow::Ortho2DFromCenterAndExtents(const Vec2f& center, float newWidth, float newHeight)
	{
		float left = center.x - newWidth / 2.f;
		float right = center.x + newWidth / 2.f;
		float top = center.y + newHeight / 2.f;
		float bottom = center.y - newHeight / 2.f;
		Ortho2D(left, right, bottom, top);

	}
	void OpenGLWindow::Perspective(float fovy, float aspect, float znear, float zfar)
	{
		m_CurrentTransform.m_ProjectionMatrix.top() = glm::perspective(fovy, aspect, znear, zfar);
		updateMatrixState();
	}

	void OpenGLWindow::MessagePump() const{ glfwPollEvents(); }


	void OpenGLWindow::updateMatrixState(){
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(m_CurrentTransform.m_ProjectionMatrix.top()));
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(m_CurrentTransform.m_ModelViewMatrix.top()));
	}




	//drawing

	void OpenGLWindow::Draw(std::shared_ptr<Texture> texture, Area area)
	{
	
	}
	void OpenGLWindow::DrawLine(const Vec2f& start, const Vec2f& stop, float strokeWidth)
	{

		Vec2f spanVector = stop - start;

		float bodyLength = spanVector.Length();

		float radians = (spanVector.x > 0.0f) ? Math<float>::ATan(spanVector.y / spanVector.x) : (Math<float>::ATan(spanVector.y / spanVector.x) + Math<float>::PI);

		float verts[12];

		verts[0 * 2] = 0.0f;				verts[0 * 2 + 1] = strokeWidth / 2.0f;
		verts[1 * 2] = 0.0f;				verts[1 * 2 + 1] = -strokeWidth / 2.0f;
		verts[2 * 2] = bodyLength;	        verts[2 * 2 + 1] = strokeWidth / 2.0f;

		verts[3 * 2] = bodyLength;			verts[3 * 2 + 1] = strokeWidth / 2.0f;
		verts[4 * 2] = 0.0f;				verts[4 * 2 + 1] = -strokeWidth / 2.0f;
		verts[5 * 2] = bodyLength;			verts[5 * 2 + 1] = -strokeWidth / 2.0f;

		PushModelView();
			Rotate(radians);
			Translate(glm::vec2(start.x, start.y));

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, verts);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glDisableClientState(GL_VERTEX_ARRAY);
		
		PopModelView();
	}
	void OpenGLWindow::DrawRect(const Area& sq)
	{
		GLfloat verts[8];
		verts[0] = sq.m_LowerRight.x;	verts[1] = sq.m_UpperLeft.y;
		verts[2] = sq.m_UpperLeft.x;	verts[3] = sq.m_UpperLeft.y;
		verts[4] = sq.m_LowerRight.x;	verts[5] = sq.m_LowerRight.y;
		verts[6] = sq.m_UpperLeft.x;	verts[7] = sq.m_LowerRight.y;
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, verts);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	void OpenGLWindow::DrawRectStroke(const Area& sq, float strokeWidth)
	{
		GLfloat verts[8];
		verts[0] = sq.m_UpperLeft.x;	verts[1] = sq.m_UpperLeft.y;
		verts[2] = sq.m_LowerRight.x;	verts[3] = sq.m_UpperLeft.y;
		verts[4] = sq.m_LowerRight.x;	verts[5] = sq.m_LowerRight.y;
		verts[6] = sq.m_UpperLeft.x;	verts[7] = sq.m_LowerRight.y;
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, verts);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	void OpenGLWindow::DrawCirle(const Vec2f& center, float radius, int numSides )
	{
		// automatically determine the number of segments from the circumference
		if (numSides <= 0) {
			numSides = (int) Math<double>::Floor(radius * Math<double>::PI * 2);
		}
		if (numSides < 2) numSides = 2;

		GLfloat *verts = new float[(numSides + 2) * 2];
		verts[0] = center.x;
		verts[1] = center.y;
		for (int s = 0; s <= numSides; s++) {
			float t = s / (float) numSides * 2.0f * 3.14159f;
			verts[(s + 1) * 2 + 0] = center.x + Math<float>::Cos(t) * radius;
			verts[(s + 1) * 2 + 1] = center.y + Math<float>::Sin(t) * radius;
		}
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, verts);
		glDrawArrays(GL_TRIANGLE_FAN, 0, numSides + 2);
		glDisableClientState(GL_VERTEX_ARRAY);
		delete [] verts;
	}
	void OpenGLWindow::DrawCirleStroke(const Vec2f& center, float radius, float strokeWidth , int numSides)
	{
		// automatically determine the number of segments from the circumference
		if (numSides <= 0) {
			numSides = (int) Math<double>::Floor(radius * Math<double>::PI * 2);
		}
		if (numSides < 2) numSides = 2;

		GLfloat *verts = new float[numSides * 2];
		for (int s = 0; s < numSides; s++) {
			float t = s / (float) numSides * 2.0f * Math<float>::PI;
			verts[s * 2 + 0] = center.x + Math<float>::Cos(t) * radius;
			verts[s * 2 + 1] = center.y + Math<float>::Sin(t) * radius;
		}
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, verts);
		glDrawArrays(GL_LINE_LOOP, 0, numSides);
		glDisableClientState(GL_VERTEX_ARRAY);
		delete [] verts;
	}
	void OpenGLWindow::DrawCoordinateFrame(const Vec2f& center, float axisLength, float headLength, float headWidth)
	{
	
	}
	void OpenGLWindow::DrawVector(const Vec2f& start, const Vec2f& target, float vectorLength, float vectorWidth, float headLength, float headWidth)
	{
		float bodyLength = (vectorLength > headLength) ? (vectorLength - headLength) : (0.0f);

		Vec2f spanVector = target - start;

		float radians = (spanVector.x > 0.0f) ? Math<float>::ATan(spanVector.y / spanVector.x) : (Math<float>::ATan(spanVector.y / spanVector.x) + Math<float>::PI);

		float verts[18];


		verts[0 * 2] = 0.0f;				verts[0 * 2 + 1] = vectorWidth / 2.0f;
		verts[1 * 2] = 0.0f;				verts[1 * 2 + 1] = -vectorWidth / 2.0f;
		verts[2 * 2] = bodyLength;	        verts[2 * 2 + 1] = vectorWidth / 2.0f;

		verts[3 * 2] = bodyLength;			verts[3 * 2 + 1] = vectorWidth / 2.0f;
		verts[4 * 2] = 0.0f;				verts[4 * 2 + 1] = -vectorWidth / 2.0f;
		verts[5 * 2] = bodyLength;			verts[5 * 2 + 1] = -vectorWidth / 2.0f;

		verts[6 * 2] = bodyLength;			verts[6 * 2 + 1] = headWidth / 2.0f;
		verts[7 * 2] = bodyLength;			verts[7 * 2 + 1] = -headWidth / 2.0f;
		verts[8 * 2] = bodyLength + headLength; verts[8 * 2 + 1] = 0.0f;

		PushModelView();
	Rotate(radians);
		Translate(glm::vec2(start.x, start.y));

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, verts);
		glDrawArrays(GL_TRIANGLES, 0, 9);
		glDisableClientState(GL_VERTEX_ARRAY);
		
		PopModelView();
	}
	void OpenGLWindow::DrawPolyLine(const std::vector<Vec2f>& line)
	{
	
	}
	void OpenGLWindow::DrawClosedPolyLine(const std::vector<Vec2f>& line)
	{
	
	}
	void OpenGLWindow::DrawPoint(const Vec2f& location, float size )
	{
		Area sq;
		sq.m_UpperLeft.x =location.x - size / 2.0f;
		sq.m_UpperLeft.y = location.y - size / 2.0f;

		sq.m_LowerRight.x = location.x + size / 2.0f;
		sq.m_LowerRight.y = location.y - size / 2.0f;

		float verts[8];

		verts[0] = sq.m_LowerRight.x;	verts[1] = sq.m_UpperLeft.y;
		verts[2] = sq.m_UpperLeft.x;	verts[3] = sq.m_UpperLeft.y;
		verts[4] = sq.m_LowerRight.x;	verts[5] = sq.m_LowerRight.y;
		verts[6] = sq.m_UpperLeft.x;	verts[7] = sq.m_LowerRight.y;
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, verts);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	void OpenGLWindow::SetColor(float r, float g, float b, float a)
	{
		glColor4f(r, g, b, a);
	}

	//static callbacks

	void OpenGLWindow::FrameBufferSizeCallback(GLFWwindow *activeWindow, int newWidth, int newHeight)
	{


	}
	void OpenGLWindow::WindowSizeCallback(GLFWwindow *activeWindow, int newWidth, int newHeight)
	{
		OpenGLWindow::GetSingleton().SetViewportSize(newWidth, newHeight);
		OpenGLWindow::GetSingleton().Ortho2DFromCenterAndExtents(OpenGLWindow::GetSingleton().m_CenterPoint, newWidth, newHeight);
	}

	void APIENTRY OpenGLErrorCallback(GLenum _source,
							 GLenum _type, GLuint _id, GLenum _severity,
							 GLsizei _length, const char* _message,
							 void* _userParam)
	{

		const char* OGL_Severities [] = {
			"HIGH",
			"MEDIUM",
			"LOW"
		};

		_severity -= GL_DEBUG_SEVERITY_HIGH;

		const char* OGL_Sources [] = {
			"API",
			"WINDOW_SYSTEM",
			"SHADER_COMPILER",
			"THIRD_PARTY",
			"APPLICATION",
			"OTHER" };

		_source -= GL_DEBUG_SOURCE_API;


		const char* OGL_Types [] = {
			"ERROR",
			"DEPRECATED_BEHAVIOR",
			"UNDEFINED_BEHAVIOR",
			"PORTABILITY",
			"PERFORMANCE",
			"OTHER"
		};

		_type -= GL_DEBUG_TYPE_ERROR;

		std::cerr << "OpenGL Error: " << OGL_Types[_type] << " from "<<OGL_Sources[_source]<<std::endl;
		std::cerr << _message << std::endl;
	}
}