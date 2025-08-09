//===============================
//
// player(通常状態)の処理[player.cpp]	
// Author Nohara Hiromu
// 
//===============================
#include "player_air.h"
#include "player.h"
#include "manager.h"
#include "camera.h"


//===============================
// コンストラクタ
//===============================
CPlayer_Air::CPlayer_Air()
{

}

//===============================
// デストラクタ
//===============================
CPlayer_Air::~CPlayer_Air()
{

}

//===============================
//	初期化処理
//===============================
void CPlayer_Air::Init()
{
	//変数の初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===============================
//	更新処理
//===============================
void CPlayer_Air::Update(CModel* pPlayer)
{
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //キーボード

	D3DXVECTOR3* pPlayerMove = pPlayer->GetMove();		//移動量
	D3DXVECTOR3* pPlayerRot = pPlayer->GetRot();		//方向

	pPlayerMove->y += -1.0f;

	if (m_pKeyboard->GetPress(DIK_D))
	{
		pPlayerMove->x += CPlayer::NORMAL_SPEED;
		pPlayerRot->y = -1.57f;
	}
	if (m_pKeyboard->GetPress(DIK_A))
	{
		pPlayerMove->x += -3.0f;
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
}

