//====================================================
//	�I�u�W�F�N�g�Ǘ�
//====================================================
#include "object.h"



//==================================================
//	�ÓI�����o�ϐ��̏�����
//==================================================
int CObject::m_nNumAll[5] = {};					//����
CObject* CObject::m_pTop[5] = {};				//�擪�̃I�u�W�F�N�g
CObject* CObject::m_pCur[5] = {};				//�Ō���̃I�u�W�F�N�g
//===========================================
//	�R���X�g���N�^
//===========================================
CObject::CObject(int nPriority)
{
	 m_nPriority = nPriority;

	if (m_pTop[m_nPriority] == nullptr)
	{
		m_pTop[m_nPriority] = this;
		m_pCur[m_nPriority] = this;
	}
	else
	{
		CObject* pPrev = m_pCur[m_nPriority];			//��ԍŌ�̓z����ɓ����
		CObject* pNext = this;				//�����
		pPrev->m_pNext = pNext;				//���̂Ƃ���Ō�̂�̎������
		pNext->m_pPrev = pPrev;				//���̂��̂̑O�̂��
		m_pCur[m_nPriority]= pNext;						//�Ō������̂ɂ���
	}

	m_bDeath=false;						//���S�t���O
	m_nNumAll[m_nPriority]++;
	
}


//===========================================
// �f�X�g���N�^
//===========================================
CObject::~CObject()
{

}

//===========================================
//�@���ׂẴI�u�W�F�N�g�̉��
//===========================================
void CObject::ReleaseAll()
{
	for (int Priority = 0; Priority < PRIORITY; Priority++)
	{
		CObject* pObj = m_pTop[Priority];
		while (pObj != nullptr)
		{

			CObject* pNext = pObj->m_pNext;
			pObj->Release();
			pObj = pNext;

		}
		m_pTop[Priority] = nullptr;
		m_pCur[Priority] = nullptr;
	}

}

//===========================================
//�@���ׂẴI�u�W�F�N�g�̍X�V
//===========================================
void CObject::UpdateAll()
{
	for (int Priority = 0; Priority < PRIORITY; Priority++)
	{
		//�X�V
		CObject* pObj = m_pTop[Priority];
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->Update();
			pObj = pNext;
		}

		//���S�t���O
		pObj = m_pTop[Priority];
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;

			if (pObj->m_bDeath == true)
			{
				pObj->Release();
			}
			pObj = pNext;
		}
	}

}

//===========================================
//�@���ׂẴI�u�W�F�N�g�̕`��
//===========================================
void CObject::DrawAll()
{
	for (int Priority = 0; Priority < PRIORITY; Priority++)
	{
		CObject* pObj = m_pTop[Priority];
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->Draw();
			pObj = pNext;
		}
	}
}

//===========================================
//�@���g�̊J��
//===========================================
void CObject::Release()
{
	//�O�̃|�C���^�@���̃|�C���^���Ăяo��
	CObject* pDelete = this;
	CObject* pPrev = m_pPrev;		
	CObject* pNext = m_pNext;		
	
	if (pPrev == nullptr)
	{	//�����O��nullptr��������next��top
		if (pNext != nullptr)
		{
			m_pTop[m_nPriority]= pNext;
			pNext->m_pPrev = nullptr;
		}
	}
	else if (pNext == nullptr)
	{	//�����オnullptr��������prev��Cur��
			m_pCur[m_nPriority] = pPrev;
			pPrev->m_pNext = nullptr;
	}
	else
	{	//�������炭������
		pPrev->m_pNext = pNext;
		pNext->m_pPrev = pPrev;
	}
	m_bDeath = false;
	m_nNumAll[m_nPriority]--;
	delete pDelete;
	pDelete = nullptr;
	
}


//===========================================
//�@�^�C�v�̎擾
//===========================================
CObject::TYPE CObject::GetType()
{
	return m_Type;
}


//===========================================
//�@�^�C�v�̐ݒ�
//===========================================
void CObject::SetType(TYPE type)
{
	m_Type = type;
}


//==============================================
//	�g�b�v�̎擾
//==============================================
CObject* CObject::GetTop(int nPriority)
{
	return m_pTop[nPriority];
}

//==============================================
//	���̎擾
//==============================================
CObject* CObject::GetpNext()
{
	return m_pNext;
}

//==============================================
//	Death�̎擾
//==============================================
void CObject::Deathflag()
{
	m_bDeath = true;
}
