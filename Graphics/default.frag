#version 330 core
in vec4 pos
out tPos

int main()
{
    gl_Position = pos;
    tPos = pos
}
