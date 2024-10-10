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

//<****************************************
//クラス定義
//<****************************************
class CResult : public CScene
{
	//公
public:

	//<===========================
	//ステート
	//<===========================
	enum STATE
	{
		STATE_NONE = 0,		//何もなし
		STATE_SELECT,		//選択肢
		STATE_MAX,
	};
	//<===========================
	//タイプ
	//<===========================
	enum XType
	{
		XTYPE_PLAYER = 0,		//プレイヤー
		XTYPE_HOUSE,			//家
		XTYPE_MAX
	};

	//コンスト・デストラ
	CResult();
	~CResult();

	//四代処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) { m_pCamera->SetCamera(); }

	//個人的
private:

	D3DXVECTOR3 m_pos;														//文字位置
	D3DXVECTOR2 m_Size;														//文字サイズ

	CObject2D *m_pObject2D;													//文字

	static LPDIRECT3DTEXTURE9	m_apTexture[CScene::TYPE_RESULT_MAX];		//テクスチャへのポインタ
	static const char*			m_acFilename[CScene::TYPE_RESULT_MAX];		//ファイル名

	static CLight *m_pLight;												//							
	static CField *m_pField;												//

	static Ccamera *m_pCamera;												//

	static CXObject *m_apXObject[XTYPE_MAX];								//
	static CObject3D *m_pObject3D;											//

	static C2DContinue *m_pContinue;										//
	static CFog *m_pFog;													//
	static CFont *m_pFont;

	STATE m_eState;
};

#endif