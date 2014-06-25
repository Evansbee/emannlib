//
//  Task.hpp
//  goldenduckLib
//
//  Created by Evan Ackmann on 5/7/14.
//
//

#ifndef goldenduckLib_Task_hpp
#define goldenduckLib_Task_hpp

struct GLFWwindow;

#include <string>
#include <inttypes.h>

#include "goldenduck\Event.hpp"
#include "goldenduck\Entity.hpp"

namespace goldenduck
{
	class Task
	{
	public:
		Task() :
			m_Priority(5000),
			m_CanKill(false)
		{
		};

		Task(uint32_t prio) :
			m_Priority(prio),
			m_CanKill(false)
		{

		}

		virtual ~Task(){};

		virtual bool Start() = 0;
		virtual void OnSuspend(){};
		virtual void Update(double deltaTime) = 0;
		virtual void OnResume(){};
		virtual void Stop() = 0;
		virtual bool CanKill() const { return m_CanKill; };
		virtual unsigned int GetPriority() const { return m_Priority; };
		virtual void Kill() { m_CanKill = true; };

	protected:
		unsigned int m_Priority;
		bool m_CanKill;
	};

	class WindowUpdateTask : public Task
	{
	public:
		WindowUpdateTask();
		~WindowUpdateTask();

		bool Start();
		void OnSuspend();
		void Update(double deltaTime);
		void OnResume();
		void Stop();

	private:
		GLFWwindow *m_Window;
		int m_PosX;
		int m_PosY;
		int m_Height;
		int m_Width;

		double m_SampleStartTime;
		unsigned int m_FrameCount;
		unsigned int m_CurrentFPS;

		std::string m_Title;
	};

	class KeyDownEvent : public Event<KeyDownEvent>
	{
	public:
		KeyDownEvent() {}
		KeyDownEvent(int keyCode, int scan) : m_KeyCode(keyCode) , m_ScanCode(scan) {}
		int m_KeyCode;
		int m_ScanCode;
	};

	class KeyUpEvent : public Event<KeyUpEvent>
	{
	public:
		KeyUpEvent() {}
		KeyUpEvent(int keyCode, int scan) : m_KeyCode(keyCode), m_ScanCode(scan) {}
		int m_KeyCode;
		int m_ScanCode;
	};

	class CursorPositionEvent : public Event<CursorPositionEvent>
	{
	public:
		CursorPositionEvent() {}
		CursorPositionEvent(double x, double y) : m_X(x), m_Y(y) {}
		double m_X;
		double m_Y;
	};

	class InputTask : public Task
	{
	public:
		InputTask();
		InputTask(std::shared_ptr<EventManager> eventMgr);
		~InputTask();

		bool Start();
		void OnSuspend();
		void Update(double deltaTime);
		void OnResume();
		void Stop();

		void KeyCallbackFunction(GLFWwindow *win, int key, int scan, int action, int mods);
			
		bool IsKeyDown(char key);

	private:
		std::shared_ptr<EventManager> m_EventManager;

		double m_StoredXPosition;
		double m_StoredYPosition;
	};

	class BufferSwapTask : public Task
	{
	public:
		BufferSwapTask();
		~BufferSwapTask();

		bool Start();
		void OnSuspend();
		void Update(double deltaTime);
		void OnResume();
		void Stop();

	private:

	};
}

#endif
