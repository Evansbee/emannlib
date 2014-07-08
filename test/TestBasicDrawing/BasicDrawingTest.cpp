#include <iostream>

#include "emannlib-graphics/OpenGLWindow.hpp"
//#include "emannlib-graphics\GLDraw.hpp"

#include "emannlib-common/Singleton.hpp"
#include "emannlib-common/Time.hpp"
#include "emannlib-math/Math.hpp"
#include "emannlib-common/Vector.hpp"

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


int main(int argc, char ** argv)
{
	std::vector<Particle *> pList;
	pList.reserve(1000);
	new emannlib::OpenGLWindow(1000,600,argv[0]);

	auto current = emannlib::Time().GetCurrentTime();
	auto last = current;

	int i = 0;
	double dt = 0;
	double frameTime = 0;
	double frameCount = 0;
	while (!emannlib::OpenGLWindow::GetSingleton().GetWindowCloseClicked())
	{
		frameCount++;
		
		if (pList.size() < 800)
		{
			pList.push_back(new Particle());
			pList.push_back(new Particle());
		}

		i++;

		current = emannlib::Time().GetCurrentTime();
		emannlib::OpenGLWindow::GetSingleton().BeginDraw(.9f, .9f, .9f);
		//emannlib::OpenGLWindow::GetSingleton().ClearFrameTriangleCount();
		for (auto p : pList)
		{
			emannlib::OpenGLWindow::GetSingleton().PushModelView();
			emannlib::OpenGLWindow::GetSingleton().Translate(glm::vec2(p->x, p->y));
			emannlib::OpenGLWindow::GetSingleton().SetColor(p->r, p->g, p->b);
			emannlib::OpenGLWindow::GetSingleton().DrawCirle(emannlib::Vec2f(0, 0), p->size);

			emannlib::OpenGLWindow::GetSingleton().SetColor(1.0 - p->r, 1.0 - p->g, 1.0 - p->b);
			emannlib::OpenGLWindow::GetSingleton().DrawVector(emannlib::Vec2f(0, 0), emannlib::Vec2f(p->vx, p->vy), 20.0, 1.0, 6.0f, 6.0f);


			emannlib::OpenGLWindow::GetSingleton().PopModelView();
		}

		dt = current - last;
		frameTime += dt;
		if (frameTime > 1.0)
		{
			std::cout << "FPS: " << frameCount << " Triangles: " <<std::endl;
			frameTime = 0.0;
			frameCount = 0;
		}

		float width = (float) emannlib::OpenGLWindow::GetSingleton().GetViewportWidth() / 1.75;
		float height = (float) emannlib::OpenGLWindow::GetSingleton().GetViewportHeight() / 1.75;
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
        GLenum err;
        
        static char* errorMsg[] = {
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
			
		emannlib::OpenGLWindow::GetSingleton().EndDraw();
	
	}

	std::cout<<emannlib::AutoProfile::Report(80)<<std::endl;
}