//<===========================================
//タイトル画面の処理(Title.h)
//
//Author:kazuki watanabe
//<===========================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "manager.h"
#include "object.h"

#include "Font.h"
#include "2DChar.h"
#include "Field.h"
#include "Light.h"
#include "Camera.h"
#include "fog.h"
#include "3DEnemy.h"
#include "2DSelect.h"

class CTitle : public CScene
{

public:
	enum SELECT
	{
		SELECT_START = 0,
		SELECT_OPTION,
		SELECT_EXIT,
		SELECT_MAX
	};

	CTitle();
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	static C2DChar *m_ap2DChar[INT_VALUE::MAX_SIZE];

	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//テクスチャへのポインタ
	static const char*			m_acFilename[SELECT_MAX];				//ファイル名

	static CLight *m_pLight;					//
	static CField *m_pField;
	static CFog *m_pFog;
	
	static Ccamera *m_pCamera;					//
	static C3DEnemy *m_ap3DEnemy[INT_VALUE::MAX_SIZE];
	static C2DSelect *m_pSelect;
};

#endif