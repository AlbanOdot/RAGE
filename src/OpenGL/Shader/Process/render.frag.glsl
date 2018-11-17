#version 410 core

in vec2 vtexCoord;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedo;
uniform sampler2D ssao;

out vec4 color;

void main(){
    //color = texture(ssao,vtexCoord).r * texture(albedo,vtexCoord);
    color = vec4(0.2);
}
