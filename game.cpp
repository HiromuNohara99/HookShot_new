/*
*
*	ゲームの処理[game.cpp]
*	Author Nohara Hiromu
*  
*/
#include "game.h"
#include "player.h"
#include "object2D.h"
#include "object3D.h"
#include "manager.h"
#include "flor.h"
#include "ObjName.h"
#include "enity.h"
#include "block.h"

/**
 * .静的メンバの初期化
 */
CObjName* CGame::m_ObjName = nullptr;

//============================================
//	コンストラクタ
//============================================
CGame::CGame()
{

}

//============================================
//	デストラクタ
//============================================
CGame::~CGame()
{

}

//============================================
//　初期化
//============================================
HRESULT CGame::Init()
{
	m_ObjName = new CObjName;
	m_ObjName->Init();
	//ステージのロード
	Load();
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	for (int nCnt = 0 ; nCnt < 10; nCnt++)
	{
		CBlock::Create(D3DXVECTOR3(60.0f*nCnt-30.0f, -50.0f, 0.0f));
	}
	
	CScene::Init();

	return S_OK;
}

//============================================
//　終了
//============================================
void CGame::Uninit()
{
	delete m_ObjName;
	m_ObjName = nullptr;
}

//============================================
//　更新処理
//============================================
void CGame::Update()
{
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //キーボード
	CScene::Update();
}

//============================================
//　描画処理
//============================================
void CGame::Draw()
{
	CScene::Draw();
	
}

/**.
 *	ステージの読み込み
 */
void CGame::Load()
{
	//変数宣言
	FILE* pFile = nullptr;
	char aString[128];
	char aTexture[64];
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//方向
	int nSize = 0;
	int nType = 0;				//タイプ
	pFile = fopen("data/Stage/Stage.txt", "r");
	if (pFile == nullptr)
	{
		return;
	}
	while (1)
	{
		fscanf(pFile, "%s", &aString[0]);

		/**.
		 *	オブジェクトの数
		 */
		if (strcmp(&aString[0], "NUM_MODEL") == 0)
		{
			fscanf(pFile, "%s", &aString[0]);
			fscanf(pFile, "%d", &m_Num);
		}

		/**
		 * . オブジェクトの名前
		 */
		if (strcmp(&aString[0], "OBJECT_NAME") == 0)
		{
			fscanf(pFile, "%s", &aString[0]);
			fscanf(pFile, "%s", &aTexture);
			CObjName::ObjSave(aTexture);
		}

		/**.
		 *	テクスチャの数
		 */
		if (strcmp(&aString[0], "NUM_TEXTURE") == 0)
		{
			fscanf(pFile, "%s", &aString[0]);
			fscanf(pFile, "%d", &m_FlorNum);
		}

		/**
		 * . テクスチャの名前
		 */
		if (strcmp(&aString[0], "TEXTURE_NAME") == 0)
		{
			fscanf(pFile, "%s", &aString[0]);
			fscanf(pFile, "%s", &aTexture);
			CObjName::FlorSave(aTexture);
		}

		/**
		 * .ブロックの設置
		 */
		if (strcmp(&aString[0], "BLOCK_SET") == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp(&aString[0], "POS") == 0)
				{
					fscanf(pFile, "%s %f %f %f",
						&aString[0],
						&pos.x,
						&pos.y,
						&pos.z);
				}
				if (strcmp(&aString[0], "ROT") == 0)
				{
					fscanf(pFile, "%s %f %f %f",
						&aString[0],
						&rot.x,
						&rot.y,
						&rot.z);
				}
				if (strcmp(&aString[0], "TYPE") == 0)
				{
					fscanf(pFile, "%s %d",
						&aTexture[0],
						&nType);
				}
				if (strcmp(&aString[0], "BLOCK_END") == 0)
				{
					CEnity::Create(pos, rot, nType);

					break;
				}
			}

		}

		/**.
		 *	床の設置
		 */
		if (strcmp(&aString[0], "FLOR_SET") == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp(&aString[0], "POS") == 0)
				{
					fscanf(pFile, "%s %f %f %f",
						&aString[0],
						&pos.x,
						&pos.y,
						&pos.z);
				}
				if (strcmp(&aString[0], "SIZE") == 0)
				{
					fscanf(pFile, "%s %d",
						&aString[0],
						&nSize);
				}
				if (strcmp(&aString[0], "TYPE") == 0)
				{
					fscanf(pFile, "%s %d",
						&aTexture[0],
						&nType);
				}
				if (strcmp(&aString[0], "FLOR_END") == 0)
				{
					CFlor::Create(pos, nSize, nType);

					break;
				}
			}

		}

		if (strcmp(&aString[0], "STAGE_END") == 0)
		{
			break;
		}

	}

	fclose(pFile);

	//CFlor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),100000.0f,0);
}