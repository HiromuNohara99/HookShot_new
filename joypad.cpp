//========================================================================================================
//
//�W���C�p�b�h���͏���[joypad.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "joypad.h"

//�ÓI�����o�ϐ�������������
const int CJoypad::MAX;   //�ő吔

//========================================================================================================
//�R���X�g���N�^
//========================================================================================================
CJoypad::CJoypad()
{
	for (int i = 0; i < MAX; i++)
	{
		m_aState[i] = {};   //���
		m_aStateTrigger[i] = {};   //���
		m_bButtonPressed[i] = {};
	}
}

//========================================================================================================
//�f�X�g���N�^
//========================================================================================================
CJoypad::~CJoypad()
{
}

//=================================================================
// �W���C�p�b�h�̏���������
//=================================================================
HRESULT CJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	for (int i = 0; i < MAX; i++)
	{
		m_bButtonPressed[i] = false;

		//�������̃N���A
		memset(&m_aState[i], 0, sizeof(XINPUT_STATE));
	}

	//XInput�̃X�e�[�g��ݒ�i�L���ɂ���j
	XInputEnable(true);

	return S_OK;
}

//=================================================================
// �W���C�p�b�h�̏I������
//=================================================================
void CJoypad::Uninit(void)
{
	//XInput�̃X�e�[�g��ݒ�i�����ɂ���j
	XInputEnable(false);
}

//=================================================================
// �W���C�p�b�h�̍X�V����
//=================================================================
void CJoypad::Update(void)
{
	XINPUT_STATE joykeyState;	//�W���C�p�b�h�̓��͏��
	XINPUT_STATE sThumbLX;
	XINPUT_STATE sThumbLY;
	//�W���C�p�b�h�̏����擾
	for (int i = 0; i < MAX; i++)
	{
		if (XInputGetState(i, &joykeyState) == ERROR_SUCCESS)
		{
			if (m_aStateTrigger[i].Gamepad.wButtons != joykeyState.Gamepad.wButtons)
			{
				// �g���K�[�����擾
				m_aStateTrigger[i] = joykeyState;
				m_bButtonPressed[i] = false;
			}
			else
			{
				m_bButtonPressed[i] = true;
			}

			// �v���X�����擾
			m_aState[i] = joykeyState;
		}
	}

}

//=================================================================
// �W���C�p�b�h�̃v���X�����擾
//=================================================================
bool CJoypad::GetPress(JOYKEY key, int nId)
{
	return (m_aState[nId].Gamepad.wButtons & key) ? true : false;
}


//=================================================================
// �W���C�p�b�h�̃g���K�[�����擾
//=================================================================
bool CJoypad::GetTrigger(JOYKEY key, int nId)
{
	// �{�^���̏�Ԃ��擾
	bool button_state = (m_aStateTrigger[nId].Gamepad.wButtons & key) ? true : false;

	// �{�^���������ꂽ�u�Ԃ��ǂ���
	bool button_just_pressed = button_state && !m_bButtonPressed[nId];

	// �{�^���������ꂽ�u�ԂȂ�true��Ԃ�
	return button_just_pressed;
}

//=================================================================
// �W���C�p�b�h�̏�Ԃ��擾
//=================================================================
XINPUT_STATE* CJoypad::GetState(int nId)
{
	return &m_aState[nId];
}