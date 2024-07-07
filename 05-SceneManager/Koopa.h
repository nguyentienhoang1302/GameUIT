#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_VY_JUMP 0.08f
#define KOOPA_VY_JUMP_MAX 0.40f
#define KOOPA_SPINNING_SPEED 0.25f

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_HEIGHT_SHELL 14
#define KOOPA_BBOX_WIDTH_WINGED 20
#define KOOPA_BBOX_HEIGHT_WINGED 24

#define KOOPA_DIE_TIMEOUT 500

#define KOOPA_STATE_WALK 100
#define KOOPA_STATE_SHELL 200
#define KOOPA_STATE_SPIN 300
#define KOOPA_STATE_WINGED_WALK 400
#define KOOPA_STATE_WINGED_JUMP 500
#define KOOPA_STATE_RED_WALK 600
#define KOOPA_STATE_RED_SHELL 700
#define KOOPA_STATE_RED_SPIN 800

#define ID_ANI_KOOPA_WALK 31000
#define ID_ANI_KOOPA_SHELL 32000
#define ID_ANI_KOOPA_SPIN 33000
#define ID_ANI_KOOPA_WINGED_WALK 34000
#define ID_ANI_KOOPA_WINGED_JUMP 35000
#define ID_ANI_KOOPA_RED_WALK 36000
#define ID_ANI_KOOPA_RED_SHELL 37000
#define ID_ANI_KOOPA_RED_SPIN 38000

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	int jumpTimer;

	ULONGLONG die_start;
	ULONGLONG walk_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y, int type);
	virtual void SetState(int state);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMBlock(LPCOLLISIONEVENT e);

	virtual void SpinLeft();
	virtual void SpinRight();
};