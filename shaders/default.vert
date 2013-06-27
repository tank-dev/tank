#version 330 core

uniform mat4 pvm;

in vec4 v_pos;
in vec2 v_tex_pos;
layout (location = 1) out vec2 tex_pos;

void main()
{
    gl_Position = pvm * v_pos;
    tex_pos = v_tex_pos;
}
