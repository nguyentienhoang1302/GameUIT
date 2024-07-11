#pragma once

#include "GameObject.h"

#define ID_ANI_TITLE 200000

#define	TITLE_WIDTH 256
#define TITLE_BBOX_WIDTH 256
#define TITLE_BBOX_HEIGHT 186

class CTitle : public CGameObject {
	ULONGLONG timer = 0;
	ULONGLONG appear = GetTickCount64();
public:
	CTitle(float x, float y) : CGameObject(x, y) {};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual int RenderPriority() { return 2; };
};