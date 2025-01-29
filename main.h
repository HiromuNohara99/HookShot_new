//
// main�w�b�_
//

#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <chrono>
#include <XInput.h>
#include "d3dx9.h"		//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)   //�r���h���̌x���̏��p�̃}�N��
#include "dinput.h"		//���͏����ɕK�v
#include "renderer.h"
//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")			//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]�ɕK�v
#pragma comment(lib,"dxguid.lib")		//Directx�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")			//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")		//���͏����ɕK�v
#pragma comment(lib, "Xinput.lib")		//�p�b�h�ɕK�v
#include <d3dx9math.h>
//�}�N����`
#define SCREEN_WIDTH	(1280)		//�E�B���h�E�̕�
#define SCREEN_HEIGTH	(720)		//�E�B���h�E�̍���
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


//�v���g�^�C�v�錾
void SetMode(MODE mode);
MODE GetMode(void);
int GetFPS(void);
//CRenderer* GetRenderer() { return g_pRenderer };


//���_���
//typedef struct
//{
//	D3DXVECTOR3 pos;		//���_���W
//	float rhw;				//���W�ϊ��p�W��
//	D3DCOLOR col;			//���_�J���[
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
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

#endif

