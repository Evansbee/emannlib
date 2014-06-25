#ifndef __SPRITE_HPP__
#define __SPRITE_HPP__

#include "goldenduck\Entity.hpp"
#include <memory>
#include <string>
#include <inttypes.h>

namespace goldenduck
{
	Entity CreateSprite(std::shared_ptr<EntityManager> entityManager, const std::string& textureFile, float x, float y, float width, float height);
}



#endif