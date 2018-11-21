#version 410 core
in vec2 vtexCoord;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedo;
uniform sampler2D ssao;

//Lights property
uniform vec3 LiPosition[10];
uniform vec3 LiColor[10];
uniform int lightCount;

out vec4 color;
void main()
{
    // retrieve data from gbuffer
    vec3 FragPos = texture(position, vtexCoord).rgb;
    vec3 Normal = texture(normal, vtexCoord).rgb;
    vec3 Diffuse = texture(albedo, vtexCoord).rgb;
    float AmbientOcclusion = texture(ssao, vtexCoord).r;
    vec3 finalcol = vec3(0.,0.,0.);
    for(int i = 0; i < 3; ++i){
        // blinn-phong (in view-space)
        vec3 lighting  = Diffuse * AmbientOcclusion;
        vec3 viewDir  = normalize(-FragPos); // viewpos is (0.0.0) in view-space
        // diffuse
        vec3 lightDir = normalize(LiPosition[i] - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * LiColor[i];
        // specular
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 8.0);
        vec3 specular = LiColor[i] * spec;
        // attenuation
        float dist = length(LiPosition[i] - FragPos);
        float attenuation = 1.0 / (1.0 + dist + dist * dist);
        diffuse  *= attenuation;
        specular *= attenuation;
        finalcol += lighting + diffuse + specular;
    }

    color = vec4(finalcol, 1.0);
}
