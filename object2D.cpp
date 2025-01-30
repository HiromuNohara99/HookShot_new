//==========================
//	2Dのやつの管理
//==========================
#include "object2D.h"
#include "renderer.h"
#include "manager.h"


//===========================================
//	コンストラクタ
//===========================================
CObject2D::CObject2D(int nPriority)/*:CObject(nPriority)*/
{
	m_pTexturePolygon = nullptr;			//テクスチャ
	m_pVtxBuffPolygon = nullptr;	//頂点
	m_Animation = D3DXVECTOR2(0.0f, 0.0f);//アニメーションのmove
}


//===========================================
// デストラクタ
//===========================================
CObject2D::~CObject2D()
{

}

//===========================================
//　初期化処理
//===========================================
HRESULT CObject2D::Init()
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenederer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPolygon,
		NULL);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"",
		&m_pTexturePolygon);

	//SetFileTexture("data\\TEXTURE\\name.png");

	m_size.x = SCREEN_WIDTH/2;
	m_size.y = SCREEN_HEIGTH/2;

	VERTEX_2D* pVtx;	//頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuffPolygon->Unlock();
	
	return S_OK;
}

//===========================================
//　終了処理
//===========================================
void CObject2D::Uninit()
{
	if (m_pTexturePolygon != NULL)
	{
 		m_pTexturePolygon->Release();
 		m_pTexturePolygon = NULL;
	}
	//頂点バッファの破棄
 	if (m_pVtxBuffPolygon != NULL)
	{
		m_pVtxBuffPolygon->Release();
		m_pVtxBuffPolygon = NULL;
	}

}

//===========================================
//　更新処理
//===========================================
void CObject2D::Update()
{
	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 25);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 25);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 25);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 25);

	pVtx[0].tex = D3DXVECTOR2(0.0f + m_Animation.x, 0.0f+ m_Animation.y);
	pVtx[1].tex = D3DXVECTOR2(1.0f + m_Animation.x, 0.0f+ m_Animation.y);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_Animation.x, 1.0f+ m_Animation.y);
	pVtx[3].tex = D3DXVECTOR2(1.0f + m_Animation.x, 1.0f+ m_Animation.y);

	
	//頂点バッファをアンロック
	m_pVtxBuffPolygon->Unlock();
}

//===========================================
//　描画処理
//===========================================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenederer()->GetDevice();

	CRenderer* pRenderer = nullptr;

	//頂点バッファをデーターストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));
	//頂点ーマット
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャ設定
	pDevice->SetTexture(0, m_pTexturePolygon);
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


 //============================================
 // 情報の設定
 //============================================
D3DXVECTOR3 CObject2D::GetPos()
 {
	 return m_pos;
 }

 void CObject2D::SetPos(D3DXVECTOR3 pos)
 {
	 m_pos = pos;
 }

 void CObject2D::SetSize(D3DXVECTOR2 size)
 {
	 m_size = size;
 }


 //==================================
 //アニメーションの動かし
 //==================================
 void CObject2D::SetAnimation(D3DXVECTOR2 Animation)	//アニメーションの動かし
 {
	 m_Animation += Animation;
 }

 



 //===========================================
// Object2Dの生成
//===========================================
 CObject2D* CObject2D::Create(D3DXVECTOR3 pos)
 {
	 CObject2D* pPolygon = new CObject2D;
	 pPolygon->Init();
	 pPolygon->SetType(TYPE_NONE);
	 pPolygon->SetPos(D3DXVECTOR3(SCREEN_WIDTH /2, SCREEN_HEIGTH /2, 0.0f));
	// pPolygon->SetFileTexture("data/TEXTURE/zone.png");
	 return pPolygon;
 }


 //============================================
 //	テクスチャの設定
 //============================================
 void CObject2D::SetFileTexture(const char* sPath)
 {
	 LPDIRECT3DDEVICE9 pDevice;

	 pDevice = CManager::GetRenederer()->GetDevice();

	 //テクスチャ読み込み
	 D3DXCreateTextureFromFile(pDevice,
		 sPath,
		 &m_pTexturePolygon);

 }