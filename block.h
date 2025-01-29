/*
*
*	ÉuÉçÉbÉNÇÃèàóù[block.h] 
*	Author Nohara Hiromu
* 
*/
#ifndef BLOCK_H_
#define BLOCK_H_

#include "main.h"
#include "model.h"

class CBlock :public CModel
{
public:
	CBlock();
	~CBlock()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlock* Create(D3DXVECTOR3 pos);
	D3DXVECTOR3* GetMove();

private:
	D3DXVECTOR3 m_move;
};

#endif // !BLOCK_H_
