//==============================================
//
//	画面遷移の作成	[scene.h]
//	Author	Nohara Hiromu
//
//==============================================


#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

class CScene 
{
public:
	typedef enum
	{
		SCENE_GAME =0,
		SCENE_TITLE,
		SCENE_MAX
	}SCENE;
	CScene();
	virtual ~CScene();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	static CScene* Create(SCENE scnene);			//モデルの取得

private:
	SCENE m_Scene;									//現在の画面繊維

};
#endif