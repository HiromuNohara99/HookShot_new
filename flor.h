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

	void SetSize(float size) { m_fSize = size; }
	void SetType(int nType) { m_nType = nType; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

	float GetSize() { return m_fSize; }
	int GetType() { return m_nType; }
	D3DXVECTOR3 GetPos() { return m_pos; }

	void UpdatePos(D3DXVECTOR3 move);			//位置情報の更新				
	static CFlor* Create(D3DXVECTOR3 pos,float Size,int nType);

private:
	LPDIRECT3DTEXTURE9 m_pTexturePolygon;			//テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;		//頂点
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
	float m_fSize;					//一つの辺のサイズ
	int m_nType;
};
#endif // !FLOR_H_