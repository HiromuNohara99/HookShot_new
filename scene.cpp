//====================================================
//
//	画面遷移の処理
//
//=====================================================
#include "scene.h"
#include "game.h"
#include "object.h"

#include "manager.h"

/*
* コンストラクタ
*/
CScene::CScene()
{

}

/*
 * デストラクタ
 */
CScene::~CScene()
{

}

//=======================================================
//　初期化処理
//=======================================================
HRESULT CScene::Init()
{
	
	return S_OK;
}

//=======================================================
//　終了処理
//=======================================================
void CScene::Uninit()
{
	
	CObject::ReleaseAll();
}

//=======================================================
//　更新処理
//=======================================================
void CScene::Update()
{
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //キーボード

	CObject::UpdateAll();
	if (m_pKeyboard->GetTrigger(DIK_P)==true)
	{
		switch (m_Scene)
		{
		case SCENE_GAME:
			CManager::SetScene(CScene::SCENE_TITLE);
			break;
		case SCENE_TITLE:
			CManager::SetScene(CScene::SCENE_GAME);
			break;
		default:

			break;
		}
		
	}

}

//=======================================================
//　描画処理
//=======================================================
void CScene::Draw()
{
	CObject::DrawAll();
}

//=======================================================
//　
//=======================================================
CScene* CScene::Create(SCENE Scene)
{
	CScene* pScene = nullptr;

	switch (Scene)
	{
	case SCENE_GAME:
		pScene = new CGame;
		break;
	/*case SCENE_TITLE:
		pScene = new CTitle;
		break;*/
	default:

		break;
	}


	pScene->m_Scene = Scene;
	pScene->Init();
	return pScene;
}