#version 330 core

in vec3 FragmentColor;
in vec2 UV;

out vec3 Color;

uniform sampler2D TextureSampler;

void main()
{
	Color = texture(TextureSampler, UV).rgb;
}