#version 330

layout (location = 0) in vec3 pos;

// uniform mat4 view;
// uniform mat4 proj;

uniform mat4 vp;

void main(){
    // gl_Position = proj * view * vec4(pos, 1.0);
    gl_Position = vp * vec4(pos, 1.0);
}
