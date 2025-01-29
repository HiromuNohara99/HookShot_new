//===================================================================
//
//	flor�̏���[flor.h]
// 
//	Autohor Nohara Hiromu
//
//===================================================================
#ifndef FLOR_H_
#define FLOR_H_

#include "model.h"

class CFlor :public CObject
{
public:
	CFlor(int nPriority = 3);
	~CFlor()override;
	HRESULT Init()override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
	void UpdatePos(D3DXVECTOR3 move);			//�ʒu���̍X�V				
	D3DXVECTOR3 GetPos();							//���W����肷��
	void SetPos(D3DXVECTOR3 pos);					//���W�̏����ʒu�����߂�
	static CFlor* Create(D3DXVECTOR3 pos,float Size,int nType);
	void SetSize(float size);
	void SetType(int nType);
	int GetSize();
	int GetType();


private:
	LPDIRECT3DTEXTURE9 m_pTexturePolygon;			//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;	//���_
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
	float m_fSize;					//��̕ӂ̃T�C�Y
	int m_nType;
};

#endif // !FLOR_H_
