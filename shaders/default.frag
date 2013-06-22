#version 330 core

in vec2 tPos;
uniform sampler2D tex;

out vec4 color;

void main()
{
    color = texture(tex, tPos);
    //color = vec4(0.f,1.f,0.f,1.0f);//texture(tex, tPos);
}
