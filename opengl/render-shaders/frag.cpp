#version 130 // 对应opengl版本 3.0
varying vec4 vColor;

void main () {
	gl_FragColor = vColor;
}
