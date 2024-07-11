#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 

	//float xM, yM;	//position of mario after entering portal

	float width;
	float height; 
public:
	CPortal(float l, float t, float r, float b, int scene_id);//, float xM, float yM);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox(void);

	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }

	//float GetxM() { return xM; }
	//float GetyM() { return yM; }
};