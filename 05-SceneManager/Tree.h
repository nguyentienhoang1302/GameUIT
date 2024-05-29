#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define TREE_WIDTH 16
#define TREE_BBOX_WIDTH 16
#define TREE_BBOX_HEIGHT 16

#define ID_SPRITE_TREE 60000
#define ID_SPRITE_TREE_TOPLEFT (ID_SPRITE_TREE+1000)
#define ID_SPRITE_TREE_TOPRIGHT (ID_SPRITE_TREE+2000)
#define ID_SPRITE_TREE_LEFT (ID_SPRITE_TREE+3000)
#define ID_SPRITE_TREE_MIDDLE (ID_SPRITE_TREE+4000)
#define ID_SPRITE_TREE_RIGHT (ID_SPRITE_TREE+5000)
#define ID_SPRITE_TREE_BOTLEFT (ID_SPRITE_TREE+6000)
#define ID_SPRITE_TREE_BOTRIGHT (ID_SPRITE_TREE+7000)


class CTree : public CGameObject {
	int aniID;
public:
	CTree(float x, float y, int aniID) {
		this->aniID = aniID;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};