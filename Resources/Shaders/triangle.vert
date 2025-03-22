#version 330 core
layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 texCoords;

out vec3 out_color;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    //gl_Position = model * vec4(vertex_pos, 1.0);
    gl_Position = projection * view * model * vec4(vertex_pos, 1.0);
    out_color = in_color;
    TexCoord = texCoords;
}