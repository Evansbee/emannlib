#ifndef __GL_DRAW_HPP__
#define __GL_DRAW_HPP__

#include <memory>
#include <vector>

#include "Texture.hpp"
#include "Area.hpp"

#include "../emannlib-common/Vector.hpp"

namespace emannlib
{
	namespace gl
	{
		void Draw(std::shared_ptr<Texture> texture, Area area);
		
		void DrawLine(const Vec2f& start, const Vec2f& stop, float strokeWidth = 1.0);
		
		void DrawRect(const Area& sq);
		
		void DrawRectStroke(const Area& sq, float strokeWidth = 1.0);

		void DrawCirle(const Vec2f& center, float radius, int numSides = 360);
		
		void DrawCirleStroke(const Vec2f& center, float radius, float strokeWidth = 1.0f, int numSides = 360);

		void DrawCoordinateFrame(const Vec2f& center, float axisLength, float headLength, float headWidth);

		void DrawVector(const Vec2f& start, const Vec2f& target, float vectorLength, float vectorWidth, float headLength, float headWidth);

		void DrawPolyLine(const std::vector<Vec2f>& line);
		void DrawClosedPolyLine(const std::vector<Vec2f>& line);

		void Color(float r, float g, float b, float a = 1.0);

		void SetLineWidth(float width);
		void SetPointSize(float size);
	}
}

#endif