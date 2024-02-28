//<===============================================
//3Dオブジェクト専門の処理[Xファイル](XObject.cpp)
//
//Author:kazuki watanabe
//<===============================================
#include "XObject.h"
#include "manager.h"
#include "Texture.h"

int CXObject::m_nNumAll = INITIAL_INT;
const char *CXObject::m_apFileName[INT_VALUE::MAX_SIZE] = {};
CXObject::DataModel CXObject::m_asaveModel[INT_VALUE::MAX_SIZE] = {};

//<====================================
//Xファイルオブジェクトのコンストラクタ
//<====================================
CXObject::CXObject(int nPriority) : CObject(nPriority)
{
	//値のクリア
	m_mtxWorld = {};

	//位置情報関連
	m_pos		=	INIT_VECTOR;
	m_rot		=	INIT_VECTOR;
	m_move		=	INIT_VECTOR;

	m_pMat = nullptr;

	m_asModel = {};
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
	for (DWORD nCntMat = 0; nCntMat < m_asModel.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		CManager::GetRenderer()->GetDevice()->SetMaterial(&m_asModel.pMat[nCntMat].MatD3D);

		//テクスチャの設定
		CManager::GetRenderer()->GetDevice()->SetTexture(0, m_asModel.apTexture[nCntMat]);

		//モデルの描画
		m_asModel.pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	CManager::GetRenderer()->GetDevice()->SetMaterial(&matDef);
}
//<====================================
//
//<====================================
CXObject::DataModel CXObject::BindModel(const char *pFileName, const bool bMatChange)
{
	int nNum = m_nNumAll;

	//数分繰り返す
	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		if (m_apFileName[nCnt] != nullptr)
		{
			//もし保存されたファイル名と引数のファイル名が一緒だったら
			if (strcmp(m_apFileName[nCnt], pFileName) == 0)
			{
				//その番号を返し、すでに登録されているテクスチャ
				m_asModel = m_asaveModel[nCnt];

				//もしマテリアルを変更したい場合
				if (bMatChange)
				{
					//<==========================================
					//色変えのためにもう一度モデルを読み込む
					//(pBuffMat以外はすでに保存されているデータを使用)
					//<==========================================
					if (FAILED(D3DXLoadMeshFromX(m_apFileName[nCnt],
						D3DXMESH_SYSTEMMEM,
						CManager::GetRenderer()->GetDevice(),
						NULL,
						&m_asModel.pBuffMat,			//ここだけ変更するモデルの引数にする
						NULL,
						&m_asaveModel[nCnt].dwNumMat,
						&m_asaveModel[nCnt].pMesh)))
					{
						return{};
					}

					assert((m_asModel.pMat =
						(D3DXMATERIAL*)m_asModel.pBuffMat->GetBufferPointer()) != nullptr);

					m_asModel.pOriginMat = m_asaveModel[nCnt].pOriginMat;
					//<==========================================
					//
					//<==========================================
				}
				m_nModelId = nCnt;
				return m_asModel;
			}
		}
	}

	m_apFileName[nNum] = pFileName;

	//モデルの設定を行う
	LoadModel();
	CheckVtxNo();

	m_nModelId = m_nNumAll;

	m_asModel = m_asaveModel[nNum];

	m_nNumAll++;

	return m_asModel;
}
//<====================================
//サイズの設定
//<====================================
void CXObject::LoadModel(void)
{
	//Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(m_apFileName[m_nNumAll],
		D3DXMESH_SYSTEMMEM,
		CManager::GetRenderer()->GetDevice(),
		NULL,
		&m_asaveModel[m_nNumAll].pBuffMat,
		NULL,
		&m_asaveModel[m_nNumAll].dwNumMat,
		&m_asaveModel[m_nNumAll].pMesh)))
	{
		
	}

	assert((m_asaveModel[m_nNumAll].pMat =
		(D3DXMATERIAL*)m_asaveModel[m_nNumAll].pBuffMat->GetBufferPointer()) != nullptr);

	m_asaveModel[m_nNumAll].pOriginMat = m_asaveModel[m_nNumAll].pMat;

	//頂点数分繰り返し
	for (DWORD nCntMat = 0; nCntMat < m_asaveModel[m_nNumAll].dwNumMat; nCntMat++)
	{
		//ファイルが存在していたら
		if (m_asaveModel[m_nNumAll].pMat[nCntMat].pTextureFilename != NULL &&
			m_asaveModel[m_nNumAll].apTexture[nCntMat] == nullptr)
		{
			//テクスチャを割り当てる
			CManager::GetTex()->Regist(
				m_asaveModel[m_nNumAll].pMat[nCntMat].pTextureFilename,
				m_asaveModel[m_nNumAll].apTexture[nCntMat]);
		}
	}
}
//<====================================
//サイズの設定
//<====================================
void CXObject::CheckVtxNo(void)
{
	//頂点確認用のバーテックス変数
	D3DXVECTOR3 rVtx = INIT_VECTOR;

	//モデルの頂点数を取得
	m_asaveModel[m_nNumAll].nNumVtx = m_asaveModel[m_nNumAll].pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	m_asaveModel[m_nNumAll].dwSizeFVF = D3DXGetFVFVertexSize(m_asaveModel[m_nNumAll].pMesh->GetFVF());

	//頂点バッファをロック
	m_asaveModel[m_nNumAll].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_asaveModel[m_nNumAll].pVtxBuff);

	//全ての頂点をチェックする
	for (int nCntVtx = 0; nCntVtx < m_asaveModel[m_nNumAll].nNumVtx; nCntVtx++)
	{
		//今回のデータ
		rVtx = *(D3DXVECTOR3*)m_asaveModel[m_nNumAll].pVtxBuff;

		//<***********************************
		//X軸判定
		//<***********************************
		//今の最小値よりも今回の値が小さかったら
		if (m_asaveModel[m_nNumAll].vtxMin.x > rVtx.x)
		{
			m_asaveModel[m_nNumAll].vtxMin.x = rVtx.x;
		}
		//今の最大値よりも今回の値が大きかったら
		if (m_asaveModel[m_nNumAll].vtxMax.x < rVtx.x)
		{
			m_asaveModel[m_nNumAll].vtxMax.x = rVtx.x;
		}
		//<***********************************
		//Y軸判定
		//<***********************************
		//今の最小値よりも今回の値が小さかったら
		if (m_asaveModel[m_nNumAll].vtxMin.y > rVtx.y)
		{
			m_asaveModel[m_nNumAll].vtxMin.y = rVtx.y;
		}
		//今の最大値よりも今回の値が大きかったら
		if (m_asaveModel[m_nNumAll].vtxMax.y < rVtx.y)
		{
			m_asaveModel[m_nNumAll].vtxMax.y = rVtx.y;
		}
		//<***********************************
		//Z軸判定
		//<***********************************
		//今の最小値よりも今回の値が小さかったら
		if (m_asaveModel[m_nNumAll].vtxMin.z > rVtx.z)
		{
			m_asaveModel[m_nNumAll].vtxMin.z = rVtx.z;
		}
		//今の最大値よりも今回の値が大きかったら
		if (m_asaveModel[m_nNumAll].vtxMax.z < rVtx.z)
		{
			m_asaveModel[m_nNumAll].vtxMax.z = rVtx.z;
		}

		//サイズ分ポインタを移動させる
		m_asaveModel[m_nNumAll].pVtxBuff += m_asaveModel[m_nNumAll].dwSizeFVF;

	}

	//頂点バッファをアンロック
	m_asaveModel[m_nNumAll].pMesh->UnlockVertexBuffer();

	//サイズの設定
	m_asaveModel[m_nNumAll].rSize = m_asaveModel[m_nNumAll].vtxMax - m_asaveModel[m_nNumAll].vtxMin;

	//代入
	m_asaveModel[m_nNumAll].rSizeX = m_asaveModel[m_nNumAll].rSize;
	m_asaveModel[m_nNumAll].rSizeZ = m_asaveModel[m_nNumAll].rSize;

	//判定用に半減する
	m_asaveModel[m_nNumAll].rSizeX.z = m_asaveModel[m_nNumAll].rSizeX.z / 2.1f;
	m_asaveModel[m_nNumAll].rSizeZ.x = m_asaveModel[m_nNumAll].rSizeZ.x / 2.1f;
}
//<====================================
//サイズの設定
//<====================================
CXObject *CXObject::Create(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rRot, const char *pFileName)
{
	CXObject *pXObject = new CXObject;

	assert(pXObject != nullptr);

	pXObject->BindModel(pFileName);

	pXObject->Init();

	pXObject->SetVector3(rPos, rRot, INIT_VECTOR);

	return pXObject;
}

