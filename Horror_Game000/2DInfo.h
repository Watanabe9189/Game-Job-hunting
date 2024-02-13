//<===========================================
//
//
//
//<===========================================
#ifndef _2DINFO_H_
#define _2DINFO_H_

#include "object2D.h"
#include "Number.h"

//<*******************************************
//
//<*******************************************
class C2DInfo : public CObject
{
public:

	C2DInfo(int nPriority = FIX_PRIORITY);
	~C2DInfo();

	static C2DInfo *Create(void);

	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override;
	void Draw(void)		override;
	void SetVtx(void)	override {}

	CObject2D *GetObject2D(void)override { return NULL; }

private:

	CObject2D *m_pObject2D;
	CNumber *m_pNumber;

	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//テクスチャへのポインタ
	static const char*			m_acFilename[];				//ファイル名

	int m_nNum;
	D3DXCOLOR m_rCol;

};
#endif