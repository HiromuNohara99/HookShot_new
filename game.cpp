/*
*
*	�Q�[���̏���[game.cpp]
*	Author Nohara Hiromu
*  
*/
#include "game.h"
#include "player.h"
#include "object3D.h"
#include "manager.h"
#include "flor.h"
#include "ObjName.h"
#include "enity.h"
#include "block.h"

//============================================
//	�R���X�g���N�^
//============================================
CGame::CGame()
{

}

//============================================
//	�f�X�g���N�^
//============================================
CGame::~CGame()
{

}

//============================================
//�@������
//============================================
HRESULT CGame::Init()
{
	Load();
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CBlock::Create(D3DXVECTOR3(-20.0f, 0.0f, 0.0f));
	CFlor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),500.0f,0);
	CScene::Init();

	return S_OK;
}

//============================================
//�@�I��
//============================================
void CGame::Uninit()
{
	//m_System->Uninit();
	//delete m_System;
	//m_System = nullptr;
	//CScene::Uninit();
}

//============================================
//�@�X�V����
//============================================
void CGame::Update()
{
	CKeyboard* m_pKeyboard = CManager::GetKeyboard();   //�L�[�{�[�h
//	m_System->Update();

	CScene::Update();
}

//============================================
//�@�`�揈��
//============================================
void CGame::Draw()
{
	CScene::Draw();
	
}

/**.
 * �V�X�e���̏��擾
 */
//CSystem* CGame::GetSystem()
//{
//	return m_System;
//}

/**.
 *	�X�e�[�W�̓ǂݍ���
 */
void CGame::Load()
{
	//�ϐ��錾
	FILE* pFile = nullptr;
	char aString[128];
	char aTexture[64];
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	int nSize = 0;
	int nType = 0;				//�^�C�v
	pFile = fopen("data/Stage/Stage.txt", "r");
	if (pFile == nullptr)
	{
		return;
	}
	while (1)
	{
		fscanf(pFile, "%s", &aString[0]);

		/**.
		 *	�I�u�W�F�N�g�̐�
		 */
		if (strcmp(&aString[0], "NUM_MODEL") == 0)
		{
			fscanf(pFile, "%s", &aString[0]);
			fscanf(pFile, "%d", &m_Num);
		}

		/**
		 * . �I�u�W�F�N�g�̖��O
		 */
		if (strcmp(&aString[0], "OBJECT_NAME") == 0)
		{
			fscanf(pFile, "%s", &aString[0]);
			fscanf(pFile, "%s", &aTexture);
			CObjName::ObjSave(aTexture);
		}

		/**.
		 *	�e�N�X�`���̐�
		 */
		if (strcmp(&aString[0], "NUM_TEXTURE") == 0)
		{
			fscanf(pFile, "%s", &aString[0]);
			fscanf(pFile, "%d", &m_FlorNum);
		}

		/**
		 * . �e�N�X�`���̖��O
		 */
		if (strcmp(&aString[0], "TEXTURE_NAME") == 0)
		{
			fscanf(pFile, "%s", &aString[0]);
			fscanf(pFile, "%s", &aTexture);
			CObjName::FlorSave(aTexture);
		}

		/**
		 * .�u���b�N�̐ݒu
		 */
		if (strcmp(&aString[0], "BLOCK_SET") == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp(&aString[0], "POS") == 0)
				{
					fscanf(pFile, "%s %f %f %f",
						&aString[0],
						&pos.x,
						&pos.y,
						&pos.z);
				}
				if (strcmp(&aString[0], "ROT") == 0)
				{
					fscanf(pFile, "%s %f %f %f",
						&aString[0],
						&rot.x,
						&rot.y,
						&rot.z);
				}
				if (strcmp(&aString[0], "TYPE") == 0)
				{
					fscanf(pFile, "%s %d",
						&aTexture[0],
						&nType);
				}
				if (strcmp(&aString[0], "BLOCK_END") == 0)
				{
					CEnity::Create(pos, rot, nType);

					break;
				}
			}

		}

		/**.
		 *	���̐ݒu
		 */
		if (strcmp(&aString[0], "FLOR_SET") == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp(&aString[0], "POS") == 0)
				{
					fscanf(pFile, "%s %f %f %f",
						&aString[0],
						&pos.x,
						&pos.y,
						&pos.z);
				}
				if (strcmp(&aString[0], "SIZE") == 0)
				{
					fscanf(pFile, "%s %d",
						&aString[0],
						&nSize);
				}
				if (strcmp(&aString[0], "TYPE") == 0)
				{
					fscanf(pFile, "%s %d",
						&aTexture[0],
						&nType);
				}
				if (strcmp(&aString[0], "FLOR_END") == 0)
				{
					CFlor::Create(pos, nSize, nType);

					break;
				}
			}

		}

		if (strcmp(&aString[0], "STAGE_END") == 0)
		{
			break;
		}

	}

	fclose(pFile);

	//CFlor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),100000.0f,0);
}
