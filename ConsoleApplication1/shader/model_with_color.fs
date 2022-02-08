#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform vec3 specular;


void main()
{    
    FragColor = vec4(specular,1.0);
}