//===============================
//
// player(�ʏ���)�̏���[player.cpp]	
// Author Nohara Hiromu
// 
//===============================
#include "player_nomal.h"
#include "player.h"
#include "manager.h"
#include "camera.h"
#include "flor.h"
#include "enity.h"
#include "object2D.h"
#include "block.h"
#include "hook.h"

//===============================
// �R���X�g���N�^
//===============================
CPlayer_Nomal::CPlayer_Nomal()
{

}

//===============================
// �f�X�g���N�^
//===============================
CPlayer_Nomal::~CPlayer_Nomal()
{

}

//===============================
//	����������
//===============================
void CPlayer_Nomal::Init()
{
	//�ϐ��̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===============================
//	�X�V����
//===============================
void CPlayer_Nomal::Update(CModel* pPlayer)
{
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //�L�[�{�[�h

	D3DXVECTOR3* pPlayerMove = pPlayer->GetMove();		//�ړ���
	D3DXVECTOR3* pPlayerRot = pPlayer->GetRot();		//����

	pPlayerMove->y = 0.0f;

	//X�ړ�
;	if (m_pKeyboard->GetPress(DIK_D))
	{
		pPlayerMove->x += CPlayer::NORMAL_SPEED;
		pPlayerRot->y = -1.57f;
	}
	if (m_pKeyboard->GetPress(DIK_A))
	{
		pPlayerMove->x += -CPlayer::NORMAL_SPEED;
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

	if (m_pKeyboard->GetTrigger(DIK_SPACE))
	{
		pPlayerMove->y = CPlayer::JUMP;
	}

}