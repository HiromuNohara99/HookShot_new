//=================================================================
//
// プレイヤー(通常状態）の処理[player_nomal.h]
// Author Nohara Hiromu
//
//=================================================================
#include "main.h"
#include "model.h"
#include "joypad.h"

#ifndef PLAYERNOMAL_H_
#define PLAYERNOMAL_H_

class CPlayer_Nomal
{
public:
	CPlayer_Nomal();
	~CPlayer_Nomal();
	void Init();
	void Update(CModel* pPlayer);
private:
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
};

#endif
