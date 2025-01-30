//================================================
// 
//	モデルの処理	[model.h]
//	Author Nohara Hiromu
// 
//================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "object.h"
#include "InputKeyboard.h"

//============================================
//	3Dモデルのクラス
//============================================
class CModel :public CObject
{
public:
	CModel(int nPriority = 3);
	~CModel();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CModel* Create();						//モデルの取得
	D3DXVECTOR3 *GetPos();							//座標の情報の取得
	D3DXVECTOR3 *GetRot();							//座標の情報の取得
	D3DXVECTOR3 *GetCenterPos();					//でかさを求める
	void SetPos(D3DXVECTOR3 pos);					//初期位置
	void SetRot(D3DXVECTOR3 rot);					//ROTの設定
	void SetFilePath(const char* sPath);			//モデルの設定
	void SetMaxMinPos();							//最大値最小値を求める
	D3DXMATRIX* GetmtxWorld();
	LPD3DXBUFFER* GetBuffMat();
	DWORD* GetNumMat();
	LPD3DXMESH* GetMesh() { return &m_pMesh };
protected:
	LPD3DXMESH m_pMesh;			//頂点座標
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_nNumMat;
	D3DXMATRIX m_mtxWorld;
	LPDIRECT3DTEXTURE9 m_pTexture[32];		//テクスチャの
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_maxpos;		//最大の場所
	D3DXVECTOR3 m_minpos;		//最小の場所
	D3DXVECTOR3 m_centerpos;	//中央の点
	D3DXVECTOR3 m_rot;			//回転
	CKeyboard* m_pKeyboard;
	
};




#endif
