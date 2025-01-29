//
//���͂̃w�b�_
//

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

#define MAX_KEY	256


//=============================
// ���͏����̃N���X
//=============================
class CInput
{

public:
	CInput();   //�R���X�g���N�^
	~CInput();   //�f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);   //����������
	virtual void Uninit();   //�I������
	virtual void Update() = 0;   //�X�V����

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;   //�f�o�C�X
	static LPDIRECTINPUT8 m_pInput;   //����
};


#endif
