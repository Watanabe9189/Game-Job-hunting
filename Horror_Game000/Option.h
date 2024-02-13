//<===========================================
//タイトル画面の処理(Title.h)
//
//Author:kazuki watanabe
//<===========================================
#ifndef _OPTION_H_
#define _OPTION_H_

#include "main.h"
#include "manager.h"
#include "fade.h"
#include "object.h"

#include "object2D.h"
#include "2DGauge.h"
#include "Number.h"
#include "3DEnemy.h"

class COption : public CScene
{

public:

	//<=========================
	//
	//<=========================
	enum SELECT
	{
		SELECT_STAMINA = 0,
		SELECT_ENEMYNUM,
		SELECT_EXIT,
		SELECT_MAX
	};

	COption();
	~COption();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	void Select(void);

	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//テクスチャへのポインタ
	static const char*			m_acFilename[];				//ファイル名

	CObject2D *m_apObject2D[SELECT::SELECT_MAX];
	CObject2D *m_pCover;

	static C2DGauge *m_p2DGauge;
	static CNumber  *m_pNumber;
	int m_nStamina;
	int m_nNumEnemy;
	int m_nSelect;
	int m_nOldSelect;
	D3DXCOLOR m_rCol;
};

#endif
