//<================================================
//2D�G�t�F�N�g����(2DEffect.h)
//
//Author:kazuki watanabe
//<================================================
#ifndef _2DEFFECT_H_
#define _2DEFFECT_H_

#include "main.h"
#include "object2D.h"

class C2DEffect : public CObject2D
{

public:

	C2DEffect(int nPriority = FIX_PRIORITY);
	~C2DEffect();

	//�I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtx(void);

	static C2DEffect *Create(const D3DXVECTOR2 rPos, const D3DXVECTOR3 rMove, const int nLife,const D3DXVECTOR2 rSize,const D3DXCOLOR rCol);


private:


	D3DXVECTOR2 m_rPos;
	D3DXVECTOR2 m_rmove;
	D3DXVECTOR2 m_rSize;
	D3DXCOLOR m_rCol;
	int m_nLife;
	bool m_bAdd;
	bool m_bDisp;

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[INT_VALUE::MAX_TEX];
	static const char*			m_acFilename[];				//�t�@�C����

};

#endif
