////<======================================================
//Xオブジェクトでの建物処理
//
//Author:Kazuki Watanabe
//<======================================================
#include "Building.h"

//<*******************************************
//静的メンバ変数の宣言
//<*******************************************
//テクスチャ関連
LPDIRECT3DTEXTURE9	CBuilding::m_apTexture[INT_VALUE::MAX_TEX] = { NULL };	//テクスチャ情報

int CBuilding::m_nNumAll = NULL;									//数
//<==========================================
//ファイル名指定
//<==========================================
const char		*CBuilding::m_acFilename[TYPE::TYPE_MAX] =
{
	"data/MODEL/House.x",		//敵２
	"data/MODEL/Tent000.x",		//敵３

};
//<==========================================
//コンストラクタ
//<==========================================
CBuilding::CBuilding()
{
	m_nNumAll++;

	//値のクリア
	m_pos = INIT_VECTOR;
	m_rot = INIT_VECTOR;
	m_move = INIT_VECTOR;

	m_pBuffMat = {};
	m_dwNumMat = {};
	m_pMesh = {};

	m_vtxMax = INIT_VECTOR;
	m_vtxMin = INIT_VECTOR;
	m_rSize = INIT_VECTOR;
	m_rSizeX = INIT_VECTOR;
	m_rSizeZ = INIT_VECTOR;

	m_pMat = nullptr;

	m_rHideRad = INIT_VECTOR;

}
//<==========================================
//デストラクタ
//<==========================================
CBuilding::~CBuilding()
{
	m_nNumAll--;
}
//<==========================================
//初期化処理
//<==========================================
HRESULT CBuilding::Init(void)
{
	//隠れられる範囲を設定
	m_rHideRad = D3DXVECTOR3(150.0f, 150.0f, 150.0f);

	//もし初期化に失敗したら
	if (FAILED(CXObject::Init()))
	{
		return E_FAIL;
	}
	//マテリアルデータへのポインタを取得
	if (FAILED(m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer()))
	{
		return E_FAIL;
	}

	return S_OK;
}
//<==========================================
//更新処理
//<==========================================
void CBuilding::Update(void)
{
	//情報取得
	m_pos = GetPosition();
	m_rot = GetRotation();

	//情報設定
	SetVector3(m_pos, m_rot, {});
}
//<==========================================
//生成処理
//<==========================================
CBuilding *CBuilding::Create(const D3DXVECTOR3 pos, const TYPE eType)
{
	CBuilding *pBuilding = new CBuilding;

	assert(pBuilding != nullptr);

	//モデルの読み込みをする
	assert(SUCCEEDED(pBuilding->LoadMesh(m_acFilename[eType], &pBuilding->m_pBuffMat, &pBuilding->m_dwNumMat, 
		&pBuilding->m_pMesh, pBuilding->m_pMat, m_apTexture)));
	
	//初期化処理
	assert(SUCCEEDED(pBuilding->Init()));

	//ベクターを代入
	pBuilding->SetVector3(pos, pBuilding->m_rot, {});

	//
	pBuilding->SetType3D(TYPE_3D::TYPE_BUILDING);

	//もし頂点確認に失敗したら
	if (FAILED(pBuilding->CheckVtx(&pBuilding->m_vtxMax, &pBuilding->m_vtxMin, pBuilding->m_rot.y)))
	{
		return nullptr;
	}

	//サイズ設定
	pBuilding->SetSize(pBuilding->m_rSize, pBuilding->m_rSizeX, pBuilding->m_rSizeZ);

	return pBuilding;
}
//<==========================================
//生成処理(Xファイルから)
//<==========================================
CBuilding *CBuilding::ReadCreate(CBuilding *apBuilding[MAX_OBJECT])
{
	//必要以外の文字列読み込み用データ
	char aChar[INT_VALUE::MAX_CHAR] = { NULL };

	//何個目かの情報
	int nCntMax = 0;

	//ファイル情報
	FILE *pFile = fopen("data/TEXT/SetBuilding.txt", "r");

	//ファイルが開けたら
	if (pFile != NULL)
	{
		//ずっと繰り返す
		while (strcmp(aChar, "EndFile") != 0)
		{
			//空字を読み込む
			(void)fscanf(pFile, "%s", &aChar[0]);

			//ENEMY-SETという文字列が存在したら
			if (strcmp(aChar, "BUILDING-SET") == 0)
			{
				//もし中身がなければ
				if (apBuilding[nCntMax] == nullptr)
				{
					apBuilding[nCntMax] = new CBuilding;
				}

				//End-Setという文字を認識するまで繰り返す
				while (strcmp(aChar, "End-Set"))
				{
					//空字を読み込む
					(void)fscanf(pFile, "%s", &aChar[0]);

					//メモリ確保されていたら
					if (apBuilding[nCntMax] != nullptr)
					{
						//TYPEという文字列が存在したら
						if (strcmp(aChar, "TYPE") == 0)
						{
							//空字を読み込む
							(void)fscanf(pFile, "%s", &aChar[0]);

							//タイプを読み込む
							(void)fscanf(pFile, "%d", &apBuilding[nCntMax]->m_eType);

							assert(SUCCEEDED(apBuilding[nCntMax]->LoadMesh(
								m_acFilename[apBuilding[nCntMax]->m_eType],
								&apBuilding[nCntMax]->m_pBuffMat,
								&apBuilding[nCntMax]->m_dwNumMat,
								&apBuilding[nCntMax]->m_pMesh, apBuilding[nCntMax]->m_pMat, m_apTexture)));

							//初期化処理を行う
							if ((apBuilding[nCntMax]->Init()) == 0xC0000005)
							{
								delete apBuilding[nCntMax];
								apBuilding[nCntMax] = nullptr;

								return *apBuilding;
							}

						}

						//POSという文字列が存在したら
						if (strcmp(aChar, "POS") == 0)
						{
							//空字を読み込む
							(void)fscanf(pFile, "%s", &aChar[0]);

							//位置を読み込む
							(void)fscanf(pFile, "%f", &apBuilding[nCntMax]->m_pos.x);
							(void)fscanf(pFile, "%f", &apBuilding[nCntMax]->m_pos.y);
							(void)fscanf(pFile, "%f", &apBuilding[nCntMax]->m_pos.z);

							//位置を代入
							apBuilding[nCntMax]->SetPosition(apBuilding[nCntMax]->m_pos);
						}
					}
					//
					apBuilding[nCntMax]->SetType3D(TYPE_3D::TYPE_BUILDING);

					//もし頂点確認に失敗したら
					if (FAILED(apBuilding[nCntMax]->CheckVtx(&apBuilding[nCntMax]->m_vtxMax, &apBuilding[nCntMax]->m_vtxMin, apBuilding[nCntMax]->m_rot.y)))
					{
						return nullptr;
					}

					//サイズ設定
					apBuilding[nCntMax]->SetSize(apBuilding[nCntMax]->m_rSize, apBuilding[nCntMax]->m_rSizeX, apBuilding[nCntMax]->m_rSizeZ);
				}
				//数を増やす
				nCntMax++;
			}
		}
		//ファイルを閉じる
		fclose(pFile);

	}
	return *apBuilding;
}
//<==========================================
//生成処理(Xファイルから)
//<==========================================
CBuilding *CBuilding::RandCreate(CBuilding *apBuilding[MAX_OBJECT], const int nNum)
{
	//ここでしか使わない変数の宣言
	D3DXVECTOR3 rRandPos = INIT_VECTOR;
	int nRandType = TYPE::TYPE_MAX;
	float nCollidRange = INITIAL_FLOAT;	

	//建物の数分回す
	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		apBuilding[nCnt] = new CBuilding;

		assert(apBuilding[nCnt] != nullptr);

		//ランダムで値を決める
		rRandPos = rRandPos = D3DXVECTOR3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false));
		nRandType = rand() % TYPE::TYPE_MAX + TYPE::TYPE_CABIN;

		//モデルの読み込みをする
		assert(SUCCEEDED(apBuilding[nCnt]->LoadMesh(m_acFilename[nRandType], &apBuilding[nCnt]->m_pBuffMat,
			&apBuilding[nCnt]->m_dwNumMat, &apBuilding[nCnt]->m_pMesh, apBuilding[nCnt]->m_pMat, m_apTexture)));

		//初期化処理
		assert(SUCCEEDED(apBuilding[nCnt]->Init()));

		//ベクターを代入
		apBuilding[nCnt]->SetVector3(rRandPos, apBuilding[nCnt]->m_rot, {});
		apBuilding[nCnt]->m_eType = (CBuilding::TYPE)nRandType;

		//
		apBuilding[nCnt]->SetType3D(TYPE_3D::TYPE_BUILDING);

		//もし頂点確認に失敗したら
		if (FAILED(apBuilding[nCnt]->CheckVtx(&apBuilding[nCnt]->m_vtxMax, &apBuilding[nCnt]->m_vtxMin, apBuilding[nCnt]->m_rot.y)))
		{
			return nullptr;
		}

		//サイズ設定
		apBuilding[nCnt]->SetSize(apBuilding[nCnt]->m_rSize, apBuilding[nCnt]->m_rSizeX, apBuilding[nCnt]->m_rSizeZ);

		//建物の数分回す
		for (int nCntBefore = -1; nCntBefore < m_nNumAll-1; nCntBefore++)
		{
			//もし手前の建物の中身があれば
			if (nCntBefore != -1 && apBuilding[nCntBefore] != nullptr)
			{
				nCollidRange = 350.0f;

				//<****************************************
				//隠れる処理
				//<****************************************
				//どの軸にも当たっていたら
				if (apBuilding[nCntBefore]->GetPosition().z + nCollidRange > apBuilding[nCnt]->GetPosition().z + apBuilding[nCnt]->GetVtxMin().z&&
					apBuilding[nCntBefore]->GetPosition().z + -nCollidRange < apBuilding[nCnt]->GetPosition().z + apBuilding[nCnt]->GetVtxMax().z&&
					apBuilding[nCntBefore]->GetPosition().x + nCollidRange > apBuilding[nCnt]->GetPosition().x + apBuilding[nCnt]->GetVtxMin().x&&
					apBuilding[nCntBefore]->GetPosition().x + -nCollidRange< apBuilding[nCnt]->GetPosition().x + apBuilding[nCnt]->GetVtxMax().x&&
					apBuilding[nCntBefore]->GetPosition().y + nCollidRange > apBuilding[nCnt]->GetPosition().y + apBuilding[nCnt]->GetVtxMin().y&&
					apBuilding[nCntBefore]->GetPosition().y + -nCollidRange < apBuilding[nCnt]->GetPosition().y + apBuilding[nCnt]->GetVtxMax().y)
				{
					rRandPos = D3DXVECTOR3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false));
					apBuilding[nCntBefore]->SetPosition(rRandPos);
				}
			}
		}
	}
	return *apBuilding;
}