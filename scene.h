//==============================================
//
//	‰æ–Ê‘JˆÚ‚Ìì¬	[scene.h]
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

	static CScene* Create(SCENE scnene);			//ƒ‚ƒfƒ‹‚Ìæ“¾
private:
	SCENE m_Scene;		//Œ»İ‚Ì‰æ–Ê‘@ˆÛ

};
#endif
