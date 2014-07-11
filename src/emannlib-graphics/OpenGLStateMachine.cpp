#include "OpenGLStateMachine.hpp"


namespace emannlib
{
	OpenGLStateMachine::OpenGLStateMachine() :
		m_CurrentProgram(nullptr)
	{
		m_ModelViewTransform.push(glm::mat4());
		m_ProjectionTransform.push(glm::mat4());
	}

	void OpenGLStateMachine::UseProgram(std::shared_ptr<Program> newProgram)
	{
		if (m_CurrentProgram == newProgram)
		{
			if (!m_CurrentProgram->IsInUse())
			{
				m_CurrentProgram->Use();
				updateMatrixState();
			}
		}
		else
		{
			m_CurrentProgram = newProgram;
			m_CurrentProgram->Use();
			updateMatrixState();
		}
	}

	void OpenGLStateMachine::PushModelView()
	{
		m_ModelViewTransform.push(m_ModelViewTransform.top());
	}
	void OpenGLStateMachine::PopModelView()
	{
		m_ModelViewTransform.pop();
		updateMatrixState();
	}
	void OpenGLStateMachine::ModelViewLoadIdentity()
	{
		m_ModelViewTransform.top() = glm::mat4();
		updateMatrixState();
	}


	void OpenGLStateMachine::LookAt(const glm::vec3& point, const glm::vec3& viewer, const glm::vec3& up){}



	void OpenGLStateMachine::Transform(const glm::mat4& matrix){
		m_ModelViewTransform.top() = m_ModelViewTransform.top() * matrix;
		updateMatrixState();
	}
	void OpenGLStateMachine::Transform(const GLfloat* matrix){}

	void OpenGLStateMachine::Translate(const glm::vec3& translate){
		m_ModelViewTransform.top() = glm::translate(m_ModelViewTransform.top(), translate);
		updateMatrixState();
	}
	void OpenGLStateMachine::Translate(const glm::vec2& translate){
		m_ModelViewTransform.top() = glm::translate(m_ModelViewTransform.top(), glm::vec3(translate, 0.0));
		updateMatrixState();
	}

	void OpenGLStateMachine::Scale(const glm::vec3& scale){
		m_ModelViewTransform.top() = glm::scale(m_ModelViewTransform.top(), scale);
		updateMatrixState();
	}
	void OpenGLStateMachine::Scale(const glm::vec2& scale){
		m_ModelViewTransform.top() = glm::scale(m_ModelViewTransform.top(), glm::vec3(scale, 1.0));
		updateMatrixState();
	}

	void OpenGLStateMachine::Rotate(float radians, const glm::vec3& normalVector)
	{
		m_ModelViewTransform.top() = glm::rotate(m_ModelViewTransform.top(), radians, normalVector);
		updateMatrixState();
	}
	void OpenGLStateMachine::Rotate(float radians)
	{
		m_ModelViewTransform.top() = glm::rotate(m_ModelViewTransform.top(), radians, glm::vec3(0, 0, 1.0));
		updateMatrixState();
	}

	void OpenGLStateMachine::PushProjection()
	{
		m_ProjectionTransform.push(m_ProjectionTransform.top());
	}
	void OpenGLStateMachine::PopProjection()
	{
		m_ProjectionTransform.pop();
		updateMatrixState();
	}

	void OpenGLStateMachine::ProjectionLoadIdentity()
	{
		m_ProjectionTransform.top() = glm::mat4();
		updateMatrixState();
	}
	void OpenGLStateMachine::updateMatrixState()
	{
		if (m_CurrentProgram != nullptr)
		{
			if (!m_CurrentProgram->IsInUse())
			{
				m_CurrentProgram->Use();
			}


			m_CurrentProgram->SetUniform("ModelViewTransform", m_ModelViewTransform.top());
			m_CurrentProgram->SetUniform("ProjectionTransform", m_ProjectionTransform.top());
		}
	}
	void OpenGLStateMachine::Ortho2D(float left, float right, float bottom, float top, float znear, float zfar)
	{
		m_ProjectionTransform.top() = glm::ortho(left, right, bottom, top, znear, zfar);
		updateMatrixState();
	}
	void OpenGLStateMachine::Ortho2DFromCenterAndExtents(const glm::vec2& center, float newWidth, float newHeight)
	{
		float left = center.x - newWidth / 2.f;
		float right = center.x + newWidth / 2.f;
		float top = center.y + newHeight / 2.f;
		float bottom = center.y - newHeight / 2.f;
		Ortho2D(left, right, bottom, top);
	
	}
	void OpenGLStateMachine::Perspective(float fovy, float aspect, float znear, float zfar)
	{
		m_ProjectionTransform.top() = glm::perspective(fovy, aspect, znear, zfar);
		updateMatrixState();
	}
}