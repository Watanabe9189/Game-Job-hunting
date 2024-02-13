//<===============================================
//3Dオブジェクト専門の処理[Xファイル](XObject.cpp)
//
//Author:kazuki watanabe
//<===============================================
#include "XObject.h"
#include "manager.h"
#include "Texture.h"

int CXObject::m_nNumAll = INITIAL_INT;

//<====================================
//Xファイルオブジェクトのコンストラクタ
//<====================================
CXObject::CXObject(int nPriority) : CObject(nPriority)
{
	//値のクリア
	m_pMat = {};
	m_pVtxBuff = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	m_mtxWorld = {};

	//位置情報関連
	m_pos		=	INIT_VECTOR;
	m_rot		=	INIT_VECTOR;
	m_move		=	INIT_VECTOR;
	m_nNumVtx	=	INITIAL_INT;

	m_vtxMin = INIT_VECTOR;					//頂点の最小値
	m_vtxMax = INIT_VECTOR;					//頂点の最大値

	//
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_TEX; nCnt++)
	{
		m_apTexture[nCnt] = nullptr;
	}
	m_bDraw = true;
}
//<====================================
//Xファイルオブジェクトのデストラクタ
//<====================================
CXObject::~CXObject()
{

}
//<====================================
//Xファイルオブジェクトの初期化処理
//<====================================
HRESULT CXObject::Init(void)
{
	return S_OK;
}
//<====================================
//Xファイルオブジェクトの終了処理
//<====================================
void CXObject::Uninit(void)
{
	Release();
}
//<====================================
//Xファイルオブジェクトの描画処理
//<====================================
void CXObject::Draw(void)
{
	//この関数でしか使わない変数宣言
	D3DXMATRIX			mtxRot = {}, mtxTrans = {};		//計算用マトリックス宣言
	D3DMATERIAL9		matDef = {};					//現在のマテリアル保存用変数

	//描画するなら
	if (m_bDraw)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//向きを反映する
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//位置を反映する
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		CManager::GetRenderer()->GetDevice()->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//現在のマテリアルを取得
		CManager::GetRenderer()->GetDevice()->GetMaterial(&matDef);

		//頂点数分繰り返し
		for (DWORD nCntMat = 0; nCntMat < m_dwNumMat; nCntMat++)
		{
			//マテリアルの設定
			CManager::GetRenderer()->GetDevice()->SetMaterial(&m_pMat[nCntMat].MatD3D);

			//テクスチャの設定
			CManager::GetRenderer()->GetDevice()->SetTexture(0, m_apTexture[nCntMat]);

			//モデルの描画
			m_pMesh->DrawSubset(nCntMat);
		}

		//保存していたマテリアルを戻す
		CManager::GetRenderer()->GetDevice()->SetMaterial(&matDef);
	}
}
//<====================================
//Xファイルオブジェクトの描画処理
//<====================================
HRESULT CXObject::CheckVtx(D3DXVECTOR3 *VtxMax, D3DXVECTOR3 *VtxMin, float fRot)
{
	//頂点確認用のバーテックス変数
	D3DXVECTOR3 rVtx = INIT_VECTOR;

	//モデルの頂点数を取得
	if (FAILED(m_nNumVtx = m_pMesh->GetNumVertices()))
	{
		return E_FAIL;
	}

	//頂点フォーマットのサイズを取得
	if (FAILED(m_dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF())))
	{
		return E_FAIL;
	}

	//頂点バッファをロック
	if (FAILED(m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff)))
	{
		return E_FAIL;
	}

	//全ての頂点をチェックする
	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		//今回のデータ
		rVtx = *(D3DXVECTOR3*)m_pVtxBuff;

		//<***********************************
		//X軸判定
		//<***********************************
		//今の最小値よりも今回の値が小さかったら
		if (VtxMin->x > rVtx.x)
		{
			VtxMin->x = rVtx.x;
			m_vtxMin.x = rVtx.x;
		}
		//今の最大値よりも今回の値が大きかったら
		if (VtxMax->x < rVtx.x)
		{
			VtxMax->x = rVtx.x;
			m_vtxMax.x = rVtx.x;
		}
		//<***********************************
		//Y軸判定
		//<***********************************
		//今の最小値よりも今回の値が小さかったら
		if (VtxMin->y > rVtx.y)
		{
			VtxMin->y = rVtx.y;
			m_vtxMin.y = rVtx.y;
		}
		//今の最大値よりも今回の値が大きかったら
		if (VtxMax->y < rVtx.y)
		{
			VtxMax->y = rVtx.y;
			m_vtxMax.y = rVtx.y;
		}
		//<***********************************
		//Z軸判定
		//<***********************************
		//今の最小値よりも今回の値が小さかったら
		if (VtxMin->z > rVtx.z)
		{
			VtxMin->z = rVtx.z;
			m_vtxMin.z = rVtx.z;
		}
		//今の最大値よりも今回の値が大きかったら
		if (VtxMax->z < rVtx.z)
		{
			VtxMax->z = rVtx.z;
			m_vtxMax.z = rVtx.z;
		}

		//サイズ分ポインタを移動させる
		if (FAILED(m_pVtxBuff += m_dwSizeFVF))
		{
			return E_FAIL;
		}
	}

	//頂点バッファをアンロック
	if (FAILED(m_pMesh->UnlockVertexBuffer()))
	{
		return E_FAIL;
	}

	return S_OK;
}
//<====================================
//Xファイル読み込みの処理
//<====================================
HRESULT CXObject::LoadMesh(const char *pFileName, LPD3DXBUFFER *pBuffMat, DWORD *pDwNumMat, LPD3DXMESH *pMesh,
	D3DXMATERIAL *pMat, LPDIRECT3DTEXTURE9 const *pTex)
{
	//Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(pFileName,
		D3DXMESH_SYSTEMMEM,
		CManager::GetRenderer()->GetDevice(),
		NULL,
		pBuffMat,
		NULL,
		pDwNumMat,
		pMesh)))
	{
		return E_FAIL;
	}
	//もし割り当てにいずれかが失敗したら
	if ((m_pBuffMat = *pBuffMat) == 0 || (m_dwNumMat = *pDwNumMat) == 0 || (m_pMesh = *pMesh) == 0)
	{
		//警告文を表示
		MessageBox(NULL, "FAILED TO QUOTA POINTER", "ERROR", MB_ICONWARNING);

		return E_FAIL;
	}

	assert((m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer()) != nullptr);

	pMat = m_pMat;

	//頂点数分繰り返し
	for (DWORD nCntMat = 0; nCntMat < m_dwNumMat; nCntMat++)
	{
		//ファイルが存在していたら
		if (m_pMat[nCntMat].pTextureFilename != NULL && m_apTexture[nCntMat] == nullptr)
		{
			//テクスチャを割り当てる
			CManager::GetTex()->Regist(
				m_pMat[nCntMat].pTextureFilename, m_apTexture[nCntMat]);
		}
	}

	//
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_TEX; nCnt++)
	{
		//持ち主のテクスチャに割り当てる
		pTex = &m_apTexture[nCnt];

		//無駄な処理を省くため
		if (m_apTexture[nCnt] == nullptr)
		{
			break;
		}
	}

	return S_OK;
}
//<====================================
//マテリアルの割り当て
//<====================================
void CXObject::BindMat(D3DXMATERIAL *pMat, LPDIRECT3DTEXTURE9 const *pTex)
{
	//頂点数分繰り返し
	for (DWORD nCntMat = 0; nCntMat < m_dwNumMat; nCntMat++)
	{
		//ファイルが存在していたら
		if (m_pMat[nCntMat].pTextureFilename != NULL && m_apTexture[nCntMat] == nullptr)
		{
			//テクスチャを割り当てる
			CManager::GetTex()->Regist(
				m_pMat[nCntMat].pTextureFilename, m_apTexture[nCntMat]);
		}
	}

	//
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_TEX; nCnt++)
	{
		//持ち主のテクスチャに割り当てる
		pTex = &m_apTexture[nCnt];

		//無駄な処理を省くため
		if (m_apTexture[nCnt] == nullptr)
		{
			break;
		}
	}

}
//<====================================
//サイズの設定
//<====================================
void CXObject::SetSize(D3DXVECTOR3 &rSize, D3DXVECTOR3 &rSizeX, D3DXVECTOR3 &rSizeZ)
{
	//サイズの設定
	m_rSize = m_vtxMax - m_vtxMin;
	rSize = m_rSize;

	//代入
	m_rSizeX = m_rSize;
	m_rSizeZ = m_rSize;

	//判定用に半減する
	m_rSizeX.z = m_rSizeX.z / 2.1f;
	m_rSizeZ.x = m_rSizeZ.x / 2.1f;
	rSizeX = m_rSizeX;
	rSizeZ = m_rSizeZ;
}
//<====================================
//サイズの設定
//<====================================
CXObject *CXObject::Create(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rRot, const char *pFileName)
{
	CXObject *pXObject = new CXObject;

	assert(pXObject != nullptr);

	pXObject->LoadMesh(pFileName, &pXObject->m_pBuffMat, &pXObject->m_dwNumMat,
		&pXObject->m_pMesh, pXObject->m_pMat, pXObject->m_apTexture);

	pXObject->Init();

	pXObject->SetVector3(rPos, rRot, INIT_VECTOR);

	return pXObject;
}