#include <iostream>

#include "emannlib-graphics\OpenGLStateMachine.hpp"
#include "emannlib-graphics\GLDraw.hpp"

#include "emannlib-common/Singleton.hpp"
#include "emannlib-common\Time.hpp"
#include "emannlib-math\Math.hpp"
#include "emannlib-common\Vector.hpp"

class Particle
{
public:
	Particle()
	{
		x = float(rand() % 100) - 25.0f;
		y = float(rand() % 100) - 25.0f;
		vx = float(rand() % 250) - 125.0f;
		vy = float(rand() % 250) - 125.0f;
		r = float(rand()) / float(RAND_MAX);
		g = float(rand()) / float(RAND_MAX);
		b = float(rand()) / float(RAND_MAX);

		size = float(rand() % 15);

		ttl = 250;
	}
	Particle(float nx, float ny)
	{
		x = nx;
		y = ny;
		vx = float(rand() % 150) - 75.0f;
		vy = float(rand() % 150) - 75.0f;
		ttl = float(rand() % 50);
		size = float(rand() % 50);

		r = float(rand()) / float(RAND_MAX);
		g = float(rand()) / float(RAND_MAX);
		b = float(rand()) / float(RAND_MAX);
	}

	void Update(double dt)
	{
		x += vx * (float) dt;
		y += vy * (float) dt;
		ttl -= (float) dt;

		vy -= .5;
	}


	float x, y;
	float vx, vy;
	float ttl;

	float r, g, b;

	float size;

};


int main()
{
	std::vector<Particle *> pList;
	pList.reserve(1000);
	new emannlib::OpenGLStateMachine(1000,600);

	auto start = emannlib::Time().GetCurrentTime();
	auto current = emannlib::Time().GetCurrentTime();
	auto last = current;

	int i = 0;
	double dt = 0;
	double frameTime = 0;
	double frameCount = 0;
	while (!emannlib::OpenGLStateMachine::GetSingleton().WindowShouldClose())
	{
		frameCount++;
		
		if (pList.size() < 800)
		{
			pList.push_back(new  Particle());
			pList.push_back(new  Particle());
		}

		i++;

		current = emannlib::Time().GetCurrentTime();
		emannlib::OpenGLStateMachine::GetSingleton().BeginDraw(.9f,.9f,.9f);
		emannlib::OpenGLStateMachine::GetSingleton().ClearFrameTriangleCount();
		for (auto p : pList)
		{
			emannlib::OpenGLStateMachine::GetSingleton().PushModelView();
			emannlib::OpenGLStateMachine::GetSingleton().Translate(glm::vec2(p->x, p->y));
			emannlib::gl::Color(p->r, p->g, p->b);
			emannlib::gl::DrawCirle(emannlib::Vec2f(0, 0), p->size);

			emannlib::gl::Color(1.0-p->r,1.0- p->g, 1.0-p->b);
			emannlib::gl::DrawVector(emannlib::Vec2f(0, 0), emannlib::Vec2f(p->vx, p->vy),20.0, 1.0, 6.0f, 6.0f);


			emannlib::OpenGLStateMachine::GetSingleton().PopModelView();
		}

		dt = current - last;
		frameTime += dt;
		if (frameTime > 1.0)
		{
			std::cout << "FPS: " << frameCount << " Triangles: " << emannlib::OpenGLStateMachine::GetSingleton().GetFrameTriangleCount() << std::endl;
			frameTime = 0.0;
			frameCount = 0;
		}

		float width = (float)emannlib::OpenGLStateMachine::GetSingleton().GetViewportWidth() / 1.75;
		float height = (float)emannlib::OpenGLStateMachine::GetSingleton().GetViewportHeight() / 1.75;
		for (auto p = pList.begin(); p != pList.end();)
		{
			(*p)->Update(dt);

			if (	(*p)->x > width  ||
					(*p)->x < -width ||
					(*p)->y > height ||
					(*p)->y < -height
				)
			{
				(*p)->ttl = -1.0f;
			}

			if ((*p)->ttl < 0.0)
			{
				delete * p;
				p = pList.erase(p);
			}
			else {
				++p;
			}
		}

		last = current;
			
		emannlib::OpenGLStateMachine::GetSingleton().EndDraw();
		emannlib::OpenGLStateMachine::GetSingleton().MessagePump();
	}

	std::cout<<emannlib::AutoProfile::Report(80)<<std::endl;
}