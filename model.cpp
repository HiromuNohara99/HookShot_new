//======================================
//
//	モデルの管理
//	Author Nohara Hiromu
//
//=======================================
#include "model.h"
#include "manager.h"
#include "renderer.h"


//======================================
//	コンストラクタ
//======================================
CModel::CModel(int nPriority)
{
	
}

//======================================
//	デストラクタ
//======================================
CModel::~CModel()
{

}


//======================================
//	初期化処理
//======================================
HRESULT CModel::Init()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenederer()->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//Xファイルの読み込み
	D3DXLoadMeshFromX("",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_pBuffMat,
		nullptr,
		&m_nNumMat,
		&m_pMesh);

	

	SetMaxMinPos();
	return S_OK;
}


//======================================
//	終了処理
//======================================
void CModel::Uninit()
{
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
	//CObject::Release();
}

//======================================
//	更新処理
//======================================
void CModel::Update()
{
	////減衰
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
}

//======================================
//	描画処理
//======================================
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenederer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat;
	D3DXMATRIX mtxParent;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタの取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//モデルの描画
		m_pMesh->DrawSubset(nCntMat);
	}


	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}



//======================================
//モデルの生成
//======================================
CModel* CModel::Create()
{
	CModel *pModel = new CModel;
	pModel->Init();

	return pModel;
}


D3DXVECTOR3* CModel::GetPos()
{
	//座標を入手する
	return &m_pos;
}

D3DXVECTOR3* CModel::GetRot()
{
	//座標を入手する
	return &m_rot;
}

D3DXVECTOR3* CModel::GetCenterPos()
{
	return &m_centerpos;
}

D3DXMATRIX* CModel::GetmtxWorld()
{
	return &m_mtxWorld;
}

LPD3DXBUFFER* CModel::GetBuffMat()
{
	return &m_pBuffMat;
}
DWORD* CModel::GetNumMat()
{
	return &m_nNumMat;
}

LPD3DXMESH* CModel::GetMesh()
{
	return &m_pMesh;
}

//==========================
// 初期位置の設定
//==========================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//
//どこのデータを読み込むか
//
void CModel::SetFilePath(const char* sPath)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenederer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(sPath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_pBuffMat,
		nullptr,
		&m_nNumMat,
		&m_pMesh);

	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat->pTextureFilename != nullptr)
		{
			D3DXCreateTextureFromFile(
				pDevice,
				pMat->pTextureFilename,
				&m_pTexture[nCntMat]);
		}
	}

}

//====================================================================
//	頂点の最大値最小値の判定
//====================================================================
void CModel::SetMaxMinPos()
{
	int nNumVtx; //頂点数
	DWORD sizeFVF; //頂点フォーマットのサイズ
	BYTE* pVtxBuff; //頂点バッファへのポインタ

	//最大値を求めるための変数
	D3DXVECTOR3 vtx;

	//頂点数を取得します
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int i = 0; i < nNumVtx; i++)
	{
		//最大値を求めるための変数（パーツ分）
		D3DXVECTOR3 vtx;

		vtx = *(D3DXVECTOR3*)pVtxBuff;

		//X最大頂点座標の比較
		if (vtx.x > m_maxpos.x)
		{
			//頂点情報を取得
			m_maxpos.x = vtx.x;
		}
		//X最小頂点座標の比較
		else if (vtx.x < m_minpos.x)
		{
			//頂点情報を取得
			m_minpos.x = vtx.x;
		}

		//Z最大頂点座標の比較
		if (vtx.z > m_maxpos.z)
		{
			//頂点情報を取得
			m_maxpos.z = vtx.z;
		}
		//Z最小頂点座標の比較
		else if (vtx.z < m_minpos.z)
		{
			//頂点情報を取得
			m_minpos.z = vtx.z;
		}

		if (vtx.y> m_maxpos.y)
		{
			//頂点情報を取得
			m_maxpos.y = vtx.y;
		}
		//Y最小頂点座標の比較
		else if (vtx.y < m_minpos.y)
		{
			//頂点情報を取得
			m_minpos.y = vtx.y;
		}

		//頂点フォーマットのサイズ分ポインタを進めよう
		pVtxBuff += sizeFVF;
	}
	//オブジェクトのサイズの計算をします
	m_centerpos = m_maxpos - m_minpos;

	//頂点バッファのアンロック
	m_pMesh->UnlockVertexBuffer();
}