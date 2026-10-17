#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec3 translate;
uniform vec3 scale;

// scale is a constant
uniform vec2 texScale;
uniform vec2 texTranslate;

void main()
{
    mat4 transmat = mat4(
	    1.0, 0.0, 0.0, 0.0,
	    0.0, 1.0, 0.0, 0.0,
	    0.0, 0.0, 1.0, 0.0,
	    translate.x, translate.y, translate.z, 1.0
	    );
    mat4 scalemat = mat4(
	    scale.x, 0.0, 0.0, 0.0,
	    0.0, scale.y, 0.0, 0.0,
	    0.0, 0.0, scale.z, 0.0,
	    0.0, 0.0, 0.0, 1.0
	    );

    gl_Position = transmat * scalemat * vec4(aPos, 1.0);

    mat3 texTrans = mat3(
	    1.0, 0.0, 0.0,
	    0.0, 1.0, 0.0,
	    texTranslate.x, texTranslate.y, 1.0
	    );

    mat3 texScale = mat3(
	    texScale.x, 0.0, 0.0,
	    0.0, texScale.y, 0.0,
	    0.0, 0.0, 1.0
	    );

    vec3 transTexCoord = texTrans * texScale * vec3(aTexCoord, 1.0);

    TexCoord = vec2(transTexCoord.x, transTexCoord.y);
}
