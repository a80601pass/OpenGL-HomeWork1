#version 130
in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform float fTransX;
uniform float fTransY;
uniform float fScale;

void main()
{
	mat4 mxTrans = mat4(
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1);

	mxTrans[3][0] = fTransX;
	mxTrans[3][1] = fTransY;


	mat4 mxScale = mat4( 
	1, 0, 0 ,0,
	0, 1, 0 ,0,
	0, 0, 1 ,0,
	0, 0, 0 ,1);

	mxScale[0][0] = fScale;
	mxScale[1][1] = fScale;

    gl_Position = Projection * ModelView * mxTrans * vPosition;
	color = vColor;
}