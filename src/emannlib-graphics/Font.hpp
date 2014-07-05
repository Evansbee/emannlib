#ifndef __font_h__
#define __font_h__

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

#include "Bitmap.hpp"

namespace emannlib
{
	class Font
	{
	public:
		Font(const std::string& fontname);
		Bitmap RenderString(const std::string& text);
		Bitmap RenderGlyph(char x);
	public:
		FT_Library m_Library;
		FT_Face m_Face;
	};
}

#endif