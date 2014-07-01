#include <memory>

#define GLFW_INCLUDE_GLU
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "GLDraw.hpp"
#include "Texture.hpp"

#include "../emannlib-math/Math.hpp"

namespace emannlib
{
	namespace gl
	{
		void Draw(std::shared_ptr<Texture> texture, Area area)
		{
		
		}

		void DrawLine(const glm::vec2& start, const glm::vec2& stop)
		{
			float lineVerts[2 * 2];
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, lineVerts);
			lineVerts[0] = start.x; lineVerts[1] = start.y;
			lineVerts[2] = stop.x; lineVerts[3] = stop.y;
			glDrawArrays(GL_LINES, 0, 2);
			glDisableClientState(GL_VERTEX_ARRAY);
		}

		void DrawRect(const Area& sq)
		{
			GLfloat verts[8];
			verts[0] = sq.m_LowerRight.x;	verts[1] = sq.m_UpperLeft.y;
			verts[2] = sq.m_UpperLeft.x;	verts[3] = sq.m_UpperLeft.y;
			verts[4] = sq.m_LowerRight.x;	verts[5] = sq.m_LowerRight.y;
			verts[6] = sq.m_UpperLeft.x;	verts[7] = sq.m_LowerRight.y;
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, verts);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glDisableClientState(GL_VERTEX_ARRAY);
		}
		void DrawRectStroke(const Area& sq)	
		{
			GLfloat verts[8];
			verts[0] = sq.m_UpperLeft.x;	verts[1] = sq.m_UpperLeft.y;
			verts[2] = sq.m_LowerRight.x;	verts[3] = sq.m_UpperLeft.y;
			verts[4] = sq.m_LowerRight.x;	verts[5] = sq.m_LowerRight.y;
			verts[6] = sq.m_UpperLeft.x;	verts[7] = sq.m_LowerRight.y;
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, verts);
			glDrawArrays(GL_LINE_LOOP, 0, 4);
			glDisableClientState(GL_VERTEX_ARRAY);
		}

		void DrawCirle(const glm::vec2& center, float radius, int numSides)
		{
			// automatically determine the number of segments from the circumference
			if (numSides <= 0) {
				numSides = (int) Math<double>::Floor(radius * Math<double>::PI * 2);
			}
			if (numSides < 2) numSides = 2;

			GLfloat *verts = new float[(numSides + 2) * 2];
			verts[0] = center.x;
			verts[1] = center.y;
			for (int s = 0; s <= numSides; s++) {
				float t = s / (float) numSides * 2.0f * 3.14159f;
				verts[(s + 1) * 2 + 0] = center.x + Math<float>::Cos(t) * radius;
				verts[(s + 1) * 2 + 1] = center.y + Math<float>::Sin(t) * radius;
			}
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, verts);
			glDrawArrays(GL_TRIANGLE_FAN, 0, numSides + 2);
			glDisableClientState(GL_VERTEX_ARRAY);
			delete [] verts;
		
		}


		void DrawCirleStroke(const glm::vec2& center, float radius, int numSides)
		{
			// automatically determine the number of segments from the circumference
			if (numSides <= 0) {
				numSides = (int) Math<double>::Floor(radius * Math<double>::PI * 2);
			}
			if (numSides < 2) numSides = 2;

			GLfloat *verts = new float[numSides * 2];
			for (int s = 0; s < numSides; s++) {
				float t = s / (float) numSides * 2.0f * Math<float>::PI;
				verts[s * 2 + 0] = center.x + Math<float>::Cos(t) * radius;
				verts[s * 2 + 1] = center.y + Math<float>::Sin(t) * radius;
			}
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, verts);
			glDrawArrays(GL_LINE_LOOP, 0, numSides);
			glDisableClientState(GL_VERTEX_ARRAY);
			delete [] verts;

		}

		void DrawCoordinateFrame(const glm::vec2& center, float axisLength, float headLength, float headWidth){}

		void DrawVector(const glm::vec2& start, const glm::vec2& end, float headLength, float headWidth){}

		void DrawPolyLine(const std::vector<glm::vec2>& line){}
		void DrawClosedPolyLine(const std::vector<glm::vec2>& line){}

		void Color(float r, float g, float b, float a)
		{
			glColor4f(r, g, b, a);
		}

		void SetLineWidth(float width)
		{
			glLineWidth(width);
		}
		void SetPointSize(float size)
		{
			glPointSize(size);
		}
	}
}