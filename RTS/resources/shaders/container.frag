#version 330 core
in vec3 ourColor;

in vec2 ourTexCoord;
uniform sampler2D ourTexture;

out vec4 color;

void main()
{
//    color = vec4(ourColor, 1.0f);
	color = texture(ourTexture, ourTexCoord);
}