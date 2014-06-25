#include "System.hpp"
#include "Entity.hpp"
#include "Event.hpp"
#include "../emannlib-utility/RunTime.hpp"
#include "../emannlib-utility/Task.hpp"
#include "Components.hpp"
#include "OpenGLStateMachine.hpp"
#include "../emannlib-utility/AutoProfile.hpp"



#define GLEW_STATIC
#define GLFW_INCLUDE_GLU
#include "GL\glew.h"
#include "GLFW\glfw3.h"

namespace goldenduck
{

	System::System(std::shared_ptr<EntityManager> entityMgr, std::shared_ptr<EventManager> eventMgr) :
		m_EntityManager(entityMgr),
		m_EventManager(eventMgr),
		Task(100)
	{

	}



	bool System::Start(){ return true; }
	void System::OnSuspend(){}
	void System::Update(double deltaTime){}
	void System::OnResume(){}
	void System::Stop(){}




	MovementSystem::MovementSystem(std::shared_ptr<EntityManager> entityMgr, std::shared_ptr<EventManager> eventMgr) :
		System(entityMgr, eventMgr)
	{

	}
	bool MovementSystem::Start(){ return true; }
	void MovementSystem::OnSuspend(){}
	void MovementSystem::Update(double deltaTime)
	{
		AUTO_PROFILE("MovementSystem::Update");
		for (Entity e : m_EntityManager->GetEntitiesWithComponents<Position2DComponent, Motion2DComponent>())
		{
			std::shared_ptr<Position2DComponent> p;
			std::shared_ptr<Motion2DComponent> m;
			e.GetComponents(p, m);

			p->m_Position += (m->m_Velocity * (float) deltaTime);
			p->m_Rotation += (m->m_RotationalVelocity * (float) deltaTime);

			m->m_Velocity += (m->m_Acceleration * (float) deltaTime);
			m->m_RotationalVelocity += (m->m_RotationalAcceleration * (float) deltaTime);
		}
	}
	void MovementSystem::OnResume(){};
	void MovementSystem::Stop(){};


	RenderSystem::RenderSystem(std::shared_ptr<EntityManager> entityMgr, std::shared_ptr<EventManager> eventMgr) :
		System(entityMgr, eventMgr)
	{

	}
	bool RenderSystem::Start(){
		return true;
	};
	void RenderSystem::OnSuspend(){};
	void RenderSystem::Update(double deltaTime)
	{
		AUTO_PROFILE("RenderSystem::Update");
		OpenGLStateMachine::GetSingleton().ClearBuffers();


		for (Entity e : m_EntityManager->GetEntitiesWithComponents<Position2DComponent, TextureComponent, Geometry2DComponent>())
		{
			std::shared_ptr<Position2DComponent> p;
			std::shared_ptr<TextureComponent> t;
			std::shared_ptr<Geometry2DComponent> g;
			e.GetComponents(p, t, g);

			if (t->m_NumTextures > 0 && g->m_NumGeometries > 0 &&
				t->m_CurrentTexture < t->m_NumTextures && g->m_CurrentGeometry < g->m_NumGeometries)
			{
				//good to go
				OpenGLStateMachine::GetSingleton().PushModelView();

				std::shared_ptr<Parent2DComponent> parent = e.GetComponent<Parent2DComponent>();

				while (parent != nullptr)
				{
					std::shared_ptr<Position2DComponent> parentXform;
					parent->m_ParentEntity.GetComponents(parentXform);
								
					OpenGLStateMachine::GetSingleton().Translate(parentXform->m_Position);
					OpenGLStateMachine::GetSingleton().Rotate(parentXform->m_Rotation);
					
					parent = parent->m_ParentEntity.GetComponent<Parent2DComponent>();
				}


				OpenGLStateMachine::GetSingleton().Translate(p->m_PositionOffset);
				OpenGLStateMachine::GetSingleton().Rotate(p->m_RotationOffset);


				OpenGLStateMachine::GetSingleton().Translate(p->m_Position);
				OpenGLStateMachine::GetSingleton().Rotate(p->m_Rotation);


				glBindTexture(GL_TEXTURE_2D, t->m_Textures[t->m_CurrentTexture]->GetTextureID());
				
				glBegin(GL_TRIANGLES);
				for (int ind : g->m_Indices[g->m_CurrentGeometry])
				{
					glTexCoord2d(g->m_TextureCoords[g->m_CurrentGeometry][ind][0], g->m_TextureCoords[g->m_CurrentGeometry][ind][1]);
					glVertex2f(g->m_Points[g->m_CurrentGeometry][ind][0], g->m_Points[g->m_CurrentGeometry][ind][1]);
				}
				glEnd();
				
				OpenGLStateMachine::GetSingleton().PopModelView();
			}
		}
	}
	void RenderSystem::OnResume(){};
	void RenderSystem::Stop(){};





	PlayerMovementSystem::PlayerMovementSystem(std::shared_ptr<EntityManager> entityMgr, std::shared_ptr<EventManager> eventMgr) :
		System(entityMgr, eventMgr)
	{

	}

	bool PlayerMovementSystem::Start(){
		m_EventManager->RegisterCallback<KeyDownEvent>(std::bind(&PlayerMovementSystem::KeyDownCallback, this, std::placeholders::_1));
		m_EventManager->RegisterCallback<KeyUpEvent>(std::bind(&PlayerMovementSystem::KeyUpCallback, this, std::placeholders::_1));
		return true;
	};


	void PlayerMovementSystem::OnSuspend(){};
	void PlayerMovementSystem::Update(double deltaTime)
	{
		AUTO_PROFILE("PlayerMovementSystem::Update");

	}
	void PlayerMovementSystem::OnResume(){};
	void PlayerMovementSystem::Stop(){};

	void PlayerMovementSystem::KeyDownCallback(std::shared_ptr<BaseEvent> e) {

		AUTO_PROFILE("PlayerMovementSystem::KeyDownCallback");

		auto e2 = std::dynamic_pointer_cast<KeyDownEvent>(e);

		for (Entity e : m_EntityManager->GetEntitiesWithComponents<Position2DComponent, Motion2DComponent>())
		{
			std::shared_ptr<Position2DComponent> p;
			std::shared_ptr<Motion2DComponent> m;
			e.GetComponents(p, m);

			if (e2->m_KeyCode == 'w' || e2->m_KeyCode == 'W')
			{
				m->m_Velocity = glm::vec2(0, .5);
			}
			else if (e2->m_KeyCode == 's' || e2->m_KeyCode == 'S')
			{
				m->m_Velocity = glm::vec2(0, -.5);
			}
			if (e2->m_KeyCode == 'd' || e2->m_KeyCode == 'D')
			{
				m->m_RotationalVelocity = -Math<float>::PI;
			}
			else if (e2->m_KeyCode == 'a' || e2->m_KeyCode == 'A')
			{
				m->m_RotationalVelocity = Math<float>::PI;
			}
			else if (e2->m_KeyCode == 'x' || e2->m_KeyCode == 'X')
			{
				m->m_RotationalVelocity = 0;
				p->m_Position = glm::vec2(0);
				p->m_Rotation = 0;
			}
			else if (e2->m_KeyCode == 'v' || e2->m_KeyCode == 'V')
			{
				//std::cout << AutoProfile::Report();
			}

		}
	}

	void PlayerMovementSystem::KeyUpCallback(std::shared_ptr<BaseEvent> e) {
		AUTO_PROFILE("PlayerMovementSystem::KeyUpCallback");

		auto e2 = std::dynamic_pointer_cast<KeyUpEvent>(e);
		for (Entity e : m_EntityManager->GetEntitiesWithComponents<Position2DComponent, Motion2DComponent>())
		{
			std::shared_ptr<Position2DComponent> p;
			std::shared_ptr<Motion2DComponent> m;
			e.GetComponents(p, m);


			m->m_Velocity = glm::vec2(0, 0);
			m->m_RotationalVelocity = 0;


		}
	}


	CursorSystem::CursorSystem(std::shared_ptr<EntityManager> entityMgr, std::shared_ptr<EventManager> eventMgr) :
		System(entityMgr, eventMgr)
	{

	}

	bool CursorSystem::Start(){
		m_EventManager->RegisterCallback<CursorPositionEvent>(std::bind(&CursorSystem::CursorPositionCallback, this, std::placeholders::_1));
		return true;
	};


	void CursorSystem::OnSuspend(){};
	void CursorSystem::Update(double deltaTime)
	{
		AUTO_PROFILE("CursorSystem::Update");
	}
	void CursorSystem::OnResume(){};
	void CursorSystem::Stop(){};

	void CursorSystem::CursorPositionCallback(std::shared_ptr<BaseEvent> e) {

		AUTO_PROFILE("CursorSystem::CursorPositionCallback");

		auto e2 = std::dynamic_pointer_cast<CursorPositionEvent>(e);

		for (Entity e : m_EntityManager->GetEntitiesWithComponents<Position2DComponent, CursorComponent>())
		{
			std::shared_ptr<Position2DComponent> p;
			e.GetComponents(p);

			

			p->m_Position = glm::vec2(e2->m_X * OpenGLStateMachine::GetSingleton().GetViewportWidth()/ 2., e2->m_Y * OpenGLStateMachine::GetSingleton().GetViewportHeight()/2.);
			//std::cout << "Cursor = " << e2->m_X << ", " << e2->m_Y << std::endl;
		}
	}
}

