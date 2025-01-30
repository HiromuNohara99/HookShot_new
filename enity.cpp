//======================================================
//
// ���ݕ�(�I�u�W�F�N�g)�̊Ǘ�[enity.cpp]
// Author Nohara Hiromu
// 
//======================================================
#include "enity.h"
#include "model.h"
#include "ObjName.h"


//===============================
// �R���X�g���N�^
//===============================
CEnity::CEnity()
{
	//������
	m_nObjNum = 0;
}

//===============================
// �f�X�g���N�^
//===============================
CEnity::~CEnity()
{

}

//===============================
// ����������
//===============================
HRESULT CEnity::Init()
{
	char aObjNme[128];	//�I�u�W�F�N�g�̖��O
	
	// �I�u�W�F�N�g�̖��O�̎擾
	strncpy(aObjNme, CObjName::ObjLoad(m_nObjNum), sizeof(aObjNme) - 1);

	SetFilePath(aObjNme);

	CModel::Init();
	
	return S_OK;
}

//===============================
//	�I������
//===============================
void CEnity::Uninit()
{
	CModel::Uninit();
}

//===============================
// �X�V����
//===============================
void CEnity::Update()
{
	CModel::Update();
}

//===============================
// �`�揈��
//===============================
void CEnity::Draw()
{
	CModel::Draw();
}

//===============================
// ��������
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
// ��ނ̎擾
//===============================
int CEnity::GetObjNum()
{
	return m_nObjNum;
}

//===============================
// ��ނ̐ݒ�
//===============================
void CEnity::SetObjNum(int nType)
{
	m_nObjNum = nType;
}
