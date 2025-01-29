//
//���͂̃w�b�_
//

#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

#include "input.h"

class CKeyboard : public CInput
{
public:
	static const int MAX = 256;   //�L�[�̐�

	CKeyboard();   //�R���X�g���N�^
	~CKeyboard();  //�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	bool GetPress(int nKey);   //�v���X���̎擾����
	bool GetTrigger(int nKey);   //�g���K�[���̎擾����

private:
	BYTE m_aState[MAX];   //���
	BYTE m_aStateTrigger[MAX];   //�g���K�[���
};



#endif
