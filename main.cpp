//=================================
//
// 
//Autor　Nohara Hiromu
//=========================
#include "main.h"
#include "manager.h"
//マクロ定義
#define CLASS_NAME	"Window Class"		//ウィンドウクラス
#define WINDOW_NAME	"Time Hook"	//ウィンドウの名前


//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMeg, WPARAM wParam, LPARAM iParam);


//グローバル関数
LPDIRECT3D9	g_pD3D = nullptr;
LPDIRECT3DDEVICE9 g_pD3DDevice = nullptr;
MODE g_mode = MODE_TITLE;
		//フォントのポインタ]
#ifdef _DEBUG
int g_nCountFPS = 0;				//FPSカウンタ
#endif
CManager* g_pManagerer = nullptr;		//マネージャー

//CRenderer* GetRenderer()
//{
//	return g_pRenderer;
//}


//=============================
//メイン関数
//=============================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,							//WINDCLASSEXのメモリカイズ
		WindowProc,							//ウィンドウのスタイル
		0,									//0にする
		0,									//0にする
		hInstance,							//インスタンスハンドル
		LoadIcon(nullptr,IDI_APPLICATION),		//タスクバーアイコン
		LoadCursor(nullptr,IDI_APPLICATION),	//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			//クライアント領域の背景色
		nullptr,								//メニューバー
		CLASS_NAME,							//ウィンドウの名前
		LoadIcon(nullptr,IDI_APPLICATION),		//ファイルのアイコン
	};
	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGTH };

	//ウィンドウの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調節
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);


	//ウィンドウを生成
	hWnd = CreateWindowEx(0,		//拡張ウィンドウスタイル
		CLASS_NAME,					//ウィンドウクラスの名前
		WINDOW_NAME,				//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,		//ウィンドウスタイル
		CW_USEDEFAULT,				//ウィンドウの左上X座標
		CW_USEDEFAULT,				//ウィンドウの左上のY座標
		(rect.right - rect.left),			//ウィンドウの幅
		(rect.bottom - rect.top),			//ウィンドウの高さ
		nullptr,						//親ウィンドウのハンドル
		nullptr,						//メニューハンドルまたは子ウィンドウid
		hInstance,					//インスタンスハンドル
		nullptr);						//ウィンドウ作成データ

	DWORD dwCurrentTime =0;		//現在の時刻
	DWORD dwExecLastTime =timeGetTime();		//最後に処理した時刻
#ifdef _DEBUG
	DWORD dwFrameCount=0;			//フレームアウント
	DWORD dwFPSLastTime = dwExecLastTime;		//最後のFPSを計測した時刻

#endif

	//マージャー生成
	g_pManagerer = new CManager();
	
	//初期化処理
	if (FAILED(g_pManagerer->Init(hInstance,hWnd, TRUE)))
	{
		//初期化処理が失敗したとき
		return-1;
	}
	
	//分割能の設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = 0;
	
	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);		//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);				//クライアント領域の更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
		{//Windowの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージが受け取ったらメッセージループ終了
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//Directxの処理
			dwCurrentTime = timeGetTime();		//現在の時刻設定
#ifdef _DEBUG
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒経過
			 // FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;    // FPSを測定した時刻を保存
				dwFrameCount = 0;                // フレームカウントをクリア
			}


#endif
			
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60/1秒経過
				dwExecLastTime = dwCurrentTime;

				//更新処理
				g_pManagerer->Update();
				
				//描画処理
				g_pManagerer->Draw();
			
#ifdef _DEBUG
				dwFrameCount++;                    // フレームカウントを加算
#endif
			}
		}
	}
	//終了処理
	g_pManagerer->Uninit();
	delete g_pManagerer;		//マネージャー
	g_pManagerer = nullptr;

	//ウィンドウクラスの登録解除
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
	case WM_CLOSE:								//バツ印を押したときにほんとに止まるかどうか
		nID = MessageBox(hwnd, "終了しますか", "終了", MB_YESNO);
		if (nID == IDYES)
		{
			DestroyWindow(hwnd);
		}
		else
		{
			return 0;
		}
		break;
	case WM_KEYDOWN:		//キー
		switch (wParam)
		{
		case VK_ESCAPE:		//ESCキーが押された
				//メッセージの表示

			nID = MessageBox(hwnd, "終了しますか？", "title", MB_YESNO | MB_ICONQUESTION);

			if (nID == IDYES)
			{
				//MessageBox(hwnd, "はい", "Answer", MB_OK);
				DestroyWindow(hwnd);
			}
			if (nID == IDNO)
			{
				//MessageBox(hwnd, "いいえ", "Answer", MB_OK);
			}

			//DestroyWindow(hwnd);
			break;
		}

		break;
	}
	
	return DefWindowProc(hwnd, uMeg, wParam, iParam);
}

//モードの設定
void SetMode(MODE mode)
{
	g_mode = mode;
}

//モードの取得
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