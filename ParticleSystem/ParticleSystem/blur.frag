uniform sampler2D texture;
uniform float blur_radius;
uniform vec2 resolution;

void main()
{
	vec2 xyCoord = (gl_FragCoord.xy/resolution.xy);
	
	vec4 pixel = vec4(0.0);
	//origin
	pixel += texture2D(texture, xyCoord + vec2(0,0)) * .225;
	//first straign
	pixel += texture2D(texture, xyCoord + vec2(0,1)) * .111;
	pixel += texture2D(texture, xyCoord + vec2(1,0)) * .111;
	pixel += texture2D(texture, xyCoord + vec2(0,-1)) * .111;
	pixel += texture2D(texture, xyCoord + vec2(-1,0)) * .111;
	//fist diagonals
	pixel += texture2D(texture, xyCoord + vec2(1,1)) * .055;
	pixel += texture2D(texture, xyCoord + vec2(1,-1)) * .055;
	pixel += texture2D(texture, xyCoord + vec2(-1,1)) * .055;	
	pixel += texture2D(texture, xyCoord + vec2(-1,-1)) * .055;
	//second straight
	pixel += texture2D(texture, xyCoord + vec2(0,2)) * .013;
	pixel += texture2D(texture, xyCoord + vec2(0,-2)) * .013;
	pixel += texture2D(texture, xyCoord + vec2(2,0)) * .013;
	pixel += texture2D(texture, xyCoord + vec2(-2,0)) * .013;
	//second semi-diag
	pixel += texture2D(texture, xyCoord + vec2(1,2)) * .007;
	pixel += texture2D(texture, xyCoord + vec2(1,-2)) * .007;
	pixel += texture2D(texture, xyCoord + vec2(-1,2)) * .007;
	pixel += texture2D(texture, xyCoord + vec2(-1,-2)) * .007;
	pixel += texture2D(texture, xyCoord + vec2(2,1)) * .007;
	pixel += texture2D(texture, xyCoord + vec2(-2,1)) * .007;
	pixel += texture2D(texture, xyCoord + vec2(2,-1)) * .007;
	pixel += texture2D(texture, xyCoord + vec2(-2,-1)) * .007;

	//vec4 pixel = vec4(0.0, 0.0, 0.0, 0.0);
	//for(int i = 0;i < blur_radius;i++)
	//{
	//	for(int ii = 0;ii<blur_radius;ii++)
	//	{
	//		pixel += texture2D(texture, xyCoord + vec2(i,ii));
	//	}
	//}
	float br = blur_radius;
	pixel /= 21;
	//pixel += texture2d(texture, xyCoord);
	//pixel /= 2;
	
	
    gl_FragColor = pixel;
}