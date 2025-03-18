//===============================
// 
// 敵の処理[enemy.h]
// Author Nohara Hiromu
// 
//===============================
#include "enemy.h"

//===============================
//コンストラクタ
//===============================
CEnemy::CEnemy()
{

}

//===============================
// デストラクタ
//===============================
CEnemy::~CEnemy()
{

}

//===============================
// 初期化処理
//===============================
HRESULT CEnemy::Init()
{
	m_pos = CModel::GetPos();
	m_rot = CModel::GetRot();
	SetFilePath("data\\MODEL\\octopas.x");

	if (m_type == ENENMY_NOMAL)
	{
		m_Life = ENEMY_LIFE_NOMAL;
	}
	CModel::Init();
	return S_OK;
}

//===============================
// 終了処理
//===============================
void CEnemy::Uninit()
{
	CModel::Uninit();
}


//===============================
// 更新処理
//===============================
void CEnemy::Update()
{
	CModel::Update();
}


//===============================
// 描画処理
//===============================
void CEnemy::Draw()
{
	CModel::Draw();
}

//===============================
// 生成処理
//===============================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, ENEMY type)
{
	CEnemy* pEnemy = new CEnemy;
	pEnemy -> Init();
	pEnemy->SetType(TYPE_ENEMY);
	pEnemy->SetPos(pos);
	pEnemy -> SetEnemyType(type);

	return pEnemy;
}

//===============================
// 敵のタイプ
//===============================
void CEnemy::SetEnemyType(ENEMY type)
{
	m_type = type;
}