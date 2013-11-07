#version 420
layout(location=0) in vec3 v_position;
layout(location=1) in vec3 v_normal;
layout(location=2) in vec2 v_uv;

uniform GMatrices
{
    mat4 mvpMatrix;
    mat4 mvMatrix;
    mat4 normalMatrix;
};

out vec3 f_position;
out vec3 f_normal;
out vec2 f_uv;

void main(void)
{
    f_uv = v_uv;
    f_position = (mvMatrix * vec4(v_position,1.0)).xyz;
    f_normal = normalize(normalMatrix * vec4(v_normal,1.0)).xyz;
    gl_Position = mvpMatrix * vec4(v_position, 1.0);
}
