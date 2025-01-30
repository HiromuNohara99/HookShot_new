/*
*
*	フックショットの処理[hook.cpp]
*	Author Nohara Hiromu
* 
*/
#include "hook.h"

/**
 * .コンストラクタ
 */
CHook::CHook()
{

}

/**
 * .デストラクタ
 */
CHook::~CHook()
{

}

/**
 * .初期化 
 */
HRESULT CHook::Init()
{
	SetFilePath("data/MODEL/hook.x");
	//変数の初期化
	m_nLife = LIFE;
	m_State = HOOK_NORMAL;
	CModel::Init();
	return S_OK;
}

/**
 * .終了処理
 */
void CHook::Uninit()
{
	CModel::Uninit();
}

/**
 * .更新処理
 */
void CHook::Update()
{
	D3DXVECTOR3* Pos = CModel::GetPos();
	D3DXVECTOR3* Rot = CModel::GetRot();
	m_nLife--;
	
	
	switch (m_State)
	{
	case HOOK_NORMAL:
		//フックを移動
		m_move.y = cosf(Rot->y + D3DX_PI) * HOOK_SPEED;
		m_move.x = sinf(Rot->y + D3DX_PI) * HOOK_SPEED;
		break;
	case HOOK_STOP:
		m_move.y = cosf(Rot->y + D3DX_PI) * 0.0f;
		m_move.x = sinf(Rot->y + D3DX_PI) * 0.0f;
		break;
	default:
		break;
	}

	if (m_nLife <= 0)
	{	//体力なくなったら消える
		/*Deathflag();*/
		m_State = HOOK_STOP;
		return;
	}
	Pos->x += -m_move.x;
	Pos->y += -m_move.y;
	CModel::Update();

}

/**
 * .描画処理
 */
void CHook::Draw()
{
	CModel::Draw();
}

/**
 * .生成処理
 */
CHook* CHook::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CHook* pHook = new CHook;
	pHook->Init();
	pHook->SetPos(pos);
	pHook->SetRot(rot);

	return pHook;
}