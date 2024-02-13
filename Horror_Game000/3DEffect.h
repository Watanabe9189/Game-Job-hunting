//<================================================
//2D�G�t�F�N�g����(2DEffect.h)
//
//Author:kazuki watanabe
//<================================================
#ifndef _3DEFFECT_H_
#define _3DEFFECT_H_

#include "main.h"
#include "BilB.h"

class C3DEffect : public CBillB
{

public:

	C3DEffect(int nPriority = FIX_PRIORITY);
	~C3DEffect();

	//�I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtx(void) { CBillB::SetVtx(); }

	static C3DEffect *Create(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rMove, const int nLife, const D3DXVECTOR2 rSize, const D3DXCOLOR rCol);

private:


	D3DXVECTOR3 m_rPos;
	D3DXVECTOR3 m_rmove;
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
