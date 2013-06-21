#version 330 core

in vec4 tPos
uniform sampler2D tex

int main()
{
   gl_Color = texture(tex, tPos);
}
