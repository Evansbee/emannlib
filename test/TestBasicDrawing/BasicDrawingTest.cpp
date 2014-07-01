#include <iostream>

#include "emannlib-graphics\OpenGLStateMachine.hpp"
#include "emannlib-graphics\GLDraw.hpp"

#include "emannlib-common/Singleton.hpp"
#include "emannlib-common\Time.hpp"
#include "emannlib-math\Math.hpp"

class Test : public emannlib::Singleton < Test >
{

};

int main()
{
	new Test;
	new emannlib::OpenGLStateMachine(640,480);

	auto start = emannlib::Time().GetCurrentTime();

	float lineWidth = 0.0;
	int sides = 0;
	while (!emannlib::OpenGLStateMachine::GetSingleton().WindowShouldClose())
	{
		lineWidth += 0.05;
		lineWidth = emannlib::Math<float>::FMod(lineWidth, 10.0);
		auto current = emannlib::Time().GetCurrentTime();
		emannlib::OpenGLStateMachine::GetSingleton().BeginDraw();
		
		
		emannlib::OpenGLStateMachine::GetSingleton().PushModelView();
		emannlib::OpenGLStateMachine::GetSingleton().Translate(glm::vec2(200.0 * (emannlib::Math<float>::Sin(current - start)), 0));
		
		emannlib::gl::Color(1.0, 0.2, 0.9);
		emannlib::gl::DrawCirle(glm::vec2(0, 0), 50.0f);
		
		emannlib::gl::Color(1.0, 1.0, 1.0);
		emannlib::gl::SetLineWidth(lineWidth);
		emannlib::gl::DrawCirleStroke(glm::vec2(0, 0), 50.0f, 8);
		
		emannlib::OpenGLStateMachine::GetSingleton().PopModelView();


		emannlib::OpenGLStateMachine::GetSingleton().PushModelView();
		emannlib::OpenGLStateMachine::GetSingleton().Translate(glm::vec2(0, 150.0 * (emannlib::Math<float>::Cos(current - start))));
		
		emannlib::Area a;
		a.m_UpperLeft = glm::vec2(-20, 20);
		a.m_LowerRight = glm::vec2(20, -20);
		emannlib::gl::Color(0, 0.2, 0.9);
		emannlib::gl::DrawRect(a);
		emannlib::OpenGLStateMachine::GetSingleton().PopModelView();

		emannlib::OpenGLStateMachine::GetSingleton().EndDraw();
		emannlib::OpenGLStateMachine::GetSingleton().MessagePump();
	}
}