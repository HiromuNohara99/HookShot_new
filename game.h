//================================================
//
//	game�̏���[game.h]
// 
// Author Nohara Hiromu
//
//================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include "ObjName.h"
//#include "system.h"

//==========================================
//	�Q�[���̃N���X
//==========================================
class CGame :public CScene
{
public:

	CGame();
	~CGame()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void Load();				//�X�e�[�W�̃f�[�^�̓ǂݍ���
//	static CSystem* GetSystem();
private:
	static bool m_goal;
	int m_nType;
	int m_Num;
	int m_FlorNum;			//�e�N�X�`���̎�ނ̂���
	static CObjName* m_ObjName;
	
};

#endif


