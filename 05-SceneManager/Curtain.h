#pragma once

#include "GameObject.h"

#define ID_ANI_CURTAIN 191000

#define	CURTAIN_WIDTH 256
#define CURTAIN_BBOX_WIDTH 256
#define CURTAIN_BBOX_HEIGHT 186

class CCurtain : public CGameObject {
	ULONGLONG timer = 0;
	ULONGLONG appear = GetTickCount64();
public:
	CCurtain(float x, float y) : CGameObject(x, y) {};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual int RenderPriority() { return 2; };
};