#version 330

uniform bool HasTextures;
uniform bool HasColors;
uniform bool HasNormals;

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

uniform sampler2D TextureID;

uniform vec4 AmbientLightColor;


in vec3 VertexPosition;
in vec4 VertexColor;
in vec3 VertexNormal;
in vec2 VertexTextureCoordinates;

out vec4 FragmentColor;
out vec2 FragmentTextureCoordinates;

void main()
{
	FragmentTextureCoordinates = VertexTextureCoordinates;
	
        vec4 workingColor = vec4(1.0,1.0,1.0,1.0);
        if(HasColors)
    {
    workingColor = VertexColor;
    }
        
        FragmentColor = workingColor * AmbientLightColor;
	
	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(VertexPosition, 1.0);
}
