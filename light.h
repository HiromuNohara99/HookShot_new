//
// ligthƒwƒbƒ_
//

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

class CLight
{
public:
	CLight();
	~CLight();
	void Init();
	void Uninit();
	void Update();
private:
	D3DLIGHT9 m_aLight[3];

};
#endif