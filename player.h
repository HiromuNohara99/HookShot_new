//=================================================================
//
// プレイヤーの処理[player.h]
//
// Author Nohara Hiromu
//
//=================================================================
#include "main.h"
#include "model.h"
#include "joypad.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class CPlayer :public CModel
{
public:
	//プレイヤーのスピード
	const float NORMAL_SPEED = 2.0f;
	const float LIFT_SPEED = 2.5f;
	const float JUMP = 10.0f;
	//プレイヤーの状態
	typedef enum
	{
		PLAYER_NOMAL = 0,		//通常状態
		PLAYER_HOOK,			//フックショット展開中
		PLAYER_AIR,				//空中にいる時
		PLAYER_LIFT,			//持ち上げてる状態
		PLAYER_MAX,

	}STATUS;		//プレイヤーの状態

	typedef enum
	{
		GRAVITE_NOMAL =0,
		GRAVITE_GRAVITE,
	}GRAVITE;

	CPlayer();									
	~CPlayer() override;						
	HRESULT Init()override;						
	void Uninit()override;						
	void Update()override;						
	void Draw()override;								
	static CPlayer* Create(D3DXVECTOR3 pos);	
	static void SetStatus(STATUS Status);	//ステータスの情報設定
	void Collision();	//当たり判定
	//状態:ノーマル
	void PlayerNomal();
	void ControlNomal();
	//状態:空中
	void PlayerAir();
	void ControlAir();
	//状態:共通
	void ShootHook();
	

private:
	D3DXVECTOR3 m_move;							//移動量	
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_oldpos;						//プレイヤーの前の行動
	D3DXVECTOR3 m_HookPos;						//フックショットの位置の取得
	static STATUS m_Status;						//プレイヤーの状態
	static GRAVITE m_Gravite;					//重力の状態
	static CJoypad* m_pJoypad;					//
	bool bInertia;
	static bool bHook;
};





#endif PLAYER_H_