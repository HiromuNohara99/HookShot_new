//========================================
//�I�u�W�F�N�g2D�w�b�_
//========================================
#include "main.h"
#include "object.h"

#ifndef OBJECT2D_H_
#define OBJECT2D_H_


//=======================
//�I�u�W�F�N�g2D�N���X�̐���
//=======================
class CObject2D :public CObject
{
public:
	CObject2D(int nPriority =5);
	~CObject2D()override;
	HRESULT Init()override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;		
	D3DXVECTOR3 GetPos();							//���W����肷��
	void SetPos(D3DXVECTOR3 pos);					//���W�̏����ʒu�����߂�
	void SetSize(D3DXVECTOR2 size);					//���W�̏����ʒu�����߂�
	void BindTex(LPDIRECT3DTEXTURE9 Texture);
	void SetAnimation(D3DXVECTOR2 Animation);		//�A�j���[�V�����̓�����
	static CObject2D* Create(D3DXVECTOR3  pos);
	void SetFileTexture(const char* sPath);			//���f���̐ݒ�
private:
	LPDIRECT3DTEXTURE9 m_pTexturePolygon;			//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;	//���_
	D3DXVECTOR3 m_pos;
	float m_rot;
	D3DXVECTOR2 m_size;						//xy�̃T�C�Y
	D3DXVECTOR2 m_Animation;				//�A�j���[�V�����̓�������
};
#endif