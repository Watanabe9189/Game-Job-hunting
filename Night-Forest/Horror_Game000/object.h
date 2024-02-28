//<==============================================
//オブジェクト処理(object.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _OBJECT_H_
#define _OBJECT_H_	// 二重インクルード防止

#include "main.h"
#include "Stencil.h"
class CObject2D;
class CStencil;

//<**********************************************
//マクロ定義(定数含む)
//<**********************************************
static const int			MAX_OBJECT = 1024;									//オブジェクトの最大数
static const int			INITIAL_INT = 0;									//Int型の初期値
static const float			INITIAL_FLOAT = 0.0f;								//float型の初期値
static const D3DXVECTOR3	INIT_VECTOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//D3DXVECTOR3型の初期値
static const D3DXVECTOR2	INIT_VECTOR2 = D3DXVECTOR2(0.0f, 0.0f);				//D3DXVECTOR2型の初期値
static const D3DXCOLOR		INIT_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//色の初期値

static const float MOVE_UP	 =	(1.0f);		//上移動
static const float MOVE_LRUP =	(0.75f);	//斜め上移動
static const float MOVE_LR	 =	(0.5f);		//水平移動
static const float MOVE_LRDW =	(0.25f);	//斜め上移動
static const float MOVE_DOWN =	(0.0f);		//下移動

//<==================================================================================
//頂点フォーマット関連
//<==================================================================================
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)					//2D頂点フォーマット
#define FVF_VERTEX_2D_MULTI	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX8)					//マルチテクスチャ用の2D頂点フォーマット
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//頂点フォーマット,法線
#define FVF_VERTEX_3D_MULTI	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX8)		//マルチテクスチャ用の3D頂点フォーマット

//<==================================================================================
//サイズ関連(Int型の値)
//<==================================================================================
namespace INT_VALUE
{
	static const int MAX_MAT = (512);	//マテリアルサイズ
	static const int MAX_TEX = (512);	//テクスチャの最大数
	static const int FRONT_MAX_TEX = (511);	//テクスチャの最大数の手前の値
	static const int NUM_MULTEX = (8);	//マルチテクスチャの数
	static const int MAX_TOP = (4);	//頂点数
	static const int MAX_CHAR = (256);	//char型の配列の最大数
	static const int MAX_SIZE = (256);	//動的メモリ確保をするために必要なメモリの最大数

	static const int NO_LIFE = (0);	//体力(寿命)のゼロの値
}

//<==================================================================================
//色関連
//<==================================================================================
namespace COLOR_VALUE
{
	static const D3DXCOLOR COLOR_RED = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//赤色
	static const D3DXCOLOR COLOR_GREEN = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);	//青色
	static const D3DXCOLOR COLOR_BLUE = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);	//緑色
	static const D3DXCOLOR COLOR_INIT = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色の初期値

	static const float ALPHA_OPACITY = 1.0f;								//不透明色
	static const float ALPHA_CLEANNESS = 0.0f;								//透明色
}

//<==================================================================================
//優先順位関連
//<==================================================================================
static const int FIX_PRIORITY	= 3;			//優先順位の固定値
static const int NEED_PRIORITY	= 8;			//優先順位の必要数

//<==================================================================================
//回転関連
//<==================================================================================
namespace FLOAT_VALUE
{
	static const float FRONT_HARF_CIRCLE = (1.56f);		//半円の手前の数値
	static const float HARF_CIRCLE = (1.57f);		//半円に回転する際の値
	static const float BACK_HARF_CIRCLE = (1.58f);		//半円の奥の数値
	static const float NO_ROTATION = (0.0f);			//回転しない値

	static const float ROT_RIGHT = (-1.57f);				//右の向き
	static const float ROT_LEFT = (1.57f);				//左の向き
}

//<**********************************************
//頂点情報[2D]の構造体を宣言
//<**********************************************
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座標変換用係数(1.0fで固定)
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標

};
//<**********************************************
////頂点情報[3D]の構造体を宣言
//<**********************************************
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標

};
//==========================================================================
//オブジェクトクラスの定義
//==========================================================================
class CObject
{
public:

	//<=================================
	//2Dオブジェクトの種類の列挙型
	//<=================================
	enum TYPE_2D
	{
		TYPE_PARTICLE,		//パーティクル
		TYPE_NUMBER,
		TYPE_SCORE,
		TYPE_TIMER,
		TYPE_2DLIFE,
		TYPE_MAX
	};

	//<=================================
	//3Dオブジェクトの種類の列挙型
	//<=================================
	enum TYPE_3D
	{
		TYPE_NONE = 0,	
		TYPE_PLAYER3D,	//プレイヤー
		TYPE_ENEMY3D,	//敵
		TYPE_BLOCK3D,	//ブロック
		TYPE_EFFECT3D,	//エフェクト
		TYPE_FIELD,		//地面
		TYPE_WALL,		//壁
		TYPE_BUILDING,	//建物
		TYPE_ITEM,		//アイテム
		TYPE_MAX3D
	};

	//<=======================================
	//コンストラクタ・デストラクタ
	//<=======================================
	CObject(int nPriotity= FIX_PRIORITY);
	virtual ~CObject();

	//<=======================================
	//純粋仮想関数にする
	//<=======================================
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void SetVtx(void) = 0;

	//<=======================================
	//静的メンバ関数
	//<=======================================
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static int GetNumObj(void) { return m_nNumAll; };

	//<=======================================
	//メンバ関数(Set系)
	//<=======================================
	void SetType(const TYPE_2D Type) { m_2DTYpe = Type; }
	void SetType3D(const TYPE_3D Type) { m_3DType = Type; }

	//<=======================================
	//メンバ関数(Get系)
	//<=======================================
	TYPE_2D GetType(void)	const { return m_2DTYpe; }

	TYPE_3D GetType3D(void)	const
	{
		if ((unsigned int)this == 0xdddddddd)
		{
			//警告文を表示
			MessageBox(NULL, "DUMPRING POINTER IN GetType3D", "ERROR", MB_ICONWARNING);

			exit(EXIT_FAILURE);
		}
		else
		{
			return m_3DType;
		}
	}
	void SetPrio(const int nPrio) { m_nPriority = nPrio; }

	//描画するかどうか
	void SetUpdatefalse(void) { m_bUpdate = false; }	//描画のオンオフ
	void SetUpdatetrue(void) { m_bUpdate = true; }	//描画のオンオフ
	bool GetbUpdate(void) { return m_bUpdate; }

	//描画するかどうか
	void SetDrawfalse(void) { m_bDraw = false; }	//描画のオンオフ
	void SetDrawtrue(void) { m_bDraw = true; }	//描画のオンオフ
	bool GetbDraw(void) { return m_bDraw; }

	//<=======================================
	//静的メンバ関数(Get系)
	//<=======================================
#if 0
	static CObject *GetObject(int nPriority,int nIdx) { return m_apObject[nPriority][nIdx]; };
#endif

	//<====================================
	//
	//<====================================
	static CObject *GetTop(int nPriority) 
	{ 
		if (m_apTop[nPriority] != nullptr)
		{
			return m_apTop[nPriority];
		}
		return nullptr;
	}
	//<====================================
	//
	//<====================================
	CObject *GetNext(void)
	{

		if ((unsigned int)this == 0xdddddddd)
		{
			//警告文を表示
			MessageBox(NULL, "DUMPRING POINTER IN GetNext", "ERROR", MB_ICONWARNING);

			exit(EXIT_FAILURE);
		}
		else
		{
			return m_pNext;
		}

	}

	//<=======================================
	//当たり判定関連
	//<=======================================
	virtual bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,D3DXVECTOR3 *pMove ,D3DXVECTOR2 pSize, bool bJump,TYPE_2D type) { return false; }
	virtual bool Collision3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, bool bJump,TYPE_3D Type3D) { return false; }
	virtual void Collision3DNoBool(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, bool bJump, TYPE_3D Type3D) { return; }
	virtual bool CollisionDestroy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, bool bJump, TYPE_3D Type3D) { return false; }
	virtual bool CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, TYPE_3D Type3D) {return false;}
	virtual bool CollisionField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, TYPE_3D Type3D) { return false; }
	virtual bool CollisionWithHP(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, int nLife, TYPE_3D Type3D) { return false; }

	CStencil *GetStencil(void) { return m_pStencil; }	//ステンシルオブジェクトを取得する

	void Release(void);

protected:

private:

	//<=======================================
	//静的メンバ変数
	//<=======================================
#if 0
	static CObject *m_apObject[NEED_PRIORITY][MAX_OBJECT];		//オブジェクト情報
#endif

	static CObject *m_pObject;
	static CObject *m_pObjNext;

	static CObject *m_apTop[NEED_PRIORITY];		//先頭オブジェクトへのポインタ
	static CObject *m_apCur[NEED_PRIORITY];		//最後尾オブジェクトへのポインタ

	CObject *m_pNext;							//次のオブジェクトへのポインタ
	CObject *m_pPrev;							//前のオブジェクトへのポインタ

	bool m_bDestru;

	static int m_nNumAll;						//オブジェクトの総数
	int m_nPriority;							//オブジェクトの優先順位

	TYPE_2D m_2DTYpe;							//2Dオブジェクトのタイプ
	TYPE_3D m_3DType;							//3Dオブジェクトのタイプ
	bool m_bDraw;
	bool m_bUpdate;

	CStencil *m_pStencil;

	//<****************************************
	//この優先順位は3Dではあまり意味がない
	//<****************************************

};
#endif