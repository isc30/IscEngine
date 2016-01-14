#version 120

void main(){
	//gl_FragColor = vec4(gl_FragCoord.z, 0.f, 0.f, 1.f);
	gl_FragDepth = gl_FragCoord.z;
}