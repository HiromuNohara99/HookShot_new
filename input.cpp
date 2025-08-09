//================================
// 
// ���͂̏��� [input.h]
// Author:Nohara Hiromu
// 
//================================
#include "input.h"

//�ÓI�����o�ϐ�������������
LPDIRECTINPUT8 CInput::m_pInput = nullptr;   //����

//-------------------
//�R���X�g���N�^
//-------------------
CInput::CInput():m_pDevice(nullptr)
{

}

//-------------------
// //�f�X�g���N�^
//-------------------
CInput::~CInput()
{
}

//-------------------
// //����������
//-------------------
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{//���͂��Ȃ��ꍇ
	//DirectInput�I�u�W�F�N�g�𐶐�����
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, nullptr)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//-------------------
// //�I������
//-------------------
void CInput::Uninit()
{
	//���̓f�o�C�X��j������
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
}