//========================================
// 
//	3Dの
//	Author Nohara　Hiromu
// 
//========================================
#include "main.h"
#include "object.h"
#include "InputKeyboard.h"
#ifndef OBJECT3D_H_
#define OBJECT3D_H_


//=======================
//オブジェクト3Dクラスの生成
//=======================
class CObject3D :public CObject
{
public:
	CObject3D(int nPriority = 3);
	~CObject3D()override;
	HRESULT Init()override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
	void UpdatePos(D3DXVECTOR3 move);			//位置情報の更新				
	D3DXVECTOR3 GetPos();							//座標を入手する
	void SetPos(D3DXVECTOR3 pos);					//座標の初期位置を決める
	
	static CObject3D* Create(D3DXVECTOR3 pos);
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexturePolygon;			//テクスチャ
	CKeyboard* m_pKeyboard;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;	//頂点
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
};

#endif
