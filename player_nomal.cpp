//===============================
//
// player(通常状態)の処理[player.cpp]	
// Author Nohara Hiromu
// 
//===============================
#include "player_nomal.h"
#include "player.h"
#include "manager.h"
#include "camera.h"
#include "flor.h"
#include "enity.h"
#include "object2D.h"
#include "block.h"
#include "hook.h"

//===============================
// コンストラクタ
//===============================
CPlayer_Nomal::CPlayer_Nomal()
{

}

//===============================
// デストラクタ
//===============================
CPlayer_Nomal::~CPlayer_Nomal()
{

}

//===============================
//	初期化処理
//===============================
void CPlayer_Nomal::Init()
{
	//変数の初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===============================
//	更新処理
//===============================
void CPlayer_Nomal::Update(CModel* pPlayer)
{
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //キーボード

	D3DXVECTOR3* pPlayerMove = pPlayer->GetMove();		//移動量
	D3DXVECTOR3* pPlayerRot = pPlayer->GetRot();		//方向

	pPlayerMove->y = 0.0f;

	//X移動
;	if (m_pKeyboard->GetPress(DIK_D))
	{
		pPlayerMove->x += CPlayer::NORMAL_SPEED;
		pPlayerRot->y = -1.57f;
	}
	if (m_pKeyboard->GetPress(DIK_A))
	{
		pPlayerMove->x += -CPlayer::NORMAL_SPEED;
		pPlayerRot->y = 1.57f;
	}
	//Z移動
	if (m_pKeyboard->GetPress(DIK_W))
	{
		pPlayerMove->z += CPlayer::NORMAL_SPEED;
		pPlayerRot->y = -3.14f;
	}
	if (m_pKeyboard->GetPress(DIK_S))
	{
		pPlayerMove->z += -CPlayer::NORMAL_SPEED;
		pPlayerRot->y = 0.0f;
	}

	if (m_pKeyboard->GetTrigger(DIK_SPACE))
	{
		pPlayerMove->y = CPlayer::JUMP;
	}

}