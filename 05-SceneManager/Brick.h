#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

//#define ID_ANI_BRICK 10000
//#define ID_ANI_WOODBRICK 11000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject {
	int aniID;
public:
	//CBrick(float x, float y) : CGameObject(x, y) {}
	CBrick(float x, float y, int aniID) {
		this->aniID = aniID;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBreakable();
};