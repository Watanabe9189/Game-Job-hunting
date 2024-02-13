#include "Cover.h"

//<****************************************************
//
//<****************************************************
LPDIRECT3DTEXTURE9	Ccover::m_apTexture[TYPE_MAX] = {};
const char*			Ccover::m_acFilename[TYPE_MAX] =
{
	NULL,
	"data\\TEXTURE\\thishibuki114.png",
	"data\\TEXTURE\\Cleared000.png",
};
//<====================================================
//
//<====================================================
namespace
{

}
//<====================================================
//
//<====================================================
Ccover::Ccover(int nPriority)
{
	//
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}

	 m_rPos = D3DXVECTOR2(0.0f, 0.0f);
	 m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	 m_rCol = INIT_COL;

	m_nCounter = 0;
}
//<====================================================
//
//<====================================================
Ccover::~Ccover()
{

}
//<====================================================
//
//<====================================================
Ccover *Ccover::Create(const TYPE eType)
{
	Ccover *pCover = new Ccover;

	assert(pCover != nullptr);

	pCover->m_eType = eType;

	pCover->Init();

	return pCover;
}
//<====================================================
//
//<====================================================
HRESULT Ccover::Init(void)	
{
	//テクスチャの初期化
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		//最初だけ読み込む
		if (m_apTexture[nCnt] == nullptr)
		{
			//テクスチャの読み込み
			if (CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt]) <= -1)
			{
				return E_FAIL;
			}
		}
	}

	//タイプ最大値まで繰り返す
	for (int nCnt = 0; nCnt < TYPE_MAX-1; nCnt++)
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

		assert(m_apObject2D != nullptr);

	}
	return S_OK;
}
//<====================================================
//
//<====================================================
void Ccover::Uninit(void)	
{
	//タイプ最大値まで繰り返す
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		//終了処理
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
	}
	Release();
}
//<====================================================
//
//<====================================================
void Ccover::Update(void)	
{
	//タイプ最大値まで繰り返す
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		//中身があれば
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->SetVtx();
		}
	}
}