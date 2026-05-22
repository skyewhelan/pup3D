#version 460 core

#define MAX_POINT_LIGHTS 8

struct MaterialData
{
    sampler2D Texture; // Texture
    vec4 Albedo; // Base color applie over texture
    float AmbientMult; // How much the material is affected by ambient light
    float Roughness; // Affects how quickly light diffuses / how far it scatters
    float Shininess; // Strength of the specular highlight
};

struct PointLightData
{
    vec3 Position;
    vec3 Color;
    float LightStrength;
    float AmbientContribution;
    float AttenuationConstant;
    float AttenuationLinear;
    float AttenuationExponent;
};

in vec2 TexCoords;
in vec3 FragPosition;
in vec3 FragNormal;

uniform MaterialData Material;
uniform PointLightData PointLights[MAX_POINT_LIGHTS];
uniform int PointLightCount;
uniform vec3 CameraPosition;
uniform vec4 BaseAmbientLight;
uniform vec4 FogColor;
uniform int IsFogEnabled;

out vec4 FragColor;

vec3 CalculatePointLight(PointLightData _light)
{
    // Light
    vec3 Normal = normalize(FragNormal);
    vec3 LightDirection = normalize(FragPosition - _light.Position);

    // Ambient Light
    vec3 AmbientLight = (_light.Color * _light.AmbientContribution) * Material.AmbientMult;

    // Light Diffuse
    float DiffuseStrength = max(dot(Normal, -LightDirection), 0.0f);
    vec3 DiffuseLight = (_light.Color * _light.LightStrength) * DiffuseStrength * (1.0 - Material.Roughness);

    // Specular Light
    vec3 ReverseViewDirection = normalize(CameraPosition - FragPosition);
    vec3 Halfway = normalize(-LightDirection + ReverseViewDirection);
    float SpecularReflectivity = pow(max(dot(Normal, Halfway), 0.0f), 32);
    vec3 SpecularLight = Material.Shininess * SpecularReflectivity * _light.Color;

    // Attenuation
    float Distance = length(_light.Position - FragPosition);
    float Attenuation = _light.AttenuationConstant + (_light.AttenuationLinear * Distance) + (_light.AttenuationExponent * pow(Distance, 2));
    
    // Combine Lighting Data
    vec3 TotalLight = (AmbientLight + DiffuseLight + SpecularLight) / Attenuation;

    return TotalLight;
}

float CalculateFog()
{
    if (IsFogEnabled == 1)
    {
        float Distance = distance(FragPosition, CameraPosition);
        float FogAmount = (Distance - 20.0f) / 50.0f;
        return clamp(FogAmount, 0.0f, 1.0f);
    }
    return 0.0f;
}

void main()
{
    vec3 FinalLight = (BaseAmbientLight.rgb * BaseAmbientLight.a) * Material.AmbientMult;
    
    for (int i = 0; i < PointLightCount; i++)
    {
       FinalLight += CalculatePointLight(PointLights[i]); 
    }
    
    vec4 FinalColor = Material.Albedo * vec4(FinalLight, 1.0f) * texture(Material.Texture, TexCoords);
    FragColor = mix(FinalColor, FogColor, CalculateFog());
}