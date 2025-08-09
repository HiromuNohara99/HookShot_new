//======================================
//
//	���f���̊Ǘ�
//	Author Nohara Hiromu
//
//=======================================
#include "model.h"
#include "manager.h"
#include "renderer.h"


//======================================
//	�R���X�g���N�^
//======================================
CModel::CModel(int nPriority)
{
	
}

//======================================
//	�f�X�g���N�^
//======================================
CModel::~CModel()
{

}


//======================================
//	����������
//======================================
HRESULT CModel::Init()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenederer()->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_pBuffMat,
		nullptr,
		&m_nNumMat,
		&m_pMesh);

	

	SetMaxMinPos();
	return S_OK;
}


//======================================
//	�I������
//======================================
void CModel::Uninit()
{
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
	//CObject::Release();
}

//======================================
//	�X�V����
//======================================
void CModel::Update()
{
	////����
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
}

//======================================
//	�`�揈��
//======================================
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenederer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat;
	D3DXMATRIX mtxParent;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//���f���̕`��
		m_pMesh->DrawSubset(nCntMat);
	}


	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}



//======================================
//���f���̐���
//======================================
CModel* CModel::Create()
{
	CModel *pModel = new CModel;
	pModel->Init();

	return pModel;
}


D3DXVECTOR3* CModel::GetPos()
{
	//���W����肷��
	return &m_pos;
}

D3DXVECTOR3* CModel::GetRot()
{
	//���W����肷��
	return &m_rot;
}

D3DXVECTOR3* CModel::GetCenterPos()
{
	return &m_centerpos;
}

D3DXMATRIX* CModel::GetmtxWorld()
{
	return &m_mtxWorld;
}

LPD3DXBUFFER* CModel::GetBuffMat()
{
	return &m_pBuffMat;
}
DWORD* CModel::GetNumMat()
{
	return &m_nNumMat;
}

LPD3DXMESH* CModel::GetMesh()
{
	return &m_pMesh;
}

//==========================
// �����ʒu�̐ݒ�
//==========================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//
//�ǂ��̃f�[�^��ǂݍ��ނ�
//
void CModel::SetFilePath(const char* sPath)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenederer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(sPath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_pBuffMat,
		nullptr,
		&m_nNumMat,
		&m_pMesh);

	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat->pTextureFilename != nullptr)
		{
			D3DXCreateTextureFromFile(
				pDevice,
				pMat->pTextureFilename,
				&m_pTexture[nCntMat]);
		}
	}

}

//====================================================================
//	���_�̍ő�l�ŏ��l�̔���
//====================================================================
void CModel::SetMaxMinPos()
{
	int nNumVtx; //���_��
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^

	//�ő�l�����߂邽�߂̕ϐ�
	D3DXVECTOR3 vtx;

	//���_�����擾���܂�
	nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int i = 0; i < nNumVtx; i++)
	{
		//�ő�l�����߂邽�߂̕ϐ��i�p�[�c���j
		D3DXVECTOR3 vtx;

		vtx = *(D3DXVECTOR3*)pVtxBuff;

		//X�ő咸�_���W�̔�r
		if (vtx.x > m_maxpos.x)
		{
			//���_�����擾
			m_maxpos.x = vtx.x;
		}
		//X�ŏ����_���W�̔�r
		else if (vtx.x < m_minpos.x)
		{
			//���_�����擾
			m_minpos.x = vtx.x;
		}

		//Z�ő咸�_���W�̔�r
		if (vtx.z > m_maxpos.z)
		{
			//���_�����擾
			m_maxpos.z = vtx.z;
		}
		//Z�ŏ����_���W�̔�r
		else if (vtx.z < m_minpos.z)
		{
			//���_�����擾
			m_minpos.z = vtx.z;
		}

		if (vtx.y> m_maxpos.y)
		{
			//���_�����擾
			m_maxpos.y = vtx.y;
		}
		//Y�ŏ����_���W�̔�r
		else if (vtx.y < m_minpos.y)
		{
			//���_�����擾
			m_minpos.y = vtx.y;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂悤
		pVtxBuff += sizeFVF;
	}
	//�I�u�W�F�N�g�̃T�C�Y�̌v�Z�����܂�
	m_centerpos = m_maxpos - m_minpos;

	//���_�o�b�t�@�̃A�����b�N
	m_pMesh->UnlockVertexBuffer();
}