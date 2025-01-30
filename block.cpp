  /*
*
*	ブロックの処理[block.cpp]
*	Author Nohara Hiromu 
* 
*/
#include "block.h"

/*
*	コンストラクタ
*/
CBlock::CBlock()
{

}

/**
 * .デストラクタ
 */
CBlock::~CBlock()
{

}


/**
 * .初期化処理
 */
HRESULT CBlock::Init()
{
	SetFilePath("data\\MODEL\\block001.x");
	CModel::Init();
	return S_OK;
}

/**
 * .終了処理
 */
void CBlock::Uninit()
{
	CModel::Uninit();
}

/**
 * .更新処理
 */
void CBlock::Update()
{
	D3DXVECTOR3* Pos = CModel::GetPos();

	*Pos += m_move;
	CModel::Update();
}


/**
 * .描画処理
 */
void CBlock::Draw()
{
	CModel::Draw();
}

/**
 * .生成処理
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
 * .移動量の取得
 */
D3DXVECTOR3* CBlock::GetMove()
{
	return &m_move;
}