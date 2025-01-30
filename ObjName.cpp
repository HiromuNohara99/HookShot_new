//===============================================
//
//	オブジェクトの種類の管理
// Author　Nohara　Hiromu
//	
//===============================================
#include "ObjName.h"
#include "model.h"

int CObjName::m_ObjnCnt = 0;
int CObjName::m_FlorCnt = 0;
char CObjName::m_ObjTexture[64][64] = {};
char CObjName::m_FlorTexture[64][64] = {};

/**
 * .初期化処理
 */
void CObjName::Init()
{
	m_ObjTexture[64][64] = {};
	m_FlorTexture[64][64] = {};
	m_ObjnCnt = 0;
	m_FlorCnt = 0;
}

/**
 * .オブジェクトセーブ
 */
void CObjName::ObjSave(char* aTexture)
{
	int nCnt = 0;
	strncpy(m_ObjTexture[m_ObjnCnt], aTexture, sizeof(m_ObjTexture[m_ObjnCnt]) - 1);
	//m_Texture[m_nCnt][0] = aTexture;
	m_ObjnCnt++;
}

/**.
 * オブジェクトロード
 */
char* CObjName::ObjLoad(int nCnt)
{
	int nNumber = nCnt % m_ObjnCnt;
	return m_ObjTexture[nNumber];
}

/**
 * 床セーブ.
 */
void CObjName::FlorSave(char* aTexture)
{

	strncpy(m_FlorTexture[m_FlorCnt], aTexture, sizeof(m_FlorTexture[m_FlorCnt]) - 1);
	//m_Texture[m_nCnt][0] = aTexture;
	m_FlorCnt++;
}

/**
 * 床ロード.
 */
char* CObjName::FlorLoad(int nCnt)
{
	int nNumber = 0;
	//数がおかしくならないように

	nNumber = nCnt % m_FlorCnt;

	return m_FlorTexture[nNumber];
}

