//========================================
//	
// レンダラーの処理	[renderer.h]
//	Author Nohara Hiromu
// 
//========================================
#ifndef RENDERER_H_
#define RENDERER_H_

#include "d3dx9.h"		//描画処理に必要
#include <windows.h>

#define SCREEN_WIDTH	(1280)		//ウィンドウの幅
#define SCREEN_HEIGTH	(720)		//ウィンドウの高さ
//=======================
//レンダラークラスの生成
//=======================
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HINSTANCE hInstance,HWND hwnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	LPDIRECT3DDEVICE9 GetDevice();
private:
	void DrawFPS();
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;


#ifdef _DEBUG
	LPD3DXFONT m_pFont = nullptr;
#endif
};

#endif
