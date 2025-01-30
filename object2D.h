//========================================
//オブジェクト2Dヘッダ
//========================================
#include "main.h"
#include "object.h"

#ifndef OBJECT2D_H_
#define OBJECT2D_H_


//=======================
//オブジェクト2Dクラスの生成
//=======================
class CObject2D :public CObject
{
public:
	CObject2D(int nPriority =5);
	~CObject2D()override;
	HRESULT Init()override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;		
	D3DXVECTOR3 GetPos();							//座標を入手する
	void SetPos(D3DXVECTOR3 pos);					//座標の初期位置を決める
	void SetSize(D3DXVECTOR2 size);					//座標の初期位置を決める
	void BindTex(LPDIRECT3DTEXTURE9 Texture);
	void SetAnimation(D3DXVECTOR2 Animation);		//アニメーションの動かし
	static CObject2D* Create(D3DXVECTOR3  pos);
	void SetFileTexture(const char* sPath);			//モデルの設定
private:
	LPDIRECT3DTEXTURE9 m_pTexturePolygon;			//テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;	//頂点
	D3DXVECTOR3 m_pos;
	float m_rot;
	D3DXVECTOR2 m_size;						//xyのサイズ
	D3DXVECTOR2 m_Animation;				//アニメーションの動かし方
};
#endif