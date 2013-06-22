#version 330 core

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform vec2 texSize;
uniform vec2 halfImgSize;
uniform vec2 viewportSize;

in vec4 pos;
out vec2 tPos;

void main()
{
    vec4 imgPos = modelTransform * viewTransform * pos;
    imgPos.x *= halfImgSize.x / viewportSize.x;
    imgPos.y *= halfImgSize.y / viewportSize.y;

    imgPos.y *= -1;
    gl_Position = imgPos;

    vec2 texturePos = (pos + 1.f) / 2.f;
    texturePos.x *= texSize.x;
    texturePos.y *= texSize.y;
    tPos = texturePos;
}
