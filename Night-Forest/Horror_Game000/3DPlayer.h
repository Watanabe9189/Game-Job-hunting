//<========================================
//3Dプレイヤー処理(3DPlayer.h)
//
//Author:kazuki watanabe
//<========================================
#ifndef _3DPLAYER_H_//二重インクルード防止
#define _3DPLAYER_H_

#include "XObject.h"

//<****************************************
//3Dプレイヤーのクラス定義
//<****************************************
class C3DPlayer : public CXObject
{
public:

	//<======================================
	//プレイヤーステート
	//<======================================
	enum STATE
	{
		STATE_NONE = 0,	//何もない状態
		STATE_HIDE,		//隠れている状態
		STATE_DEATH,
		STATE_MAX
	};



	C3DPlayer(int nPriority = FIX_PRIORITY);
	~C3DPlayer();

	//<==========================
	//オーバーロードメンバ関数
	//<==========================
	HRESULT Init(void);
	void Uninit(void) { CXObject::Uninit(); }
	void Update(void);
	void Draw(void) 
	{ 
		//隠れていなければ
		if (m_sState != STATE_DEATH&& m_sState != STATE_HIDE)
		{
			CXObject::Draw();
		}
	}

	static C3DPlayer *Create(const D3DXVECTOR3 pos);
	int GetStamina(void) { return m_nStamina; }
	float GetCollidRad(void) {return m_fCollidRad;}

	void SetState(const STATE sState) { m_sState = sState; }
	STATE GetState(void) { return m_sState; }

	void SetStateHide(void) { m_sState == STATE_NONE ? m_sState = STATE_HIDE : m_sState = STATE_NONE; ; }

	void Controll(void);

private:

	void MoveAction(void);
	void Movement(void);
	//void Collision(void);
	void Hide(void);
	void Dash(void);

	//<==============
	//位置情報関連
	//<==============
	D3DXVECTOR3 m_pos;										//位置
	D3DXVECTOR3 m_posOld;									//前回の位置
	D3DXVECTOR3 m_rot;										//向き
	D3DXVECTOR3 m_move;										//移動値

	D3DXVECTOR3 m_rRad;

	float m_fRotMove;
	float m_fRotDest;
	float m_fRotDiff;
	float m_fCollidRad;

	float m_fMoveValue;

	int m_nStamina;

	STATE m_sState;

	bool m_bJump;
	bool m_bDash;
	bool m_bMove;

	DataModel m_sModel;

};
#endif
