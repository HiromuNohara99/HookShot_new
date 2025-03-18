//===============================
// 
// �G�̏���[enemy.h]
// Author Nohara Hiromu
// 
//===============================
#include "enemy.h"

//===============================
//�R���X�g���N�^
//===============================
CEnemy::CEnemy()
{

}

//===============================
// �f�X�g���N�^
//===============================
CEnemy::~CEnemy()
{

}

//===============================
// ����������
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
// �I������
//===============================
void CEnemy::Uninit()
{
	CModel::Uninit();
}


//===============================
// �X�V����
//===============================
void CEnemy::Update()
{
	CModel::Update();
}


//===============================
// �`�揈��
//===============================
void CEnemy::Draw()
{
	CModel::Draw();
}

//===============================
// ��������
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
// �G�̃^�C�v
//===============================
void CEnemy::SetEnemyType(ENEMY type)
{
	m_type = type;
}