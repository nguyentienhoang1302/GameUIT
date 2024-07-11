#pragma once

#include "GameObject.h"

#define ID_ANI_INTRO_BACKGROUND 181000
#define ID_ANI_INTRO_BACKGROUND2 182000

#define	INTRO_BG_WIDTH 256
#define INTRO_BG_BBOX_WIDTH 256
#define INTRO_BG_BBOX_HEIGHT 224

#define INTRO_BG_STATE_1	100
#define INTRO_BG_STATE_2	200

class CIntrobackground : public CGameObject {
	ULONGLONG timer = 0;
public:
	CIntrobackground(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual int RenderPriority() { return 2; };
};