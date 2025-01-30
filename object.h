//========================================
// 
//	�S�ẴI�u�W�F�N�g�̊Ǘ��̏���	[object.h]
// Author Nohara Hiromu
// 
//========================================
#include "main.h"

#ifndef OBJECT_H_
#define OBJECT_H_

//=============================================
//�I�u�W�F�N�g�N���X�̐���
//=============================================
class CObject
{
public:
	static const int MAX_OBJECT = 256;
	static const int PRIORITY = 5;
	typedef enum
	{
		TYPE_NONE=0,
		TYPE_PLAYER,
		TYPE_PARTS,
		TYPE_OBJECT3D,
		TYPE_ENITY,
		TYPE_HOOK,
		TYPE_HUMAN,
		TYPE_FLOR,
		TYPE_ENEMY,
		TYPE_BLOCK,
		TYPE_MAX,

	}TYPE;

	CObject(int nPriority=3);
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static void ReleaseAll();	//�S�I�u�W�F�N�g�̉��
	static void UpdateAll();	//�S�I�u�W�F�N�g�̍X�V
	static void DrawAll();		//�S�I�u�W�F�N�g�`��
	static CObject* GetTop(int nPriority);
	CObject* GetpNext();
	TYPE GetType();					//�^�C�v�̎擾
	void SetType(TYPE type);			//�^�C�v�̐ݒ�
	void Deathflag();
protected:
	void Release();				//�������g�̉��
private:
	TYPE m_Type;							//�^�C�v
	int m_nPriority;
	static int m_nNumAll[5];				//�I�u�W�F�N�g�̑���
	static CObject* m_pTop[5];			//�擪�I�u�W�F�N�g�̃|�C���^
	static CObject* m_pCur[5];			//�Ō���I�u�W�F�N�g�̃|�C���^
	CObject* m_pPrev;					//�O�̃|�C���^
	CObject* m_pNext;					//��̃|�C���^
	bool m_bDeath;						//���S�t���O
};
#endif