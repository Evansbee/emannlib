#include "Task.hpp"
#include "RunTime.hpp"
#include "AutoProfile.hpp"
#include "../emannlib-graphics/Texture.hpp"
#include "../emannlib-graphics/Bitmap.hpp"
#include "../emannlib-graphics/Font.hpp"
#include "../emannlib-graphics/OpenGLStateMachine.hpp"
#include "../emannlib-ecs/Entity.hpp"
#include "../emannlib-ecs/Event.hpp"

#include <memory>


#include <iostream>
#include <chrono>
#include <sstream>
#include <ctime>

#define GLEW_STATIC
#define GLFW_INCLUDE_GLU
#include "GL\glew.h"
#include "GLFW\glfw3.h"



namespace goldenduck
{
	WindowUpdateTask::WindowUpdateTask() :
		m_Width(640),
		m_Height(480),
		m_PosX(25),
		m_PosY(25),
		m_Title("Hello World"),
		m_CurrentFPS(0),
		Task(2)
	{
		m_Priority = 1;
	}
	WindowUpdateTask::~WindowUpdateTask(){};

	bool WindowUpdateTask::Start(){
		AUTO_PROFILE("WindowUpdateTask::Start");
		m_SampleStartTime;
		m_FrameCount = 0;
		if (glfwInit() == GL_TRUE)
		{

			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			glfwSwapInterval(1);
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
			glfwSetWindowPos(m_Window, m_PosX, m_PosY);
			if (!m_Window) /* rgba, depth, stencil */
			{
				glfwTerminate();
				return false;
			}
			glfwMakeContextCurrent(m_Window);

			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/

			GLenum err = glewInit();
			if (err != GLEW_OK)
			{
				glfwTerminate();
				return false;
			}

			if (!GLEW_VERSION_3_2)
			{
				glfwTerminate();
				return false;
			}

			m_SampleStartTime = 0.0;

			new OpenGLStateMachine(m_Window, m_Height, m_Width);

			OpenGLStateMachine::GetSingleton().ModelViewLoadIdentity();

			return true;
		}

		return false;


	};
	void WindowUpdateTask::OnSuspend(){};
	void WindowUpdateTask::Update(double deltaTime){
		AUTO_PROFILE("WindowTask::Update");
		m_SampleStartTime += deltaTime;
		if (m_SampleStartTime > 1.0)
		{
			m_CurrentFPS = m_FrameCount;
			m_FrameCount = 0;
			m_SampleStartTime = 0;
			std::cout << "FPS: " << m_CurrentFPS << std::endl;
		}

		m_FrameCount++;

		glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		auto ratio = m_Width / (float) m_Height;

		OpenGLStateMachine::GetSingleton().SetViewport(m_Width, m_Height);
		OpenGLStateMachine::GetSingleton().Ortho2D(-m_Width / 2., m_Width/2., -m_Height/2., m_Height/2., 1.f, -1.f);


		glViewport(0, 0, m_Width, m_Height);


	};
	void WindowUpdateTask::OnResume(){};
	void WindowUpdateTask::Stop(){
		glfwDestroyWindow(m_Window);
		OpenGLStateMachine::GetSingleton().SetActiveWindow(NULL);
		glfwTerminate();
	};

	InputTask::InputTask(){}

	InputTask::InputTask(std::shared_ptr<EventManager> eventMgr) :
		m_EventManager(eventMgr),
		m_StoredXPosition(-50),
		m_StoredYPosition(-50),
		Task(10)
	{

	}
	InputTask::~InputTask()
	{}

	InputTask* CurrentInputTask = NULL;


	void _InternalKeyCallBack(GLFWwindow *win, int key, int scan, int action, int mods)
	{
		if (CurrentInputTask)
		{
			CurrentInputTask->KeyCallbackFunction(win, key, scan, action, mods);
		}
	}
	void SetInputTask(InputTask *it)
	{
		CurrentInputTask = it;
		if (CurrentInputTask)
		{
			glfwSetKeyCallback(OpenGLStateMachine::GetSingleton().GetActiveWindow(), _InternalKeyCallBack);
		}
	}




	bool InputTask::Start(){
		SetInputTask(this);
		return true;
	}
	void InputTask::OnSuspend(){}
	void InputTask::Update(double deltaTime)
	{
		glfwPollEvents();

		double x, y;
		glfwGetCursorPos(OpenGLStateMachine::GetSingleton().GetActiveWindow(), &x, &y);



		x = (2 * x / OpenGLStateMachine::GetSingleton().GetViewportWidth()) - 1.0;
		y = (2 * y / OpenGLStateMachine::GetSingleton().GetViewportHeight()) - 1.0;
		y = -y;

		if (x != m_StoredXPosition || y != m_StoredYPosition)
		{
			m_EventManager->Emit<CursorPositionEvent>(x, y);
		}

		m_CanKill = (glfwWindowShouldClose(OpenGLStateMachine::GetSingleton().GetActiveWindow()) > 0);
		if (m_CanKill)
		{
			goldenduck::RunTime::GetSingleton().KillAllTasks();
		}
		m_StoredXPosition = x;
		m_StoredYPosition = y;
	}

	void InputTask::KeyCallbackFunction(GLFWwindow *win, int key, int scan, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			m_EventManager->Emit<KeyDownEvent>(key, scan);
		}
		else if (action == GLFW_RELEASE)
		{
			m_EventManager->Emit<KeyUpEvent>(key, scan);
		}

	}

	void InputTask::OnResume(){}
	void InputTask::Stop(){ SetInputTask(NULL); }

	bool InputTask::IsKeyDown(char key)
	{
		return false;
	}


	BufferSwapTask::BufferSwapTask() : Task(50000) {}
	BufferSwapTask::~BufferSwapTask(){}

	bool BufferSwapTask::Start(){ return true; }
	void BufferSwapTask::OnSuspend(){}
	void BufferSwapTask::Update(double deltaTime)
	{
		if (OpenGLStateMachine::GetSingleton().GetActiveWindow() != NULL)
		{
			glfwSwapBuffers(OpenGLStateMachine::GetSingleton().GetActiveWindow());
		}
	}
	void BufferSwapTask::OnResume(){}
	void BufferSwapTask::Stop(){}

}