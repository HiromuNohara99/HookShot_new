//
//入力のヘッダ
//

#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

#include "input.h"

class CKeyboard : public CInput
{
public:
	static const int MAX = 256;   //キーの数

	CKeyboard();   //コンストラクタ
	~CKeyboard();  //デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;   //初期化処理
	void Uninit() override;   //終了処理
	void Update() override;   //更新処理
	bool GetPress(int nKey);   //プレス情報の取得処理
	bool GetTrigger(int nKey);   //トリガー情報の取得処理

private:
	BYTE m_aState[MAX];   //状態
	BYTE m_aStateTrigger[MAX];   //トリガー状態
};



#endif
