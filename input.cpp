//================================
// 入力の処理
//================================
#include "input.h"

//静的メンバ変数を初期化する
LPDIRECTINPUT8 CInput::m_pInput = nullptr;   //入力

//-------------------
//コンストラクタ
//-------------------
CInput::CInput()
{
	//メンバ変数を初期化する
	m_pDevice = nullptr;   //デバイス
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







////キーボードの初期化処理
//HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
//{
//	//DirectInputオブジェクトの生成
//	if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
//		IID_IDirectInput8,(void**)&g_pInput, nullptr)))
//	{
//		return E_FAIL;
//	}
//	//入力デバイスの生成
//	if(FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, nullptr)))
//	{
//		return E_FAIL;
//	}
//	//データほぁーまっとを設定
//	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
//	{
//		return E_FAIL;
//	}
//
//	//協調モードの設定
//	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
//	{
//		return E_FAIL;
//	}
//	//キーボードへのアクセス権を獲得
//	g_pDevKeyboard->Acquire();
//	return S_OK;
//}
//
//
//
//	//キーボードの終了処理
//	void UnintKeyboard(void)
//	{
//		//入力デバイスの破棄
//		if (g_pDevKeyboard != nullptr)
//		{
//			g_pDevKeyboard->Unacquire();
//			g_pDevKeyboard-> Release();
//			g_pDevKeyboard = nullptr;
//		}
//		//DirectInputオブジェクト
//		if (g_pInput != nullptr)
//		{
//			g_pInput->Release();
//			g_pInput = nullptr;
//		}
//	}
//	//キーボードの更新処理
//	void UpdateKeyboard(void)
//	{
//		BYTE aKeyState[NUM_KEY_MAX];
//		//BYTE aKeyStateTrigger[NUM_KEY_MAX];
//		int nCntKey;
//		//入力デバイスからデータ取得
//		if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
//		{
//			for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
//			{
//
//				g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
//
//				g_aKeyState[nCntKey] = aKeyState[nCntKey];
//			}
//		}
//		else
//		{
//			g_pDevKeyboard->Acquire();		//キーボードのアクセス権
//		}
//	}
//
//	bool GetKeyboardPress(int nKey)
//	{
//		return(g_aKeyState[nKey] & 0x80) != 0;
//	}
//
//	bool GetKeyboardTrigger(int nKey)
//	{
//		return(g_aKeyStateTrigger[nKey] & 0x80) != 0;
//	}