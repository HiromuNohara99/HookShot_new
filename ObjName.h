//===============================================
//
//	�I�u�W�F�N�g�̎�ނ̊Ǘ�
// Author�@Nohara�@Hiromu
//	
//===============================================
#ifndef OBJNAME_H_
#define OBJNAME_H_

#include "main.h"

class CObjName
{
public:
	void Init();
	static void ObjSave(char* aTexture);
	static char* ObjLoad(int nCnt);
	static void FlorSave(char* aTexture);
	static char* FlorLoad(int nCnt);
private:
	static char m_ObjTexture[64][64];		//�e�N�X�`���̐�
	static char m_FlorTexture[64][64];
	static int m_ObjnCnt;
	static int m_FlorCnt;
};


#endif // OBJNAME_H_

