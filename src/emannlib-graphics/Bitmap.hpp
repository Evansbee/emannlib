#ifndef __bitmap_h__
#define __bitmap_h__

#include <inttypes.h>
#include <vector>

#include <iostream>
#include <string>


namespace goldenduck
{
	class Pixel
	{
	public:
		Pixel() : m_R(0), m_G(0), m_B(0), m_A(255) {};
		Pixel(uint8_t bw) : m_R(bw), m_G(bw), m_B(bw), m_A(255) {};
		Pixel(uint8_t bw, uint8_t a) : m_R(bw), m_G(bw), m_B(bw), m_A(a) {};
		Pixel(uint8_t r, uint8_t g, uint8_t b) : m_R(r), m_G(g), m_B(b), m_A(255) {};
		Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : m_R(r), m_G(g), m_B(b), m_A(a) {};
		Pixel(uint32_t rgba) :
			m_R(uint8_t((rgba >> 24) & 0x000000FF)),
			m_G(uint8_t((rgba >> 16) & 0x000000FF)),
			m_B(uint8_t((rgba >> 8) & 0x000000FF)),
			m_A(uint8_t((rgba >> 0) & 0x000000FF))
		{};

		bool operator ==(Pixel other) const
		{
			return m_R == other.m_R &&
				m_G == other.m_G &&
				m_B == other.m_B &&
				m_A == other.m_A;
		}

		bool operator !=(Pixel other) const
		{
			return !(*this == other);
		}

	public:
		uint8_t m_R;
		uint8_t m_G;
		uint8_t m_B;
		uint8_t m_A;
	};


	class Bitmap
	{
	private:
		Bitmap() : m_ImageHeight(0), m_ImageWidth(0){};
		void _swap(Bitmap &other)
		{
			std::swap(this->m_ImageHeight, m_ImageHeight);
			std::swap(this->m_ImageWidth, m_ImageWidth);
			std::swap(this->m_PixelData, m_PixelData);
		}
	public:

		Bitmap& operator=(Bitmap other);
		Bitmap(Bitmap&& other);


		//construct from data;
		Bitmap(uint32_t width, uint32_t height, uint32_t bpp, unsigned char *data);
		Bitmap(uint32_t width, uint32_t height);

		bool operator ==(Bitmap other) const;
		bool operator !=(Bitmap other) const;

		uint32_t GetWidth() const { return m_ImageWidth; }
		uint32_t GetHeight() const { return m_ImageHeight; }
		uint32_t GetBPP() const { return m_ImageComposition; }

		//internally we'll compute everything to 32bpp
		//if we're going to write it out, we'll change to 24bpp
		uint32_t GetSize() const { return m_ImageWidth * m_ImageHeight * 4; }

		unsigned char * GetData() { return reinterpret_cast<unsigned char*>(&m_PixelData.front()); }

		void FlipAroundYAxis();
		void FlipAroundXAxis();

		//blit grows, append just throws it on top
		void Blit(int x, int y, Bitmap& addition);
		void Append(int startx, int starty, Bitmap& addition);




	private:
		inline int32_t _idx(int32_t x, int32_t y){ return (y*m_ImageWidth) + x; }


	private:
		//in order for the file...

		int32_t m_ImageWidth;
		int32_t m_ImageHeight;
		int32_t m_ImageComposition;
		std::vector<Pixel> m_PixelData;

	public:
		friend Bitmap LoadBitmapFromFile(const std::string& filename);
		void SaveToFile(const std::string& filename);

		void SaveToPNG(const std::string& filename);
		void SaveToBMP(const std::string& filename);
		void SaveToTGA(const std::string& filename);
	};

	Bitmap LoadBitmapFromFile(const std::string& filename);


	struct BitmapFileHeader
	{
		uint16_t m_BitmapSignature;
		uint32_t m_FileSize;
		uint16_t m_Reserved1;
		uint16_t m_Reserved2;
		uint32_t m_OffsetToPixelArray;
		uint32_t GetSize()
		{
			return
				sizeof(m_BitmapSignature) +
				sizeof(m_FileSize) +
				sizeof(m_Reserved1) +
				sizeof(m_Reserved2) +
				sizeof(m_OffsetToPixelArray);
		}
	};

	struct BitmapInfoHeader
	{
		uint32_t m_DIBHeaderSize;
		uint32_t m_ImageWidth;
		uint32_t m_ImageHeight;
		uint16_t m_Planes;
		uint16_t m_BitsPerPixel;
		uint32_t m_Compression;
		uint32_t m_ImageSize;
		uint32_t m_XPixelsPerMeter;
		uint32_t m_YPixelsPerMeter;
		uint32_t m_ColorsInColorTable;
		uint32_t m_ImportantColorCount;
		uint32_t GetSize()
		{
			return
				sizeof(m_DIBHeaderSize) +
				sizeof(m_ImageWidth) +
				sizeof(m_ImageHeight) +
				sizeof(m_Planes) +
				sizeof(m_BitsPerPixel) +
				sizeof(m_Compression) +
				sizeof(m_ImageSize) +
				sizeof(m_XPixelsPerMeter) +
				sizeof(m_YPixelsPerMeter) +
				sizeof(m_ColorsInColorTable) +
				sizeof(m_ImportantColorCount);
		}
	};
}


#endif