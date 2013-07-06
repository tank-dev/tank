#version 140

uniform mat4 pvm;

in vec4 v_pos;
in vec2 v_tex_pos;
out vec2 tex_pos;

void main()
{
    gl_Position = pvm * v_pos;
    tex_pos = v_tex_pos;
}
