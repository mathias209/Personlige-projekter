#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 textColor;
uniform sampler2D ourTexture;

void main()
{
    vec4 outColor = texture(ourTexture, TexCoord) * textColor;
    if (outColor.a < 0.1)
	discard;
    FragColor = outColor;

}
