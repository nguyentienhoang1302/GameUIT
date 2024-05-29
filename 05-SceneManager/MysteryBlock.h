#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define MBLOCK_WIDTH 16
#define MBLOCK_BBOX_WIDTH 16
#define MBLOCK_BBOX_HEIGHT 16

class CMBlock : public CGameObject {
protected:
	int aniId;
public:
	CMBlock(float x, float y, int aniId) : CGameObject(x, y) {
		this->aniId = aniId;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};