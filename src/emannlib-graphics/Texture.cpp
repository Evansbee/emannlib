#include "goldenduck/Texture.hpp"

namespace goldenduck
{
	Texture::Texture(Bitmap& bmp) :
		m_ImageHeight(bmp.GetHeight()),
		m_ImageWidth(bmp.GetWidth()),
		m_TextureWidth(NextPowerOf2(m_ImageWidth)),
		m_TextureHeight(NextPowerOf2(m_ImageHeight)),
		m_TextureID(0)
	{
		bmp.FlipAroundXAxis();

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR_MIPMAP_NEAREST
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_TextureWidth, m_TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_ImageWidth, m_ImageHeight, GL_RGBA, GL_UNSIGNED_BYTE, bmp.GetData());
	}

	Texture::~Texture()
	{
		std::cout << "Deleting Texture id " << m_TextureID << std::endl;
		glDeleteTextures(1, &m_TextureID);
	}

}