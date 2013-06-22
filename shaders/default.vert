#version 330 core

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform vec2 halfImgSize;
uniform vec2 viewportSize;

in vec4 pos;
in vec2 tPos;
out vec2 texturePosOut;

void main()
{
    vec4 imgPos = modelTransform * viewTransform * pos;
    imgPos.x *= halfImgSize.x / viewportSize.x;
    imgPos.y *= halfImgSize.y / viewportSize.y;
    
    imgPos.y *= -1;
    gl_Position = imgPos;

    texturePosOut = tPos;
}
