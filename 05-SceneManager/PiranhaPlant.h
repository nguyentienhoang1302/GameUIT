#pragma once
#include "GameObject.h"

#define PIRANHAPLANT_BBOX_WIDTH 16
#define PIRANHAPLANT_BBOX_HEIGHT 26

#define ID_ANI_PIRANHAPLANT 139000

class CPPlant : public CGameObject
{
protected:
	ULONGLONG risetime;

	//bool settime = false;
	float y0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }

	virtual void Rise();
	virtual void Fall();

public:
	CPPlant(float x, float y);
	virtual void SetState(int state);
};