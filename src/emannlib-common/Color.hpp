#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <inttypes.h>

namespace emannlib
{
	class Color
	{
	private:
		union
		{
			struct{
				float m_R;
				float m_G;
				float m_B;
				float m_A;
			};
			float m_D[4];
		};

	public:
		Color(float r, float g, float b, float a = 1.0) :
			m_R(r),
			m_G(g),
			m_B(b),
			m_A(a)
		{

		}

		explicit Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) :
			m_R(float(r) / 255.0f),
			m_G(float(g) / 255.0f),
			m_B(float(b) / 255.0f),
			m_A(float(a) / 255.0f)
		{

		}

		const float * GetData() const
		{
			return &m_D[0];
		}

		float R() const
		{
			return m_R;
		}

		float G() const
		{
			return m_G;
		}

		float B() const
		{
			return m_B;
		}

		float A() const
		{
			return m_A;
		}


	};
}


#endif