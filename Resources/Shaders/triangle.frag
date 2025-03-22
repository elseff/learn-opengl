#version 330 core
in vec3 out_color;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec4 uniform_color;
uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord) + (vec4(uniform_color.x, out_color.yz,0.3f))*0.3f;
    //FragColor = texture(ourTexture, TexCoord);
}