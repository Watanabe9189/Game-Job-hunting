//<================================================
//�e�N�X�`���֘A����(Texture.h)
//
//Author:kazuki watanabe
//<================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

//<**************************************
//�e�N�X�`���̃N���X��`
//<**************************************
class CTexture
{
public:

	//<============================
	//�R���X�g���N�^�E�f�X�g���N�^
	//<============================
	CTexture();
	~CTexture();

	//<============================
	//�����o�֐�
	//<============================
	HRESULT Load(void);
	void UnloadAll(void);
	void Unload(void);
	int Regist(const char *pTexName, LPDIRECT3DTEXTURE9 &pTex);

	//<====================================
	//�����o�֐�(Get)
	//<====================================
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx) { return m_apTexture[nIdx]; }	//�e�N�X�`���ԍ��̎擾
	const char* GetAddressName(int nIdx)	{ return m_apFileName[nIdx]; }	//���Ԗڂ̃e�N�X�`�������擾���邩

	static int GetNumAll(void) { return m_nNumAll; }

private:

	void LoadTxtTex(void);

	//<============================
	//�����o�ϐ�
	//<============================
	LPDIRECT3DTEXTURE9 m_apTexture[INT_VALUE::MAX_TEX];			//�e�N�X�`���ւ̃|�C���^
	const char *m_apFileName[INT_VALUE::MAX_TEX];				//
	static int m_nNumAll;										//�e�N�X�`���̑���

};

#endif
