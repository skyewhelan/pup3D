#version 460 core


in vec2 TexCoords;
in vec3 FragPosition;
in vec3 FragNormal;

out vec4 FragColor;

void main()
{

    //FragColor = vec4(1 - FragNormal.x, 1 - FragNormal.y, 1 - FragNormal.z, 1.0f);
    vec3 rgbNormal = FragNormal * 0.5 + 0.5;
    FragColor = vec4(rgbNormal, 1.0);
    //FragColor = vec4(FragNormal, 1.0f);
}