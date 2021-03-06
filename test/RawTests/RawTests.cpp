#include <iostream>

#include "emannlib-graphics/OpenGLWindow.hpp"
#include "emannlib-graphics/Shader.hpp"

//#include "emannlib-graphics\GLDraw.hpp"

#include "emannlib-common/Singleton.hpp"
#include "emannlib-common/Time.hpp"
#include "emannlib-math/Math.hpp"
#include "emannlib-math/Vector.hpp"

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
	GLFWwindow* activeWindow;
	if (glfwInit() == GL_TRUE)
	{

		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);


		glfwSwapInterval(1);
		activeWindow = glfwCreateWindow(640, 480, "TargetDummy", NULL, NULL);

		if (!activeWindow) /* rgba, depth, stencil */
		{
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(activeWindow);

		//glfwSetInputMode(m_ActiveWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/

		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			glfwTerminate();
			return -1 ;
		}

		if (!GLEW_VERSION_3_2)
		{
			glfwTerminate();
			return -1;
		}
	}
	else
	{
		return -1;
	}
	
	//glViewport(0, 0, 640, 480);


	std::shared_ptr<emannlib::Shader> vs = std::make_shared<emannlib::Shader>(GL_VERTEX_SHADER);

	vs->AppendSource("#version 330");
	vs->AppendSource("in vec3 VertexPosition;");
	vs->AppendSource("in vec4 VertexColor;");
	vs->AppendSource("out vec4 FragmentColor;");
	vs->AppendSource("void main()");
	vs->AppendSource("{");
	vs->AppendSource("	FragmentColor = VertexColor;");
	vs->AppendSource("	gl_Position = vec4(VertexPosition, 1.0);");
	vs->AppendSource("}");

	if (!(vs->Compile()))
	{
		std::cerr << "Failed to compile vertex shader\n";
		return -1;
	}

	std::shared_ptr<emannlib::Shader> fs = std::make_shared<emannlib::Shader>(GL_FRAGMENT_SHADER);

	fs->AppendSource("#version 330");
	
	fs->AppendSource("in vec4 FragmentColor;");
	fs->AppendSource("out vec4 ScreenColor;");
	fs->AppendSource("void main()");
	fs->AppendSource("{");
	fs->AppendSource("	ScreenColor = FragmentColor;");
	fs->AppendSource("}");


	if (!(fs->Compile()))
	{
		std::cerr << "Failed to compile fragment shader\n";
		return -1;
	}

	std::vector<std::shared_ptr<emannlib::Shader> > shaders;
	shaders.push_back(vs);
	shaders.push_back(fs);

	std::shared_ptr<emannlib::Program> p = std::make_shared<emannlib::Program>(shaders);

	auto vertAttribposition = p->Attribute("VertexPosition");
	auto vertAttribColor = p->Attribute("VertexColor");

	
	while (!glfwWindowShouldClose(activeWindow))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		p->Use();

		GLuint vao;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLuint vbo_VertexPositions;

		glGenBuffers(1, &vbo_VertexPositions);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_VertexPositions);

		GLfloat vertexData [] = {
			//  X     Y     Z
			0.0f, 0.8f, 0.0f,
			-0.8f, -0.8f, 0.0f,
			0.8f, -0.8f, 0.0f,
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glVertexAttribPointer(vertAttribposition, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vertAttribposition);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint vbo_VertexColors;

		glGenBuffers(1, &vbo_VertexColors);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_VertexColors);

		GLfloat vertColors [] = {
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertColors), vertColors, GL_STATIC_DRAW);

		glVertexAttribPointer(vertAttribColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vertAttribColor);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		
		glDeleteBuffers(1, &vbo_VertexPositions);
		glDeleteBuffers(1, &vbo_VertexColors);
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vao);
		
		
		p->StopUsing();
		
		glfwSwapBuffers(activeWindow);
		glfwPollEvents();
	}


	glfwTerminate();

	std::vector<Particle *> pList;
	pList.reserve(1000);

	std::cout<<emannlib::AutoProfile::Report(80)<<std::endl;
	return 0;
}