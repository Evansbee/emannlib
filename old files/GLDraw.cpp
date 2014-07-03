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
#include "../emannlib-common/AutoProfile.hpp"

#include "OpenGLStateMachine.hpp"

namespace emannlib
{
	namespace gl
	{
		void Draw(std::shared_ptr<Texture> texture, Area area)
		{
		
		}

		void DrawLine(const Vec2f& start, const Vec2f& stop, float strokeWidth)
		{
			AUTO_PROFILE("gl::DrawLine");
						
			Vec2f spanVector = stop - start;

			float bodyLength = spanVector.Length();

			float radians = (spanVector.x > 0.0f) ? Math<float>::ATan(spanVector.y / spanVector.x) : (Math<float>::ATan(spanVector.y / spanVector.x) + Math<float>::PI);

			float verts[12];
			
			verts[0 * 2] = 0.0f;				verts[0 * 2 + 1] = strokeWidth / 2.0f;
			verts[1 * 2] = 0.0f;				verts[1 * 2 + 1] = -strokeWidth / 2.0f;
			verts[2 * 2] = bodyLength;	        verts[2 * 2 + 1] = strokeWidth / 2.0f;

			verts[3 * 2] = bodyLength;			verts[3 * 2 + 1] = strokeWidth / 2.0f;
			verts[4 * 2] = 0.0f;				verts[4 * 2 + 1] = -strokeWidth / 2.0f;
			verts[5 * 2] = bodyLength;			verts[5 * 2 + 1] = -strokeWidth / 2.0f;

			OpenGLStateMachine::GetSingleton().PushModelView();
			OpenGLStateMachine::GetSingleton().Rotate(radians);
			OpenGLStateMachine::GetSingleton().Translate(glm::vec2(start.x, start.y));

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, verts);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glDisableClientState(GL_VERTEX_ARRAY);
			OpenGLStateMachine::GetSingleton().AddTrianglesToFrameCount(3);
			OpenGLStateMachine::GetSingleton().PopModelView();
		}

		void DrawRect(const Area& sq)
		{
			AUTO_PROFILE("gl::DrawRect");
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
			AUTO_PROFILE("gl::DrawRectStroke");
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

		void DrawCirle(const Vec2f& center, float radius, int numSides )
		{
			AUTO_PROFILE("gl::DrawCirle");
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
			OpenGLStateMachine::GetSingleton().AddTrianglesToFrameCount(numSides);
			delete [] verts;
		
		}


		void DrawCirleStroke(const glm::vec2& center, float radius, int numSides)
		{
			AUTO_PROFILE("gl::DrawCirleStroke");
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

		void DrawVector(const Vec2f& start, const Vec2f& target, float vectorLength, float vectorWidth, float headLength, float headWidth)
		{
			AUTO_PROFILE("gl::DrawVector");
			float bodyLength = (vectorLength > headLength)?(vectorLength - headLength):(0.0f);
			
			Vec2f spanVector = target - start;

			float radians = (spanVector.x > 0.0f) ? Math<float>::ATan(spanVector.y / spanVector.x) : (Math<float>::ATan(spanVector.y / spanVector.x) + Math<float>::PI);
			
			float verts[18];
	
			
			verts[0 * 2] = 0.0f;				verts[0 * 2 + 1] = vectorWidth / 2.0f; 
			verts[1 * 2] = 0.0f;				verts[1 * 2 + 1] = -vectorWidth / 2.0f;
			verts[2 * 2] = bodyLength;	        verts[2 * 2 + 1] = vectorWidth / 2.0f; 

			verts[3 * 2] = bodyLength;			verts[3 * 2 + 1] = vectorWidth / 2.0f; 
			verts[4 * 2] = 0.0f;				verts[4 * 2 + 1] = -vectorWidth / 2.0f; 
			verts[5 * 2] = bodyLength;			verts[5 * 2 + 1] = -vectorWidth / 2.0f; 

			verts[6 * 2] = bodyLength;			verts[6 * 2 + 1] = headWidth / 2.0f; 
			verts[7 * 2] = bodyLength;			verts[7 * 2 + 1] = -headWidth / 2.0f; 
			verts[8 * 2] = bodyLength + headLength; verts[8 * 2 + 1] = 0.0f; 

			OpenGLStateMachine::GetSingleton().PushModelView();
			OpenGLStateMachine::GetSingleton().Rotate(radians);
			OpenGLStateMachine::GetSingleton().Translate(glm::vec2(start.x, start.y));

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, verts);
			glDrawArrays(GL_TRIANGLES, 0, 9);
			glDisableClientState(GL_VERTEX_ARRAY);
			OpenGLStateMachine::GetSingleton().AddTrianglesToFrameCount(3);
			OpenGLStateMachine::GetSingleton().PopModelView();
		}

		void DrawPolyLine(const std::vector<glm::vec2>& line){}
		void DrawClosedPolyLine(const std::vector<glm::vec2>& line){}

		void Color(float r, float g, float b, float a)
		{
			AUTO_PROFILE("gl::Color");
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