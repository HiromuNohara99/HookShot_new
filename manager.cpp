//================================
//
// �Ǘ��҂̃��C������
// 
//================================
#include "manager.h"
#include "object.h"
#include "renderer.h"
#include "InputKeyboard.h"
#include "light.h"

//�ÓI�����o�̏�����
CRenderer* CManager::m_pRenderer = nullptr;
CKeyboard* CManager::m_pKeyboard = nullptr;
CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;
CScene* CManager::m_pScene = nullptr;
CJoypad* CManager::m_pJoypad = nullptr;

//==============================
// �R���X�g���N�^
//==============================
CManager::CManager()
{

}

//==============================
//  �f�X�g���N�^
//==============================
CManager::~CManager()
{

}

//==============================
// �@������
//==============================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hwnd, bool bWindow)
{
	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
	//�����_���[�̍쐬
	m_pRenderer = new CRenderer();
	m_pRenderer->Init(hInstance, hwnd, bWindow);

	//�L�[�{�[�h�̎擾
	m_pKeyboard = new CKeyboard();
	m_pKeyboard->Init(hInstance, hwnd);

	//�J�����̎擾
	m_pCamera = new CCamera();
	m_pCamera->Init();

	//���C�g�̎擾
	m_pLight = new CLight();
	m_pLight->Init();

	

	m_pJoypad = new CJoypad();
	m_pJoypad->Init(hInstance, hwnd);
	
	SetScene(CScene::SCENE::SCENE_GAME);
	
	return S_OK;
}

//==============================
// �@�I������
//==============================
void CManager::Uninit()
{

	//�L�[�{�[�h
	m_pKeyboard->Uninit();
	delete m_pKeyboard;
	m_pKeyboard = nullptr;

	//�J����
	m_pCamera->Uninit();
	delete m_pCamera;
	m_pCamera = nullptr;

	//���C�g
	m_pLight->Uninit();
	delete m_pLight;
	m_pLight = nullptr;

	//�V�[��
	m_pScene->Uninit();
	delete m_pScene;
	m_pScene = nullptr;

	//�Q�[���p�b�h
	m_pJoypad->Uninit();
	delete m_pJoypad;
	m_pJoypad = nullptr;
	

	//�����_���[
	m_pRenderer->Uninit();
	delete m_pRenderer;
	m_pRenderer = nullptr;


}

//==============================
// �@�X�V����
//==============================
void CManager::Update()
{
	//�����_���[
	m_pRenderer->Update();
	
	//�J����
	m_pCamera->Update();

	//�L�[�{�[�h
	m_pKeyboard->Update();

	//���C�g
	m_pLight->Update();

	//�V�[��
	m_pScene->Update();

	//���[�ނς���
	m_pJoypad->Update();

	
}

//==============================
// �@�`�揈��
//==============================
void CManager::Draw()
{
	//�����_���[
	m_pRenderer->Draw();

	//�V�[��
	m_pScene->Draw();
}

//==============================
// �@�Ǘ��҂̎擾
//==============================
CRenderer* CManager::GetRenederer()
{
	return m_pRenderer;
}

//=============================
// �L�[�{�[�h�̎擾
//=============================
CKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;

}

//=============================
// �J�����̎擾
//=============================
CCamera* CManager::GetCamera()
{
	return m_pCamera;
}

//=============================
// �J�����̎擾
//=============================
CScene* CManager::GetScene()
{
	return m_pScene;
}

//=============================
// ���C�g�̎擾
//=============================
CLight* CManager::GetLight()
{
	return m_pLight;
}

//=================================
//	�Q�[���p�b�h�̎擾
//=================================
CJoypad* CManager::GetJoypad()
{
	return m_pJoypad;
}

//====================================
//

//======================================
//	�V�[���̕ύX
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