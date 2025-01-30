//========================================
// 
//	全てのオブジェクトの管理の処理	[object.h]
// Author Nohara Hiromu
// 
//========================================
#include "main.h"

#ifndef OBJECT_H_
#define OBJECT_H_

//=============================================
//オブジェクトクラスの生成
//=============================================
class CObject
{
public:
	static const int MAX_OBJECT = 256;
	static const int PRIORITY = 5;
	typedef enum
	{
		TYPE_NONE=0,
		TYPE_PLAYER,
		TYPE_PARTS,
		TYPE_OBJECT3D,
		TYPE_ENITY,
		TYPE_HOOK,
		TYPE_HUMAN,
		TYPE_FLOR,
		TYPE_ENEMY,
		TYPE_BLOCK,
		TYPE_MAX,

	}TYPE;

	CObject(int nPriority=3);
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static void ReleaseAll();	//全オブジェクトの解放
	static void UpdateAll();	//全オブジェクトの更新
	static void DrawAll();		//全オブジェクト描画
	static CObject* GetTop(int nPriority);
	CObject* GetpNext();
	TYPE GetType();					//タイプの取得
	void SetType(TYPE type);			//タイプの設定
	void Deathflag();
protected:
	void Release();				//自分自身の解放
private:
	TYPE m_Type;							//タイプ
	int m_nPriority;
	static int m_nNumAll[5];				//オブジェクトの総数
	static CObject* m_pTop[5];			//先頭オブジェクトのポインタ
	static CObject* m_pCur[5];			//最後尾オブジェクトのポインタ
	CObject* m_pPrev;					//前のポインタ
	CObject* m_pNext;					//後のポインタ
	bool m_bDeath;						//死亡フラグ
};
#endif