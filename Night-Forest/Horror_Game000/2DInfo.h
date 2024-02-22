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

	//<**********************
	//
	//<**********************
	enum TYPE
	{
		TYPE_INFO_CHAR = 0,
		TYPE_INFO_NUMBER,
		TYPE_INFO_FIGURE,
		TYPE_MAX
	};
	//<**********************
	//
	//<**********************
	enum Class
	{
		CLASS_NUMBER = 0,
		CLASS_FIGURE,
		CLASS_MAX
	};


	C2DInfo(int nPriority = FIX_PRIORITY);
	~C2DInfo();

	static C2DInfo *Create(const Class eClass);

	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override {}
	void Draw(void)		override {}
	void SetVtx(void)	override {}

protected:

	static LPDIRECT3DTEXTURE9	m_apTexture[TYPE_MAX];		//テクスチャへのポインタ
	static const char*			m_acFilename[TYPE_MAX];				//ファイル名

private:

	Class m_eClass;

};
//<*******************************************
//
//<*******************************************
class CInfoNum : public C2DInfo
{
public:

	CInfoNum(int nPriority = FIX_PRIORITY);
	~CInfoNum();

	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override;
	void Draw(void)		override {}
	void SetVtx(void)	override {}

private:

	CObject2D *m_pObject2D;

	CNumber *m_pNumber;

	int m_nNum;
};
//<*******************************************
//
//<*******************************************
class CInfoFigure : public C2DInfo
{
public:

	CInfoFigure(int nPriority = FIX_PRIORITY);
	~CInfoFigure();

	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override;
	void Draw(void)		override {}
	void SetVtx(void)	override {}

	CObject2D *GetFigure(int nNum) { return m_apObject2D[nNum]; }

private:

	CObject2D *m_apObject2D[INT_VALUE::MAX_SIZE];

	int m_nNum;
	D3DXCOLOR m_rCol;
};
#endif