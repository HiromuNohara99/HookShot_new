//======================================================
//
// 実在物(オブジェクト)の管理[enity.cpp]
// Author Nohara Hiromu
// 
//======================================================
#include "enity.h"
#include "model.h"
#include "ObjName.h"


//===============================
// コンストラクタ
//===============================
CEnity::CEnity()
{
	//初期化
	m_nObjNum = 0;
}

//===============================
// デストラクタ
//===============================
CEnity::~CEnity()
{

}

//===============================
// 初期化処理
//===============================
HRESULT CEnity::Init()
{
	char aObjNme[128];	//オブジェクトの名前
	
	// オブジェクトの名前の取得
	strncpy(aObjNme, CObjName::ObjLoad(m_nObjNum), sizeof(aObjNme) - 1);

	SetFilePath(aObjNme);

	CModel::Init();
	
	return S_OK;
}

//===============================
//	終了処理
//===============================
void CEnity::Uninit()
{
	CModel::Uninit();
}

//===============================
// 更新処理
//===============================
void CEnity::Update()
{
	CModel::Update();
}

//===============================
// 描画処理
//===============================
void CEnity::Draw()
{
	CModel::Draw();
}

//===============================
// 生成処理
//===============================
CEnity* CEnity::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nType)
{
	CEnity* pEnity= new CEnity;
	pEnity->SetObjNum(nType);
	pEnity->Init();
	pEnity->SetType(TYPE_ENITY);
	pEnity->SetPos(pos);
	pEnity->SetRot(rot);
	return pEnity;
}

//===============================
// 種類の取得
//===============================
int CEnity::GetObjNum()
{
	return m_nObjNum;
}

//===============================
// 種類の設定
//===============================
void CEnity::SetObjNum(int nType)
{
	m_nObjNum = nType;
}
