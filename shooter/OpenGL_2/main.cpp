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
#include "Common/HealthIcon.h"
#include "Common/MyGuard.h"

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
float FlySpeed = 2;
//飛機
MYPLANE *g_MyPlane;
//防禦寮機
MYGUARD *g_MyGuard1;
MYGUARD *g_MyGuard2;
MYGUARD *g_MyGuard3;
MYGUARD *g_MyGuard4;
MYGUARD *g_MyGuard5;
MYGUARD *g_MyGuard6;
MYGUARD *g_MyGuard7;
MYGUARD *g_MyGuard8;
float g_GuardRot = 0;
//敵機
EnemyTypeA *g_EnemyA;
EnemyTypeB *g_EnemyB;
bool g_EnemyAisAlreadyDelete = false;
bool g_EnemyBisAlreadyDelete = false;
//我的子彈
int BulletNumber = 100;
BULLET *g_MyBullet[100];
int ThisBullet = 0;
//敵人子彈
BULLET *g_EnemyABullet[5];
int EnemyABulletNumber = 5;
int EnemyAThisBullet = 1;
//我的生命
HEALTHICON *g_MyHeart1;
HEALTHICON *g_MyHeart2;
bool FirstHeartIsDelete = false;
bool SecondHeartIsDelete = false;

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

	g_MyHeart1 = new HEALTHICON;
	g_MyHeart1->SetShader(g_mxModelView, g_mxProjection);
	g_MyHeart1->SetTrans(2.0, -3.5);
	g_MyHeart2 = new HEALTHICON;
	g_MyHeart2->SetShader(g_mxModelView, g_mxProjection);
	g_MyHeart2->SetTrans(2.3, -3.5);

	g_MyPlane = new MYPLANE;
	g_MyPlane->SetShader(g_mxModelView, g_mxProjection);

	g_MyGuard1 = new MYGUARD;
	g_MyGuard1->SetShader(g_mxModelView, g_mxProjection);
	g_MyGuard2 = new MYGUARD;
	g_MyGuard2->SetShader(g_mxModelView, g_mxProjection);
	g_MyGuard3 = new MYGUARD;
	g_MyGuard3->SetShader(g_mxModelView, g_mxProjection);
	g_MyGuard4 = new MYGUARD;
	g_MyGuard4->SetShader(g_mxModelView, g_mxProjection);
	g_MyGuard5 = new MYGUARD;
	g_MyGuard5->SetShader(g_mxModelView, g_mxProjection);
	g_MyGuard6 = new MYGUARD;
	g_MyGuard6->SetShader(g_mxModelView, g_mxProjection);
	g_MyGuard7 = new MYGUARD;
	g_MyGuard7->SetShader(g_mxModelView, g_mxProjection);
	g_MyGuard8 = new MYGUARD;
	g_MyGuard8->SetShader(g_mxModelView, g_mxProjection);

	g_EnemyA = new EnemyTypeA;
	g_EnemyA->SetShader(g_mxModelView, g_mxProjection);
	g_EnemyA->SetTrans(g_EnemyA->EnemyAPosX, g_EnemyA->EnemyAPosY);

	g_EnemyB = new EnemyTypeB;
	g_EnemyB->SetShader(g_mxModelView, g_mxProjection);
	g_EnemyB->SetTrans(g_EnemyB->EnemyBPosX, g_EnemyB->EnemyBPosY);

	for (int i = 0; i < BulletNumber; i++) {
		g_MyBullet[i] = new BULLET;
		g_MyBullet[i]->SetShader(g_mxModelView, g_mxProjection);
	}

	for (int i = 0; i < EnemyABulletNumber; i++) {
		g_EnemyABullet[i] = new BULLET;
		g_EnemyABullet[i]->SetShader(g_mxModelView, g_mxProjection);
		g_EnemyABullet[i]->BulletX = g_EnemyA->EnemyAPosX;
		g_EnemyABullet[i]->BulletY = g_EnemyA->EnemyAPosY;
	}
	
	glClearColor(0.0, 0.0, 0.0, 1.0); // black background
}
//----------------------------------------------------------------------------
void GameStart(float dt) {
	g_TotTime += dt;

	
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
	g_MyPlane->SetTrans(g_MyPlane->PlaneX, g_MyPlane->PlaneY);
}
//----------------------------------------------------------------------------
void PlanePassiveMotion(int x, int y)
{
	g_MyPlane->PlaneX = 2.5f*(x - 320) / (320);
	g_MyPlane->PlaneY = -4.0f*(y - 512) / (512);
	g_MyPlane->SetTrans(g_MyPlane->PlaneX, g_MyPlane->PlaneY);
}
//----------------------------------------------------------------------------
void MyGuardMotion(float dt)
{
	g_GuardRot += dt;
	if (g_GuardRot == 4)g_GuardRot = 0;
	g_MyGuard1->mxRT = Translate(g_MyPlane->PlaneX, g_MyPlane->PlaneY, 0);
	g_MyGuard2->mxRT = Translate(g_MyPlane->PlaneX, g_MyPlane->PlaneY, 0);
	g_MyGuard3->mxRT = Translate(g_MyPlane->PlaneX, g_MyPlane->PlaneY, 0);
	g_MyGuard4->mxRT = Translate(g_MyPlane->PlaneX, g_MyPlane->PlaneY, 0);
	g_MyGuard5->mxRT = Translate(g_MyPlane->PlaneX, g_MyPlane->PlaneY, 0);
	g_MyGuard6->mxRT = Translate(g_MyPlane->PlaneX, g_MyPlane->PlaneY, 0);
	g_MyGuard7->mxRT = Translate(g_MyPlane->PlaneX, g_MyPlane->PlaneY, 0);
	g_MyGuard8->mxRT = Translate(g_MyPlane->PlaneX, g_MyPlane->PlaneY, 0);

	g_MyGuard1->mxGT = Translate(-0.4, 0.4, 0);
	g_MyGuard2->mxGT = Translate(0.4, -0.4, 0);
	g_MyGuard3->mxGT = Translate(-0.4, -0.4, 0);
	g_MyGuard4->mxGT = Translate(0.4, 0.4, 0);
	g_MyGuard5->mxGT = Translate(0.4, 0, 0);
	g_MyGuard6->mxGT = Translate(-0.4, 0, 0);
	g_MyGuard7->mxGT = Translate(0, 0.4, 0);
	g_MyGuard8->mxGT = Translate(0, -0.4, 0);

	g_MyGuard1->mxGR = RotateZ(90 * g_GuardRot);
	g_MyGuard2->mxGR = RotateZ(90 * g_GuardRot);
	g_MyGuard3->mxGR = RotateZ(90 * g_GuardRot);
	g_MyGuard4->mxGR = RotateZ(90 * g_GuardRot);
	g_MyGuard5->mxGR = RotateZ(90 * g_GuardRot);
	g_MyGuard6->mxGR = RotateZ(90 * g_GuardRot);
	g_MyGuard7->mxGR = RotateZ(90 * g_GuardRot);
	g_MyGuard8->mxGR = RotateZ(90 * g_GuardRot);

	g_MyGuard1->GuardPos = g_MyGuard1->mxRT*g_MyGuard1->mxGR*g_MyGuard1->mxGT;
	g_MyGuard2->GuardPos = g_MyGuard2->mxRT*g_MyGuard2->mxGR*g_MyGuard2->mxGT;
	g_MyGuard3->GuardPos = g_MyGuard3->mxRT*g_MyGuard3->mxGR*g_MyGuard3->mxGT;
	g_MyGuard4->GuardPos = g_MyGuard4->mxRT*g_MyGuard4->mxGR*g_MyGuard4->mxGT;
	g_MyGuard5->GuardPos = g_MyGuard5->mxRT*g_MyGuard5->mxGR*g_MyGuard5->mxGT;
	g_MyGuard6->GuardPos = g_MyGuard6->mxRT*g_MyGuard6->mxGR*g_MyGuard6->mxGT;
	g_MyGuard7->GuardPos = g_MyGuard7->mxRT*g_MyGuard7->mxGR*g_MyGuard7->mxGT;
	g_MyGuard8->GuardPos = g_MyGuard8->mxRT*g_MyGuard8->mxGR*g_MyGuard8->mxGT;

	g_MyGuard1->SetTRSMatrix(g_MyGuard1->GuardPos);
	g_MyGuard2->SetTRSMatrix(g_MyGuard2->GuardPos);
	/*g_MyGuard3->SetTRSMatrix(g_MyGuard3->GuardPos);
	g_MyGuard4->SetTRSMatrix(g_MyGuard4->GuardPos);
	g_MyGuard5->SetTRSMatrix(g_MyGuard5->GuardPos);
	g_MyGuard6->SetTRSMatrix(g_MyGuard6->GuardPos);
	g_MyGuard7->SetTRSMatrix(g_MyGuard7->GuardPos);
	g_MyGuard8->SetTRSMatrix(g_MyGuard8->GuardPos);*/

	
}
//----------------------------------------------------------------------------
void GuardBullet()
{
	for (int i = 0; i < EnemyABulletNumber; i++) {
		if (((g_EnemyABullet[i]->BulletX >= (g_MyGuard1->GuardPos[0][3] - g_MyGuard1->HitRange)) && (g_EnemyABullet[i]->BulletX <= (g_MyGuard1->GuardPos[0][3] + g_MyGuard1->HitRange))) && ((g_EnemyABullet[i]->BulletY >= (g_MyGuard1->GuardPos[1][3] - g_MyGuard1->HitRange)) && (g_EnemyABullet[i]->BulletY <= (g_MyGuard1->GuardPos[1][3] + g_MyGuard1->HitRange))))
		{
			g_EnemyABullet[i]->BulletHitFlag = true;
		}
	}
	for (int i = 0; i < EnemyABulletNumber; i++) {
		if (((g_EnemyABullet[i]->BulletX >= (g_MyGuard2->GuardPos[0][3] - g_MyGuard2->HitRange)) && (g_EnemyABullet[i]->BulletX <= (g_MyGuard2->GuardPos[0][3] + g_MyGuard2->HitRange))) && ((g_EnemyABullet[i]->BulletY >= (g_MyGuard2->GuardPos[1][3] - g_MyGuard2->HitRange)) && (g_EnemyABullet[i]->BulletY <= (g_MyGuard2->GuardPos[1][3] + g_MyGuard2->HitRange))))
		{
			g_EnemyABullet[i]->BulletHitFlag = true;
		}
	}
	/*for (int i = 0; i < EnemyABulletNumber; i++) {
		if (((g_EnemyABullet[i]->BulletX >= (g_MyGuard3->GuardPos[0][3] - g_MyGuard3->HitRange)) && (g_EnemyABullet[i]->BulletX <= (g_MyGuard3->GuardPos[0][3] + g_MyGuard3->HitRange))) && ((g_EnemyABullet[i]->BulletY >= (g_MyGuard3->GuardPos[1][3] - g_MyGuard3->HitRange)) && (g_EnemyABullet[i]->BulletY <= (g_MyGuard3->GuardPos[1][3] + g_MyGuard3->HitRange))))
		{
			g_EnemyABullet[i]->BulletHitFlag = true;
		}
	}
	for (int i = 0; i < EnemyABulletNumber; i++) {
		if (((g_EnemyABullet[i]->BulletX >= (g_MyGuard4->GuardPos[0][3] - g_MyGuard4->HitRange)) && (g_EnemyABullet[i]->BulletX <= (g_MyGuard4->GuardPos[0][3] + g_MyGuard4->HitRange))) && ((g_EnemyABullet[i]->BulletY >= (g_MyGuard4->GuardPos[1][3] - g_MyGuard4->HitRange)) && (g_EnemyABullet[i]->BulletY <= (g_MyGuard4->GuardPos[1][3] + g_MyGuard4->HitRange))))
		{
			g_EnemyABullet[i]->BulletHitFlag = true;
		}
	}
	for (int i = 0; i < EnemyABulletNumber; i++) {
		if (((g_EnemyABullet[i]->BulletX >= (g_MyGuard5->GuardPos[0][3] - g_MyGuard5->HitRange)) && (g_EnemyABullet[i]->BulletX <= (g_MyGuard5->GuardPos[0][3] + g_MyGuard5->HitRange))) && ((g_EnemyABullet[i]->BulletY >= (g_MyGuard5->GuardPos[1][3] - g_MyGuard5->HitRange)) && (g_EnemyABullet[i]->BulletY <= (g_MyGuard5->GuardPos[1][3] + g_MyGuard5->HitRange))))
		{
			g_EnemyABullet[i]->BulletHitFlag = true;
		}
	}
	for (int i = 0; i < EnemyABulletNumber; i++) {
		if (((g_EnemyABullet[i]->BulletX >= (g_MyGuard6->GuardPos[0][3] - g_MyGuard6->HitRange)) && (g_EnemyABullet[i]->BulletX <= (g_MyGuard6->GuardPos[0][3] + g_MyGuard6->HitRange))) && ((g_EnemyABullet[i]->BulletY >= (g_MyGuard6->GuardPos[1][3] - g_MyGuard6->HitRange)) && (g_EnemyABullet[i]->BulletY <= (g_MyGuard6->GuardPos[1][3] + g_MyGuard6->HitRange))))
		{
			g_EnemyABullet[i]->BulletHitFlag = true;
		}
	}
	for (int i = 0; i < EnemyABulletNumber; i++) {
		if (((g_EnemyABullet[i]->BulletX >= (g_MyGuard7->GuardPos[0][3] - g_MyGuard7->HitRange)) && (g_EnemyABullet[i]->BulletX <= (g_MyGuard7->GuardPos[0][3] + g_MyGuard7->HitRange))) && ((g_EnemyABullet[i]->BulletY >= (g_MyGuard7->GuardPos[1][3] - g_MyGuard7->HitRange)) && (g_EnemyABullet[i]->BulletY <= (g_MyGuard7->GuardPos[1][3] + g_MyGuard7->HitRange))))
		{
			g_EnemyABullet[i]->BulletHitFlag = true;
		}
	}
	for (int i = 0; i < EnemyABulletNumber; i++) {
		if (((g_EnemyABullet[i]->BulletX >= (g_MyGuard8->GuardPos[0][3] - g_MyGuard8->HitRange)) && (g_EnemyABullet[i]->BulletX <= (g_MyGuard8->GuardPos[0][3] + g_MyGuard8->HitRange))) && ((g_EnemyABullet[i]->BulletY >= (g_MyGuard8->GuardPos[1][3] - g_MyGuard8->HitRange)) && (g_EnemyABullet[i]->BulletY <= (g_MyGuard8->GuardPos[1][3] + g_MyGuard8->HitRange))))
		{
			g_EnemyABullet[i]->BulletHitFlag = true;
		}
	}*/
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
void PlaneCrashCheck()
{
	for (int i = 0; i < EnemyABulletNumber; i++) {
		if (FirstHeartIsDelete == false)
		{
			if (((g_EnemyABullet[i]->BulletX >= (g_MyPlane->PlaneX - g_MyPlane->HitRange)) && (g_EnemyABullet[i]->BulletX <= (g_MyPlane->PlaneX + g_MyPlane->HitRange))) && ((g_EnemyABullet[i]->BulletY >= (g_MyPlane->PlaneY - g_MyPlane->HitRange)) && (g_EnemyABullet[i]->BulletY <= (g_MyPlane->PlaneY + g_MyPlane->HitRange))))
			{
				g_EnemyABullet[i]->BulletHitFlag = true;
				delete g_MyHeart1;
				FirstHeartIsDelete = true;
			}
			if (FirstHeartIsDelete)break;
		}
		
		for (int i = 0; i < EnemyABulletNumber; i++) {
			if (SecondHeartIsDelete == false)
			{
				if (((g_EnemyABullet[i]->BulletX >= (g_MyPlane->PlaneX - g_MyPlane->HitRange)) && (g_EnemyABullet[i]->BulletX <= (g_MyPlane->PlaneX + g_MyPlane->HitRange))) && ((g_EnemyABullet[i]->BulletY >= (g_MyPlane->PlaneY - g_MyPlane->HitRange)) && (g_EnemyABullet[i]->BulletY <= (g_MyPlane->PlaneY + g_MyPlane->HitRange))))
				{
					g_EnemyABullet[i]->BulletHitFlag = true;
					delete g_MyHeart2;
					SecondHeartIsDelete = true;
				}
				if (SecondHeartIsDelete)break;
			}
			for (int i = 0; i < EnemyABulletNumber; i++) {
				if (FirstHeartIsDelete && SecondHeartIsDelete)
				{
					if (((g_EnemyABullet[i]->BulletX >= (g_MyPlane->PlaneX - g_MyPlane->HitRange)) && (g_EnemyABullet[i]->BulletX <= (g_MyPlane->PlaneX + g_MyPlane->HitRange))) && ((g_EnemyABullet[i]->BulletY >= (g_MyPlane->PlaneY - g_MyPlane->HitRange)) && (g_EnemyABullet[i]->BulletY <= (g_MyPlane->PlaneY + g_MyPlane->HitRange))))
					{
						exit(EXIT_SUCCESS);
					}
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
void EnemyAFire()
{
	g_EnemyABullet[0]->BulletFlag = true;
	if (((g_EnemyABullet[EnemyAThisBullet]->BulletY) - (g_EnemyABullet[EnemyAThisBullet - 1]->BulletY)) >= 0.5)
	{
		g_EnemyABullet[EnemyAThisBullet]->BulletFlag = true;
		EnemyAThisBullet++;
	}
}
//----------------------------------------------------------------------------
void EnemyCrashCheck()
{
	for (int i = 0; i < BulletNumber; i++) {
		if (g_EnemyAisAlreadyDelete == false)
		{
			if (((g_MyBullet[i]->BulletX >= (g_EnemyA->EnemyAPosX - g_EnemyA->HitRange)) && (g_MyBullet[i]->BulletX <= (g_EnemyA->EnemyAPosX + g_EnemyA->HitRange))) && ((g_MyBullet[i]->BulletY >= (g_EnemyA->EnemyAPosY - g_EnemyA->HitRange)) && (g_MyBullet[i]->BulletY <= (g_EnemyA->EnemyAPosY + g_EnemyA->HitRange))))
			{
				g_EnemyA->HealthPoint = g_EnemyA->HealthPoint - g_MyBullet[i]->DamagePoint;
				g_MyBullet[i]->BulletHitFlag = true;
				if (g_EnemyA->HealthPoint == 0)
				{
					g_EnemyA->CrashFlag = true;
					if ((g_EnemyA->CrashFlag) && g_EnemyAisAlreadyDelete == false)
					{
						delete g_EnemyA;
						g_EnemyAisAlreadyDelete = true;
					}
				}
			}
		}
	}
	for (int i = 0; i < BulletNumber; i++) {
		if (g_EnemyBisAlreadyDelete == false)
		{
			if (((g_MyBullet[i]->BulletX >= (g_EnemyB->EnemyBPosX - g_EnemyB->HitRange)) && (g_MyBullet[i]->BulletX <= (g_EnemyB->EnemyBPosX + g_EnemyB->HitRange))) && ((g_MyBullet[i]->BulletY >= (g_EnemyB->EnemyBPosY - g_EnemyB->HitRange)) && (g_MyBullet[i]->BulletY <= (g_EnemyB->EnemyBPosY + g_EnemyB->HitRange))))
			{
				g_EnemyB->HealthPoint = g_EnemyB->HealthPoint - g_MyBullet[i]->DamagePoint;
				g_MyBullet[i]->BulletHitFlag = true;
				if (g_EnemyB->HealthPoint == 0)
				{
					g_EnemyB->CrashFlag = true;
					if ((g_EnemyB->CrashFlag) && g_EnemyBisAlreadyDelete == false)
					{
						delete g_EnemyB;
						g_EnemyBisAlreadyDelete = true;
					}
				}
			}
		}
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
	g_MyGuard1->Draw();
	g_MyGuard2->Draw();
	/*g_MyGuard3->Draw();
	g_MyGuard4->Draw();
	g_MyGuard5->Draw();
	g_MyGuard6->Draw();
	g_MyGuard7->Draw();
	g_MyGuard8->Draw();*/
	g_EnemyA->Draw();
	g_EnemyB->Draw();
	
	for (int i = 0; i < BulletNumber; i++) {
		if (g_MyBullet[i]->BulletFlag)g_MyBullet[i]->Draw();
	}

	for (int i = 0; i < EnemyABulletNumber; i++) {
		if (g_EnemyABullet[i]->BulletFlag)g_EnemyABullet[i]->Draw();
	}

	g_MyHeart1->Draw();
	g_MyHeart2->Draw();

	glutSwapBuffers();	// 交換 Frame Buffer
}
//----------------------------------------------------------------------------
void onFrameMove(float delta)
{
	if (GameStartFlag)
	{
		BackGround(delta);
		GameStart(delta);
		MyGuardMotion(delta);
		EnemyAFire();
		GuardBullet();
		PlaneCrashCheck();
		EnemyCrashCheck();

		for (int i = 0; i < BulletNumber; i++) {
			if (g_MyBullet[i]->BulletFlag)
			{
				if (g_MyBullet[i]->BulletHitFlag)
				{
					g_MyBullet[i]->BulletX = 0;
					g_MyBullet[i]->BulletY = 99;
					g_MyBullet[i]->MyBulletMotion(delta);
					g_MyBullet[i]->BulletHitFlag = false;
				}
				else g_MyBullet[i]->MyBulletMotion(delta * 2);
			}
		}//我的子彈控制

		for (int i = 0; i < EnemyABulletNumber; i++) {
			if (g_EnemyABullet[i]->BulletFlag)
			{
				if (g_EnemyABullet[i]->BulletHitFlag)
				{
					g_EnemyABullet[i]->BulletX = 0;
					g_EnemyABullet[i]->BulletY = 99;
					g_EnemyABullet[i]->MyBulletMotion(delta);
					g_EnemyABullet[i]->BulletHitFlag = false;
				}
				else g_EnemyABullet[i]->EnemyABulletMotion(delta * 2);
			}
		}//敵人A子彈控制

	}//遊戲腳本與背景

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