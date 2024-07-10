#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Cloud.h"
#include "Tree.h"
#include "ColorBlock.h"
#include "Pipe.h"
#include "MysteryBlock.h"
#include "DarkZone.h"
#include "Koopa.h"
//#include "Koopas.h"


class CPlayScene: public CScene
{
	static CPlayScene* __instance;
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	void SpawnGameObject(CGameObject* obj, float x, float y);

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

