//========================================================================================================
//
//ジョイパッド入力処理[joypad.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "joypad.h"

//静的メンバ変数を初期化する
const int CJoypad::MAX;   //最大数

//========================================================================================================
//コンストラクタ
//========================================================================================================
CJoypad::CJoypad()
{
	for (int i = 0; i < MAX; i++)
	{
		m_aState[i] = {};   //状態
		m_aStateTrigger[i] = {};   //状態
		m_bButtonPressed[i] = {};
	}
}

//========================================================================================================
//デストラクタ
//========================================================================================================
CJoypad::~CJoypad()
{
}

//=================================================================
// ジョイパッドの初期化処理
//=================================================================
HRESULT CJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	for (int i = 0; i < MAX; i++)
	{
		m_bButtonPressed[i] = false;

		//メモリのクリア
		memset(&m_aState[i], 0, sizeof(XINPUT_STATE));
	}

	//XInputのステートを設定（有効にする）
	XInputEnable(true);

	return S_OK;
}

//=================================================================
// ジョイパッドの終了処理
//=================================================================
void CJoypad::Uninit(void)
{
	//XInputのステートを設定（無効にする）
	XInputEnable(false);
}

//=================================================================
// ジョイパッドの更新処理
//=================================================================
void CJoypad::Update(void)
{
	XINPUT_STATE joykeyState;	//ジョイパッドの入力情報
	XINPUT_STATE sThumbLX;
	XINPUT_STATE sThumbLY;
	//ジョイパッドの情報を取得
	for (int i = 0; i < MAX; i++)
	{
		if (XInputGetState(i, &joykeyState) == ERROR_SUCCESS)
		{
			if (m_aStateTrigger[i].Gamepad.wButtons != joykeyState.Gamepad.wButtons)
			{
				// トリガー情報を取得
				m_aStateTrigger[i] = joykeyState;
				m_bButtonPressed[i] = false;
			}
			else
			{
				m_bButtonPressed[i] = true;
			}

			// プレス情報を取得
			m_aState[i] = joykeyState;
		}
	}

}

//=================================================================
// ジョイパッドのプレス情報を取得
//=================================================================
bool CJoypad::GetPress(JOYKEY key, int nId)
{
	return (m_aState[nId].Gamepad.wButtons & key) ? true : false;
}


//=================================================================
// ジョイパッドのトリガー情報を取得
//=================================================================
bool CJoypad::GetTrigger(JOYKEY key, int nId)
{
	// ボタンの状態を取得
	bool button_state = (m_aStateTrigger[nId].Gamepad.wButtons & key) ? true : false;

	// ボタンが押された瞬間かどうか
	bool button_just_pressed = button_state && !m_bButtonPressed[nId];

	// ボタンが押された瞬間ならtrueを返す
	return button_just_pressed;
}

//=================================================================
// ジョイパッドの状態を取得
//=================================================================
XINPUT_STATE* CJoypad::GetState(int nId)
{
	return &m_aState[nId];
}