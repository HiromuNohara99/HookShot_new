//=================================
//
// 
//Autor�@Nohara Hiromu
//=========================
#include "main.h"
#include "manager.h"
//�}�N����`
#define CLASS_NAME	"Window Class"		//�E�B���h�E�N���X
#define WINDOW_NAME	"Time Hook"	//�E�B���h�E�̖��O


//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMeg, WPARAM wParam, LPARAM iParam);


//�O���[�o���֐�
LPDIRECT3D9	g_pD3D = nullptr;
LPDIRECT3DDEVICE9 g_pD3DDevice = nullptr;
MODE g_mode = MODE_TITLE;
		//�t�H���g�̃|�C���^]
#ifdef _DEBUG
int g_nCountFPS = 0;				//FPS�J�E���^
#endif
CManager* g_pManagerer = nullptr;		//�}�l�[�W���[

//CRenderer* GetRenderer()
//{
//	return g_pRenderer;
//}


//=============================
//���C���֐�
//=============================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,							//WINDCLASSEX�̃������J�C�Y
		WindowProc,							//�E�B���h�E�̃X�^�C��
		0,									//0�ɂ���
		0,									//0�ɂ���
		hInstance,							//�C���X�^���X�n���h��
		LoadIcon(nullptr,IDI_APPLICATION),		//�^�X�N�o�[�A�C�R��
		LoadCursor(nullptr,IDI_APPLICATION),	//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C�A���g�̈�̔w�i�F
		nullptr,								//���j���[�o�[
		CLASS_NAME,							//�E�B���h�E�̖��O
		LoadIcon(nullptr,IDI_APPLICATION),		//�t�@�C���̃A�C�R��
	};
	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGTH };

	//�E�B���h�E�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);


	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,		//�g���E�B���h�E�X�^�C��
		CLASS_NAME,					//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,				//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,				//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,				//�E�B���h�E�̍����Y���W
		(rect.right - rect.left),			//�E�B���h�E�̕�
		(rect.bottom - rect.top),			//�E�B���h�E�̍���
		nullptr,						//�e�E�B���h�E�̃n���h��
		nullptr,						//���j���[�n���h���܂��͎q�E�B���h�Eid
		hInstance,					//�C���X�^���X�n���h��
		nullptr);						//�E�B���h�E�쐬�f�[�^

	DWORD dwCurrentTime =0;		//���݂̎���
	DWORD dwExecLastTime =timeGetTime();		//�Ō�ɏ�����������
#ifdef _DEBUG
	DWORD dwFrameCount=0;			//�t���[���A�E���g
	DWORD dwFPSLastTime = dwExecLastTime;		//�Ō��FPS���v����������

#endif

	//�}�[�W���[����
	g_pManagerer = new CManager();
	
	//����������
	if (FAILED(g_pManagerer->Init(hInstance,hWnd, TRUE)))
	{
		//���������������s�����Ƃ�
		return-1;
	}
	
	//�����\�̐ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = 0;
	
	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);		//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);				//�N���C�A���g�̈�̍X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
		{//Window�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�I��
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//Directx�̏���
			dwCurrentTime = timeGetTime();		//���݂̎����ݒ�
#ifdef _DEBUG
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�o��
			 // FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;    // FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;                // �t���[���J�E���g���N���A
			}


#endif
			
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60/1�b�o��
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				g_pManagerer->Update();
				
				//�`�揈��
				g_pManagerer->Draw();
			
#ifdef _DEBUG
				dwFrameCount++;                    // �t���[���J�E���g�����Z
#endif
			}
		}
	}
	//�I������
	g_pManagerer->Uninit();
	delete g_pManagerer;		//�}�l�[�W���[
	g_pManagerer = nullptr;

	//�E�B���h�E�N���X�̓o�^����
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMeg, WPARAM wParam, LPARAM iParam)
{
	int nID;
	switch (uMeg)
	{
		case WM_DESTROY :
		WM_QUIT;
		PostQuitMessage(0);
		break;
	case WM_CLOSE:								//�o�c����������Ƃ��ɂق�ƂɎ~�܂邩�ǂ���
		nID = MessageBox(hwnd, "�I�����܂���", "�I��", MB_YESNO);
		if (nID == IDYES)
		{
			DestroyWindow(hwnd);
		}
		else
		{
			return 0;
		}
		break;
	case WM_KEYDOWN:		//�L�[
		switch (wParam)
		{
		case VK_ESCAPE:		//ESC�L�[�������ꂽ
				//���b�Z�[�W�̕\��

			nID = MessageBox(hwnd, "�I�����܂����H", "title", MB_YESNO | MB_ICONQUESTION);

			if (nID == IDYES)
			{
				//MessageBox(hwnd, "�͂�", "Answer", MB_OK);
				DestroyWindow(hwnd);
			}
			if (nID == IDNO)
			{
				//MessageBox(hwnd, "������", "Answer", MB_OK);
			}

			//DestroyWindow(hwnd);
			break;
		}

		break;
	}
	
	return DefWindowProc(hwnd, uMeg, wParam, iParam);
}

//���[�h�̐ݒ�
void SetMode(MODE mode)
{
	g_mode = mode;
}

//���[�h�̎擾
MODE GetMode(void)
{
	return g_mode;
}

#ifdef _DEBUG
int GetFPS(void)
{
	return g_nCountFPS;
}
#endif