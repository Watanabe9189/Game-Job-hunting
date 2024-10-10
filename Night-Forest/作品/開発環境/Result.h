//<===========================================
//リザルト画面の処理(Result.h)
//
//Author:kazuki watanabe
//<===========================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "manager.h"
#include "object.h"

#include "object2D.h"
#include "2DSelect.h"

#include "Field.h"
#include "Light.h"
#include "Camera.h"

#include "Object3D.h"
#include "XObject.h"

#include "2DContinue.h"
#include "fog.h"
#include "Font.h"

class CResult : public CScene
{
public:

	//<===========================
	//
	//<===========================
	enum STATE
	{
		STATE_NONE = 0,
		STATE_SELECT,
		STATE_MAX,
	};
	//<===========================
	//
	//<===========================
	enum XType
	{
		XTYPE_PLAYER = 0,
		XTYPE_ENEMY,
		XTYPE_HOUSE,
		XTYPE_MAX
	};

	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) { m_pCamera->SetCamera(); }

	static void SetName(const char* cName) { m_EnemyName = cName; }

private:

	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_Size;

	CObject2D *m_pObject2D;

	static LPDIRECT3DTEXTURE9	m_apTexture[CScene::TYPE_RESULT_MAX];		//テクスチャへのポインタ
	static const char*			m_acFilename[CScene::TYPE_RESULT_MAX];				//ファイル名
	static const char*			m_EnemyName;

	static CLight *m_pLight;					//
	static CField *m_pField;

	static Ccamera *m_pCamera;					//

	static CXObject *m_apXObject[XTYPE_MAX];
	static CObject3D *m_pObject3D;

	static C2DContinue *m_pContinue;
	static CFog *m_pFog;
	static CFont *m_pFont;

	STATE m_eState;
};

#endif