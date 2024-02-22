#ifndef _2DSELECT_H_
#define _2DSELECT_H_

#include "main.h"
#include "object2D.h"

//<*************************************************
//
//<*************************************************
class C2DSelect : public CObject
{
public:

	C2DSelect(int nPriority = FIX_PRIORITY);
	~C2DSelect();

	static C2DSelect *Create(const D3DXVECTOR2 rPos,const int nNumSelect);

	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override;
	void Draw(void)		override;
	void SetVtx(void)	override {}

	//���݂̑I����
	int GetSelect(void) { return m_nSelect; }

	void SetTexName(const char *pFileName, int nCnt);

private:

	void SelectUpdate(void);

	D3DXVECTOR2 m_rPos;
	D3DXVECTOR2 m_rSize;
	D3DXCOLOR m_rCol;

	CObject2D *m_apObject2D[INT_VALUE::MAX_SIZE];
	int m_nNumSelect;

	LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//�e�N�X�`���ւ̃|�C���^
	const char*			m_acFilename[INT_VALUE::MAX_TEX];				//�t�@�C����

	int m_nSelect;
	int m_nOldSelect;

	float m_fDistance;

};

#endif
