//===============================
//
// player�̏���[player.cpp]	
// Author Nohara Hiromu
// 
//===============================
#include "player.h"
#include "manager.h"
#include "camera.h"
#include "flor.h"
#include "enity.h"
#include "object2D.h"
#include "block.h"
#include "hook.h"
//===============================
//
//===============================
CPlayer::STATUS CPlayer::m_Status = PLAYER_NOMAL;
CPlayer::GRAVITE CPlayer::m_Gravite = GRAVITE_NOMAL;
CJoypad* CPlayer::m_pJoypad = nullptr;
bool CPlayer::bHook = false;
//===============================
// �R���X�g���N�^
//===============================
CPlayer::CPlayer()
{

}

//===============================
// �f�X�g���N�^
//===============================
CPlayer::~CPlayer()
{

}

//===============================
// ����������
//===============================
HRESULT CPlayer::Init()
{
	SetFilePath("data\\MODEL\\player.x");
	m_Status = PLAYER_AIR;
	m_move = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	m_pJoypad = CManager::GetJoypad();					//�Q�[���p�b�h
	CModel::Init();
	return S_OK;
}

//===============================
// �I������
//===============================
void CPlayer::Uninit()
{
	CModel::Uninit();
}

//===============================
// �X�V����
//===============================
void CPlayer::Update()
{
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();		//�v���C���[�̈ʒu�̏��
	m_oldpos = *pPlayerPos;							//�������ꏊ���X�V
	D3DXVECTOR3* pPlayerRot = CModel::GetRot();		//�v���C���[�̕����̏��
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //�L�[�{�[�h
	switch (m_Status)
	{
	case PLAYER_NOMAL:		//�m�[�}�����
		m_Gravite = GRAVITE_NOMAL;
		PlayerNomal();
		break;
	case PLAYER_AIR:
		m_Gravite = GRAVITE_GRAVITE;
		PlayerAir();
		break;
	case PLAYER_HOOK:		//�t�b�N�V���b�g
		m_Gravite = GRAVITE_NOMAL;
		PlayerHook();
		break;
	default:
		break;
	}

	//�d�͂̏���
	if (m_Gravite == GRAVITE_NOMAL)
	{
		m_move.y += 0.0f;
	}
	else if (m_Gravite == GRAVITE_GRAVITE)
	{
		m_move.y += -0.5f;
	}
	ShootHook();
	//�ړ��ʂ̍X�V
	pPlayerPos->x += m_move.x;
	pPlayerPos->y += m_move.y;
	pPlayerPos->z += m_move.z;

	Collision();

	//�����̒���
	pPlayerRot->x = m_rot.x;
	pPlayerRot->y = m_rot.y;
	pPlayerRot->z = m_rot.z;
	CModel::Update();
}

//===============================
// �`�揈��
//===============================
void CPlayer::Draw()
{
	CModel::Draw();
}

//===============================
// ��������
//===============================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->Init();
	pPlayer->SetType(TYPE_PLAYER);
	pPlayer->SetPos(pos);
	return pPlayer;
}

//===============================
// �v���C���[�̃m�[�}�����
//===============================
void CPlayer::PlayerNomal()
{
	ControlNomal();
}

//===============================
// �v���C���[�̋󒆏��
//===============================
void CPlayer::PlayerAir()
{
	ControlAir();
}

//===============================
// �v���C���[�̃R���g���[��
//===============================
void CPlayer::ControlNomal()
{
	m_rot.x = 0.0f;
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();		//�v���C���[�̈ʒu�̏��
	D3DXVECTOR3* pPlayerRot = CModel::GetRot();		//�v���C���[�̈ʒu�̏��
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //�L�[�{�[�h
	//���X�e�B�b�N�̓��͏����擾����
	short sThumbLX = m_pJoypad->GetState(0)->Gamepad.sThumbLX;  //���E����
	short sThumbLY = m_pJoypad->GetState(0)->Gamepad.sThumbLY;  //�㉺����
	float fDire = atan2f(sThumbLX, sThumbLY);					//�|���Ă�������v�Z����
	
	if (sqrtf(sThumbLX * sThumbLX + sThumbLY * sThumbLY) > 6000.0f)
	{
		if (fDire < 0.0f)
		{
			m_move.x -= NORMAL_SPEED;
			m_rot.y = 1.57f;
		}
		else if (fDire > 0.0f)
		{
			m_move.x += NORMAL_SPEED;
			m_rot.y = -1.57f;
		}
	}

	if (m_pJoypad->GetTrigger(CJoypad::JOYKEY::JOYKEY_A, 0))	//�W�����v
	{	//�W�����v
		m_move.y += JUMP;
		m_Status = PLAYER_AIR;
	}

	if (m_pKeyboard->GetPress(DIK_D))
	{
		m_move.x += NORMAL_SPEED;
		m_rot.y = -1.57f;
	}
	if (m_pKeyboard->GetPress(DIK_A))
	{
		m_move.x += -NORMAL_SPEED;
		m_rot.y = 1.57f;
	}

	m_move.x += (0.0f - m_move.x) * 0.3f;
	m_move.z += (0.0f - m_move.z) * 0.3f;
}

//===============================
// �v���C���[�̋󒆏���
//===============================
void CPlayer::ControlAir()
{
	//�v���C���[�̏��擾
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();
	D3DXVECTOR3* pPlayerRot = CModel::GetRot();
	//���X�e�B�b�N�̓��͏����擾����
	short sThumbLX = m_pJoypad->GetState(0)->Gamepad.sThumbLX;   //���E����
	short sThumbLY = m_pJoypad->GetState(0)->Gamepad.sThumbLY;   //�㉺����
	//�|���Ă�������v�Z����
	float fDire = atan2f(sThumbLX, sThumbLY);
	if (sqrtf(sThumbLX * sThumbLX + sThumbLY * sThumbLY) > 6000)
	{
		if (fDire < 0.0f)
		{
			m_move.x -= NORMAL_SPEED;
			m_rot.y = 1.57f;
		}
		else if (fDire > 0.0f)
		{
			m_move.x += NORMAL_SPEED;
			m_rot.y = -1.57f;
		}
	}

	m_move.x += (0.0f - m_move.x) * 0.2f;
	m_move.z += (0.0f - m_move.z) * 0.2f;
}

//===============================
// �v���C���[�̃t�b�N���
//===============================
void CPlayer::PlayerHook()
{
	PlayerHookMove();
}

//===============================
// �t�b�N���̓���
//===============================
void CPlayer::PlayerHookMove()
{
	//�t�b�N�V���b�g�̈ʒu�̎擾
	D3DXVECTOR3* Pos = GetHookPos();
	//�v���C���[�̈ʒu�擾
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();
	//���X�e�B�b�N�̓��͏����擾����
	short sThumbLX = m_pJoypad->GetState(0)->Gamepad.sThumbLX;   //���E����
	short sThumbLY = m_pJoypad->GetState(0)->Gamepad.sThumbLY;   //�㉺����
	//�|���Ă�������v�Z����
	float fDire = atan2f(sThumbLX, sThumbLY);

	//�p�x�����߂�
	float Angle = atan2f(pPlayerPos->y- Pos->y, pPlayerPos->x - Pos->x);
	float g = 9.81f;	//�d�͉����x(��)
	//�P�U��q�̌���
	float  a = -(g / 1000.0f) * sin(Angle + D3DX_PI * 0.5f);
	
	//�t�b�N�V���b�g�̑���
	if (sqrtf(sThumbLX * sThumbLX + sThumbLY * sThumbLY) > 6000.0f)
	{
		if (fabs(m_HookSpeed) < fabs(MAX_SPEED))
		{
			if (fDire > 0)
			{
				a += 0.05f;
			}
			else if (fDire < 0)
			{
				a += -0.05f;
			}
		}
		else
		{ //�ő呬�x���z�����ꍇ
			a += 0.00f;
		}
	}
	
	m_HookSpeed += a;											//�p���x�̍X�V
	m_move.y = cosf(Angle) * m_HookSpeed * 10.0f;			//�t�b�N�̓���
	m_move.x = -sinf(Angle) * m_HookSpeed * 10.0f;			//�t�b�N�̓���
}

//===============================
// ��������ꎞ�̓���
//===============================
void CPlayer::PlayerPull()
{
	
}

//===============================
// �����蔻��(xz
//===============================
void CPlayer::Collision()
{
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();		//�v���C���[�̈ʒu�̏��
	D3DXVECTOR3* pPlayerCenter = CModel::GetCenterPos();		//�v���C���[�̒��a�̑傫��
	m_Status = PLAYER_AIR;
	CObject* pObj = CObject::GetTop(3);
	while (pObj != nullptr)
	{
		CObject* pNext = pObj->GetpNext();			//
		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BLOCK)
		{
			CBlock* pBlock = (CBlock*)pObj;		//�_�E���L���X�g

			D3DXVECTOR3* ObjPos = pBlock->CModel::GetPos();
			D3DXVECTOR3* CenterObjPos = pBlock->CModel::GetCenterPos();
			if (fabs(m_move.y) >= fabs(m_move.x))
			{
				//�܂����ɓ�������
				if (pPlayerPos->x + pPlayerCenter->x * 0.5f >= ObjPos->x - CenterObjPos->x * 0.5f
					&& pPlayerPos->x - pPlayerCenter->x * 0.5f <= ObjPos->x + CenterObjPos->x * 0.5f
					&& pPlayerPos->z + pPlayerCenter->z * 0.5f >= ObjPos->z - CenterObjPos->z * 0.5f
					&& pPlayerPos->z - pPlayerCenter->z * 0.5f <= ObjPos->z + CenterObjPos->z * 0.5f
					&& pPlayerPos->y + pPlayerCenter->y * 0.5f >= ObjPos->y - CenterObjPos->y * 0.5f
					&& pPlayerPos->y - pPlayerCenter->y * 0.5f <= ObjPos->y + CenterObjPos->y * 0.5f)
				{
				
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& m_oldpos.y - pPlayerCenter->y * 0.5f >= ObjPos->y + CenterObjPos->y * 0.5f)
					{
						pPlayerPos->y = ObjPos->y + CenterObjPos->y * 0.5f + pPlayerCenter->y * 0.5f;
						m_Status = PLAYER_NOMAL;
						m_move.y = 0.0f;
					}
					//z�̓����蔻��
					if (pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.z - pPlayerCenter->z * 0.5f > ObjPos->z + CenterObjPos->z * 0.5f)
					{
						pPlayerPos->z = ObjPos->z + CenterObjPos->z * 0.5f + pPlayerCenter->z * 0.5f + 1.0f;
					}
					if (pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.z + pPlayerCenter->z * 0.5f < ObjPos->z - CenterObjPos->z * 0.5f)
					{
						pPlayerPos->z = ObjPos->z - CenterObjPos->z * 0.5f - pPlayerCenter->z * 0.5f - 1.0f;
					}
					//���̓����蔻��
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.x - pPlayerCenter->x * 0.5f > ObjPos->x + CenterObjPos->x * 0.5f)
					{
						pPlayerPos->x = ObjPos->x + CenterObjPos->x * 0.5f + pPlayerCenter->x * 0.5f + 1.0f;
					}
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.x + pPlayerCenter->x * 0.5f < ObjPos->x - CenterObjPos->x * 0.5f)
					{
						pPlayerPos->x = ObjPos->x - CenterObjPos->x * 0.5f - pPlayerCenter->x * 0.5f - 1.0f;
					
					}
					//y�̓����蔻��
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& m_oldpos.y + pPlayerCenter->y * 0.5f < ObjPos->y - CenterObjPos->y * 0.5f)
					{
						pPlayerPos->y = ObjPos->y - CenterObjPos->y * 0.5f - pPlayerCenter->y * 0.5f - 1.0f;
					}
					D3DXVECTOR3* move = pBlock->GetMove();
					*pPlayerPos += *move;
				}
				
			}
			else if (fabs(m_move.y) <= fabs(m_move.x))
			{
				//�܂����ɓ�������
				if (pPlayerPos->x + pPlayerCenter->x * 0.5f >= ObjPos->x - CenterObjPos->x * 0.5f
					&& pPlayerPos->x - pPlayerCenter->x * 0.5f <= ObjPos->x + CenterObjPos->x * 0.5f
					&& pPlayerPos->z + pPlayerCenter->z * 0.5f >= ObjPos->z - CenterObjPos->z * 0.5f
					&& pPlayerPos->z - pPlayerCenter->z * 0.5f <= ObjPos->z + CenterObjPos->z * 0.5f
					&& pPlayerPos->y + pPlayerCenter->y * 0.5f >= ObjPos->y - CenterObjPos->y * 0.5f
					&& pPlayerPos->y - pPlayerCenter->y * 0.5f <= ObjPos->y + CenterObjPos->y * 0.5f)
				{
				
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& m_oldpos.y - pPlayerCenter->y * 0.5f >= ObjPos->y + CenterObjPos->y * 0.5f)
					{
						pPlayerPos->y = ObjPos->y + CenterObjPos->y * 0.5f + pPlayerCenter->y * 0.5f;
						m_Status = PLAYER_NOMAL;
						m_move.y = 0.0f;
					}
					//z�̓����蔻��
					if (pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.z - pPlayerCenter->z * 0.5f > ObjPos->z + CenterObjPos->z * 0.5f)
					{
						pPlayerPos->z = ObjPos->z + CenterObjPos->z * 0.5f + pPlayerCenter->z * 0.5f + 1.0f;
					}
					if (pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos->x + CenterObjPos->x * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.z + pPlayerCenter->z * 0.5f < ObjPos->z - CenterObjPos->z * 0.5f)
					{
						pPlayerPos->z = ObjPos->z - CenterObjPos->z * 0.5f - pPlayerCenter->z * 0.5f - 1.0f;
					}
					//���̓����蔻��
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.x - pPlayerCenter->x * 0.5f > ObjPos->x + CenterObjPos->x * 0.5f)
					{
						pPlayerPos->x = ObjPos->x + CenterObjPos->x * 0.5f + pPlayerCenter->x * 0.5f + 1.0f;

					}
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->y + pPlayerCenter->y * 0.5f > ObjPos->y - CenterObjPos->y * 0.5f
						&& pPlayerPos->y - pPlayerCenter->y * 0.5f < ObjPos->y + CenterObjPos->y * 0.5f
						&& m_oldpos.x + pPlayerCenter->x * 0.5f < ObjPos->x - CenterObjPos->x * 0.5f)
					{
						pPlayerPos->x = ObjPos->x - CenterObjPos->x * 0.5f - pPlayerCenter->x * 0.5f - 1.0f;
					
					}
					//y�̓����蔻��
					if (pPlayerPos->z + pPlayerCenter->z * 0.5f >= ObjPos->z - CenterObjPos->z * 0.5f
						&& pPlayerPos->z - pPlayerCenter->z * 0.5f <= ObjPos->z + CenterObjPos->z * 0.5f
						&& pPlayerPos->x + pPlayerCenter->x * 0.5f >= ObjPos->x - CenterObjPos->x * 0.5f
						&& pPlayerPos->x - pPlayerCenter->x * 0.5f <= ObjPos->x + CenterObjPos->x * 0.5f
						&& m_oldpos.y + pPlayerCenter->y * 0.5f < ObjPos->y - CenterObjPos->y * 0.5f)
					{
						pPlayerPos->y = ObjPos->y - CenterObjPos->y * 0.5f - pPlayerCenter->y * 0.5f - 1.0f;
					}
					D3DXVECTOR3* move = pBlock->GetMove();
					*pPlayerPos += *move;
				}	
			
			}
		}
		if (type == CObject::TYPE::TYPE_FLOR)
		{
			CFlor* pFlor = (CFlor*)pObj;		//�_�E���L���X�g

			D3DXVECTOR3 ObjPos = pFlor->CFlor::GetPos();
			int size = pFlor->CFlor::GetSize();
			if (pPlayerPos->y - pPlayerCenter->y * 0.5f <= ObjPos.y
				&& pPlayerPos->z + pPlayerCenter->z * 0.5f > ObjPos.z - size
				&& pPlayerPos->z - pPlayerCenter->z * 0.5f < ObjPos.z + size
				&& pPlayerPos->x + pPlayerCenter->x * 0.5f > ObjPos.x - size
				&& pPlayerPos->x - pPlayerCenter->x * 0.5f < ObjPos.x + size)
			{
				pPlayerPos->y =0.0f+pPlayerCenter->y*0.5f+ObjPos.y;
				m_move.y = 0.0f;
				m_Status = PLAYER_NOMAL;
			}
		}
		pObj = pNext;
	}
}

/**
 * . �t�b�N���˂Ɋւ���
 */
void CPlayer::ShootHook()
{
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();		//�v���C���[�̈ʒu�̏��
	//���X�e�B�b�N�̓��͏����擾����
	short sThumbLX = m_pJoypad->GetState(0)->Gamepad.sThumbLX;   //���E����
	short sThumbLY = m_pJoypad->GetState(0)->Gamepad.sThumbLY;   //�㉺����
	//�|���Ă�������v�Z����
	float fDire = atan2f(sThumbLX, sThumbLY);
	BYTE rtValue = m_pJoypad->GetState(0)->Gamepad.bRightTrigger;
	if (rtValue > XINPUT_GAMEPAD_TRIGGER_THRESHOLD && !bHook)
	{
		CHook::Create(*pPlayerPos, D3DXVECTOR3(fDire, fDire, fDire));
		bHook = true;

	}
	else if (rtValue <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{		//�������Ƃ��̏���
		CObject* pObj = CObject::GetTop(3);
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->GetpNext();
			CObject::TYPE type = pObj->GetType();
			if (type == CObject::TYPE::TYPE_HOOK)
			{
				CHook* pHook = (CHook*)pObj;
				pHook->Deathflag();
				m_Status = PLAYER_NOMAL;
				CHook::SetState(CHook::HOOK_FINISH);
				bHook = false;
				return;
			}
			pObj = pNext;
		}
	}
}

//===============================
// �t�b�N�V���b�g�̈ʒu�擾
//===============================
D3DXVECTOR3* CPlayer::GetHookPos()
{
	D3DXVECTOR3* Pos = {};
	CObject* pObj = CObject::GetTop(3);
	while (pObj != nullptr)
	{
		CObject* pNext = pObj->GetpNext();
		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_HOOK)
		{
			CHook* pHook = (CHook*)pObj;
			 Pos = pHook->GetPos();
		}
		pObj = pNext;
	}
	return Pos;
	
}