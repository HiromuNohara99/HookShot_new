//===================================================
//
//	flor�̏���[flor.cpp]
// 
// Author Nohara Hiromu
//
//===================================================
#include "flor.h"
#include "manager.h"
#include "ObjName.h"


//===========================================
//	�R���X�g���N�^
//===========================================
CFlor::CFlor(int nPriority) :CObject(nPriority)
{
	m_pTexturePolygon = nullptr;			//�e�N�X�`��
	m_pVtxBuffPolygon = nullptr;	//���_
	m_pos = D3DXVECTOR3(0.0f, 0.0, 50.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
#define MAX_SIZE_X	15000
#define MAX_SIZE_Y	15000

//===========================================
// �f�X�g���N�^
//===========================================
CFlor::~CFlor()
{

}

//===========================================
//�@����������
//===========================================
HRESULT CFlor::Init()
{
	
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenederer()->GetDevice();

	char aString[64];

	//strncpy(aString, CObjName::FlorLoad(m_nType), sizeof(aString) - 1);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPolygon,
		nullptr);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ruins.png",
		&m_pTexturePolygon);

	VERTEX_3D* pVtx;	//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(-m_fSize, -100.0f, m_fSize);
	pVtx[1].pos = D3DXVECTOR3(m_fSize,  -100.0f, m_fSize);
	pVtx[2].pos = D3DXVECTOR3(-m_fSize, -100.0f, -m_fSize);
	pVtx[3].pos = D3DXVECTOR3(m_fSize,  -100.0f, -m_fSize);


	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�@���x�N�g���̂����Ă�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffPolygon->Unlock();
	CKeyboard* m_pKeyboard = new CKeyboard();
	return S_OK;
}

//===========================================
//�@�I������
//===========================================
void CFlor::Uninit()
{
	if (m_pTexturePolygon != nullptr)
	{
		m_pTexturePolygon->Release();
		m_pTexturePolygon = nullptr;
	}
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffPolygon != nullptr)
	{
		m_pVtxBuffPolygon->Release();
		m_pVtxBuffPolygon = nullptr;
	}

}

//===========================================
//�@�X�V����
//===========================================
void CFlor::Update()
{
	VERTEX_3D* pVtx;	//���_���ւ̃|�C���^
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //�L�[�{�[�h
	
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_fSize, 0.0f, m_fSize);
	pVtx[1].pos = D3DXVECTOR3(m_fSize,  0.0f, m_fSize);
	pVtx[2].pos = D3DXVECTOR3(-m_fSize, 0.0f, -m_fSize);
	pVtx[3].pos = D3DXVECTOR3(m_fSize,  0.0f, -m_fSize);

	//�@���x�N�g���̂����Ă�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(10.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 10.0f);
	pVtx[3].tex = D3DXVECTOR2(10.0f, 10.0f);
	m_pos = GetPos();
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffPolygon->Unlock();
}

//===========================================
//�@�`�揈��
//===========================================
void CFlor::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenederer()->GetDevice();

	CRenderer* pRenderer = nullptr;

	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�}�g���b�N�X	

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	//�������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�̔ɉh
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, m_pTexturePolygon);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


//============================================
// ���̐ݒ�
//============================================
D3DXVECTOR3 CFlor::GetPos()
{
	return m_pos;
}

void CFlor::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//===================================================
//	�ʒu�̍X�V�@�@�@�@�@�@	
//====================================================
void  CFlor::UpdatePos(D3DXVECTOR3 move)
{
	//�ʒu�̍X�V
	m_pos += move;

	VERTEX_3D* pVtx;	//���_���ւ̃|�C���^
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	float m_rot = 0.0f;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffPolygon->Unlock();
}

//===========================================
// Object3D�̐���
//===========================================
CFlor* CFlor::Create(D3DXVECTOR3 pos,float Size,int nType)
{
	CFlor* pPolygon = new CFlor;
	pPolygon->SetType(nType);
	pPolygon->Init();
	pPolygon->SetPos(pos);
	pPolygon->CObject::SetType(TYPE_FLOR);
	pPolygon->SetSize(Size);

	return pPolygon;
}



int  CFlor::GetSize()
{
	return (int)m_fSize;
}

int CFlor::GetType()
{
	return m_nType;
}



/**
 * �^�C�v.
 */
void CFlor::SetType(int nType)
{
	m_nType = nType;
}

/**
 * �T�C�Y.
 */
void CFlor::SetSize(float size)
{
	m_fSize = size;
}