#ifndef __components_h__
#define __components_h__

#include "goldenduck/Entity.hpp"
#include "goldenduck/Texture.hpp"
#include "goldenduck/Easing.hpp"

#define GLFW_INCLUDE_GLU
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <vector>
#include <string>
#include <inttypes.h>
#include <memory>



namespace goldenduck
{
	class TextureComponent : public Component<TextureComponent>
	{
	public:
		std::vector<std::shared_ptr<Texture>> m_Textures;
		uint32_t m_NumTextures;
		uint32_t m_CurrentTexture;

		TextureComponent() : m_NumTextures(0), m_CurrentTexture(0) {}
		void AddTexture(std::shared_ptr<Texture> newTexture) { m_Textures.push_back(newTexture); m_NumTextures++; }
	};

	class CursorComponent : public Component<CursorComponent>
	{
	public:
	
	};

	class Geometry2DComponent : public Component <Geometry2DComponent>
	{
	public:
		std::vector<std::vector<glm::vec2>> m_Points;
		std::vector<std::vector<int>> m_Indices;
		std::vector<std::vector<glm::vec2>> m_TextureCoords;
		uint32_t m_NumGeometries;
		uint32_t m_CurrentGeometry;

		Geometry2DComponent() : m_NumGeometries(0), m_CurrentGeometry(0) {}
		void AddGeometry(std::vector<glm::vec2>& newPoints, std::vector<int>& newIndices, std::vector<glm::vec2>& newTextureCoords) 
		{ 
			m_Points.push_back(newPoints);
			m_Indices.push_back(newIndices);
			m_TextureCoords.push_back(newTextureCoords);
			m_NumGeometries++;
		}
	};

	class Position2DComponent : public Component<Position2DComponent>
	{
	public:
		glm::vec2 m_Position;
		float m_Rotation;

		glm::vec2 m_PositionOffset;
		float m_RotationOffset;

		Position2DComponent() : m_Position(glm::vec2(0.0f)), m_Rotation(0.0f), m_PositionOffset(glm::vec2(0.0f)), m_RotationOffset(0.0f)
		{

		}

		glm::vec2 GetForward() const { 
			float actualRotation = m_Rotation + m_RotationOffset;
			return glm::vec2(Math<float>::Cos(actualRotation), Math<float>::Sin(actualRotation));
		}

		glm::vec2 GetRight() const {
			float actualRotation = m_Rotation + m_RotationOffset;
			float tempRot = actualRotation - Math<float>::PI;
			return glm::vec2(Math<float>::Cos(tempRot), Math<float>::Sin(tempRot));
		}
	};



	class Parent2DComponent : public Component < Parent2DComponent >
	{
	public:
		Entity m_ParentEntity;
		Parent2DComponent(Entity parent) :m_ParentEntity(parent) {}
	};



	class Motion2DComponent : public Component < Motion2DComponent >
	{
	public:
		Motion2DComponent() :
			m_Velocity(glm::vec2(0,0)),
			m_Acceleration(glm::vec2(0, 0)),
			m_RotationalVelocity(0.),
			m_RotationalAcceleration(0.),
			m_Damping(glm::vec2(0, 0)),
			m_RotationDamping(0.)
		{}
	public:
		glm::vec2 m_Velocity;
		glm::vec2 m_Acceleration;
		float m_RotationalVelocity;
		float m_RotationalAcceleration;
		glm::vec2 m_Damping;
		float m_RotationDamping;
	};


	class Geometry3DComponent : public Component <Geometry3DComponent>
	{
	public:
		std::vector<std::vector<glm::vec3>> m_Points;
		std::vector<std::vector<int>> m_Indices;
		std::vector<std::vector<glm::vec3>> m_TextureCoords;
		uint32_t m_NumGeometries;
		uint32_t m_CurrentGeometry;
		void AddGeometry(std::vector<glm::vec3>& newPoints, std::vector<int>& newIndices, std::vector<glm::vec3>& newTextureCoords)
		{
			m_Points.push_back(newPoints);
			m_Indices.push_back(newIndices);
			m_TextureCoords.push_back(newTextureCoords);
			m_NumGeometries++;
		}
	};

	class Position3DComponent : public Component<Position3DComponent>
	{
	public:
		glm::vec3 m_Position;
		//float m_Rotation;
	};

	class Motion3DComponent : public Component < Motion3DComponent >
	{
		glm::vec3 m_Velocity;
		glm::vec3 m_Acceleration;
		float m_RotationalVelocity;
		float m_RotationalAcceleration;
		glm::vec3 m_Damping;
		glm::vec3 m_RotationDamping;
	};


	class BoundingSphereComponent : public Component < BoundingSphereComponent >
	{
		float m_Radius;
	};

	class PlayerComponent : public Component < PlayerComponent >
	{

	};

	//template <class T>
	//class EasingComponent : public Component < EasingComponent >
	//{
	//	
	//	EasingComponent(double endTime, EasingType type, T* value, T target) :
	//		m_Ease(0.0, endtime, type),
	//		m_ValueToEase(value),
	//		m_StartingValue(*m_ValueToEase),
	//		m_TargetValue(target)
	//	{}

	//	Easing m_Ease;
	//	T* m_ValueToEase;
	//	T m_StartingValue;
	//	T m_TargetValue;
	//	 



	//};
}



#endif