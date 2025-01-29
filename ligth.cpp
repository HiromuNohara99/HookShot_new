//=================================
// ligthのメイン[ligth.cpp]
// Author;Nohara Hiromu
//=================================

//===============================
//インクルード
//==============================
#include "main.h"
#include "light.h"
#include "manager.h"
//===============================
//マクロ定義
//==============================
#define RIGHT	3			//ライトの数

//===============================
//グローバル変数
//==============================
//D3DLIGHT9 g_Ligth[RIGTH];		//ライトの情報

//===================================
//	こんすとらくた
//===================================
CLight::CLight()
{
	for (int nCnt = 0; nCnt < RIGHT; nCnt++)
	{
		//ライトの情報をクリア
		ZeroMemory(&m_aLight[nCnt], sizeof(D3DLIGHT9));
	}
}

//=====================================
//デストラクタ
//=====================================
CLight::~CLight()
{

}


//===============================
//初期化処理
//==============================
void CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenederer()->GetDevice();
	D3DXVECTOR3 vecDir[RIGHT];		//設定用方向ベクトル


	for (int nCnt = 0; nCnt < RIGHT; nCnt++)
	{
		//ライトの種類
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;
		//ライトの拡散
		m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
		switch(nCnt)
		{
		case 0:
			//ライトの方向	
			vecDir[0] = D3DXVECTOR3(-0.9f, -1.0f, -0.4f);
			break;
		case 1:
			//ライトの方向	
			vecDir[1] = D3DXVECTOR3(0.2f, 1.0f, 0.9f);
			break;
		case 2:
			//ライトの方向	
			vecDir[2] = D3DXVECTOR3(0.9f, -1.0f, 0.4f);
			break;
		}
		
		m_aLight[nCnt].Direction = vecDir[nCnt];
		D3DXVec3Normalize(&vecDir[nCnt], &vecDir[nCnt]);
		//ライト設定
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);

		//ライトを有効
		pDevice->LightEnable(nCnt, TRUE);
	}
}

//===============================
//終了処理
//==============================
void CLight::Uninit(void)
{

}

//===============================
//更新処理
//==============================
void CLight::Update(void)
{

}