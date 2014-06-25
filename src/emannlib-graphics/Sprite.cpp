#include "Sprite.hpp"
#include "../emannlib-ecs/Components.hpp"
#include "../emannlib-graphics/Texture.hpp"

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace goldenduck
{
	Entity CreateSprite(std::shared_ptr<EntityManager> entityManager, const std::string& textureFile, float x, float y, float width, float height)
	{
		auto e = entityManager->Create();
		e.AddComponent<Position2DComponent>();
		e.AddComponent<TextureComponent>();
		e.AddComponent<Geometry2DComponent>();

		e.GetComponent<Position2DComponent>()->m_Position = glm::vec2(x, y);
		e.GetComponent<Position2DComponent>()->m_Rotation = 0.;

		e.GetComponent<TextureComponent>()->AddTexture(std::make_shared<Texture>(LoadBitmapFromFile(textureFile)));
		e.GetComponent<TextureComponent>()->m_CurrentTexture = 0;

		std::vector<glm::vec2> points;

		points.push_back(glm::vec2(-width / 2., height / 2.));
		points.push_back(glm::vec2(width / 2., height / 2.));
		points.push_back(glm::vec2(width / 2., -height / 2.));
		points.push_back(glm::vec2(-width / 2., -height / 2.));

		std::vector<int> indices;
		indices.push_back(0);
		indices.push_back(3);
		indices.push_back(1);
		indices.push_back(1);
		indices.push_back(3);
		indices.push_back(2);

		std::vector<glm::vec2> textureCoords;

		auto t = e.GetComponent<TextureComponent>();

		textureCoords.push_back(glm::vec2(0., t->m_Textures[t->m_CurrentTexture]->GetNormalizedHeight()));
		textureCoords.push_back(glm::vec2(t->m_Textures[t->m_CurrentTexture]->GetNormalizedWidth(), t->m_Textures[t->m_CurrentTexture]->GetNormalizedHeight()));
		textureCoords.push_back(glm::vec2(t->m_Textures[t->m_CurrentTexture]->GetNormalizedWidth(), 0.));
		textureCoords.push_back(glm::vec2(0.,0.));

		e.GetComponent<Geometry2DComponent>()->AddGeometry(points,indices,textureCoords);

		return e;
	}
}