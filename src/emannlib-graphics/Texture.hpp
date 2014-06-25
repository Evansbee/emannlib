#ifndef __texture_h__
#define __texture_h__

#include "../emannlib-math/Math.hpp"
#include "../emannlib-utility/AutoProfile.hpp"
#include "../emannlib-graphics/Bitmap.hpp"

#include <inttypes.h>

#define GLFW_INCLUDE_GLU
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace goldenduck
{
	class Texture
	{
	public:
		Texture(Bitmap& bmp);
		~Texture();

		float GetNormalizedWidth() const { return (float)m_ImageWidth / (float)m_TextureWidth; }
		float GetNormalizedHeight() const { return (float) m_ImageHeight / (float) m_TextureHeight; }

		GLuint GetTextureID() const { return m_TextureID; }


	private:
		uint32_t m_ImageWidth;
		uint32_t m_TextureWidth;
		uint32_t m_ImageHeight;
		uint32_t m_TextureHeight;
		GLuint m_TextureID;
	};
}

#endif