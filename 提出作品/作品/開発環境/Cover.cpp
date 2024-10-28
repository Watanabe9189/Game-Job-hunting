//<============================================
//カバー処理(Cover.cpp)
//
//Author:kazuki watanabe
//<============================================
#include "Cover.h"

//<****************************************************
//
//<****************************************************
LPDIRECT3DTEXTURE9	Ccover::m_apTexture[TYPE_MAX] = {NULL};
const char*			Ccover::m_acFilename[TYPE_MAX] =
{
	NULL,								//何もなし
	"data\\TEXTURE\\thishibuki114.png",	//血しぶき
	"data\\TEXTURE\\Cleared000.png",	//クリア
};
//<====================================================
//コンストラクタ
//<====================================================
Ccover::Ccover(int nPriority)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; ++nCnt)
	{
		m_apObject2D[nCnt] = {};
	}
	
	 m_rPos = D3DXVECTOR2(0.0f, 0.0f);
	 m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	 m_rCol = INIT_COL;

	m_nCounter = 0;
}
//<====================================================
//デストラクタ
//<====================================================
Ccover::~Ccover()
{

}
//<====================================================
//生成処理
//<====================================================
Ccover *Ccover::Create(const TYPE eType)
{
	Ccover *pCover = new Ccover;

	assert(pCover );

	pCover->m_eType = eType;

	pCover->Init();

	return pCover;
}
//<====================================================
//初期化処理
//<====================================================
HRESULT Ccover::Init(void)	
{
	//テクスチャの初期化
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); ++nCnt)
	{
		//最初だけ読み込む
		if (!m_apTexture[nCnt])
		{
			//テクスチャの読み込み
			if (CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt]) <= -1)
			{
				return E_FAIL;
			}
		}
	}

	//タイプ最大値まで繰り返す
	for (int nCnt = 0; nCnt < TYPE_MAX-1; ++nCnt)
	{
		switch (nCnt)
		{
		case TYPE::TYPE_COVER:

			m_apObject2D[nCnt] = CObject2D::Create(m_rPos, D3DXVECTOR2(SCREEN_WIDTH,SCREEN_HEIGHT), INIT_COL, m_apTexture[nCnt]);

			break;

		case TYPE::TYPE_BLOOD_COV:

			if (m_eType == TYPE_BLOOD_COV)
			{
				m_apObject2D[nCnt] = CObject2D::Create(m_rPos, D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), INIT_COL, m_apTexture[nCnt]);
			}
			else if (m_eType == TYPE_SAFE_COV)
			{
				//位置を設定
				m_rPos = D3DXVECTOR2(625.0f, 375.0f);

				m_apObject2D[nCnt] = CObject2D::Create(m_rPos, D3DXVECTOR2(720.0f, 375.0f), INIT_COL, m_apTexture[nCnt+1]);
			}

			break;

		default:

			break;
		}

		assert(m_apObject2D );

	}
	return S_OK;
}
//<====================================================
//終了処理
//<====================================================
void Ccover::Uninit(void)	
{
	//タイプ最大値まで繰り返す
	for (int nCnt = 0; nCnt < TYPE_MAX; ++nCnt)
	{
		//終了処理
		if (m_apObject2D[nCnt] )
		{
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
	}
	Release();
}
//<====================================================
//更新処理
//<====================================================
void Ccover::Update(void)	
{
	//タイプ最大値まで繰り返す
	for (int nCnt = 0; nCnt < TYPE_MAX; ++nCnt)
	{
		//中身があれば
		if (m_apObject2D[nCnt] )
		{
			m_apObject2D[nCnt]->SetVtx();
		}
	}
}