#version 150

uniform bool HasTextures;
uniform bool HasColors;
uniform bool HasNormals;

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

uniform smapler2D TextureID;

in vec3 VertexPosition;
in vec4 VertexColor;
in vec3 VertexNormal;
in vec2 VertexTextureCoordinates;

out vec4 FragmentColor;
out vec2 FragmentTextureCoordinates;

void main()
{
	FragmentTextureCoordinates = VertexTextureCoordinates;
	FragmentColor = VertexColor;
	
	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(VertexPosition, 1.0);
}