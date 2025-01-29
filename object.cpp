//====================================================
//	オブジェクト管理
//====================================================
#include "object.h"



//==================================================
//	静的メンバ変数の初期化
//==================================================
int CObject::m_nNumAll[5] = {};					//総数
CObject* CObject::m_pTop[5] = {};				//先頭のオブジェクト
CObject* CObject::m_pCur[5] = {};				//最後尾のオブジェクト
//===========================================
//	コンストラクタ
//===========================================
CObject::CObject(int nPriority)
{
	 m_nPriority = nPriority;

	if (m_pTop[m_nPriority] == nullptr)
	{
		m_pTop[m_nPriority] = this;
		m_pCur[m_nPriority] = this;
	}
	else
	{
		CObject* pPrev = m_pCur[m_nPriority];			//一番最後の奴を手に入れる
		CObject* pNext = this;				//今回の
		pPrev->m_pNext = pNext;				//今のところ最後のやつの次を作る
		pNext->m_pPrev = pPrev;				//今のものの前のやつを
		m_pCur[m_nPriority]= pNext;						//最後を今回のにする
	}

	m_bDeath=false;						//死亡フラグ
	m_nNumAll[m_nPriority]++;
	
}


//===========================================
// デストラクタ
//===========================================
CObject::~CObject()
{

}

//===========================================
//　すべてのオブジェクトの解放
//===========================================
void CObject::ReleaseAll()
{
	for (int Priority = 0; Priority < PRIORITY; Priority++)
	{
		CObject* pObj = m_pTop[Priority];
		while (pObj != nullptr)
		{

			CObject* pNext = pObj->m_pNext;
			pObj->Release();
			pObj = pNext;

		}
		m_pTop[Priority] = nullptr;
		m_pCur[Priority] = nullptr;
	}

}

//===========================================
//　すべてのオブジェクトの更新
//===========================================
void CObject::UpdateAll()
{
	for (int Priority = 0; Priority < PRIORITY; Priority++)
	{
		//更新
		CObject* pObj = m_pTop[Priority];
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->Update();
			pObj = pNext;
		}

		//死亡フラグ
		pObj = m_pTop[Priority];
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;

			if (pObj->m_bDeath == true)
			{
				pObj->Release();
			}
			pObj = pNext;
		}
	}

}

//===========================================
//　すべてのオブジェクトの描画
//===========================================
void CObject::DrawAll()
{
	for (int Priority = 0; Priority < PRIORITY; Priority++)
	{
		CObject* pObj = m_pTop[Priority];
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->Draw();
			pObj = pNext;
		}
	}
}

//===========================================
//　自身の開放
//===========================================
void CObject::Release()
{
	//前のポインタ　次のポインタを呼び出す
	CObject* pDelete = this;
	CObject* pPrev = m_pPrev;		
	CObject* pNext = m_pNext;		
	
	if (pPrev == nullptr)
	{	//もし前がnullptrだったらnextをtop
		if (pNext != nullptr)
		{
			m_pTop[m_nPriority]= pNext;
			pNext->m_pPrev = nullptr;
		}
	}
	else if (pNext == nullptr)
	{	//もし後がnullptrだったらprevをCurに
			m_pCur[m_nPriority] = pPrev;
			pPrev->m_pNext = nullptr;
	}
	else
	{	//あったらくっつける
		pPrev->m_pNext = pNext;
		pNext->m_pPrev = pPrev;
	}
	m_bDeath = false;
	m_nNumAll[m_nPriority]--;
	delete pDelete;
	pDelete = nullptr;
	
}


//===========================================
//　タイプの取得
//===========================================
CObject::TYPE CObject::GetType()
{
	return m_Type;
}


//===========================================
//　タイプの設定
//===========================================
void CObject::SetType(TYPE type)
{
	m_Type = type;
}


//==============================================
//	トップの取得
//==============================================
CObject* CObject::GetTop(int nPriority)
{
	return m_pTop[nPriority];
}

//==============================================
//	次の取得
//==============================================
CObject* CObject::GetpNext()
{
	return m_pNext;
}

//==============================================
//	Deathの取得
//==============================================
void CObject::Deathflag()
{
	m_bDeath = true;
}
