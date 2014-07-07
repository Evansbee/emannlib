#version 150

uniform bool HasTextures;
uniform bool HasColors;
uniform bool HasNormals;

uniform smapler2D TextureID;

in vec4 FragmentColor;
in vec2 FragmentTextureCoordinates;

out vec4 ScreenColor;

void main()
{
	if(HasTextures)
	{
		ScreenColor = texture(Texture, FragmentTextureCoordinates);
	}
	else if(HasColors)
	{
		ScreenColor = FragmentColor;
	}	
	else
	{
		ScreenColor = vec4(1.0,1.0,1.0,1.0);
	}
}