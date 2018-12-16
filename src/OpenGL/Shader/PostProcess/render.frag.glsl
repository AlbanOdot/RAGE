#version 410 core
in vec2 vtexCoord;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedo;
uniform sampler2D ssao;

out vec4 color;

void main()
{

    vec3 lightCol = vec3(0.5);
    vec3 lightPos= vec3(1.0);
    // retrieve data from gbuffer
    vec3 FragPos = texture(position, vtexCoord).rgb;
    vec3 Normal = texture(normal, vtexCoord).rgb;
    vec3 Diffuse = texture(albedo, vtexCoord).rgb;
    float AmbientOcclusion = texture(ssao, vtexCoord).r;
    // blinn-phong (in view-space)
    vec3 lighting  = Diffuse * AmbientOcclusion;
    vec3 viewDir  = normalize(-FragPos); // viewpos is (0.0.0) in view-space
    // diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lightCol;
    // specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(Normal, halfwayDir), 0.0), 8.0);
    vec3 specular = lightCol * spec;
    // attenuation
    float dist = length(lightPos - FragPos);
    color = vec4(lighting + diffuse + specular, 1.0);
}
