#pragma once


#include "GameObject.h"
//Gift types in GiftSelect
#define ID_ANI_MUSHROOM_RED 110000
#define ID_ANI_MUSHROOM_GREEN 111000
#define ID_ANI_LEAF_FALLLEFT	171000

#define	GSELECT_WIDTH 16
#define GSELECT_BBOX_WIDTH 16
#define GSELECT_BBOX_HEIGHT 16

//Each stage is each type of gift
#define GSELECT_STATE_1	100
#define GSELECT_STATE_2	200
#define GSELECT_STATE_3	300

class CGSelect : public CGameObject {
	ULONGLONG timer = 0;
public:
	CGSelect(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	virtual int RenderPriority() { return 2; };
};
