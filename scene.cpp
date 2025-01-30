//====================================================
//
//	��ʑJ�ڂ̏���
//
//=====================================================
#include "scene.h"
#include "game.h"
#include "object.h"

#include "manager.h"

/*
* �R���X�g���N�^
*/
CScene::CScene()
{

}

/*
 * �f�X�g���N�^
 */
CScene::~CScene()
{

}

//=======================================================
//�@����������
//=======================================================
HRESULT CScene::Init()
{
	
	return S_OK;
}

//=======================================================
//�@�I������
//=======================================================
void CScene::Uninit()
{
	
	CObject::ReleaseAll();
}

//=======================================================
//�@�X�V����
//=======================================================
void CScene::Update()
{
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //�L�[�{�[�h

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
//�@�`�揈��
//=======================================================
void CScene::Draw()
{
	CObject::DrawAll();
}

//=======================================================
//�@
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