#include "DarkBox.h"

void CDBox::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CDBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}