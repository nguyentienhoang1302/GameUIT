#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_GROUND1 60000
#define GROUD1_WIDTH 16
#define GROUND1_BBOX_WIDTH 16
#define GROUND1_BBOX_HEIGHT 16

class CGround1 : public CGameObject {
public:
	CGround1(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};