#version 330 core

layout (location = 1) in vec2 tPos;

layout (location = 0) out vec4 color;

uniform sampler2D tex;

void main()
{
    color = texture(tex, tPos);
}
