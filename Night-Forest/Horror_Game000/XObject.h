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

	//<=================================
	//モデルデータの
	//<=================================
	struct DataModel
	{
		//マテリアル関連
		LPDIRECT3DTEXTURE9	apTexture[INT_VALUE::MAX_TEX];		//テクスチャへのポインタ
		LPD3DXMESH			pMesh;					//メッシュ(頂点情報)へのポインタ
		LPD3DXBUFFER		pBuffMat;					//マテリアルへのポインタ
		DWORD				dwNumMat;					//マテリアルの数
		D3DXMATERIAL		*pMat;

		//頂点情報関連
		int					nNumVtx;					//頂点数
		DWORD				dwSizeFVF;				//頂点フォーマットのサイズ
		BYTE				*pVtxBuff;				//頂点バッファのポインタ
		D3DXVECTOR3			vtxMin;					//頂点の最小値
		D3DXVECTOR3			vtxMax;					//頂点の最大値

		D3DXVECTOR3 rSize;							//サイズ
		D3DXVECTOR3 rSizeX;							//判定用のXサイズ
		D3DXVECTOR3 rSizeZ;							//判定用のZサイズ
	};


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

	void CheckVtxNo(void);

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

	//<==========================================
	//設定系のメンバ関数
	//<==========================================
	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }					//位置設定
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }					//向き設定
	void SetMove(const D3DXVECTOR3& move) { m_move = move; }						//移動量設定
	void SetMaterial(D3DXMATERIAL *pMat) { m_asModel.pMat = pMat; }

	DataModel BindModel(const char *pFileName, const bool bMatChange = false);
	void LoadModel(void);

	void SetDrawfalse(void) { m_bDraw = false; }	//描画のオンオフ
	void SetDrawtrue(void) { m_bDraw = true; }	//描画のオンオフ

	//<==========================================
	//Get系のメンバ関数
	//<==========================================
	int GetModelId(void) { return m_nModelId; }
	D3DXVECTOR3		GetPosition(void)	const	{ return m_pos; }				//位置取得
	D3DXVECTOR3		GetMove(void)		const	{ return m_move; }				//移動量取得
	D3DXVECTOR3		GetRotation(void)	const	{ return m_rot; }				//向き取得

	D3DXMATERIAL*	GetMaterial(void)	const	{ return m_pMat; }				//マテリアル情報の取得

	void SetModel(const DataModel sModel) {m_asModel = sModel;};
	DataModel GetModel(void) { return m_asModel; }
	static int GetNum(void) { return m_nNumAll; }

private:

	DataModel m_asModel;
	static DataModel m_asaveModel[INT_VALUE::MAX_SIZE];
	static const char *m_apFileName[INT_VALUE::MAX_SIZE];				//
	int m_nModelId;

	D3DXMATRIX			m_mtxWorld;					//ワールドマトリックス
	D3DXMATERIAL		*m_pMat;

	//ベクトル関連
	D3DXVECTOR3			m_pos;						//位置
	D3DXVECTOR3			m_rot;						//向き
	D3DXVECTOR3			m_move;						//移動量

	static int m_nNumAll;
	bool m_bDraw;
};

#endif
