//<=====================================================
//地面処理(Field.cpp)
//
//Author:kazuki watanabe
//<=====================================================
#include "Field.h"
#include "manager.h"
#include "Texture.h"

int CField::m_nNumAll = NULL;
LPDIRECT3DTEXTURE9 CField::m_pTexture = nullptr;

//<==========================
//地面のコンストラクタ
//<==========================
CField::CField()
{
	m_nNumAll++;
	//値のクリア
	m_pos = INIT_VECTOR;
	m_rot = INIT_VECTOR;
	m_Size = INIT_VECTOR;
	m_mtxWorld = {};
	m_Depth = INITIAL_INT;
	m_width = INITIAL_INT;
	m_nNumIndex = INITIAL_INT;
	m_NumVtx = INITIAL_INT;
}
//<==========================
//地面のデストラクタ
//<==========================
CField::~CField()
{
	m_nNumAll--;
}
//<==========================
//地面の生成処理
//<==========================
CField *CField::Create(const D3DXVECTOR3 pos)
{
	CField *pField = new CField;

	if (pField != NULL)
	{
		pField->m_pos = pos;

		//初期化処理
		pField->Init();
	}

	return pField;
}
//<==========================
//地面の初期化処理
//<==========================
HRESULT CField::Init(void)
{
	if (m_pTexture == nullptr)
	{
		if (FAILED(CManager::GetTex()->Regist("data/TEXTURE/Grass001.png", m_pTexture)))
		{
			return E_FAIL;
		}
	}

	//値の設定
	m_NumVtx = (m_width + 1) * (m_Depth + 1);								//頂点数
	m_nNumIndex = (m_Depth * ((m_width + 1) * 2)) + (2 * (m_Depth - 1));	//インデックス数

	SetVtx();

	SetIndex();

	return S_OK;
}
//<==========================
//地面の終了処理
//<==========================
void CField::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	Release();
}
//<==========================
//地面の更新処理(今は使わない)
//<==========================
void CField::Update(void)
{
	
}
//<==========================
//地面の描画処理
//<==========================
void CField::Draw(void)
{
	//この関数でしか使わない変数宣言
	D3DXMATRIX	mtxRot = {}, mtxTrans = {};		//計算用マトリックス宣言

	//アルファテストの設定
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 255);					//0x000000FF[数字で言う255まで]
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//有効にする
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	//値が現在のピクセルの値以上の場合、新しいピクセルを受け入れる。

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

	//頂点バッファをデータストリームに設定
	CManager::GetRenderer()->GetDevice()->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	CManager::GetRenderer()->GetDevice()->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	CManager::GetRenderer()->GetDevice()->SetFVF(FVF_VERTEX_3D_MULTI);

	//テクスチャの設定
	CManager::GetRenderer()->GetDevice()->SetTexture(0, m_pTexture);

	if (m_NumVtx != NULL && m_nNumIndex != NULL)
	{
		//ポリゴンの描画
		CManager::GetRenderer()->GetDevice()->DrawIndexedPrimitive(
			D3DPT_TRIANGLESTRIP,
			NULL,
			NULL,
			m_NumVtx,
			NULL,
			m_nNumIndex);

	}

	//アルファテストの設定解除
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0);//0にする
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);//無効にする
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NEVER);//常に失敗する

}
//<==========================
//地面の頂点情報設定処理
//<==========================
void CField::SetVtx(void)
{
	if (m_pVtxBuff == nullptr)
	{
		//頂点バッファの生成
		CManager::GetRenderer()->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * m_NumVtx,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D_MULTI,
			D3DPOOL_MANAGED,
			&m_pVtxBuff,
			NULL);
	}
	
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(NULL, NULL, (void**)&pVtx, NULL);

	//奥のデータ数分
	for (int nCntDepth = 0; nCntDepth < m_Depth; nCntDepth++)
	{
		for (int nCntWidth = 0; nCntWidth < m_width + 1; nCntWidth++)
		{//横の頂点数分繰り返す

		 //頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(
				(m_Size.x * nCntWidth) - ((m_Size.x * m_width) * 0.5f),
				NULL,
				-((m_Size.z * nCntDepth) - ((m_Size.z * m_Depth) * 0.5f)));

			//法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2
			(
				((float)nCntWidth / (1.0f / (float)(m_width + 1))) * (1.0f / (float)(m_width + 1)),
				((float)nCntDepth / (1.0f / (float)(m_Depth + 1))) * (1.0f / (float)(m_Depth + 1))
			);

			pVtx += 1;
		}


	}
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//<==========================
//地面のインデックス情報設定
//<==========================
void CField::SetIndex(void)
{
	if (m_pIdxBuff == nullptr)
	{
		//インデックスバッファの生成
		CManager::GetRenderer()->GetDevice()->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&m_pIdxBuff,
			NULL);
	}

	//インデックスバッファの要素番号
	int nNumIdx = 0;

	//インデックス情報へのポインタ
	WORD *pIdx;

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//奥のデータ数分
	for (int nCntDepth = 0; nCntDepth < m_Depth; nCntDepth++)
	{
		//横の頂点数分繰り返す
		for (int nCntWidth = 0; nCntWidth < m_width + 1; nCntWidth++)
		{

			pIdx[nNumIdx + 0] = nCntWidth + (m_width + 1) * (nCntDepth + 1);
			pIdx[nNumIdx + 1] = nCntWidth + ((m_width + 1) * nCntDepth);

			//2個ずつチェック
			nNumIdx += 2;
		}

		if (nCntDepth + 1 < m_Depth)
		{

			//空打ち2つ分
			pIdx[nNumIdx + 0] = ((m_width + 1) * (nCntDepth + 1)) - 1;
			pIdx[nNumIdx + 1] = (m_width + 1) * (nCntDepth + 2);

			//2個ずつチェック
			nNumIdx += 2;

		}

	}

	//インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();
}
//<==========================
//地面の当たり判定
//<==========================
bool CField::CollisionField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, TYPE_3D Type3D)
{
	//フィールドの範囲内にいる場合
	if (pPos->x + vtxMax->x	  >=	m_pos.x - (m_Size.x  * m_width)
		&& pPos->x + vtxMin->x <= m_pos.x + (m_Size.x * m_width)
		&& pPos->z + vtxMax->z >= m_pos.z - (m_Size.z * m_Depth)
		&& pPos->z + vtxMin->z <= m_pos.z + (m_Size.z * m_Depth))
	{

	 //もしその下に行きそうになったら
		if (-pPosOld->y >= m_pos.y &&
			pPos->y < m_pos.y)
		{
			pPos->y = m_pos.y;
			return true;
		}

	}
	return false;
}
//<==========================
//地面の生成
//<==========================
CField *CField::ReadCreate(CField *apField[MAX_OBJECT])
{
	//必要以外の文字列読み込み用データ
	char aChar[INT_VALUE::MAX_CHAR] = { NULL };

	//何個目かの情報
	int nCntMax = 0;

	//ファイル情報
	FILE *pFile = nullptr;

	pFile = fopen("data/TEXT/SetField.txt", "r");

	//ファイルが開けたら
	if (pFile != NULL)
	{
		//ずっと繰り返す
		while (strcmp(aChar, "EndFile") != 0)
		{
			//空字を読み込む
			(void)fscanf(pFile, "%s", &aChar[0]);

			//ENEMY-SETという文字列が存在したら
			if (strcmp(aChar, "FIELD-SET") == 0)
			{

				//もし中身がなければ
				if (apField[nCntMax] == nullptr)
				{
					apField[nCntMax] = new CField;
				}

				//End-Setという文字を認識するまで繰り返す
				while (strcmp(aChar, "End-Set"))
				{
					//空字を読み込む
					(void)fscanf(pFile, "%s", &aChar[0]);

					//メモリ確保されていたら
					if (apField[nCntMax] != nullptr)
					{
						//POSという文字列が存在したら
						if (strcmp(aChar, "POS") == 0)
						{
							//空字を読み込む
							(void)fscanf(pFile, "%s", &aChar[0]);

							//位置を読み込む
							(void)fscanf(pFile, "%f", &apField[nCntMax]->m_pos.x);
							(void)fscanf(pFile, "%f", &apField[nCntMax]->m_pos.y);
							(void)fscanf(pFile, "%f", &apField[nCntMax]->m_pos.z);
						}
						//SIZEという文字列が存在したら
						if (strcmp(aChar, "SIZE") == 0)
						{
							//空字を読み込む
							(void)fscanf(pFile, "%s", &aChar[0]);

							//サイズを読み込む
							(void)fscanf(pFile, "%f", &apField[nCntMax]->m_Size.x);
							(void)fscanf(pFile, "%f", &apField[nCntMax]->m_Size.y);
							(void)fscanf(pFile, "%f", &apField[nCntMax]->m_Size.z);
						}
						//DEPTHという文字列が存在したら
						if (strcmp(aChar, "DEPTH") == 0)
						{
							//空字を読み込む
							(void)fscanf(pFile, "%s", &aChar[0]);

							//奥の分割数を読み込む
							(void)fscanf(pFile, "%d", &apField[nCntMax]->m_Depth);
						}
						//WIDTHという文字列が存在したら
						if (strcmp(aChar, "WIDTH") == 0)
						{
							//空字を読み込む
							(void)fscanf(pFile, "%s", &aChar[0]);

							//手前の分割数を読み込む
							(void)fscanf(pFile, "%d", &apField[nCntMax]->m_width);
						}
					}

					//もし奥の分割数と手前の分割数の中身が両方あれば
					if (apField[nCntMax]->m_width != NULL &&apField[nCntMax]->m_Depth != NULL)
					{
						//初期化処理
						if (FAILED(apField[nCntMax]->Init()))
						{
							delete apField[nCntMax];
							apField[nCntMax] = nullptr;

							return *apField;
						}

					}
					
					//タイプの設定
					apField[nCntMax]->SetType3D(TYPE_3D::TYPE_FIELD);
				}
				//数を増やす
				nCntMax++;
			}
		}
		//ファイルを閉じる
		fclose(pFile);

	}

	return *apField;
}
