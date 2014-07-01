#include <iostream>

#include "emannlib-graphics\OpenGLStateMachine.hpp"
#include "emannlib-graphics\GLDraw.hpp"

#include "emannlib-common/Singleton.hpp"
#include "emannlib-common\Time.hpp"
#include "emannlib-math\Math.hpp"

class Particle
{
public:
	Particle()
	{
		x = float(rand() % 100) - 25.0f;
		y = float(rand() % 100) - 25.0f;
		vx = float(rand() % 150) - 75.0f;
		vy = float(rand() % 150) - 75.0f;
		r = float(rand()) / float(RAND_MAX);
		g = float(rand()) / float(RAND_MAX);
		b = float(rand()) / float(RAND_MAX);

		size = float(rand() % 15);

		ttl = float(rand() % 50);
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

	new emannlib::OpenGLStateMachine(640, 480);

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
		pList.push_back(new  Particle());

		i++;

		current = emannlib::Time().GetCurrentTime();
		emannlib::OpenGLStateMachine::GetSingleton().BeginDraw();
		for (auto p : pList)
		{
			emannlib::OpenGLStateMachine::GetSingleton().PushModelView();
			emannlib::OpenGLStateMachine::GetSingleton().Translate(glm::vec2(p->x, p->y));
			emannlib::gl::Color(p->r, p->g, p->b);
			emannlib::gl::DrawCirle(glm::vec2(0, 0), p->size, 50);
			emannlib::OpenGLStateMachine::GetSingleton().PopModelView();
		}

		dt = current - last;
		frameTime += dt;
		if (frameTime > 1.0)
		{
			std::cout << "FPS: " << frameCount << " Elements: "<< pList.size() <<std::endl;
			frameTime = 0.0;
			frameCount = 0;
		}
		for (auto p = pList.begin(); p != pList.end();)
		{
			(*p)->Update(dt);
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
}