//=================================================================
//
// プレイヤーの処理[player.h]
// Author Nohara Hiromu
//
//=================================================================
#include "main.h"
#include "model.h"
#include "joypad.h"
#include "player_nomal.h"
#include "player_air.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class CPlayer :public CModel
{
public:
	//プレイヤーのスピード
	const static float NORMAL_SPEED;
	const static float LIFT_SPEED;
	const static float JUMP;
	const static float MAX_SPEED;		//スピードの限界

	typedef enum
	{
		PLAYER_NOMAL = 0,		//通常状態
		PLAYER_HOOK,			//フックショット展開中
		PLAYER_PULL,			//引き上げる
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
	void Collision();	//当たり判定

	static void SetStatus(STATUS Status) {m_Status = Status;}	//ステータスの情報設定

	static STATUS* GetStatus() { return &m_Status; }

	D3DXVECTOR3* GetHookPos();	//フックショットの位置

	
	//状態:フック
	void PlayerHook();
	void PlayerHookMove();
	//状態:引っ張られる
	void PlayerPull();
	//状態:共通
	void ShootHook();
	void MouseP();	//マウスで一回テレポート

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
	float m_HookSpeed; //フックのスピード
	static CPlayer_Nomal* m_pPlayer_Nomal;
	static CPlayer_Air* m_pPlayer_Air;
	
};
#endif PLAYER_H_