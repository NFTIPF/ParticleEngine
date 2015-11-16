
void main()
{
	gl_Position = gl_Vertex * gl_ModelViewProjectionMatrix;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_FrontColor = gl_Color;
}