#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_VY_JUMP 0.08f
#define GOOMBA_VY_JUMP_MAX 0.40f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 14
#define GOOMBA_BBOX_WIDTH_WINGED 20
#define GOOMBA_BBOX_HEIGHT_WINGED 19

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define GOOMBA_STATE_WINGED_WALK 300
#define GOOMBA_STATE_WINGED_JUMP 400

#define ID_ANI_GOOMBA_WALKING 21000
#define ID_ANI_GOOMBA_DIE 22000
#define ID_ANI_GOOMBA_WINGED_WALK 23000
#define ID_ANI_GOOMBA_WINGED_JUMP 24000

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 
	int jumpTimer;

	ULONGLONG die_start;
	ULONGLONG walk_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y, int type);	//type: 1 - Goomba, 2 - Para-Goomba
	virtual void SetState(int state);
};