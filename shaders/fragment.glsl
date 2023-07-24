#version 330 core
out vec4 FragColor;
in vec3 ourColor;

uniform float phase;

void main()
{
    FragColor = vec4(ourColor.x / phase, ourColor.y / phase, ourColor.z / phase, 1.0);
//    FragColor = vec4(ourColor.x / phase, ourColor.y / phase, ourColor.z / phase, 1.0);
}