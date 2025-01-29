//=================================
// ligth�̃��C��[ligth.cpp]
// Author;Nohara Hiromu
//=================================

//===============================
//�C���N���[�h
//==============================
#include "main.h"
#include "light.h"
#include "manager.h"
//===============================
//�}�N����`
//==============================
#define RIGHT	3			//���C�g�̐�

//===============================
//�O���[�o���ϐ�
//==============================
//D3DLIGHT9 g_Ligth[RIGTH];		//���C�g�̏��

//===================================
//	���񂷂Ƃ炭��
//===================================
CLight::CLight()
{
	for (int nCnt = 0; nCnt < RIGHT; nCnt++)
	{
		//���C�g�̏����N���A
		ZeroMemory(&m_aLight[nCnt], sizeof(D3DLIGHT9));
	}
}

//=====================================
//�f�X�g���N�^
//=====================================
CLight::~CLight()
{

}


//===============================
//����������
//==============================
void CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenederer()->GetDevice();
	D3DXVECTOR3 vecDir[RIGHT];		//�ݒ�p�����x�N�g��


	for (int nCnt = 0; nCnt < RIGHT; nCnt++)
	{
		//���C�g�̎��
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;
		//���C�g�̊g�U
		m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
		switch(nCnt)
		{
		case 0:
			//���C�g�̕���	
			vecDir[0] = D3DXVECTOR3(-0.9f, -1.0f, -0.4f);
			break;
		case 1:
			//���C�g�̕���	
			vecDir[1] = D3DXVECTOR3(0.2f, 1.0f, 0.9f);
			break;
		case 2:
			//���C�g�̕���	
			vecDir[2] = D3DXVECTOR3(0.9f, -1.0f, 0.4f);
			break;
		}
		
		m_aLight[nCnt].Direction = vecDir[nCnt];
		D3DXVec3Normalize(&vecDir[nCnt], &vecDir[nCnt]);
		//���C�g�ݒ�
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);

		//���C�g��L��
		pDevice->LightEnable(nCnt, TRUE);
	}
}

//===============================
//�I������
//==============================
void CLight::Uninit(void)
{

}

//===============================
//�X�V����
//==============================
void CLight::Update(void)
{

}