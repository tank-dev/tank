#version 330 core

uniform vec2 tex_aspect;
layout (location = 1) in vec2 tex_pos;

layout (location = 0) out vec4 color;

uniform sampler2D tex;

void main()
{
    vec2 adjusted_coord;
    adjusted_coord.x = tex_pos.x * (1/ tex_aspect.x);
    adjusted_coord.y = tex_pos.y * (1 / tex_aspect.y);
    color = texture(tex, adjusted_coord);
}
