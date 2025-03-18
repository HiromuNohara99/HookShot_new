//===============================
//
// playerの処理[player.cpp]	
// Author Nohara Hiromu
// 
//===============================
#include "player.h"
#include "manager.h"
#include "camera.h"
#include "flor.h"
#include "enity.h"
#include "object2D.h"
#include "block.h"
#include "hook.h"
//===============================
//
//===============================
CPlayer::STATUS CPlayer::m_Status = PLAYER_NOMAL;
CPlayer::GRAVITE CPlayer::m_Gravite = GRAVITE_NOMAL;
CJoypad* CPlayer::m_pJoypad = nullptr;
bool CPlayer::bHook = false;
//===============================
// コンストラクタ
//===============================
CPlayer::CPlayer()
{

}

//===============================
// デストラクタ
//===============================
CPlayer::~CPlayer()
{

}

//===============================
// 初期化処理
//===============================
HRESULT CPlayer::Init()
{
	SetFilePath("data\\MODEL\\player.x");
	m_Status = PLAYER_AIR;
	m_move = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	m_pJoypad = CManager::GetJoypad();					//ゲームパッド
	CModel::Init();
	return S_OK;
}

//===============================
// 終了処理
//===============================
void CPlayer::Uninit()
{
	CModel::Uninit();
}

//===============================
// 更新処理
//===============================
void CPlayer::Update()
{
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();		//プレイヤーの位置の情報
	m_oldpos = *pPlayerPos;							//元居た場所を更新
	D3DXVECTOR3* pPlayerRot = CModel::GetRot();		//プレイヤーの方向の情報
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //キーボード
	switch (m_Status)
	{
	case PLAYER_NOMAL:		//ノーマル状態
		m_Gravite = GRAVITE_NOMAL;
		PlayerNomal();
		break;
	case PLAYER_AIR:
		m_Gravite = GRAVITE_GRAVITE;
		PlayerAir();
		break;
	case PLAYER_HOOK:		//フックショット
		m_Gravite = GRAVITE_NOMAL;
		PlayerHook();
		break;
	default:
		break;
	}

	//重力の処理
	if (m_Gravite == GRAVITE_NOMAL)
	{
		m_move.y += 0.0f;
	}
	else if (m_Gravite == GRAVITE_GRAVITE)
	{
		m_move.y += -0.5f;
	}
	ShootHook();
	//移動量の更新
	pPlayerPos->x += m_move.x;
	pPlayerPos->y += m_move.y;
	pPlayerPos->z += m_move.z;

	Collision();

	//方向の調整
	pPlayerRot->x = m_rot.x;
	pPlayerRot->y = m_rot.y;
	pPlayerRot->z = m_rot.z;
	CModel::Update();
}

//===============================
// 描画処理
//===============================
void CPlayer::Draw()
{
	CModel::Draw();
}

//===============================
// 生成処理
//===============================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->Init();
	pPlayer->SetType(TYPE_PLAYER);
	pPlayer->SetPos(pos);
	return pPlayer;
}

//===============================
// プレイヤーのノーマル状態
//===============================
void CPlayer::PlayerNomal()
{
	ControlNomal();
}

//===============================
// プレイヤーの空中状態
//===============================
void CPlayer::PlayerAir()
{
	ControlAir();
}

//===============================
// プレイヤーのコントロール
//===============================
void CPlayer::ControlNomal()
{
	m_rot.x = 0.0f;
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();		//プレイヤーの位置の情報
	D3DXVECTOR3* pPlayerRot = CModel::GetRot();		//プレイヤーの位置の情報
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //キーボード
	//左スティックの入力情報を取得する
	short sThumbLX = m_pJoypad->GetState(0)->Gamepad.sThumbLX;  //左右入力
	short sThumbLY = m_pJoypad->GetState(0)->Gamepad.sThumbLY;  //上下入力
	float fDire = atan2f(sThumbLX, sThumbLY);					//倒してる方向を計算する
	
	if (sqrtf(sThumbLX * sThumbLX + sThumbLY * sThumbLY) > 6000.0f)
	{
		if (fDire < 0.0f)
		{
			m_move.x -= NORMAL_SPEED;
			m_rot.y = 1.57f;
		}
		else if (fDire > 0.0f)
		{
			m_move.x += NORMAL_SPEED;
			m_rot.y = -1.57f;
		}
	}

	if (m_pJoypad->GetTrigger(CJoypad::JOYKEY::JOYKEY_A, 0))	//ジャンプ
	{	//ジャンプ
		m_move.y += JUMP;
		m_Status = PLAYER_AIR;
	}

	if (m_pKeyboard->GetPress(DIK_D))
	{
		m_move.x += NORMAL_SPEED;
		m_rot.y = -1.57f;
	}
	if (m_pKeyboard->GetPress(DIK_A))
	{
		m_move.x += -NORMAL_SPEED;
		m_rot.y = 1.57f;
	}

	m_move.x += (0.0f - m_move.x) * 0.3f;
	m_move.z += (0.0f - m_move.z) * 0.3f;
}

//===============================
// プレイヤーの空中処理
//===============================
void CPlayer::ControlAir()
{
	//プレイヤーの情報取得
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();
	D3DXVECTOR3* pPlayerRot = CModel::GetRot();
	//左スティックの入力情報を取得する
	short sThumbLX = m_pJoypad->GetState(0)->Gamepad.sThumbLX;   //左右入力
	short sThumbLY = m_pJoypad->GetState(0)->Gamepad.sThumbLY;   //上下入力
	//倒してる方向を計算する
	float fDire = atan2f(sThumbLX, sThumbLY);
	if (sqrtf(sThumbLX * sThumbLX + sThumbLY * sThumbLY) > 6000)
	{
		if (fDire < 0.0f)
		{
			m_move.x -= NORMAL_SPEED;
			m_rot.y = 1.57f;
		}
		else if (fDire > 0.0f)
		{
			m_move.x += NORMAL_SPEED;
			m_rot.y = -1.57f;
		}
	}

	m_move.x += (0.0f - m_move.x) * 0.2f;
	m_move.z += (0.0f - m_move.z) * 0.2f;
}

//===============================
// プレイヤーのフック状態
//===============================
void CPlayer::PlayerHook()
{
	PlayerHookMove();
}

//===============================
// フック時の動き
//===============================
void CPlayer::PlayerHookMove()
{
	//フックショットの位置の取得
	D3DXVECTOR3* Pos = GetHookPos();
	//プレイヤーの位置取得
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();
	//左スティックの入力情報を取得する
	short sThumbLX = m_pJoypad->GetState(0)->Gamepad.sThumbLX;   //左右入力
	short sThumbLY = m_pJoypad->GetState(0)->Gamepad.sThumbLY;   //上下入力
	//倒してる方向を計算する
	float fDire = atan2f(sThumbLX, sThumbLY);

	//角度を求める
	float Angle = atan2f(pPlayerPos->y- Pos->y, pPlayerPos->x - Pos->x);
	float g = 9.81f;	//重力加速度(仮)
	//単振り子の公式
	float  a = -(g / 1000.0f) * sin(Angle + D3DX_PI * 0.5f);
	
	//フックショットの操作
	if (sqrtf(sThumbLX * sThumbLX + sThumbLY * sThumbLY) > 6000.0f)
	{
		if (fabs(m_HookSpeed) < fabs(MAX_SPEED))
		{
			if (fDire > 0)
			{
				a += 0.05f;
			}
			else if (fDire < 0)
			{
				a += -0.05f;
			}
		}
		else
		{ //最大速度を越した場合
			a += 0.00f;
		}
	}
	
	m_HookSpeed += a;											//角速度の更新
	m_move.y = cosf(Angle) * m_HookSpeed * 10.0f;			//フックの動き
	m_move.x = -sinf(Angle) * m_HookSpeed * 10.0f;			//フックの動き
}

//===============================
// 引っ張られ時の動き
//===============================
void CPlayer::PlayerPull()
{
	
}

//===============================
// 当たり判定(xz
//===============================
void CPlayer::Collision()
{
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();		//プレイヤーの位置の情報
	D3DXVECTOR3* pPlayerCenter = CModel::GetCenterPos();		//プレイヤーの直径の大きさ
	m_Status = PLAYER_AIR;
	CObject* pObj = CObject::GetTop(3);
	while (pObj != nullptr)
	{
		CObject* pNext = pObj->GetpNext();			//
		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BLOCK)
		{
			CBlock* pBlock = (CBlock*)pObj;		//ダウンキャスト

			D3DXVECTOR3* ObjPos = pBlock->CModel::GetPos();
			D3DXVECTOR3* CenterObjPos = pBlock->CModel::GetCenterPos();
			if (fabs(m_move.y) >= fabs(m_move.x))
			{
				//まず中に入ったら
				if (pPlayerPos->x + pPlayerCenter->x * 0.5f >= ObjPos->x - CenterObjPos->x * 0.5f
					&& pPlayerPos->x - pPlayerCenter->x * 0.5f <= ObjPos->x + CenterObjPos->x * 0.5f
					&& pPlayerPos->z + pPlayerCenter->z * 0.5f >= ObjPos->z - CenterObjPos->z * 0.5f
					&& pPlayerPos->z - pPlayerCenter->z * 0.5f <= ObjPos->z + CenterObjPos->z * 0.5f
					&& pPlayerPos->y + pPlayerCenter->y * 0.5f >= ObjPos->y - CenterObjPos->y * 0.5f
					&& pPlayerPos->y - pPlayerCenter->y * 0.5f <= ObjPos->y + CenterObjPos->y * 0.5f)
				{
				
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& m_oldpos.y - pPlayerCenter->y * 0.5f >= ObjPos->y + CenterObjPos->y * 0.5f)
					{
						pPlayerPos->y = ObjPos->y + CenterObjPos->y * 0.5f + pPlayerCenter->y * 0.5f;
						m_Status = PLAYER_NOMAL;
						m_move.y = 0.0f;
					}
					//zの当たり判定
					if (pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.z - pPlayerCenter->z * 0.5f > ObjPos->z + CenterObjPos->z * 0.5f)
					{
						pPlayerPos->z = ObjPos->z + CenterObjPos->z * 0.5f + pPlayerCenter->z * 0.5f + 1.0f;
					}
					if (pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.z + pPlayerCenter->z * 0.5f < ObjPos->z - CenterObjPos->z * 0.5f)
					{
						pPlayerPos->z = ObjPos->z - CenterObjPos->z * 0.5f - pPlayerCenter->z * 0.5f - 1.0f;
					}
					//ｘの当たり判定
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.x - pPlayerCenter->x * 0.5f > ObjPos->x + CenterObjPos->x * 0.5f)
					{
						pPlayerPos->x = ObjPos->x + CenterObjPos->x * 0.5f + pPlayerCenter->x * 0.5f + 1.0f;
					}
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.x + pPlayerCenter->x * 0.5f < ObjPos->x - CenterObjPos->x * 0.5f)
					{
						pPlayerPos->x = ObjPos->x - CenterObjPos->x * 0.5f - pPlayerCenter->x * 0.5f - 1.0f;
					
					}
					//yの当たり判定
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& m_oldpos.y + pPlayerCenter->y * 0.5f < ObjPos->y - CenterObjPos->y * 0.5f)
					{
						pPlayerPos->y = ObjPos->y - CenterObjPos->y * 0.5f - pPlayerCenter->y * 0.5f - 1.0f;
					}
					D3DXVECTOR3* move = pBlock->GetMove();
					*pPlayerPos += *move;
				}
				
			}
			else if (fabs(m_move.y) <= fabs(m_move.x))
			{
				//まず中に入ったら
				if (pPlayerPos->x + pPlayerCenter->x * 0.5f >= ObjPos->x - CenterObjPos->x * 0.5f
					&& pPlayerPos->x - pPlayerCenter->x * 0.5f <= ObjPos->x + CenterObjPos->x * 0.5f
					&& pPlayerPos->z + pPlayerCenter->z * 0.5f >= ObjPos->z - CenterObjPos->z * 0.5f
					&& pPlayerPos->z - pPlayerCenter->z * 0.5f <= ObjPos->z + CenterObjPos->z * 0.5f
					&& pPlayerPos->y + pPlayerCenter->y * 0.5f >= ObjPos->y - CenterObjPos->y * 0.5f
					&& pPlayerPos->y - pPlayerCenter->y * 0.5f <= ObjPos->y + CenterObjPos->y * 0.5f)
				{
				
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& m_oldpos.y - pPlayerCenter->y * 0.5f >= ObjPos->y + CenterObjPos->y * 0.5f)
					{
						pPlayerPos->y = ObjPos->y + CenterObjPos->y * 0.5f + pPlayerCenter->y * 0.5f;
						m_Status = PLAYER_NOMAL;
						m_move.y = 0.0f;
					}
					//zの当たり判定
					if (pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.z - pPlayerCenter->z * 0.5f > ObjPos->z + CenterObjPos->z * 0.5f)
					{
						pPlayerPos->z = ObjPos->z + CenterObjPos->z * 0.5f + pPlayerCenter->z * 0.5f + 1.0f;
					}
					if (pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.z + pPlayerCenter->z * 0.5f < ObjPos->z - CenterObjPos->z * 0.5f)
					{
						pPlayerPos->z = ObjPos->z - CenterObjPos->z * 0.5f - pPlayerCenter->z * 0.5f - 1.0f;
					}
					//ｘの当たり判定
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.x - pPlayerCenter->x * 0.5f > ObjPos->x + CenterObjPos->x * 0.5f)
					{
						pPlayerPos->x = ObjPos->x + CenterObjPos->x * 0.5f + pPlayerCenter->x * 0.5f + 1.0f;

					}
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.x + pPlayerCenter->x * 0.5f < ObjPos->x - CenterObjPos->x * 0.5f)
					{
						pPlayerPos->x = ObjPos->x - CenterObjPos->x * 0.5f - pPlayerCenter->x * 0.5f - 1.0f;
					
					}
					//yの当たり判定
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f >= ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f <= ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->x + pPlayerCenter->x * 0.5f >= ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f <= ObjPos->x + CenterObjPos->x * 0.5f
						&& m_oldpos.y + pPlayerCenter->y * 0.5f < ObjPos->y - CenterObjPos->y * 0.5f)
					{
						pPlayerPos->y = ObjPos->y - CenterObjPos->y * 0.5f - pPlayerCenter->y * 0.5f - 1.0f;
					}
					D3DXVECTOR3* move = pBlock->GetMove();
					*pPlayerPos += *move;
				}	
			
			}
		}
		if (type == CObject::TYPE::TYPE_FLOR)
		{
			CFlor* pFlor = (CFlor*)pObj;		//ダウンキャスト

			D3DXVECTOR3 ObjPos = pFlor->CFlor::GetPos();
			int size = pFlor->CFlor::GetSize();
			if (pPlayerPos->y - pPlayerCenter->y * 0.5f <= ObjPos.y
				&& pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos.z - size
				&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos.z + size
				&& pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos.x - size
				&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos.x + size)
			{
				pPlayerPos->y =0.0f+pPlayerCenter->y*0.5f+ObjPos.y;
				m_move.y = 0.0f;
				m_Status = PLAYER_NOMAL;
			}
		}
		pObj = pNext;
	}
}

/**
 * . フック発射に関して
 */
void CPlayer::ShootHook()
{
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();		//プレイヤーの位置の情報
	//左スティックの入力情報を取得する
	short sThumbLX = m_pJoypad->GetState(0)->Gamepad.sThumbLX;   //左右入力
	short sThumbLY = m_pJoypad->GetState(0)->Gamepad.sThumbLY;   //上下入力
	//倒してる方向を計算する
	float fDire = atan2f(sThumbLX, sThumbLY);
	BYTE rtValue = m_pJoypad->GetState(0)->Gamepad.bRightTrigger;
	if (rtValue > XINPUT_GAMEPAD_TRIGGER_THRESHOLD && !bHook)
	{
		CHook::Create(*pPlayerPos, D3DXVECTOR3(fDire, fDire, fDire));
		bHook = true;

	}
	else if (rtValue <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{		//離したときの処理
		CObject* pObj = CObject::GetTop(3);
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetpNext();
			CObject::TYPE type = pObj->GetType();
			if (type == CObject::TYPE::TYPE_HOOK)
			{
				CHook* pHook = (CHook*)pObj;
				pHook->Deathflag();
				m_Status = PLAYER_NOMAL;
				CHook::SetState(CHook::HOOK_FINISH);
				bHook = false;
				return;
			}
			pObj = pNext;
		}
	}
}

//===============================
// フックショットの位置取得
//===============================
D3DXVECTOR3* CPlayer::GetHookPos()
{
	D3DXVECTOR3* Pos = {};
	CObject* pObj = CObject::GetTop(3);
	while (pObj != nullptr)
	{
		CObject* pNext = pObj->GetpNext();
		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_HOOK)
		{
			CHook* pHook = (CHook*)pObj;
			 Pos = pHook->GetPos();
		}
		pObj = pNext;
	}
	return Pos;
	
}