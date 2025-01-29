//==========================================================
//
//	player�̏���[player.cpp]
//	
// Author Nohara Hiromu
// 
//==========================================================
#include "player.h"
#include "manager.h"
#include "camera.h"
#include "flor.h"
#include "enity.h"
#include "object2D.h"
#include "block.h"
/*
* 
*/
CPlayer::STATUS CPlayer::m_Status = PLAYER_NOMAL;
CPlayer::GRAVITE CPlayer::m_Gravite = GRAVITE_NOMAL;
CJoypad* CPlayer::m_pJoypad = nullptr;
/*
*	�R���X�g���N�^
*/
CPlayer::CPlayer()
{

}

/*
*	�f�X�g���N�^
*/
CPlayer::~CPlayer()
{

}

/*
*	����������
*/
HRESULT CPlayer::Init()
{
	
	SetFilePath("data\\MODEL\\player.x");
	m_Status = PLAYER_AIR;
	m_move = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	m_pJoypad = CManager::GetJoypad();					//�Q�[���p�b�h
	CModel::Init();
	return S_OK;
}

/*
*	�I������
*/
void CPlayer::Uninit()
{
	CModel::Uninit();
}

/*
*	�X�V����
*/
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
	case PLAYER_HOOK:		//�t�b�N�V���b�g
		m_Gravite = GRAVITE_NOMAL;
		break;
	case PLAYER_AIR:
		m_Gravite = GRAVITE_GRAVITE;
		PlayerAir();
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
		m_move.y += -1.0f;
	}
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

/*
*�@�`�揈��
*/
void CPlayer::Draw()
{
	CModel::Draw();
}


/*
*	��������
*/
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer = new CPlayer;

	pPlayer->Init();
	pPlayer->SetType(TYPE_PLAYER);
	pPlayer->SetPos(pos);
	return pPlayer;
}



/*
*	�v���C���[�̃m�[�}�����
*/
void CPlayer::PlayerNomal()
{
	//�v���C���[�̃R���g���[��
	Control();
}

/*
*	�v���C���[�̃R���g���[��
*/
void CPlayer::Control()
{
	m_rot.x = 0.0f;
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();		//�v���C���[�̈ʒu�̏��
	D3DXVECTOR3* pPlayerRot = CModel::GetRot();		//�v���C���[�̈ʒu�̏��
	CCamera* Camera = CManager::GetCamera();
	D3DXVECTOR3 Rot = Camera->GetRot();
	//���X�e�B�b�N�̓��͏����擾����
	short sThumbLX = m_pJoypad->GetState(0)->Gamepad.sThumbLX;  //���E����
	short sThumbLY = m_pJoypad->GetState(0)->Gamepad.sThumbLY;  //�㉺����
	float fDire = atan2f(sThumbLX, sThumbLY);					//�|���Ă�������v�Z����
	
	if (sqrtf(sThumbLX * sThumbLX + sThumbLY * sThumbLY) > 6000)
	{
		if (fDire < 0.0f)
		{
			m_move.x -= NORMAL_SPEED;
		}
		else if (fDire > 0.0f)
		{
			m_move.x += NORMAL_SPEED;
		}
	}

	
	if (m_pJoypad->GetTrigger(CJoypad::JOYKEY::JOYKEY_A, 0))	//�W�����v
	{	//�W�����v
		m_move.y += JUMP;
		m_Status = PLAYER_AIR;
	}

	m_rot.z *= 0.9f;
	m_rot.y = Rot.y + D3DX_PI * -1.0f;
	m_move.x += (0.0f - m_move.x) * 0.3f;
	m_move.z += (0.0f - m_move.z) * 0.3f;
}

/*
*	�v���C���[�̋󒆏���
*/
void CPlayer::PlayerAir()
{
	CJoypad* m_pJoypad = CManager::GetJoypad();		//�Q�[���p�b�h
	D3DXVECTOR3* pPlayerPos = CModel::GetPos();		//�v���C���[�̈ʒu�̏��
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //�L�[�{�[�h
	D3DXVECTOR3* pPlayerRot = CModel::GetRot();		//�v���C���[�̕����̏��
	CCamera* Camera = CManager::GetCamera();
	D3DXVECTOR3 Rot = Camera->GetRot();

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
		}
		else if (fDire > 0.0f)
		{
			m_move.x += NORMAL_SPEED;
		}
	}

	m_rot.z *= 0.9f;
	m_move.x += (0.0f - m_move.x) * 0.3f;
	m_move.z += (0.0f - m_move.z) * 0.3f;
}

/*
*	�X�e�[�^�X�̕ύX
*/
void CPlayer::SetStatus(STATUS Status)
{
	m_Status = Status;
}

/*
*	�����蔻��(xz
*/
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







