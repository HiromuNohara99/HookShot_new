//================================================
//
//	gameの処理[game.h]
// 
// Author Nohara Hiromu
//
//================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include "ObjName.h"
//#include "system.h"

//==========================================
//	ゲームのクラス
//==========================================
class CGame :public CScene
{
public:

	CGame();
	~CGame()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void Load();				//ステージのデータの読み込み
//	static CSystem* GetSystem();
private:
	static bool m_goal;
	int m_nType;
	int m_Num;
	int m_FlorNum;			//テクスチャの種類のかず
	static CObjName* m_ObjName;
	
};

#endif


