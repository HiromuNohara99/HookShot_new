//========================================
// 
//	3D��
//	Author Nohara�@Hiromu
// 
//========================================
#include "main.h"
#include "object.h"
#include "InputKeyboard.h"
#ifndef OBJECT3D_H_
#define OBJECT3D_H_


//=======================
//�I�u�W�F�N�g3D�N���X�̐���
//=======================
class CObject3D :public CObject
{
public:
	CObject3D(int nPriority = 3);
	~CObject3D()override;
	HRESULT Init()override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
	void UpdatePos(D3DXVECTOR3 move);			//�ʒu���̍X�V				
	D3DXVECTOR3 GetPos();							//���W����肷��
	void SetPos(D3DXVECTOR3 pos);					//���W�̏����ʒu�����߂�
	
	static CObject3D* Create(D3DXVECTOR3 pos);
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexturePolygon;			//�e�N�X�`��
	CKeyboard* m_pKeyboard;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;	//���_
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
};

#endif
