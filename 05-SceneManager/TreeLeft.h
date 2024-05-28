#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_TREELEFT 60003
#define TREELEFT_WIDTH 16
#define TREELEFT_BBOX_WIDTH 16
#define TREELEFT_BBOX_HEIGHT 16

class CTreeLeft : public CGameObject {
public:
	CTreeLeft(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};