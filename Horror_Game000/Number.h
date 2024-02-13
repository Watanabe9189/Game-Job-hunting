//<===================================
//�ԍ��֘A�̏���(Number.h)
//
//Author:kazuki watanabe
//<===================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "object2D.h"

//<***********************************
//�ԍ��̃N���X��`
//<***********************************
class CNumber : public CObject2D
{

public:

//�}�N����`
#define NUMBER_PRI	(6)		//�ԍ��̗D�揇��

	CNumber(int nPriority = NUMBER_PRI);
	~CNumber();

	static CNumber *Create(const D3DXVECTOR2 rPos = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2 rSize = D3DXVECTOR2(0.0f, 0.0f),const LPDIRECT3DTEXTURE9 pTexture = nullptr);

	HRESULT Init(const D3DXVECTOR2 rPos = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2 rSize = D3DXVECTOR2(0.0f, 0.0f), const LPDIRECT3DTEXTURE9 pTexture = nullptr);
	void Uninit(void);
	void Update(void);
	void Draw(void) {}
	void SetVtx(void);

	//<===============================================================
	//GetSet�n�̊֐�
	//<===============================================================
	void SetNum(const int *nNum) { m_nNum = *nNum; }	//�ԍ��̐��ݒ�
	int GetNum(void) const { return m_nNum; }			//�ԍ��̐��擾 

private:


	CObject2D *m_pObject2D;

	int m_nNum;											//�ԍ��̐�

};
#endif