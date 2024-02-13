//<================================================
//�e�N�X�`���֘A����(Texture.cpp)
//
//Author:kazuki watanabe
//<================================================
#include "Texture.h"
#include "manager.h"

//<************************************************
//�ÓI�����o�ϐ��̐錾
//<************************************************
int CTexture::m_nNumAll = 0;	//�e�N�X�`���̑���

//<===============================
//�e�N�X�`���̃R���X�g���N�^
//<===============================
CTexture::CTexture()
{
	//�e�N�X�`���̃N���A
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_TEX; nCnt++)
	{
		m_apTexture[nCnt] = {nullptr};
		m_apFileName[nCnt] = { nullptr };
	}
}
//<===============================
//�e�N�X�`���̃f�X�g���N�^
//<===============================
CTexture::~CTexture()
{

}
//<===============================
//�e�N�X�`���̓ǂݍ��ݏ���
//<===============================
HRESULT CTexture::Load(void)
{
	//LoadTxtTex();

	return S_OK;
}
//<===============================
//�e�N�X�`���̑S�j������
//<===============================
void CTexture::UnloadAll(void)
{
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_TEX; nCnt++)
	{
		//�S�Ẵe�N�X�`���̔j��
		if (m_apTexture[nCnt] != nullptr)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
		if (m_apFileName[nCnt] != nullptr)
		{
			m_apFileName[nCnt] = nullptr;
		}
		else if (m_apFileName[nCnt] == nullptr&&m_apTexture[nCnt] == nullptr)
		{
			break;
		}
	}

	m_nNumAll = 0;
}
//<===============================
//�e�N�X�`���̔j������
//<===============================
void CTexture::Unload(void)
{
	//�����ۑ��p�̕ϐ�
	int nNum = m_nNumAll;

	if (m_apTexture[nNum] != NULL)
	{
		m_apTexture[nNum]->Release();
		m_apTexture[nNum] = NULL;
	}
	//<*******************************
	//�����Ńe�N�X�`���̔j���͍s��Ȃ�
	//<*******************************
}
//<===============================
//�e�L�X�g����e�N�X�`����ǂݍ���
//<===============================
void CTexture::LoadTxtTex(void)
{
	//�K�v�ȊO�̕�����ǂݍ��ݗp�f�[�^
	char aChar[INT_VALUE::MAX_CHAR] = { NULL };

	//�t�@�C���̖��O
	char apFileName[INT_VALUE::MAX_CHAR][INT_VALUE::MAX_CHAR];

	//�t�@�C�����
	FILE *pFile = fopen("data/TEXT/LoadTexture.txt", "r");;

	//�t�@�C�����J������
	if (pFile != NULL)
	{
		//�����ƌJ��Ԃ�
		while (strcmp(aChar, "EndFile") != 0)
		{
			//�󎚂�ǂݍ���
			(void)fscanf(pFile, "%s", &aChar[0]);

			//ENEMY-SET�Ƃ��������񂪑��݂�����
			if (strcmp(aChar, "TEX_NAME") == 0)
			{
				//�󎚂�ǂݍ���
				(void)fscanf(pFile, "%s", &aChar[0]);

				//�t�@�C���p�X��ǂݍ���
				(void)fscanf(pFile, "%s", &apFileName[m_nNumAll][0]);

				//�t�@�C���l�[����o�^����
				m_apFileName[m_nNumAll] = &apFileName[m_nNumAll][0];

				//�����𑝂₷
				m_nNumAll++;
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}
}
//<===============================
//�e�N�X�`���̓o�^����
//<===============================
int CTexture::Regist(const char *pTexName, LPDIRECT3DTEXTURE9 &pTex)
{
	//�����ۑ��p�̕ϐ�
	int nNum = m_nNumAll;

	//�e�N�X�`���l�[��������ꍇ
	if (pTexName != nullptr)
	{
		//<*********************************************
		//�e�N�X�`���v�f�̃`�F�b�N
		//<*********************************************
		//�����J��Ԃ�
		for (int nCnt = 0; nCnt < nNum; nCnt++)
		{
			if (m_apFileName[nCnt] != nullptr)
			{
				//�����ۑ����ꂽ�t�@�C�����ƈ����̃t�@�C�������ꏏ��������
				if (strcmp(m_apFileName[nCnt], pTexName) == 0)
				{
					//���̔ԍ���Ԃ��A���łɓo�^����Ă���e�N�X�`��
					pTex = m_apTexture[nCnt];
					return nCnt;
				}
			}
		}

		m_apFileName[nNum] = pTexName;

		//�����Ȃ����
		if (pTex == nullptr)
		{
			assert((D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),
				pTexName,
				&m_apTexture[nNum])) == D3D_OK);

			pTex = m_apTexture[nNum];

			m_apTexture[nNum] = pTex;

		}

		m_nNumAll++;

		//���̔ԍ���Ԃ�
		return nNum;

	}

	//NULL��Ԃ�
	return NULL;
}