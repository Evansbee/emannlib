#ifndef __GL_DRAW_HPP__
#define __GL_DRAW_HPP__

#include <memory>
#include <vector>

#include "Texture.hpp"
#include "Area.hpp"


namespace emannlib
{
	namespace gl
	{
		void Draw(std::shared_ptr<Texture> texture, Area area);
		
		void DrawLine(const glm::vec2& start, const glm::vec2& stop);
		
		void DrawRect(const Area& sq);
		void DrawRextStroke(const Area& sq);

		void DrawCirle(const glm::vec2& center, float radius, int numSides = 360);
		void DrawCirleStroke(const glm::vec2& center, float radius, int numSides = 360);

		void DrawCoordinateFrame(const glm::vec2& center, float axisLength, float headLength, float headWidth);

		void DrawVector(const glm::vec2& start, const glm::vec2& end, float headLength, float headWidth);

		void DrawPolyLine(const std::vector<glm::vec2>& line);
		void DrawClosedPolyLine(const std::vector<glm::vec2>& line);

		void Color(float r, float g, float b, float a = 1.0);

		void SetLineWidth(float width);
		void SetPointSize(float size);
	}
}

#endif