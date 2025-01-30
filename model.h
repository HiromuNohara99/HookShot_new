//================================================
// 
//	���f���̏���	[model.h]
//	Author Nohara Hiromu
// 
//================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "object.h"
#include "InputKeyboard.h"

//============================================
//	3D���f���̃N���X
//============================================
class CModel :public CObject
{
public:
	CModel(int nPriority = 3);
	~CModel();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CModel* Create();						//���f���̎擾
	D3DXVECTOR3 *GetPos();							//���W�̏��̎擾
	D3DXVECTOR3 *GetRot();							//���W�̏��̎擾
	D3DXVECTOR3 *GetCenterPos();					//�ł��������߂�
	void SetPos(D3DXVECTOR3 pos);					//�����ʒu
	void SetRot(D3DXVECTOR3 rot);					//ROT�̐ݒ�
	void SetFilePath(const char* sPath);			//���f���̐ݒ�
	void SetMaxMinPos();							//�ő�l�ŏ��l�����߂�
	D3DXMATRIX* GetmtxWorld();
	LPD3DXBUFFER* GetBuffMat();
	DWORD* GetNumMat();
	LPD3DXMESH* GetMesh() { return &m_pMesh };
protected:
	LPD3DXMESH m_pMesh;			//���_���W
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_nNumMat;
	D3DXMATRIX m_mtxWorld;
	LPDIRECT3DTEXTURE9 m_pTexture[32];		//�e�N�X�`����
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_maxpos;		//�ő�̏ꏊ
	D3DXVECTOR3 m_minpos;		//�ŏ��̏ꏊ
	D3DXVECTOR3 m_centerpos;	//�����̓_
	D3DXVECTOR3 m_rot;			//��]
	CKeyboard* m_pKeyboard;
	
};




#endif
