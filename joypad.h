//========================================================================================================
//
//ジョイパッド入力処理[joypad.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#include "input.h"


//ジョイパッドクラス
class CJoypad : public CInput
{
public:
	static const int MAX = 4;   //ジョイパッドの最大数

	typedef enum
	{
		JOYKEY_nullptr = 0,
		JOYKEY_UP = XINPUT_GAMEPAD_DPAD_UP,
		JOYKEY_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
		JOYKEY_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
		JOYKEY_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
		JOYKEY_START = XINPUT_GAMEPAD_START,
		JOYKEY_BACK = XINPUT_GAMEPAD_BACK,
		JOYKEY_LT = XINPUT_GAMEPAD_LEFT_THUMB,
		JOYKEY_RT = XINPUT_GAMEPAD_RIGHT_THUMB,
		JOYKEY_LS = XINPUT_GAMEPAD_LEFT_SHOULDER,
		JOYKEY_RS = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		JOYKEY_A = XINPUT_GAMEPAD_A,
		JOYKEY_B = XINPUT_GAMEPAD_B,
		JOYKEY_X = XINPUT_GAMEPAD_X,
		JOYKEY_Y = XINPUT_GAMEPAD_Y
	}JOYKEY;   //ジョイパッド

	CJoypad();   //コンストラクタ
	~CJoypad();  //デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;   //初期化処理
	void Uninit() override;   //終了処理
	void Update() override;   //更新処理
	bool GetPress(JOYKEY key, int nId);   //プレス情報の取得処理
	bool GetTrigger(JOYKEY key, int nId);   //トリガー情報の取得処理
	XINPUT_STATE* GetState(int nId);   //ジョイパッド状態の取得処理

private:
	XINPUT_STATE m_aState[MAX];   //状態
	XINPUT_STATE m_aStateTrigger[MAX];   //トリガー状態
	bool m_bButtonPressed[MAX];   //押されたかどうか
};
#endif // !_JOYPAD_H_