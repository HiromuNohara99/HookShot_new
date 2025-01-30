//==========================
//	2D�̂�̊Ǘ�
//==========================
#include "object2D.h"
#include "renderer.h"
#include "manager.h"


//===========================================
//	�R���X�g���N�^
//===========================================
CObject2D::CObject2D(int nPriority)/*:CObject(nPriority)*/
{
	m_pTexturePolygon = nullptr;			//�e�N�X�`��
	m_pVtxBuffPolygon = nullptr;	//���_
	m_Animation = D3DXVECTOR2(0.0f, 0.0f);//�A�j���[�V������move
}


//===========================================
// �f�X�g���N�^
//===========================================
CObject2D::~CObject2D()
{

}

//===========================================
//�@����������
//===========================================
HRESULT CObject2D::Init()
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenederer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPolygon,
		NULL);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"",
		&m_pTexturePolygon);

	//SetFileTexture("data\\TEXTURE\\name.png");

	m_size.x = SCREEN_WIDTH/2;
	m_size.y = SCREEN_HEIGTH/2;

	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffPolygon->Unlock();
	
	return S_OK;
}

//===========================================
//�@�I������
//===========================================
void CObject2D::Uninit()
{
	if (m_pTexturePolygon != NULL)
	{
 		m_pTexturePolygon->Release();
 		m_pTexturePolygon = NULL;
	}
	//���_�o�b�t�@�̔j��
 	if (m_pVtxBuffPolygon != NULL)
	{
		m_pVtxBuffPolygon->Release();
		m_pVtxBuffPolygon = NULL;
	}

}

//===========================================
//�@�X�V����
//===========================================
void CObject2D::Update()
{
	VERTEX_2D* pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 25);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 25);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 25);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 25);

	pVtx[0].tex = D3DXVECTOR2(0.0f + m_Animation.x, 0.0f+ m_Animation.y);
	pVtx[1].tex = D3DXVECTOR2(1.0f + m_Animation.x, 0.0f+ m_Animation.y);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_Animation.x, 1.0f+ m_Animation.y);
	pVtx[3].tex = D3DXVECTOR2(1.0f + m_Animation.x, 1.0f+ m_Animation.y);

	
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffPolygon->Unlock();
}

//===========================================
//�@�`�揈��
//===========================================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenederer()->GetDevice();

	CRenderer* pRenderer = nullptr;

	//���_�o�b�t�@���f�[�^�[�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));
	//���_�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, m_pTexturePolygon);
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


 //============================================
 // ���̐ݒ�
 //============================================
D3DXVECTOR3 CObject2D::GetPos()
 {
	 return m_pos;
 }

 void CObject2D::SetPos(D3DXVECTOR3 pos)
 {
	 m_pos = pos;
 }

 void CObject2D::SetSize(D3DXVECTOR2 size)
 {
	 m_size = size;
 }


 //==================================
 //�A�j���[�V�����̓�����
 //==================================
 void CObject2D::SetAnimation(D3DXVECTOR2 Animation)	//�A�j���[�V�����̓�����
 {
	 m_Animation += Animation;
 }

 



 //===========================================
// Object2D�̐���
//===========================================
 CObject2D* CObject2D::Create(D3DXVECTOR3 pos)
 {
	 CObject2D* pPolygon = new CObject2D;
	 pPolygon->Init();
	 pPolygon->SetType(TYPE_NONE);
	 pPolygon->SetPos(D3DXVECTOR3(SCREEN_WIDTH /2, SCREEN_HEIGTH /2, 0.0f));
	// pPolygon->SetFileTexture("data/TEXTURE/zone.png");
	 return pPolygon;
 }


 //============================================
 //	�e�N�X�`���̐ݒ�
 //============================================
 void CObject2D::SetFileTexture(const char* sPath)
 {
	 LPDIRECT3DDEVICE9 pDevice;

	 pDevice = CManager::GetRenederer()->GetDevice();

	 //�e�N�X�`���ǂݍ���
	 D3DXCreateTextureFromFile(pDevice,
		 sPath,
		 &m_pTexturePolygon);

 }