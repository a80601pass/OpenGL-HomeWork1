// Model-View matrix and Projection matrix
// Orthogonal or Orthographic projection
// Windows Events - Keyboard & Mouse
// Rotate Rectangle

#include "header/Angel.h"
#include "Common/BackgroundStar_Big.h"
#include "Common/BackgroundStar_Small.h"
#include "Common/MyPlane.h"
#include "Common/Enemy.h"
#include "Common/Bullet.h"

#define SPACE_KEY 32

// 必須在 glewInit(); 執行完後,在執行物件實體的取得
// 宣告 Quad 指標物件，結束時記得釋放
//背景物件
BIGSTAR *g_BigStar1;
BIGSTAR *g_BigStar2;
BIGSTAR *g_BigStar3;
BIGSTAR *g_BigStar4;
BIGSTAR *g_BigStar5;
BIGSTAR *g_BigStar6;
SMALLSTAR *g_SmallStar1;
SMALLSTAR *g_SmallStar2;
SMALLSTAR *g_SmallStar3;
SMALLSTAR *g_SmallStar4;
SMALLSTAR *g_SmallStar5;
SMALLSTAR *g_SmallStar6;
SMALLSTAR *g_SmallStar7;
SMALLSTAR *g_SmallStar8;
float BigStar1Pos = 3;
float BigStar2Pos = -3;
float BigStar3Pos = 0.5;
float BigStar4Pos = -1;
float BigStar5Pos = -3.5;
float BigStar6Pos = 2.5;
float SmallStar1Pos = 0;
float SmallStar2Pos = 1;
float SmallStar3Pos = -2;
float SmallStar4Pos = -2.5;
float SmallStar5Pos = 2.5;
float SmallStar6Pos = 2;
float SmallStar7Pos = 0.6;
float SmallStar8Pos = 3.8;
float FlySpeed = 1;
//飛機
MYPLANE *g_MyPlane;
//敵機
EnemyTypeA *g_EnemyA;
EnemyTypeB *g_EnemyB;
bool g_EnemyAisAlreadyDeleteA = false;
bool g_EnemyAisAlreadyDeleteB = false;
//我的子彈
int BulletNumber = 100;
BULLET *g_MyBullet[100];
int ThisBullet = 0;

// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;

bool  GameStartFlag = false; // Controlled by Space Key
float g_TotTime = 0; //總時間

					 //----------------------------------------------------------------------------
					 // 函式的原型宣告
void IdleProcess();

void init(void)
{
	//  產生 projection 矩陣，此處為產生正投影矩陣
	g_mxProjection = Ortho(-2.5f, 2.5f, -4.0f, 4.0f, -2.0f, 2.0f);

	// 必須在 glewInit(); 執行完後,在執行物件實體的取得
	g_BigStar1 = new BIGSTAR;
	g_BigStar1->SetShader(g_mxModelView, g_mxProjection);
	g_BigStar1->SetTrans(1, 3);
	g_BigStar2 = new BIGSTAR;
	g_BigStar2->SetShader(g_mxModelView, g_mxProjection);
	g_BigStar2->SetTrans(-1.5, -3);
	g_BigStar3 = new BIGSTAR;
	g_BigStar3->SetShader(g_mxModelView, g_mxProjection);
	g_BigStar3->SetTrans(2.2, 0.5);
	g_BigStar4 = new BIGSTAR;
	g_BigStar4->SetShader(g_mxModelView, g_mxProjection);
	g_BigStar4->SetTrans(-1, -1);
	g_BigStar5 = new BIGSTAR;
	g_BigStar5->SetShader(g_mxModelView, g_mxProjection);
	g_BigStar5->SetTrans(1.7, -3.5);
	g_BigStar6 = new BIGSTAR;
	g_BigStar6->SetShader(g_mxModelView, g_mxProjection);
	g_BigStar6->SetTrans(-2, 2.5);
	g_SmallStar1 = new SMALLSTAR;
	g_SmallStar1->SetShader(g_mxModelView, g_mxProjection);
	g_SmallStar1->SetTrans(0, 0);
	g_SmallStar2 = new SMALLSTAR;
	g_SmallStar2->SetShader(g_mxModelView, g_mxProjection);
	g_SmallStar2->SetTrans(1, 1);
	g_SmallStar3 = new SMALLSTAR;
	g_SmallStar3->SetShader(g_mxModelView, g_mxProjection);
	g_SmallStar3->SetTrans(1.5, -2);
	g_SmallStar4 = new SMALLSTAR;
	g_SmallStar4->SetShader(g_mxModelView, g_mxProjection);
	g_SmallStar4->SetTrans(0.2, -2.5);
	g_SmallStar5 = new SMALLSTAR;
	g_SmallStar5->SetShader(g_mxModelView, g_mxProjection);
	g_SmallStar5->SetTrans(-0.3, 2.5);
	g_SmallStar6 = new SMALLSTAR;
	g_SmallStar6->SetShader(g_mxModelView, g_mxProjection);
	g_SmallStar6->SetTrans(-2.3, 2);
	g_SmallStar7 = new SMALLSTAR;
	g_SmallStar7->SetShader(g_mxModelView, g_mxProjection);
	g_SmallStar7->SetTrans(-1.7, 0.6);
	g_SmallStar8 = new SMALLSTAR;
	g_SmallStar8->SetShader(g_mxModelView, g_mxProjection);
	g_SmallStar8->SetTrans(-0.8, 3.8);

	g_MyPlane = new MYPLANE;
	g_MyPlane->SetShader(g_mxModelView, g_mxProjection);

	g_EnemyA = new EnemyTypeA;
	g_EnemyA->SetShader(g_mxModelView, g_mxProjection);
	g_EnemyA->SetTransAndRotate(g_EnemyA->EnemyAPosX, g_EnemyA->EnemyAPosY);

	g_EnemyB = new EnemyTypeB;
	g_EnemyB->SetShader(g_mxModelView, g_mxProjection);
	g_EnemyB->SetTransAndRotate(g_EnemyB->EnemyBPosX, g_EnemyB->EnemyBPosY);

	for (int i = 0; i < BulletNumber; i++) {
		g_MyBullet[i] = new BULLET;
		g_MyBullet[i]->SetShader(g_mxModelView, g_mxProjection);
	}

	glClearColor(0.0, 0.0, 0.0, 1.0); // black background
}
//----------------------------------------------------------------------------
void GameStart(float dt) {
	g_TotTime += dt;
	for (int i = 0; i < BulletNumber; i++) {
		if (g_EnemyAisAlreadyDeleteA == false)
		{
			g_EnemyA->DetectBullet(*g_MyBullet[i]);
			if ((g_EnemyA->CrashFlag) && g_EnemyAisAlreadyDeleteA == false)
			{
				delete g_EnemyA;
				g_MyBullet[i]->BulletHitFlag = true;
				g_EnemyAisAlreadyDeleteA = true;
			}
		}
	}
	for (int i = 0; i < BulletNumber; i++) {
		if (g_EnemyAisAlreadyDeleteB == false)
		{
			g_EnemyB->DetectBullet(*g_MyBullet[i]);
			if ((g_EnemyB->CrashFlag) && g_EnemyAisAlreadyDeleteB == false)
			{
				delete g_EnemyB;
				g_MyBullet[i]->BulletHitFlag = true;
				g_EnemyAisAlreadyDeleteB = true;
			}
		}
	}
	
	
}
//----------------------------------------------------------------------------
void BackGround(float dt) {
	BigStar1Pos -= dt * 2 * FlySpeed;
	BigStar2Pos -= dt * 2 * FlySpeed;
	BigStar3Pos -= dt * 2 * FlySpeed;
	BigStar4Pos -= dt * 2 * FlySpeed;
	BigStar5Pos -= dt * 2 * FlySpeed;
	BigStar6Pos -= dt * 2 * FlySpeed;
	SmallStar1Pos -= dt* FlySpeed;
	SmallStar2Pos -= dt* FlySpeed;
	SmallStar3Pos -= dt* FlySpeed;
	SmallStar4Pos -= dt* FlySpeed;
	SmallStar5Pos -= dt* FlySpeed;
	SmallStar6Pos -= dt* FlySpeed;
	SmallStar7Pos -= dt* FlySpeed;
	SmallStar8Pos -= dt* FlySpeed;
	g_BigStar1->SetTrans(1, BigStar1Pos);
	g_BigStar2->SetTrans(-1.5, BigStar2Pos);
	g_BigStar3->SetTrans(2.2, BigStar3Pos);
	g_BigStar4->SetTrans(-1, BigStar4Pos);
	g_BigStar5->SetTrans(1.7, BigStar5Pos);
	g_BigStar6->SetTrans(-2, BigStar6Pos);
	g_SmallStar1->SetTrans(0, SmallStar1Pos);
	g_SmallStar2->SetTrans(1, SmallStar2Pos);
	g_SmallStar3->SetTrans(1.5, SmallStar3Pos);
	g_SmallStar4->SetTrans(0.2, SmallStar4Pos);
	g_SmallStar5->SetTrans(-0.3, SmallStar5Pos);
	g_SmallStar6->SetTrans(-2.3, SmallStar6Pos);
	g_SmallStar7->SetTrans(-1.7, SmallStar7Pos);
	g_SmallStar8->SetTrans(-0.8, SmallStar8Pos);
	if (BigStar1Pos <= -4)BigStar1Pos = 4;
	if (BigStar2Pos <= -4)BigStar2Pos = 4;
	if (BigStar3Pos <= -4)BigStar3Pos = 4;
	if (BigStar4Pos <= -4)BigStar4Pos = 4;
	if (BigStar5Pos <= -4)BigStar5Pos = 4;
	if (BigStar6Pos <= -4)BigStar6Pos = 4;
	if (SmallStar1Pos <= -4)SmallStar1Pos = 4;
	if (SmallStar2Pos <= -4)SmallStar2Pos = 4;
	if (SmallStar3Pos <= -4)SmallStar3Pos = 4;
	if (SmallStar4Pos <= -4)SmallStar4Pos = 4;
	if (SmallStar5Pos <= -4)SmallStar5Pos = 4;
	if (SmallStar6Pos <= -4)SmallStar6Pos = 4;
	if (SmallStar7Pos <= -4)SmallStar7Pos = 4;
	if (SmallStar8Pos <= -4)SmallStar8Pos = 4;
}
//----------------------------------------------------------------------------
void PlaneMotion(int x, int y)
{
	g_MyPlane->PlaneX = 2.5f*(x - 320) / (320);
	g_MyPlane->PlaneY = -4.0f*(y - 512) / (512);
	g_MyPlane->SetTransAndRotate(g_MyPlane->PlaneX, g_MyPlane->PlaneY);
}
//----------------------------------------------------------------------------
void PlanePassiveMotion(int x, int y)
{
	g_MyPlane->PlaneX = 2.5f*(x - 320) / (320);
	g_MyPlane->PlaneY = -4.0f*(y - 512) / (512);
	g_MyPlane->SetTransAndRotate(g_MyPlane->PlaneX, g_MyPlane->PlaneY);
}
//----------------------------------------------------------------------------
void Fire(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
		if (state == GLUT_DOWN) {  // 目前的滑鼠狀態是按住
			if (g_MyBullet[ThisBullet]->BulletFlag == false)
			{
				g_MyBullet[ThisBullet]->BulletX = 2.5f*(x - 320) / (320);
				g_MyBullet[ThisBullet]->BulletY = -4.0f*(y - 512) / (512);
				g_MyBullet[ThisBullet]->BulletFlag = true;
			}
			ThisBullet += 1;
			if (ThisBullet >= BulletNumber)
			{
				ThisBullet = 0;
				for (int i = 0; i < BulletNumber / 2; i++) {
					g_MyBullet[i]->BulletFlag = false;
				}
			}
			if (ThisBullet == ((BulletNumber / 2) - 1))
			{
				for (int i = BulletNumber / 2; i < BulletNumber; i++) {
					g_MyBullet[i]->BulletFlag = false;
				}
			}
		}
		break;
	case GLUT_MIDDLE_BUTTON:  // 目前按下的是滑鼠中鍵
		if (state == GLUT_DOWN) {

		}
		break;
	case GLUT_RIGHT_BUTTON:   // 目前按下的是滑鼠右鍵
		if (state == GLUT_DOWN) {

		}
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------------
void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window
	g_BigStar1->Draw();
	g_BigStar2->Draw();
	g_BigStar3->Draw();
	g_BigStar4->Draw();
	g_BigStar5->Draw();
	g_BigStar6->Draw();
	g_SmallStar1->Draw();
	g_SmallStar2->Draw();
	g_SmallStar3->Draw();
	g_SmallStar4->Draw();
	g_SmallStar5->Draw();
	g_SmallStar6->Draw();
	g_SmallStar7->Draw();
	g_SmallStar8->Draw();
	g_MyPlane->Draw();
	g_EnemyA->Draw();
	g_EnemyB->Draw();
	for (int i = 0; i < BulletNumber; i++) {
		if (g_MyBullet[i]->BulletFlag)g_MyBullet[i]->Draw();
	}

	glutSwapBuffers();	// 交換 Frame Buffer
}
//----------------------------------------------------------------------------
void onFrameMove(float delta)
{
	if (GameStartFlag)
	{
		GameStart(delta);
		BackGround(delta);
	}
	for (int i = 0; i < BulletNumber; i++) {
		if (GameStartFlag && g_MyBullet[i]->BulletFlag)
		{
			if (g_MyBullet[i]->BulletHitFlag)
			{
				g_MyBullet[i]->BulletX = 0;
				g_MyBullet[i]->BulletY = 99;
				g_MyBullet[i]->BulletMotion(delta);
				g_MyBullet[i]->BulletHitFlag = false;
			}
			else g_MyBullet[i]->BulletMotion(delta * 2);
		}
	}

	GL_Display();
}
//----------------------------------------------------------------------------
void Win_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case  SPACE_KEY:
		GameStartFlag = !GameStartFlag;
		break;
	case 033:
		delete g_BigStar1;
		delete g_BigStar2;
		delete g_BigStar3;
		delete g_BigStar4;
		delete g_BigStar5;
		delete g_BigStar6;
		delete g_SmallStar1;
		delete g_SmallStar2;
		delete g_SmallStar3;
		delete g_SmallStar4;
		delete g_SmallStar5;
		delete g_SmallStar6;
		delete g_SmallStar7;
		delete g_SmallStar8;
		delete g_MyPlane;
		delete[] g_MyBullet;
		exit(EXIT_SUCCESS);
		break;
	}
}
//----------------------------------------------------------------------------
void GL_Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
}
//----------------------------------------------------------------------------
int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640, 1024);

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Draw two triangles");

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutMouseFunc(Fire);
	glutMotionFunc(PlaneMotion);
	glutPassiveMotionFunc(PlanePassiveMotion);
	glutKeyboardFunc(Win_Keyboard);	// 處理 ASCI 按鍵如 A、a、ESC 鍵...等等
	glutDisplayFunc(GL_Display);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);

	glutMainLoop();
	return 0;
}
