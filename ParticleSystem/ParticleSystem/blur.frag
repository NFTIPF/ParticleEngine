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
	vec4 white = vec4(1, 1, 1, 1);
	vec4 deepColor = vec4(.8863, .3451, .1373, 1.0);//vec4(.8863, .3451, .1373, 1.0);
	vec4 highlightColor = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 deepPercent = deepColor/highlightColor;
	vec4 highlightPercent = highlightColor/deepColor;
	vec2 mousePos = vec2(mousePosition.x, 1080-mousePosition.y);
	vec2 mouseDelta = abs(gl_FragCoord.xy - mousePos);
	float mouseDistance = mouseDelta.x * mouseDelta.x + mouseDelta.y*mouseDelta.y;
	mouseDistance = clamp(sqrt(sqrt(mouseDistance))/100,.2, 200);

	//pixel = vec4(0, .001, 0, 255) * mouseDistance;
	//pixel.a = 255;
	vec4 locationTexture = texture2D(texture, xyCoord);
	vec4 finalDeepColor = deepColor * (1/locationTexture.a);
	vec4 finalHighlightColor = highlightColor * locationTexture.a;
	vec4 pixelMult = finalDeepColor + finalHighlightColor;
	pixel = locationTexture * pixelMult;
	
	//if(mouseDistance < 600)
	//{
	//	pixel.rgb += vec3(2.5, 2.5, 2.5);
	//}
	
    gl_FragColor = pixel;
}