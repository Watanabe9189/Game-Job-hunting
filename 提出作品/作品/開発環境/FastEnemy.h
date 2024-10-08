//<======================================
//高速型敵の処理(FastEnemy.h)
//
//Author:Kazuki Watanabe
//<======================================
#ifndef _FAST_ENEMY_H_
#define _FAST_ENEMY_H_

#include "3DEnemy.h"

//<***************************************
//クラス定義
//<***************************************
class CFastEnemy : public C3DEnemy
{
public:

	//<=========================================
	//高速型敵のステート
	//<=========================================
	enum FAST_STATE
	{
		FAST_STATE_NORMAL = 0,			//通常状態
		FAST_STATE_MOVE,				//移動状態
		FAST_STATE_INTERVAL,			//動くまでの状態
		FAST_STATE_WAIT,				//待機状態
		FAST_STATE_MAX
	};

	//コンスト・デストラ
	CFastEnemy();
	~CFastEnemy() {}

	//五大処理
	static CFastEnemy* Create(void);
	HRESULT Init(void);
	void Uninit(void){ C3DEnemy::Uninit(); }
	void Update(void);
	void Draw(void) { C3DEnemy::Draw(); }

private:

	void HighSpeedMove(void);

	FAST_STATE m_sFastState;		//高速型のステート
	D3DXVECTOR3 m_rTelportPos;		//テレポートする位置

	int m_nInterval;				//動き出すまでの時間
	int m_nRandInter;				//ランダム時間
};

#endif