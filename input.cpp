//================================
// 
// 入力の処理 [input.h]
// Author:Nohara Hiromu
// 
//================================
#include "input.h"

//静的メンバ変数を初期化する
LPDIRECTINPUT8 CInput::m_pInput = nullptr;   //入力

//-------------------
//コンストラクタ
//-------------------
CInput::CInput():m_pDevice(nullptr)
{

}

//-------------------
// //デストラクタ
//-------------------
CInput::~CInput()
{
}

//-------------------
// //初期化処理
//-------------------
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{//入力がない場合
	//DirectInputオブジェクトを生成する
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, nullptr)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//-------------------
// //終了処理
//-------------------
void CInput::Uninit()
{
	//入力デバイスを破棄する
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
}