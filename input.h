//
//入力のヘッダ
//

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

#define MAX_KEY	256


//=============================
// 入力処理のクラス
//=============================
class CInput
{

public:
	CInput();   //コンストラクタ
	~CInput();   //デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);   //初期化処理
	virtual void Uninit();   //終了処理
	virtual void Update() = 0;   //更新処理

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;   //デバイス
	static LPDIRECTINPUT8 m_pInput;   //入力
};


#endif
