# version 130        // 对应opengl版本 3.0
varying vec4 vColor;

void main () {
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	//gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	//gl_Position = ftransform();
	
	vColor = gl_Color;
}
