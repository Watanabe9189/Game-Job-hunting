#ifndef _COVER_H_
#define _COVER_H_

#include "main.h"
#include "Object.h"
#include "object2D.h"
#include "manager.h"

class Ccover :public CObject
{
public:
	enum TYPE
	{
		TYPE_COVER = 0,
		TYPE_BLOOD_COV,
		TYPE_SAFE_COV,
		TYPE_MAX
	};

	Ccover(int nPriority = FIX_PRIORITY);
	~Ccover();

	static Ccover *Create(const TYPE eType);

	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override;
	void Draw(void)		override {}
	void SetVtx(void)	override {}

	CObject2D *GetObject2D(void)override { return NULL; }

private:

	static LPDIRECT3DTEXTURE9	m_apTexture[TYPE_MAX];		//テクスチャへのポインタ
	static const char*			m_acFilename[TYPE_MAX];				//ファイル名

	D3DXVECTOR2 m_rPos;
	D3DXVECTOR2 m_rSize;
	D3DXCOLOR m_rCol;

	int m_nCounter;

	CObject2D *m_apObject2D[TYPE_MAX];
	TYPE m_eType;

};

#endif
