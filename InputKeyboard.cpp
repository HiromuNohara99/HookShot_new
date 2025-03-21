//======================================
//
//　キーボードの入力のメイン
//
//======================================
#include "InputKeyboard.h"



//静的メンバ変数を初期化する
const int CKeyboard::MAX;   //最大数

//----------------------------------------
//コンストラクタ
//----------------------------------------
CKeyboard::CKeyboard()
{
	for (int i = 0; i < MAX; i++)
	{
		m_aState[i] = {};   //状態
		m_aStateTrigger[i] = {};   //状態
	}
}

//----------------------------------------
//デストラクタ
//----------------------------------------
CKeyboard::~CKeyboard()
{
}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{

	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//キーボードの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, nullptr)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CKeyboard::Uninit()
{
	//入力デバイスを破棄する
	CInput::Uninit();
}

//----------------------------------------
//更新処理
//----------------------------------------
void CKeyboard::Update()
{
	BYTE aKeyState[MAX];

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int i = 0; i < MAX; i++)
		{
			m_aStateTrigger[i] = (m_aState[i] ^ aKeyState[i]) & aKeyState[i];
			m_aState[i] = aKeyState[i];   //キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//----------------------------------------
//プレス情報の取得処理
//----------------------------------------
bool CKeyboard::GetPress(int nKey)
{ 
	return (m_aState[nKey] & 0x80) != 0; 
}

//----------------------------------------
//トリガー情報の取得処理
//----------------------------------------
bool CKeyboard::GetTrigger(int nKey)
{ 
	return(m_aStateTrigger[nKey] & 0x80) != 0; 
}