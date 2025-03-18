//================================
//
// 管理者のメイン処理
// 
//================================
#include "manager.h"
#include "object.h"
#include "renderer.h"
#include "InputKeyboard.h"
#include "light.h"

//静的メンバの初期化
CRenderer* CManager::m_pRenderer = nullptr;
CKeyboard* CManager::m_pKeyboard = nullptr;
CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;
CScene* CManager::m_pScene = nullptr;
CJoypad* CManager::m_pJoypad = nullptr;

//==============================
// コンストラクタ
//==============================
CManager::CManager()
{

}

//==============================
//  デストラクタ
//==============================
CManager::~CManager()
{

}

//==============================
// 　初期化
//==============================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hwnd, bool bWindow)
{
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
	//レンダラーの作成
	m_pRenderer = new CRenderer();
	m_pRenderer->Init(hInstance, hwnd, bWindow);

	//キーボードの取得
	m_pKeyboard = new CKeyboard();
	m_pKeyboard->Init(hInstance, hwnd);

	//カメラの取得
	m_pCamera = new CCamera();
	m_pCamera->Init();

	//ライトの取得
	m_pLight = new CLight();
	m_pLight->Init();

	

	m_pJoypad = new CJoypad();
	m_pJoypad->Init(hInstance, hwnd);
	
	SetScene(CScene::SCENE::SCENE_GAME);
	
	return S_OK;
}

//==============================
// 　終了処理
//==============================
void CManager::Uninit()
{

	//キーボード
	m_pKeyboard->Uninit();
	delete m_pKeyboard;
	m_pKeyboard = nullptr;

	//カメラ
	m_pCamera->Uninit();
	delete m_pCamera;
	m_pCamera = nullptr;

	//ライト
	m_pLight->Uninit();
	delete m_pLight;
	m_pLight = nullptr;

	//シーン
	m_pScene->Uninit();
	delete m_pScene;
	m_pScene = nullptr;

	//ゲームパッド
	m_pJoypad->Uninit();
	delete m_pJoypad;
	m_pJoypad = nullptr;
	

	//レンダラー
	m_pRenderer->Uninit();
	delete m_pRenderer;
	m_pRenderer = nullptr;


}

//==============================
// 　更新処理
//==============================
void CManager::Update()
{
	//レンダラー
	m_pRenderer->Update();
	
	//カメラ
	m_pCamera->Update();

	//キーボード
	m_pKeyboard->Update();

	//ライト
	m_pLight->Update();

	//シーン
	m_pScene->Update();

	//げーむぱっど
	m_pJoypad->Update();

	
}

//==============================
// 　描画処理
//==============================
void CManager::Draw()
{
	//レンダラー
	m_pRenderer->Draw();

	//シーン
	m_pScene->Draw();
}

//==============================
// 　管理者の取得
//==============================
CRenderer* CManager::GetRenederer()
{
	return m_pRenderer;
}

//=============================
// キーボードの取得
//=============================
CKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;

}

//=============================
// カメラの取得
//=============================
CCamera* CManager::GetCamera()
{
	return m_pCamera;
}

//=============================
// カメラの取得
//=============================
CScene* CManager::GetScene()
{
	return m_pScene;
}

//=============================
// ライトの取得
//=============================
CLight* CManager::GetLight()
{
	return m_pLight;
}

//=================================
//	ゲームパッドの取得
//=================================
CJoypad* CManager::GetJoypad()
{
	return m_pJoypad;
}

//====================================
//

//======================================
//	シーンの変更
//======================================
void CManager::SetScene(CScene::SCENE scene)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	 }

	m_pScene = CScene::Create(scene);
}