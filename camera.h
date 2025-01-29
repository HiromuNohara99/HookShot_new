//
// polygonƒwƒbƒ_
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"


class CCamera
{
public:
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetRot();
private:
	D3DXVECTOR3 m_posV;
	D3DXVECTOR3 m_posR;
	D3DXVECTOR3 m_vecU;
	D3DXMATRIX m_mtxProjection;
	D3DXMATRIX m_mtxView;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	float fLengthCamer;			//‘ÎŠpü‚Ì’·‚³
	float fAngleCamera;				//‘ÎŠpü‚ÌŠp“x
	

};


////ƒJƒƒ‰‚Ì\‘¢‘Ì
//typedef struct
//{
//	D3DXVECTOR3 posV;
//	D3DXVECTOR3 posR;
//	D3DXVECTOR3 vecU;
//	D3DXMATRIX mtxProjection;
//	D3DXMATRIX mtxView;
//	D3DXVECTOR3 move;
//	D3DXVECTOR3 rot;
//	float fLengthCamer;			//‘ÎŠpü‚Ì’·‚³
//	float fAngleCamera;				//‘ÎŠpü‚ÌŠp“x
//
//}Camera;
//
//
//void InitCamera(void);
//void UninitCamera(void);
//void UpdateCamera(void);
//void SetCamera(void);
//Camera* GetCamera(void);

#endif

