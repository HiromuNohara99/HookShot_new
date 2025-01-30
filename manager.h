//========================================
//ä«óùé“ÉwÉbÉ_
//========================================
#include "main.h"
#include "InputKeyboard.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "joypad.h"
#include "time.h"
#ifndef MANAGER_H_
#define MANAGER_H_

//=======================
//ä«óùé“ÇÃê∂ê¨
//=======================
class CManager
{
public:
	
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hwnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();
	static CRenderer* GetRenederer();
	static CKeyboard* GetKeyboard();
	static CCamera* GetCamera();
	static CLight* GetLight();
	static CScene* GetScene();
	static CJoypad* GetJoypad();

	static void SetScene(CScene::SCENE scene);
protected:

private:
	static CRenderer* m_pRenderer;
	static CKeyboard* m_pKeyboard;
	static CCamera* m_pCamera;
	static CLight* m_pLight;
	static CScene* m_pScene;
	static CJoypad* m_pJoypad;

};
#endif