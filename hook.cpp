/*
*
*	�t�b�N�V���b�g�̏���[hook.cpp]
*	Author Nohara Hiromu
* 
*/
#include "hook.h"

/**
 * .�R���X�g���N�^
 */
CHook::CHook()
{

}

/**
 * .�f�X�g���N�^
 */
CHook::~CHook()
{

}

/**
 * .������ 
 */
HRESULT CHook::Init()
{
	SetFilePath("data/MODEL/hook.x");
	//�ϐ��̏�����
	m_nLife = LIFE;
	m_State = HOOK_NORMAL;
	CModel::Init();
	return S_OK;
}

/**
 * .�I������
 */
void CHook::Uninit()
{
	CModel::Uninit();
}

/**
 * .�X�V����
 */
void CHook::Update()
{
	D3DXVECTOR3* Pos = CModel::GetPos();
	D3DXVECTOR3* Rot = CModel::GetRot();
	m_nLife--;
	
	
	switch (m_State)
	{
	case HOOK_NORMAL:
		//�t�b�N���ړ�
		m_move.y = cosf(Rot->y + D3DX_PI) * HOOK_SPEED;
		m_move.x = sinf(Rot->y + D3DX_PI) * HOOK_SPEED;
		break;
	case HOOK_STOP:
		m_move.y = cosf(Rot->y + D3DX_PI) * 0.0f;
		m_move.x = sinf(Rot->y + D3DX_PI) * 0.0f;
		break;
	default:
		break;
	}

	if (m_nLife <= 0)
	{	//�̗͂Ȃ��Ȃ����������
		/*Deathflag();*/
		m_State = HOOK_STOP;
		return;
	}
	Pos->x += -m_move.x;
	Pos->y += -m_move.y;
	CModel::Update();

}

/**
 * .�`�揈��
 */
void CHook::Draw()
{
	CModel::Draw();
}

/**
 * .��������
 */
CHook* CHook::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CHook* pHook = new CHook;
	pHook->Init();
	pHook->SetPos(pos);
	pHook->SetRot(rot);

	return pHook;
}