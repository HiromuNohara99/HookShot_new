//===============================================
//
//	�I�u�W�F�N�g�̎�ނ̊Ǘ�
// Author�@Nohara�@Hiromu
//	
//===============================================
#ifndef OBJNAME_H_
#define OBJNAME_H_

#include "main.h"

#define MAX_CHAE (64)

//������^���������߂̎Q�l����
// https://zenn.dev/reputeless/books/standard-cpp-for-competitive-programming/viewer/string

class CObjName
{
public:
	void Init();
	static void ObjSave(char* aTexture);
	static char* ObjLoad(int nCnt);
	static void FlorSave(char* aTexture);
	static char* FlorLoad(int nCnt);
private:
	static char m_ObjTexture[MAX_CHAE][MAX_CHAE];		//�e�N�X�`���̐�
	static char m_FlorTexture[MAX_CHAE][MAX_CHAE];
	static int m_ObjnCnt;
	static int m_FlorCnt;
};


#endif // OBJNAME_H_

