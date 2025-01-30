  /*
*
*	�u���b�N�̏���[block.cpp]
*	Author Nohara Hiromu 
* 
*/
#include "block.h"

/*
*	�R���X�g���N�^
*/
CBlock::CBlock()
{

}

/**
 * .�f�X�g���N�^
 */
CBlock::~CBlock()
{

}


/**
 * .����������
 */
HRESULT CBlock::Init()
{
	SetFilePath("data\\MODEL\\block001.x");
	CModel::Init();
	return S_OK;
}

/**
 * .�I������
 */
void CBlock::Uninit()
{
	CModel::Uninit();
}

/**
 * .�X�V����
 */
void CBlock::Update()
{
	D3DXVECTOR3* Pos = CModel::GetPos();

	*Pos += m_move;
	CModel::Update();
}


/**
 * .�`�揈��
 */
void CBlock::Draw()
{
	CModel::Draw();
}

/**
 * .��������
 */
CBlock* CBlock::Create(D3DXVECTOR3 pos)
{
	CBlock* pBlock = new CBlock;
	pBlock->Init();
	pBlock->SetPos(pos);
	pBlock->SetType(TYPE_BLOCK);
	return pBlock;
}


/**
 * .�ړ��ʂ̎擾
 */
D3DXVECTOR3* CBlock::GetMove()
{
	return &m_move;
}