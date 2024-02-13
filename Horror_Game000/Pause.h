#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "manager.h"
#include "object2D.h"

class CPause
{
public:

	enum TYPE
	{
		TYPE_COVER = 0,
		TYPE_FRAME,
		TYPE_MAX
	};
	enum SELECT
	{
		SELECT_RESUME = 0,
		SELECT_RESTART,
		SELECT_RETURN,
		SELECT_MAX,
	};

	CPause();
	~CPause();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	void Select(void);

	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//テクスチャへのポインタ
	static const char*			m_acFilename[];				//ファイル名

	CObject2D *m_apObject2D[TYPE_MAX];

	CObject2D *m_apSelct[SELECT_MAX];
	D3DXVECTOR2 m_rSize;
	D3DXVECTOR2 m_rSizeSelect;
	D3DXCOLOR m_rCOl;

	int m_nSelect;
	int m_nOldSelect;

};


#endif