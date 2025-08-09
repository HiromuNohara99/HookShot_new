//=========================================================
// 
// �J�����̏���[camera.cpp]
//	 Author:Nohara Hiromu
// 
//=========================================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "manager.h"
#include "model.h"
#include "player.h"
#include "object.h"


//==============================
// �R���X�g���N�^
//==============================
CCamera::CCamera()
{

}

//==============================
// �R���X�g���N�^
//==============================
CCamera::~CCamera()
{

}

//===============================
// ����������
//===============================
void CCamera::Init(void)
{
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 25.0f, 0.0f);

	CObject* pObj = CObject::GetTop(3);
	while (pObj != nullptr)
	{
		CObject* pNext = pObj->GetpNext();			//
		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_PLAYER)
		{
			CPlayer* pPlayer = (CPlayer*)pObj;
			D3DXVECTOR3 pos = *pPlayer->CModel::GetPos();
			m_posR = pos;
			m_posR.y = pos.y;
			
		}
		pObj = pNext;
	}

}

//===============================
//�@�I������
//===============================
void CCamera::Uninit(void)
{

}
float cameraHeightOffset = 100.0f;  // �J�����̏�������
//int g_nCnt = 0;
//===============================
//	�X�V����
//===============================
void CCamera::Update(void)
{
	CJoypad* m_pJoypad = CManager::GetJoypad();		//�Q�[���p�b�h
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //�L�[�{�[�h
	CObject* pObj = CObject::GetTop(3);

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	while (pObj != nullptr)
	{
		CObject* pNext = pObj->GetpNext();			//
		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_PLAYER)
		{
			CPlayer* pPlayer = (CPlayer*)pObj;
			pos = *pPlayer->CModel::GetPos();
			rot = *pPlayer->CModel::GetRot();
			m_posR = pos;
			m_posR.y = pos.y + 50.0f;
			m_posV.y = pos.y + 200.0f;
		}
		pObj = pNext;
	}
	
	//�E�X�e�B�b�N�̓��͏����擾����
	short sThumbRX = m_pJoypad->GetState(0)->Gamepad.sThumbRX;   //���E����
	short sThumbRY = m_pJoypad->GetState(0)->Gamepad.sThumbRY;   //�㉺����
	//�|���Ă�������v�Z����
	float fDire = atan2f(sThumbRX, sThumbRY);

	if (fabs(sThumbRX)  > 5000)
	{
		if (sThumbRX < 0.0f)
		{
			m_rot.y -= 0.07f;
		}
		if (sThumbRX > 0.0f)
		{

			m_rot.y += 0.07f;

		}
		
	}
	if (fabs(sThumbRY) > 5000)
	{
		if (sThumbRY < 0.0f)
		{
			if (m_rot.x > -1.0f)
			{
				m_rot.x -= 0.03f;
			}
		}
		if (sThumbRY >0.0f)
		{
			
			if (m_rot.x < 1.0f)
			{
				m_rot.x += 0.03f;
			}
		}

	}
	
	if (m_pKeyboard->GetPress(DIK_Z))
	{
		m_rot.y += 0.08f;
	}	

	m_posV.x = m_posR.x - sinf(m_rot.y) * 300.0f;
	m_posV.z = m_posR.z - cosf(m_rot.y) * 300.0f;
	//m_posV.y = m_posR.y - sinf(m_rot.x) * 240.0f;

}

//===============================
//	�O���[�o��
//===============================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenederer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
	////�쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGTH,
		10.0f,
		20000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW,&m_mtxView);
}