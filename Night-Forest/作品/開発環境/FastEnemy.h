//<======================================
//‚‘¬Œ^“G‚Ìˆ—
//
//
//<======================================
#ifndef _FAST_ENEMY_H_
#define _FAST_ENEMY_H_

#include "3DEnemy.h"

//<***************************************
//
//<***************************************
class CFastEnemy : public C3DEnemy
{
public:

	//<=========================================
	//‚‘¬Œ^“G‚ÌƒXƒe[ƒg
	//<=========================================
	enum FAST_STATE
	{
		FAST_STATE_NORMAL = 0,			//’Êíó‘Ô
		FAST_STATE_MOVE,				//ˆÚ“®ó‘Ô
		FAST_STATE_INTERVAL,			//“®‚­‚Ü‚Å‚Ìó‘Ô
		FAST_STATE_WAIT,				//‘Ò‹@ó‘Ô
		FAST_STATE_MAX
	};

	CFastEnemy();
	~CFastEnemy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	void HighSpeedMove(void);
	FAST_STATE m_sFastState;
	D3DXVECTOR3 m_rTelportPos;
	bool m_bStartMove;

	int m_nInterval;
	int m_nRandInter;
	int m_nFixedInter;
};

#endif