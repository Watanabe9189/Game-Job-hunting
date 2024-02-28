//<===========================================
//ƒQ[ƒ€‰æ–Ê‚Ìˆ—(game.h)
//
//Author:kazuki watanabe
//<===========================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "manager.h"
#include "object.h"

//<*****************************************
//2DŠÖ˜A
//<*****************************************
#include "DestArrow2D.h"
//<*****************************************
//3DŠÖ˜A
//<*****************************************
#include "Camera.h"
#include "Light.h"
#include "3DPlayer.h"
#include "2DEffect.h"
#include "Field.h"
#include "fog.h"
#include "Building.h"
#include "2DGauge.h"
#include "3DEnemy.h"
#include "Item.h"
#include "2DInfo.h"
#include "Cover.h"
#include "2DChar.h"
#include "Plant.h"
#include "LandMark.h"
#include "DestArrow.h"
#include "DestArrowX.h"
//<*************************************************
//
//<*************************************************
class CGame : public CScene
{
public:

	enum STATE
	{
		STATE_NONE = 0,
		STATE_PAUSE,
		STATE_END,
		STATE_MAX
	};

	enum CHAR2D
	{
		CHAR2D_HIDE = 0,
		CHAR2D_PICKUP,
		CHAR2D_COMEOUT,
		CHAR2D_SEALED,
		CHAR2D_FOUND,
		CHAR2D_MAX
	};

	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	STATE GetState(void) { return m_sState; }

	static CLight *GetLight(void) { return m_pLight; }
	static CBuilding *GetBuil(int nCnt) { return m_apBuilding[nCnt]; }
	static CLandMark *GetLand(int nCnt) { return m_apLandMark[nCnt]; }
	static C2DGauge *GetGauge(void) { return m_p2DGauge; }
	static C3DPlayer *Get3DPlayer(void) { return m_p3DPlayer; }
	static C3DEnemy *Get3DEnemy(int nCnt) { return m_ap3DEnemy[nCnt]; }
	static C2DChar *Get2DChar(int nCnt) { return m_ap2DChar[nCnt]; }
	static CItem *GetItem(int nCnt) { return m_apItem[nCnt]; }
	static Ccamera *GetCamera(void) { return m_pCamera; }
	static CDestArrow *GetDestArrow(void) { return m_pDestArrow; }
private:

	void ItemUpdate(void);

	static CLight *m_pLight;					//
	static C3DPlayer *m_p3DPlayer;
	static CBuilding *m_apBuilding[INT_VALUE::MAX_SIZE];
	static CField *m_apField[INT_VALUE::MAX_SIZE];
	static C3DEnemy *m_ap3DEnemy[INT_VALUE::MAX_SIZE];
	static CFog *m_pFog;
	static C2DGauge *m_p2DGauge;
	static CItem *m_apItem[INT_VALUE::MAX_SIZE];
	static C2DInfo *m_pInfo;
	static Ccover *m_pCover;
	static C2DChar *m_ap2DChar[CHAR2D_MAX];
	static CPlant *m_apPlant[INT_VALUE::MAX_SIZE];
	static CLandMark *m_apLandMark[INT_VALUE::MAX_SIZE];
	static CDestArrowX *m_pDestArrowX;
	static CDestArrow *m_pDestArrow;
	//
	static Ccamera *m_pCamera;					//

	int m_nWaitTime;
	bool m_bMoved;
	STATE m_sState;
};

#endif
