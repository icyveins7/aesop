#version 330

out vec4 FragColor;

// We need to make each square a colour from
// the geometry shader

void main(){
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
