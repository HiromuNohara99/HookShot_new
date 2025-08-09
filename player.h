//=================================================================
//
// �v���C���[�̏���[player.h]
// Author Nohara Hiromu
//
//=================================================================
#include "main.h"
#include "model.h"
#include "joypad.h"
#include "player_nomal.h"
#include "player_air.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class CPlayer :public CModel
{
public:
	//�v���C���[�̃X�s�[�h
	const static float NORMAL_SPEED;
	const static float LIFT_SPEED;
	const static float JUMP;
	const static float MAX_SPEED;		//�X�s�[�h�̌��E

	typedef enum
	{
		PLAYER_NOMAL = 0,		//�ʏ���
		PLAYER_HOOK,			//�t�b�N�V���b�g�W�J��
		PLAYER_PULL,			//�����グ��
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
	void Collision();	//�����蔻��

	static void SetStatus(STATUS Status) {m_Status = Status;}	//�X�e�[�^�X�̏��ݒ�

	static STATUS* GetStatus() { return &m_Status; }

	D3DXVECTOR3* GetHookPos();	//�t�b�N�V���b�g�̈ʒu

	
	//���:�t�b�N
	void PlayerHook();
	void PlayerHookMove();
	//���:����������
	void PlayerPull();
	//���:����
	void ShootHook();
	void MouseP();	//�}�E�X�ň��e���|�[�g

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
	float m_HookSpeed; //�t�b�N�̃X�s�[�h
	static CPlayer_Nomal* m_pPlayer_Nomal;
	static CPlayer_Air* m_pPlayer_Air;
	
};
#endif PLAYER_H_