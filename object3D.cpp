//===========================
//	レンダラーのメイン
//===========================
#include "object3D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "InputKeyboard.h"
float m_nCnt;
LPDIRECT3DTEXTURE9 CObject3D::m_pTexturePolygon = nullptr;
//===========================================
//	コンストラクタ
//===========================================
CObject3D::CObject3D(int nPriority) :CObject(nPriority)
{
	m_pTexturePolygon = nullptr;			//テクスチャ
	m_pVtxBuffPolygon = nullptr;	//頂点
	m_pos = D3DXVECTOR3(0.0f, 0.0, 200.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
#define MAX_SIZE_X	50
#define MAX_SIZE_Y	50

//===========================================
// デストラクタ
//===========================================
CObject3D::~CObject3D()
{

}

//===========================================
//　初期化処理
//===========================================
HRESULT CObject3D::Init()
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenederer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPolygon,
		nullptr);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\matuya.png",
		&m_pTexturePolygon);

	VERTEX_3D* pVtx;	//頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(-MAX_SIZE_X, 0.0f, MAX_SIZE_Y);
	pVtx[1].pos = D3DXVECTOR3(MAX_SIZE_X, 0.0f, MAX_SIZE_Y );
	pVtx[2].pos = D3DXVECTOR3(-MAX_SIZE_X, 0.0f, -MAX_SIZE_Y );
	pVtx[3].pos = D3DXVECTOR3(MAX_SIZE_X, 0.0f, -MAX_SIZE_Y );


	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//法線ベクトルのせってい
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点バッファをアンロック
	m_pVtxBuffPolygon->Unlock();
	CKeyboard* m_pKeyboard = new CKeyboard();
	return S_OK;
}

//===========================================
//　終了処理
//===========================================
void CObject3D::Uninit()
{
	if (m_pTexturePolygon != nullptr)
	{
		m_pTexturePolygon->Release();
		m_pTexturePolygon = nullptr;
	}
	//頂点バッファの破棄
	if (m_pVtxBuffPolygon != nullptr)
	{
		m_pVtxBuffPolygon->Release();
		m_pVtxBuffPolygon = nullptr;
	}

}

//===========================================
//　更新処理
//===========================================
void CObject3D::Update()
{
	VERTEX_3D* pVtx;	//頂点情報へのポインタ
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //キーボード
	
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-MAX_SIZE_X, MAX_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(MAX_SIZE_X, MAX_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-MAX_SIZE_X, -MAX_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MAX_SIZE_X, -MAX_SIZE_Y, 0.0f);
	//法線ベクトルのせってい
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	m_pos = GetPos();
	//頂点バッファをアンロック
	m_pVtxBuffPolygon->Unlock();
}

//===========================================
//　描画処理
//===========================================
void CObject3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenederer()->GetDevice();

	CRenderer* pRenderer = nullptr;

	D3DXMATRIX mtxRot, mtxTrans;		//計算マトリックス	

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	//向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置の繁栄
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, m_pTexturePolygon);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


 //============================================
 // 情報の設定
 //============================================
D3DXVECTOR3 CObject3D::GetPos()
{
	return m_pos;
}

void CObject3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//===================================================
//	位置の更新　　　　　　	
//====================================================
void  CObject3D::UpdatePos(D3DXVECTOR3 move)
{
	//位置の更新
	m_pos += move;

	VERTEX_3D* pVtx;	//頂点情報へのポインタ
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	float m_rot = 0.0f;

	//頂点バッファをアンロック
	m_pVtxBuffPolygon->Unlock();
}

//===========================================
// Object3Dの生成
//===========================================
CObject3D* CObject3D::Create(D3DXVECTOR3 pos)
{
	CObject3D* pPolygon = new CObject3D;
	pPolygon->Init();
	pPolygon->SetPos(pos);
	pPolygon->SetType(TYPE_OBJECT3D);

	return pPolygon;
}

