//=================================================================
//
// プレイヤー(空中状態）の処理[player_air.h]
// Author Nohara Hiromu
//
//=================================================================
#include "main.h"
#include "model.h"
#include "joypad.h"

#ifndef PLAYERAIR_H_
#define PLAYERAIR_H_

class CPlayer_Air
{
public:
	CPlayer_Air();
	~CPlayer_Air();
	void Init();
	void Update(CModel* pPlayer);
private:
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
};

#endif