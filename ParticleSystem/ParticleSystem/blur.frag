uniform sampler2D texture;
//uniform float blur_radius;
uniform vec2 resolution;
uniform vec2 mousePosition;

void main()
{
	vec2 xyCoord = (gl_FragCoord.xy/resolution.xy);
	
	vec4 pixel = vec4(0.0);
	//origin
	//pixel += texture2D(texture, xyCoord + vec2(0,0)) * .333;
	//first straign
	//pixel += texture2D(texture, xyCoord + vec2(0,1)) * .111;
	//pixel += texture2D(texture, xyCoord + vec2(1,0)) * .111;
	//pixel += texture2D(texture, xyCoord + vec2(0,-1)) * .111;
	//pixel += texture2D(texture, xyCoord + vec2(-1,0)) * .111;
	//fist diagonals
	//pixel += texture2D(texture, xyCoord + vec2(1,1)) * .05;
	//pixel += texture2D(texture, xyCoord + vec2(1,-1)) * .05;
	//pixel += texture2D(texture, xyCoord + vec2(-1,1)) * .05;	
	//pixel += texture2D(texture, xyCoord + vec2(-1,-1)) * .05;
	//second straight
	//pixel += texture2D(texture, xyCoord + vec2(0,2)) * .013;
	//pixel += texture2D(texture, xyCoord + vec2(0,-2)) * .013;
	//pixel += texture2D(texture, xyCoord + vec2(2,0)) * .013;
	//pixel += texture2D(texture, xyCoord + vec2(-2,0)) * .013;
	//second semi-diag
	//pixel += texture2D(texture, xyCoord + vec2(1,2)) * .007;
	//pixel += texture2D(texture, xyCoord + vec2(1,-2)) * .007;
	//pixel += texture2D(texture, xyCoord + vec2(-1,2)) * .007;
	//pixel += texture2D(texture, xyCoord + vec2(-1,-2)) * .007;
	//pixel += texture2D(texture, xyCoord + vec2(2,1)) * .007;
	//pixel += texture2D(texture, xyCoord + vec2(-2,1)) * .007;
	//pixel += texture2D(texture, xyCoord + vec2(2,-1)) * .007;
	//pixel += texture2D(texture, xyCoord + vec2(-2,-1)) * .007;

	//vec4 pixel = vec4(0.0, 0.0, 0.0, 0.0);
	//for(int i = 0;i < blur_radius;i++)
	//{
	//	for(int ii = 0;ii<blur_radius;ii++)
	//	{
	//		pixel += texture2D(texture, xyCoord + vec2(i,ii));
	//	}
	//}
	//float br = blur_radius;
	//pixel /= 21;
	//pixel += texture2d(texture, xyCoord);
	
	//pixel /= 2;
	vec4 white = vec4(255, 255, 255, 255);
	vec4 fireColor = vec4(226, 88, 34, 255);
	vec4 firePercent = fireColor/white;
	
	vec2 mouseDelta = mousePosition - xyCoord;
	float mouseDistance2 = mouseDelta.x * mouseDelta.x + mouseDelta.y*mouseDelta.y;
	mouseDistance2 = 1/mouseDistance2;
	pixel = texture2D(texture, xyCoord)*firePercent;
	if(mouseDistance2 > .001)
	{
		pixel += white*mouseDistance2;
	}
	
    gl_FragColor = pixel;
}