#version 120

varying vec2 UV;

uniform sampler2D renderedTexture;
uniform float time;

void main(){

	/*gl_FragColor = texture2D(renderedTexture, UV);
	if (gl_FragColor.r < 0.5 && gl_FragColor.g < 0.5 && gl_FragColor.b < 0.5) gl_FragColor.rgb = vec3(0,0,0);
	//gl_FragColor.rgb = 1 - gl_FragColor.rgb;*/

	//this will be our RGBA sum
    vec4 sum = vec4(0.0);

    //our original texcoord for this fragment
    vec2 tc = UV;

    //the amount to blur, i.e. how far off center to sample from 
    //1.0 -> blur by one pixel
    //2.0 -> blur by two pixels, etc.
    float blur = 0.005; 

    //the direction of our blur
    //(1.0, 0.0) -> x-axis blur
    //(0.0, 1.0) -> y-axis blur
    float hstep = 1.0;
    float vstep = 1.0;

    //apply blurring, using a 9-tap filter with predefined gaussian weights

    sum += texture2D(renderedTexture, vec2(tc.x - 4.0*blur*hstep, tc.y - 4.0*blur*vstep)) * 0.0162162162;
    sum += texture2D(renderedTexture, vec2(tc.x - 3.0*blur*hstep, tc.y - 3.0*blur*vstep)) * 0.0540540541;
    sum += texture2D(renderedTexture, vec2(tc.x - 2.0*blur*hstep, tc.y - 2.0*blur*vstep)) * 0.1216216216;
    sum += texture2D(renderedTexture, vec2(tc.x - 1.0*blur*hstep, tc.y - 1.0*blur*vstep)) * 0.1945945946;

    sum += texture2D(renderedTexture, vec2(tc.x, tc.y)) * 0.2270270270;

    sum += texture2D(renderedTexture, vec2(tc.x + 1.0*blur*hstep, tc.y + 1.0*blur*vstep)) * 0.1945945946;
    sum += texture2D(renderedTexture, vec2(tc.x + 2.0*blur*hstep, tc.y + 2.0*blur*vstep)) * 0.1216216216;
    sum += texture2D(renderedTexture, vec2(tc.x + 3.0*blur*hstep, tc.y + 3.0*blur*vstep)) * 0.0540540541;
    sum += texture2D(renderedTexture, vec2(tc.x + 4.0*blur*hstep, tc.y + 4.0*blur*vstep)) * 0.0162162162;

    //discard alpha for our simple demo, multiply by vertex color and return
    gl_FragColor = vec4(sum.rgb, 1.0);

	if (gl_FragColor.r < 0.5 && gl_FragColor.g < 0.5 && gl_FragColor.b < 0.5) discard;

}