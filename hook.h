/*
*
*	フックの処理[hook.h]
*	Author Nohara Hiromu
* 
*/
#ifndef HOOK_H_
#define HOOK_H_
#include "model.h"


class CHook :public CModel
{
public:
	const int LIFE = 30;		//ライフ
	const float  HOOK_SPEED = 10.0f;
	typedef enum
	{
		HOOK_NORMAL =0,
		HOOK_STOP,
		HOOK_MAX,
	}HOOK;
	CHook();
	~CHook()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CHook* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:
	D3DXVECTOR3 m_move;			//移動量
	int m_nLife;				//体力
	HOOK m_State;				//状態
};
#endif // !HOOK_H_