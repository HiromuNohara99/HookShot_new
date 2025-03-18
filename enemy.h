//
//
//
//
//
#ifndef ENEMY_H_
#define ENEMY_H_

#include  "model.h"

class CEnemy :public CModel
{
public:
	const int ENEMY_LIFE_NOMAL = 30;
	typedef enum
	{
		ENENMY_NOMAL =0,

		ENEMY_MAX,

	}ENEMY;
	CEnemy();
	~CEnemy();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CEnemy* Create(D3DXVECTOR3 pos,  ENEMY type);
	void SetEnemyType(ENEMY type);
private:
	D3DXVECTOR3* m_pos;
	D3DXVECTOR3* m_rot;
	ENEMY m_type;
	int m_Life;
	D3DXVECTOR3 m_move;

};
#endif // !ENEMY_H_