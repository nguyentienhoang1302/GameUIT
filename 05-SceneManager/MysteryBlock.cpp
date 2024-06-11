#include "MysteryBlock.h"


CMBlock::CMBlock(float x, float y,int aniID, int content) : CGameObject(x, y) {
	this->aniId = aniID;
	if (content == 1) {
		subObject = new CCoinSpawn(x, y);
		subObject->SetPosition(x, y - 16);
	}
	else if (content == 2) {
		subObject = new CMushroom(x, y);
	}
	empty_start = -1;
	SetState(MBLOCK_STATE_DEFAULT);
	y0 = y;
}

void CMBlock::Render()
{
	int aniID = ID_ANI_MBLOCK;
	if (state == MBLOCK_STATE_EMPTY)
	{
		aniID = ID_ANI_MBLOCK_EMPTY;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CMBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MBLOCK_BBOX_WIDTH / 2;
	t = y - MBLOCK_BBOX_HEIGHT / 2;
	r = l + MBLOCK_BBOX_WIDTH;
	b = t + MBLOCK_BBOX_HEIGHT;
}

void CMBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MBLOCK_STATE_DEFAULT:
		break;
	case MBLOCK_STATE_EMPTY:
		empty_start = GetTickCount64();
		CreateSubObject = true;
		break;
	}
}

void CMBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (state == MBLOCK_STATE_EMPTY) {
		y += vy * dt;
		if (GetTickCount64() - empty_start < 70) {
			vy = -0.1f;
		}
		else if (y < y0) {
			vy = 0.1f;
		}
		else {
			y = y0;
			vy = 0;
			aniId = ID_ANI_MBLOCK_EMPTY;
			//CAnimations* animations = CAnimations::GetInstance();
			//animations->Get(aniId)->Render(x, y);
		}
	}
}