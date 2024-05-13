#version 330

layout (points) in;
layout (triangle_strip, max_vertices = 6) out;

uniform mat4 vp;
uniform float halflength;

void main(){
    // btm left
    gl_Position = gl_in[0].gl_Position + vec4(-halflength, -halflength, 0.0, 1.0);
    EmitVertex();

    // top left
    gl_Position = gl_in[0].gl_Position + vec4(-halflength,  halflength, 0.0, 1.0);
    EmitVertex();

    // top right
    gl_Position = gl_in[0].gl_Position + vec4( halflength,  halflength, 0.0, 1.0);
    EmitVertex();

    EndPrimitive();

    // btm left
    gl_Position = gl_in[0].gl_Position + vec4(-halflength, -halflength, 0.0, 1.0);
    EmitVertex();

    // top right
    gl_Position = gl_in[0].gl_Position + vec4( halflength,  halflength, 0.0, 1.0);
    EmitVertex();

    // btm right
    gl_Position = gl_in[0].gl_Position + vec4( halflength, -halflength, 0.0, 1.0);
    EmitVertex();

    EndPrimitive();
}
