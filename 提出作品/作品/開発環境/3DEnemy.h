//<============================================
//3Dエネミー処理(3DEnemy.h)
//
//Author:kazuki watanabe
//<============================================
#ifndef _3DENEMY_H_
#define _3DENEMY_H_

#include "XObject.h"
#include "3DPlayer.h"

//<**********************************************
//3Dエネミーのクラス定義
//<**********************************************
class C3DEnemy : public CXObject
{
public:

	C3DEnemy(int nPriority = FIX_PRIORITY);
	~C3DEnemy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//<============================================
	//今回使用しないオーバーロードメンバ関数
	//<============================================
	void SetVtx(void) { return; }

protected:

	//メンバ関数
	void CollidPlayer(void);

	void DeathSound(void);
	void SetDest(void);

	void SetDest(const D3DXVECTOR3 rDestPos);

	//メンバ変数
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rDestPos;	//目的の位置
	D3DXVECTOR3 m_OldPos;	//前回の位置
	D3DXVECTOR3 m_rot;		//向き
	D3DXVECTOR3 m_move;		//移動値

	D3DXVECTOR3 m_rDis;

	float m_fMoveValue;

	D3DXVECTOR3 m_rRandDest;
	D3DXVECTOR3 m_fFrontDest;
	D3DXVECTOR3 m_fBackDest;

	C3DPlayer *m_pPlayer;
	CSound *m_pSound;

	DataModel m_sModel;
	D3DXMATERIAL *m_pMat;
};
#endif
