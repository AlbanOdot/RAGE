#version 410 core
out vec4 color;

in vec2 vtexCoord;

uniform sampler2D screenTexture;

void main()
{
    vec3 col = texture(screenTexture, vtexCoord).rgb;
    float brightness = dot(col.rgb, vec3(0.2126, 0.7152, 0.0722));
    
    if(brightness > 1.0){
        color = vec4(col , 1.0);
    }else{
        color = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
