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

	//<=========================================
	//敵タイプの列挙型
	//<=========================================
	enum TYPE
	{
		TYPE_ENEMY_NORMAL = 0,	//通常型
		TYPE_ENEMY_INVISIBLE,	//透明型
		TYPE_ENEMY_HIGHSPEED,	//高速型
		TYPE_MAX

	};
	//<=========================================
	//敵ステートの列挙型
	//<=========================================
	enum STATE
	{
		STATE_NORMAL = 0,		//何もない状態
		STATE_SEARCH,			//探索状態
		STATE_WAIT,				//待機状態
		STATE_CHASE,			//追跡状態
		STATE_MAX

	};
	//<=========================================
	//敵ステートの列挙型
	//<=========================================
	enum FAST_STATE
	{
		FAST_STATE_NORMAL = 0,			//通常状態
		FAST_STATE_MOVE,				//移動状態
		FAST_STATE_INTERVAL,			//動くまでの状態
		FAST_STATE_WAIT,				//待機状態
		FAST_STATE_MAX
	};

	C3DEnemy(int nPriority = FIX_PRIORITY);
	~C3DEnemy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static C3DEnemy *Create(const D3DXVECTOR3 pos, const int nLife, const int nType, const int CoolTime);
	static C3DEnemy *ReadCreate(C3DEnemy *apEnemy[MAX_OBJECT]);
	static C3DEnemy *RandCreate(C3DEnemy *apEnemy[MAX_OBJECT]);
	void Search(void);
	static int GetNum(void) { return m_nNumAll; }

	static void SetNumSet(const int nNumSet) { m_nNumSet = nNumSet; }
	static int GetNumSet(void) { return m_nNumSet; }
	static int GetNumMax(void) { return m_nNumMax; }
	static int GetNumMin(void) { return m_nNumMin; }
	//<============================================
	//今回使用しないオーバーロードメンバ関数
	//<============================================
	void SetVtx(void) { return; }

	//
	STATE GetState(void) { return m_sState; }
	TYPE GetType(void) { return m_eType; }

	/*bool CollisionDestroy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, bool bJump, TYPE_3D Type3D);*/

private:


	//メンバ関数
	void ChangeRot(void);
	void MoveMent(void);
	void SetSound(const CSound::LABEL Label, const int nMaxCount, const D3DXVECTOR3 rTargetPos);
	void SetDest(void);
	void SetDest(const D3DXVECTOR3 rDestPos);
	void CollidPlayer(void);
	void DeathSound(void);

	//メンバ変数
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rDestPos;	//目的の位置
	D3DXVECTOR3 m_OldPos;	//前回の位置
	D3DXVECTOR3 m_rot;		//向き
	D3DXVECTOR3 m_move;		//移動値
	float m_fSearchRad;		//探索円
	D3DXVECTOR3 m_rDis;
	static int m_nNumAll;	//総数
	static int m_nNumSet;		//
	static int m_nNumMax;
	static int m_nNumMin;

	STATE m_sState;
	FAST_STATE m_sFastState;
	//<==============
	//マテリアル関連
	//<==============
	LPD3DXMESH	m_pMesh;							//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER	m_pBuffMat;							//マテリアルへのポインタ
	DWORD		m_dwNumMat;							//マテリアルの数
	D3DXMATERIAL*	m_pMat;							//マテリアルデータへのポインタ

															//<==============
															//テクスチャ関連
															//<==============
	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//テクスチャへのポインタ
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//ファイル名

															//<=============
															//頂点情報関連
															//<=============
	D3DXVECTOR3			m_vtxMin;					//頂点の最小値
	D3DXVECTOR3			m_vtxMax;					//頂点の最大値

	int m_nSoundCount;
	int m_nSoundMax;
	int m_nInterval;
	int m_nRandInter;

	float m_fMoveValue;

	D3DXVECTOR3 m_rRandDest;

	D3DXVECTOR3 m_fFrontDest;
	D3DXVECTOR3 m_fBackDest;

	D3DXVECTOR3 m_rSize;
	D3DXVECTOR3 m_rSizeX;
	D3DXVECTOR3 m_rSizeZ;

	C3DPlayer *m_pPlayer;
	CSound *m_pSound;
	D3DXVECTOR3 m_rTelportPos;

	TYPE m_eType;
};
#endif
