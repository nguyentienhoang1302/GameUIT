#pragma once

#include "GameObject.h"

#define ID_ANI_STAGE_SELECT 210000

#define	STAGE_SELECT_WIDTH 234
#define STAGE_SELECT_BBOX_WIDTH 234
#define STAGE_SELECT_BBOX_HEIGHT 162

class CSSelect : public CGameObject {
	ULONGLONG timer = 0;
	ULONGLONG appear = GetTickCount64();
public:
	CSSelect(float x, float y) : CGameObject(x, y) {};
	void Render();
	//void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual int RenderPriority() { return 2; };
};