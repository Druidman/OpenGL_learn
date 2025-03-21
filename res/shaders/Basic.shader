#shader vertex
#version 460 core

layout(location=0) in vec4 position;
layout(location=2) in float tex_index;
layout(location=3) in vec2 tex_Coords;

out float v_tex_index;
out vec2 v_tex_Coords;

uniform mat4 u_MVP;

void main(){
    gl_Position = u_MVP * position;
    v_tex_index = tex_index;
    v_tex_Coords = tex_Coords;
};



#shader fragment
#version 460 core

layout(location=0) out vec4 color;

in vec2 v_tex_Coords;
in float v_tex_index;

uniform sampler2D u_Texture[2];

void main(){
    int index = int(v_tex_index);
    vec4 texColor = texture(u_Texture[index], v_tex_Coords);
    color = texColor;
};
