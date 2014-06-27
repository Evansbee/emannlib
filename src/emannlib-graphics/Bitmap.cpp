#include "Bitmap.hpp"
#include "../emannlib-filesystem/FileSystemAccess.hpp"
#include "../emannlib-common/Assert.hpp"
#include "../emannlib-common/AutoProfile.hpp"
#include "../emannlib-math/Math.hpp"

#include "stb_image.h"
#include "stb_image_write.h"


namespace emannlib
{
	Bitmap& Bitmap::operator = (Bitmap other)
	{
		other._swap(*this);
		return *this;
	}
	Bitmap::Bitmap(Bitmap&& other) :
		m_PixelData(std::move(other.m_PixelData)),
		m_ImageHeight(std::move(other.m_ImageHeight)),
		m_ImageWidth(std::move(other.m_ImageWidth))

	{

	}

	Bitmap::Bitmap(uint32_t width, uint32_t height) :
		m_ImageHeight(height),
		m_ImageWidth(width),
		m_ImageComposition(4)
	{
		AUTO_PROFILE("Bitmap::Bitmap(From width and height)");
		m_PixelData.reserve(m_ImageHeight * m_ImageWidth);
		for (int32_t y = 0; y < m_ImageHeight; y++)
		{
			for (int32_t x = 0; x < m_ImageWidth; x++)
			{
				Pixel p;
				p.m_A = 0;
				m_PixelData.push_back(p);
			}
		}
	}

	Bitmap::Bitmap(uint32_t width, uint32_t height, uint32_t bpp, unsigned char *data) :
		m_ImageHeight(height),
		m_ImageWidth(width),
		m_ImageComposition(bpp)
	{
		AUTO_PROFILE("Bitmap::Bitmap(From Buffer)");
		m_PixelData.reserve(m_ImageHeight * m_ImageWidth);

		uint32_t dataPtr = 0;

		for (int32_t y = 0; y < m_ImageHeight; y++)
		{
			for (int32_t x = 0; x < m_ImageWidth; x++)
			{
				if (_idx(x, y) >= m_ImageHeight * m_ImageWidth)
				{
					GD_ASSERT(_idx(x, y) < m_ImageHeight * m_ImageWidth);
				}

				if (bpp == 1)
				{
					Pixel p;
					p.m_A = data[dataPtr++];
					p.m_R = 255;
					p.m_G = 255;
					p.m_B = 255;
					m_PixelData.push_back(p);
				}
				else if (bpp == 3)
				{
					Pixel p;
					p.m_R = data[dataPtr++];
					p.m_G = data[dataPtr++];
					p.m_B = data[dataPtr++];
					p.m_A = 255;
					m_PixelData.push_back(p);

				}
				else if (bpp == 4)
				{
					Pixel p;
					p.m_R = data[dataPtr++];
					p.m_G = data[dataPtr++];
					p.m_B = data[dataPtr++];
					p.m_A = data[dataPtr++];
					m_PixelData.push_back(p);
				}
				else
				{
					//punt
				}
			}
		}
	}


	bool Bitmap::operator ==(Bitmap other) const
	{
		if (m_ImageHeight == other.m_ImageHeight &&
			m_ImageWidth == other.m_ImageWidth)
		{
			for (auto i = 0; i < m_ImageHeight * m_ImageWidth; i++)
			{
				if (m_PixelData[i] != other.m_PixelData[i])
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
		return true;
	}

	void Bitmap::Blit(int x, int y, Bitmap& addition)
	{
		int32_t leftMostPoint;
		int32_t rightMostPoint;
		int32_t upperMostPoint;
		int32_t lowerMostPoint;

		
		leftMostPoint = Math<int32_t>::GetLesserValue(x, 0);
		rightMostPoint = Math<int32_t>::GetGreaterValue(leftMostPoint + addition.m_ImageWidth, m_ImageWidth);
		upperMostPoint = Math<int32_t>::GetLesserValue(y, 0);
		lowerMostPoint = Math<int32_t>::GetGreaterValue(upperMostPoint + addition.m_ImageHeight, m_ImageHeight);

		int32_t existingBitmapStartX;
		int32_t existingBitmapStartY;

		//int32_t newBitmapStartX;
		//int32_t newBitmapStartY;

		existingBitmapStartX = -leftMostPoint;
		existingBitmapStartY = -upperMostPoint;

	}

	void Bitmap::Append(int startx, int starty, Bitmap& addition)
	{
		for (int y = 0; y < m_ImageHeight; y++)
		{
			for (int x = 0; x < m_ImageWidth; x++)
			{
				if (x >= startx && x < startx + addition.m_ImageWidth && y >= starty && y < starty + addition.m_ImageHeight && addition.m_PixelData[addition._idx(x - startx, y - starty)].m_A != 0)
				{
					m_PixelData[_idx(x, y)] = addition.m_PixelData[addition._idx(x - startx, y - starty)];
				}
			}
		}
	}


	bool Bitmap::operator !=(Bitmap other) const
	{
		return !(*this == other);
	}

	Bitmap LoadBitmapFromFile(const std::string& filename)
	{
		AUTO_PROFILE("LoadBitmapFromFile");

		int w, h, bpp;
		unsigned char *data;
		data = stbi_load(filename.c_str(), &w, &h, &bpp, 0);
		Bitmap loadedBitmap = Bitmap(w, h, bpp, data);
		stbi_image_free(data);
		return loadedBitmap;
	}

	void Bitmap::SaveToPNG(const std::string& filename)
	{
		stbi_write_png(filename.c_str(), m_ImageWidth, m_ImageHeight, m_ImageComposition, &m_PixelData[0], 0);
	}
	void Bitmap::SaveToBMP(const std::string& filename)
	{
		stbi_write_bmp(filename.c_str(), m_ImageWidth, m_ImageHeight, m_ImageComposition, &m_PixelData[0]);
	}
	void Bitmap::SaveToTGA(const std::string& filename)
	{
		stbi_write_tga(filename.c_str(), m_ImageWidth, m_ImageHeight, m_ImageComposition, &m_PixelData[0]);
	}

	void Bitmap::FlipAroundXAxis()
	{
		AUTO_PROFILE("Bitmap::FlipAroundXAxis");
		for (int y = 0; y < m_ImageHeight/2; y++)
		{
			for (int x = 0; x < m_ImageWidth; x++)
			{
				Pixel p = m_PixelData[_idx(x, y)];
				m_PixelData[_idx(x, y)] = m_PixelData[_idx(x, m_ImageHeight - y - 1)];
				m_PixelData[_idx(x, m_ImageHeight - y - 1)] = p;
			}
		}
	}
}