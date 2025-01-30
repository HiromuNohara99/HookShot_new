//========================================================
//
//	���ݕ�(�I�u�W�F�N�g�j�̏���[enity.h]
// 
// Author NoharaHiromu 
//
//========================================================
#ifndef ENITY_H_
#define ENITY_H_

#include "model.h"

/*
*	�N���X
*/
class CEnity :public CModel
{
public:
	CEnity();
	~CEnity();
	HRESULT Init()override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
	static CEnity* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nType);
	int  GetObjNum();		
	void SetObjNum(int nType);
	
private:
	int m_nObjNum;					//�I�u�W�F�N�g�̎��
};
#endif