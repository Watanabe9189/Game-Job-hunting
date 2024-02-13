//<===============================================
//3Dオブジェクト専門の処理[Xファイル](XObject.h)
//
//Author:kazuki watanabe
//<===============================================
#ifndef _XOBJECT_H_//二重インクルード防止
#define _XOBJECT_H_

#include "main.h"
#include "Sound.h"
#include "manager.h"
#include "DebugProc.h"
#include "input.h"
#include "Texture.h"

//<***************************************
//Xファイルオブジェクトのクラス定義
//<***************************************
class CXObject : public CObject
{
public:

//<==============================================
//頂点値関連のマクロ定義(継承オブジェクトと共有)
//<==============================================
#define INITIAL_VTX_MIN	(D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f))	//頂点の最小値の初期値
#define INITIAL_VTX_MAX	(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))		//頂点の最大値の初期値

	//<================================
	//コンストラクタ・デストラクタ
	//<================================
	CXObject(int nPriority = FIX_PRIORITY);
	~CXObject();

	//<==========================
	//オーバーロードメンバ関数
	//<==========================
	HRESULT Init(void);
	void Uninit(void);
	void Draw(void);
	HRESULT CheckVtx(D3DXVECTOR3 *VtxMax, D3DXVECTOR3 *VtxMin,float fRot);
	void SetSize(D3DXVECTOR3 &rSize, D3DXVECTOR3 &rSizeX, D3DXVECTOR3 &rSizeZ);

	static CXObject *Create(const D3DXVECTOR3 rPos,const D3DXVECTOR3 rRot,const char *pFileName);

	//<============================================
	//今回使用しないオーバーロードメンバ関数
	//<============================================
	void Update(void) { return; }
	CObject2D *GetObject2D(void) { return NULL; }
	void SetVtx(void) { return; }
	//<====================================================================================
	//
	//<====================================================================================
	void SetVector3(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move)
	{
		//もしどちらかがnullptrでなければ
		if (pos != nullptr)
		{
			m_pos = pos;
		}
		if (rot != nullptr)
		{
			m_rot = rot;
		}
		if (move != nullptr)
		{
			m_move = move;
		}
	}

	void BindMat(D3DXMATERIAL *pMat,
				LPDIRECT3DTEXTURE9 const *pTex);					

	//<==========================================
	//設定系のメンバ関数
	//<==========================================
	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }					//位置設定
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }					//向き設定
	void SetMove(const D3DXVECTOR3& move) { m_move = move; }						//移動量設定
	void SetMaterial(D3DXMATERIAL *pMat) { m_pMat = pMat; }						//マテリアル情報単体での設定
	HRESULT LoadMesh(const char *pFileName, LPD3DXBUFFER *pBuffMat, DWORD *pDwNumMat, LPD3DXMESH *pMesh, 
		D3DXMATERIAL *pMat,LPDIRECT3DTEXTURE9 const *pTex);

	void SetDrawfalse(void) { m_bDraw = false; }	//描画のオンオフ
	void SetDrawtrue(void) { m_bDraw = true; }	//描画のオンオフ

	//<==========================================
	//Get系のメンバ関数
	//<==========================================
	D3DXVECTOR3		GetPosition(void)	const	{ return m_pos; }				//位置取得
	D3DXVECTOR3		GetMove(void)		const	{ return m_move; }				//移動量取得
	D3DXVECTOR3		GetRotation(void)	const	{ return m_rot; }				//向き取得
	DWORD			GetdwNumMat(void)	const	{ return m_dwNumMat; }			//マテリアル数取得
	LPD3DXMESH		GetMesh(void)		const	{ return m_pMesh; }				//メッシュの取得
	LPD3DXBUFFER	GetBuffMat(void)	const	{ return m_pBuffMat; }			//マテリアルの取得
	D3DXVECTOR3		GetVtxMax(void)		const	{ return m_vtxMax; }			//頂点情報の最大値取得
	D3DXVECTOR3		GetVtxMin(void)		const	{ return m_vtxMin; }			//頂点情報の最小値取得

	D3DXVECTOR3		GetSize(void)		const	{ return m_rSize; }				//サイズ取得
	D3DXVECTOR3		GetSizeX(void)		const	{ return m_rSizeX; }			//判定用Xサイズの取得
	D3DXVECTOR3		GetSizeZ(void)		const	{ return m_rSizeZ; }			//判定用Zサイズの取得

	D3DXMATERIAL*	GetMaterial(void)	const	{ return m_pMat; }				//マテリアル情報の取得

private:

	//マテリアル関連
	LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//テクスチャへのポインタ
	LPD3DXMESH			m_pMesh;					//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER		m_pBuffMat;					//マテリアルへのポインタ
	DWORD				m_dwNumMat;					//マテリアルの数
	D3DXMATERIAL		*m_pMat;					//マテリアルデータへのポインタ

	//頂点情報関連
	int					m_nNumVtx;					//頂点数
	DWORD				m_dwSizeFVF;				//頂点フォーマットのサイズ
	BYTE				*m_pVtxBuff;				//頂点バッファのポインタ
	D3DXVECTOR3			m_vtxMin;					//頂点の最小値
	D3DXVECTOR3			m_vtxMax;					//頂点の最大値

	D3DXMATRIX			m_mtxWorld;					//ワールドマトリックス

	D3DXVECTOR3 m_rSize;							//サイズ
	D3DXVECTOR3 m_rSizeX;							//判定用のXサイズ
	D3DXVECTOR3 m_rSizeZ;							//判定用のZサイズ

	//ベクトル関連
	D3DXVECTOR3			m_pos;						//位置
	D3DXVECTOR3			m_rot;						//向き
	D3DXVECTOR3			m_move;						//移動量

	static int m_nNumAll;
	bool m_bDraw;
};

#endif
