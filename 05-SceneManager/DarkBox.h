#pragma once

#include "GameObject.h"

#define DBOX_WIDTH 16
#define DBOX_BBOX_WIDTH 16
#define DBOX_BBOX_HEIGHT 16


class CDBox : public CGameObject {
	int aniID;
public:
	CDBox(float x, float y, int aniID) {
		this->aniID = aniID;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};