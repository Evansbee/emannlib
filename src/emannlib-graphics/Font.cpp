#include "Font.hpp"
#include "../emannlib-math/Math.hpp"
#include "../emannlib-utility/AutoProfile.hpp"

#include "ftglyph.h"

#include <iostream>

namespace emannlib
{
	Font::Font(const std::string& fontname)
	{
		AUTO_PROFILE("Font::Font");
		auto error = FT_Init_FreeType(&m_Library);
		if (error)
		{
			std::cout << "Error occured loading font file\n";
		}

		error = FT_New_Face(m_Library, fontname.c_str(), 0, &m_Face);
		error = FT_Set_Pixel_Sizes(m_Face, 0, 256);
	}

	Bitmap Font::RenderString(const std::string& text)
	{
		AUTO_PROFILE("Font::RenderString");
		int x = 0;
		int y = 28;

		int max_ymax=0;
		int min_ymin=0;

		for (unsigned char c = 32; c < 128; c++)
		{
			if (FT_Load_Char(m_Face, c, FT_LOAD_RENDER))
			{
				__debugbreak();
				continue;
			}

			FT_Glyph glyph;
			
			FT_GlyphSlot g = m_Face->glyph;
			FT_BBox  bbox;
			FT_Get_Glyph(g, &glyph);
			
			FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_PIXELS, &bbox);
			
			max_ymax = Math<int>::GetGreaterValue(max_ymax, bbox.yMax);
			min_ymin = Math<int>::GetLesserValue(min_ymin, bbox.yMin);
		}

		int width=0;

		bool use_kerning = FT_HAS_KERNING(m_Face) > 0;
		FT_UInt previous =0 ;
		FT_UInt glyph_index;

		for (const char *p = text.c_str(); *p; ++p)
		{
			if (FT_Load_Char(m_Face, *p, FT_LOAD_RENDER))
			{
				continue;
			}

			glyph_index = FT_Get_Char_Index(m_Face, *p);

			if (use_kerning && previous && glyph_index)
			{
				FT_Vector  delta;


				FT_Get_Kerning(m_Face, previous, glyph_index,
							   FT_KERNING_DEFAULT, &delta);

				width += delta.x >> 6;
			}

			FT_GlyphSlot g = m_Face->glyph;
			if (g->bitmap.buffer)
			{
				width += g->advance.x >> 6;
			}

			previous = glyph_index;
		}

		auto b = Bitmap(width, max_ymax - min_ymin);

		for (const char *p = text.c_str(); *p; ++p)
		{
			if (FT_Load_Char(m_Face, *p, FT_LOAD_RENDER))
			{
				continue;
			}
			glyph_index = FT_Get_Char_Index(m_Face, *p);

			if (use_kerning && previous && glyph_index)
			{
				FT_Vector  delta;


				FT_Get_Kerning(m_Face, previous, glyph_index,
							   FT_KERNING_DEFAULT, &delta);

				x += delta.x >> 6;
			}
			FT_Glyph glyph;
			FT_GlyphSlot g = m_Face->glyph;
			if (g->bitmap.buffer)
			{
				FT_BBox  bbox;
				FT_Get_Glyph(g, &glyph);
				FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_TRUNCATE, &bbox);
				
				Bitmap d(g->bitmap.width, g->bitmap.rows, 1, g->bitmap.buffer);
				
				b.Append(x + g->bitmap_left, (max_ymax - bbox.yMax), d);
				x += g->advance.x >> 6;
			}
			previous = glyph_index;
		}
		b.SaveToPNG(text + ".png");
		return b;
	}

	Bitmap Font::RenderGlyph(char x)
	{
		AUTO_PROFILE("Font::RenderGlyph");


		if (FT_Load_Char(m_Face, x, FT_LOAD_RENDER))
		{
			return Bitmap(0, 0, 4, NULL);;
		}

		FT_GlyphSlot g = m_Face->glyph;
		if (g->bitmap.buffer)
		{
			Bitmap b(g->bitmap.width, g->bitmap.rows, 1, g->bitmap.buffer);
			return b;
		}


		return Bitmap(0, 0, 4, NULL);;
	}
}