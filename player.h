//=================================================================
//
// �v���C���[�̏���[player.h]
//
// Author Nohara Hiromu
//
//=================================================================
#include "main.h"
#include "model.h"
#include "joypad.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class CPlayer :public CModel
{
public:
	//�v���C���[�̃X�s�[�h
	const float NORMAL_SPEED = 2.0f;
	const float LIFT_SPEED = 2.5f;
	const float JUMP = 10.0f;
	//�v���C���[�̏��
	typedef enum
	{
		PLAYER_NOMAL = 0,		//�ʏ���
		PLAYER_HOOK,			//�t�b�N�V���b�g�W�J��
		PLAYER_AIR,				//�󒆂ɂ��鎞
		PLAYER_LIFT,			//�����グ�Ă���
		PLAYER_MAX,

	}STATUS;		//�v���C���[�̏��

	typedef enum
	{
		GRAVITE_NOMAL =0,
		GRAVITE_GRAVITE,
	}GRAVITE;

	CPlayer();									
	~CPlayer() override;						
	HRESULT Init()override;						
	void Uninit()override;						
	void Update()override;						
	void Draw()override;								
	static CPlayer* Create(D3DXVECTOR3 pos);	
	static void SetStatus(STATUS Status);	//�X�e�[�^�X�̏��ݒ�
	void Collision();	//�����蔻��
	//���:�m�[�}��
	void PlayerNomal();
	void ControlNomal();
	//���:��
	void PlayerAir();
	void ControlAir();
	//���:����
	void ShootHook();
	

private:
	D3DXVECTOR3 m_move;							//�ړ���	
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_oldpos;						//�v���C���[�̑O�̍s��
	D3DXVECTOR3 m_HookPos;						//�t�b�N�V���b�g�̈ʒu�̎擾
	static STATUS m_Status;						//�v���C���[�̏��
	static GRAVITE m_Gravite;					//�d�͂̏��
	static CJoypad* m_pJoypad;					//
	bool bInertia;
	static bool bHook;
};





#endif PLAYER_H_