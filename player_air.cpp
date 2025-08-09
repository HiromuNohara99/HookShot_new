//===============================
//
// player(�ʏ���)�̏���[player.cpp]	
// Author Nohara Hiromu
// 
//===============================
#include "player_air.h"
#include "player.h"
#include "manager.h"
#include "camera.h"


//===============================
// �R���X�g���N�^
//===============================
CPlayer_Air::CPlayer_Air()
{

}

//===============================
// �f�X�g���N�^
//===============================
CPlayer_Air::~CPlayer_Air()
{

}

//===============================
//	����������
//===============================
void CPlayer_Air::Init()
{
	//�ϐ��̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===============================
//	�X�V����
//===============================
void CPlayer_Air::Update(CModel* pPlayer)
{
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //�L�[�{�[�h

	D3DXVECTOR3* pPlayerMove = pPlayer->GetMove();		//�ړ���
	D3DXVECTOR3* pPlayerRot = pPlayer->GetRot();		//����

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
	//Z�ړ�
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

