#version 330 core

uniform vec2 tex_scale;
uniform vec4 tex_clip;
layout (location = 1) in vec2 tex_pos;

layout (location = 0) out vec4 color;

uniform sampler2D tex;

void main()
{
    vec2 adjusted_coord = tex_pos;
    vec2 clip_trans = tex_clip.xy;
    vec2 clip_scale = tex_clip.zw;

    adjusted_coord.xy *= clip_scale.xy;
    adjusted_coord.xy += clip_trans.xy;
    adjusted_coord.xy *= (1 / tex_scale.xy);
    //adjusted_coord.y *= (1 / tex_scale.y);
    color = texture(tex, adjusted_coord);
}
