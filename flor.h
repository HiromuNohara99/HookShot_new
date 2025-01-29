//===================================================================
//
//	florの処理[flor.h]
// 
//	Autohor Nohara Hiromu
//
//===================================================================
#ifndef FLOR_H_
#define FLOR_H_

#include "model.h"

class CFlor :public CObject
{
public:
	CFlor(int nPriority = 3);
	~CFlor()override;
	HRESULT Init()override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
	void UpdatePos(D3DXVECTOR3 move);			//位置情報の更新				
	D3DXVECTOR3 GetPos();							//座標を入手する
	void SetPos(D3DXVECTOR3 pos);					//座標の初期位置を決める
	static CFlor* Create(D3DXVECTOR3 pos,float Size,int nType);
	void SetSize(float size);
	void SetType(int nType);
	int GetSize();
	int GetType();


private:
	LPDIRECT3DTEXTURE9 m_pTexturePolygon;			//テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;	//頂点
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
	float m_fSize;					//一つの辺のサイズ
	int m_nType;
};

#endif // !FLOR_H_
