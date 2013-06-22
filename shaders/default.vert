#version 330 core

uniform mat4 modelTransform;
uniform vec4 viewTransform;
uniform vec2 halfTexSize;
uniform vec2 halfImgSize;
uniform vec2 viewportSize;

in  vec4 vertex;
out vec4 tPos;

void main()
{
    imgPos = vertex * halfImgSize;

    gl_Position = modelTransform*viewTransform*imgPos;

    tPos = vertex * halfTexSize;
}
