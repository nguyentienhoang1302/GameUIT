#pragma once
#include "GameObject.h"

#define FIREPIRANHAPLANT_BBOX_WIDTH 16
#define FIREPIRANHAPLANT_BBOX_HEIGHT_GREEN 26
#define FIREPIRANHAPLANT_BBOX_HEIGHT_RED 34

//#define FIREPIRANHAPLANT_STATE_GREEN_BL_SHOOT 100
//#define FIREPIRANHAPLANT_STATE_GREEN_BL_IDLE 200
//#define FIREPIRANHAPLANT_STATE_GREEN_TL_SHOOT 300
//#define FIREPIRANHAPLANT_STATE_GREEN_TL_IDLE 400
//#define FIREPIRANHAPLANT_STATE_GREEN_TR_SHOOT 500
//#define FIREPIRANHAPLANT_STATE_GREEN_TR_IDLE 600
//#define FIREPIRANHAPLANT_STATE_GREEN_BR_SHOOT 700
//#define FIREPIRANHAPLANT_STATE_GREEN_BR_IDLE 800
//
//#define FIREPIRANHAPLANT_STATE_RED_BL_SHOOT 110
//#define FIREPIRANHAPLANT_STATE_RED_BL_IDLE 210
//#define FIREPIRANHAPLANT_STATE_RED_TL_SHOOT 310
//#define FIREPIRANHAPLANT_STATE_RED_TL_IDLE 410
//#define FIREPIRANHAPLANT_STATE_RED_TR_SHOOT 510
//#define FIREPIRANHAPLANT_STATE_RED_TR_IDLE 610
//#define FIREPIRANHAPLANT_STATE_RED_BR_SHOOT 710
//#define FIREPIRANHAPLANT_STATE_RED_BR_IDLE 810

#define FIREPIRANHAPLANT_STATE_WAIT 000
#define FIREPIRANHAPLANT_STATE_TL 100
#define FIREPIRANHAPLANT_STATE_TR 200
#define FIREPIRANHAPLANT_STATE_BL 300
#define FIREPIRANHAPLANT_STATE_BR 400

#define ID_ANI_PIRANHAPLANT_WAIT 130000

#define ID_ANI_PIRANHAPLANT_GREEN_BL_SHOOT 131100
#define ID_ANI_PIRANHAPLANT_GREEN_BL_IDLE 132100
#define ID_ANI_PIRANHAPLANT_GREEN_TL_SHOOT 133100
#define ID_ANI_PIRANHAPLANT_GREEN_TL_IDLE 134100
#define ID_ANI_PIRANHAPLANT_GREEN_TR_SHOOT 136100
#define ID_ANI_PIRANHAPLANT_GREEN_TR_IDLE 135100
#define ID_ANI_PIRANHAPLANT_GREEN_BR_SHOOT 138100
#define ID_ANI_PIRANHAPLANT_GREEN_BR_IDLE 137100

#define ID_ANI_PIRANHAPLANT_RED_BL_SHOOT 131000
#define ID_ANI_PIRANHAPLANT_RED_BL_IDLE 132000
#define ID_ANI_PIRANHAPLANT_RED_TL_SHOOT 133000
#define ID_ANI_PIRANHAPLANT_RED_TL_IDLE 134000
#define ID_ANI_PIRANHAPLANT_RED_TR_SHOOT 136000
#define ID_ANI_PIRANHAPLANT_RED_TR_IDLE 135000
#define ID_ANI_PIRANHAPLANT_RED_BR_SHOOT 138000
#define ID_ANI_PIRANHAPLANT_RED_BR_IDLE 137000

class CFPlant : public CGameObject
{
protected:
	ULONGLONG risetime;

	float y0;
	int type;
	bool isShooting = false;
	bool isStart = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; };

	virtual void Rise();
	virtual void Fall();
	virtual void Shoot();

public:
	CFPlant(float x, float y, int type); //1 - Green, 2 - Red
	virtual void SetState(int state);
};