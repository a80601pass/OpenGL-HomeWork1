#ifndef ENEMY_A_H
#define ENEMY_A_H
#include "../Header/Angel.h"
#include "Bullet.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 6

class ENEMY_A
{
private:
	vec4 m_Points[QUAD_NUM];
	vec4 m_Colors[QUAD_NUM];
	// VAO
	GLuint m_uiVao;
	// VBO
	GLuint m_uiBuffer;
	//  for Shader
	GLuint m_uiProgram;
	// Vertex Position Attribute
	GLuint m_uiModelView, m_uiProjection;
	//位移
	GLuint m_uiTransX, m_uiTransY;
	//旋轉
	GLuint m_uiRotate;
	// Matrix 
	mat4 m_mxView, m_mxProjection;
	mat4 m_mxMVFinal, m_mxTRS;

	// 紀錄是否有矩陣的更新
	bool  m_bUpdateMV;
	bool  m_bUpdateProj;

	void CreateBufferObject();
public:
	ENEMY_A();

	float EnemyAPosX = 0;
	float EnemyAPosY = 3.5;
	float HitRange = 0.1;
	bool CrashFlag = false;

	void SetShader(mat4 &mxModelView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return m_uiProgram; }
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);
	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4]); // Single color
	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color
	void SetTransAndRotate(float fTransX, float fTransY);
	void SetTransAndRotate(float fTransX, float fTransY, float fAngle);
	void DetectBullet(BULLET MyBullet);

	void Draw();
	void DrawW();
};




#endif