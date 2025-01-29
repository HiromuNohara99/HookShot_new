//
// mainヘッダ
//

#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <chrono>
#include <XInput.h>
#include "d3dx9.h"		//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)   //ビルド時の警告体処用のマクロ
#include "dinput.h"		//入力処理に必要
#include "renderer.h"
//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")			//描画処理に必要
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]に必要
#pragma comment(lib,"dxguid.lib")		//Directxコンポーネント使用に必要
#pragma comment(lib,"winmm.lib")			//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")		//入力処理に必要
#pragma comment(lib, "Xinput.lib")		//パッドに必要
#include <d3dx9math.h>
//マクロ定義
#define SCREEN_WIDTH	(1280)		//ウィンドウの幅
#define SCREEN_HEIGTH	(720)		//ウィンドウの高さ
#define MAX_WORD	(256)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

typedef enum
{
	MODE_TITLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_RANK,
	MODE_TUTORIAL,
	MODE_MAX
}MODE;


//プロトタイプ宣言
void SetMode(MODE mode);
MODE GetMode(void);
int GetFPS(void);
//CRenderer* GetRenderer() { return g_pRenderer };


//頂点情報
//typedef struct
//{
//	D3DXVECTOR3 pos;		//頂点座標
//	float rhw;				//座標変換用係数
//	D3DCOLOR col;			//頂点カラー
//	D3DXVECTOR2 tex;
//}VERTEX_2D;

class VERTEX_2D
{
public:
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

class VERTEX_3D
{
public:
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

#endif

