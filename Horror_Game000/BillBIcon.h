//<==============================================
//�r���{�[�h��������(BillB.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _BILLBICON_H_
#define _BILLBICON_H_

#include "BilB.h"

//<**********************************************
//�r���{�[�h�����̃N���X��`
//<**********************************************
class CBilBIcon : public CBillB
{
public:

	//<================================
	//
	//<================================
	enum BICON
	{

		BICON_INFO_EXPLAIN = 0,
		BICON_INFO_MEMO1,
		BICON_INFO_MEMO2,
		BICON_INFO_MEMO3,
		BICON_MAX
	};

	CBilBIcon(int nPriority = FIX_PRIORITY);
	~CBilBIcon();

	//<=======================
	//�I�[�o�[���[�h�����o�֐�
	//<=======================
	HRESULT Init(void);
	void Uninit(void) { CBillB::Uninit(); }
	void Update(void);
	void Draw(void) 
	{ 
		CBillB::Draw();
	}
	void SetVtx(void) {}

	static CBilBIcon *Create(const D3DXVECTOR3 pos, const int nIcon);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

	void ChangeIcon(int nIcon) { m_nIcon = nIcon; }

	static int GetNum(void) { return m_nNumAll; }

private:

	static LPDIRECT3DTEXTURE9 m_apTexture[BICON_MAX];

	static const char*			m_acFilename[];				//�t�@�C����
	static int m_nNumAll;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Size;

	int m_nIcon;
};

#endif
