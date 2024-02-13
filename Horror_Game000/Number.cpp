//<===================================
//番号関連の処理(Number.cpp)
//
//Author:kazuki watanabe
//<===================================
#include "Number.h"
#include "object2D.h"
#include "manager.h"
#include "Texture.h"

//<=====================================
//番号のコンストラクタ
//<=====================================
CNumber::CNumber(int nPriority)
{
	//値のクリア
	m_nNum = INITIAL_INT;
	m_pObject2D = nullptr;
}
//<=====================================
//番号のデストラクタ
//<=====================================
CNumber::~CNumber()
{

}
//<=====================================
//番号の生成処理
//<=====================================
CNumber *CNumber::Create(const D3DXVECTOR2 rPos, const D3DXVECTOR2 rSize, const LPDIRECT3DTEXTURE9 pTexture)
{
	CNumber *pNumber = new CNumber;

	assert(pNumber != nullptr);

	//初期化処理
	pNumber->Init(rPos, rSize, pTexture);

	return pNumber;
}
//<=====================================
//番号の初期化処理
//<=====================================
HRESULT CNumber::Init(const D3DXVECTOR2 rPos, const D3DXVECTOR2 rSize, const LPDIRECT3DTEXTURE9 pTexture)
{
	m_pObject2D = CObject2D::Create(rPos, rSize);

	assert(m_pObject2D != nullptr);

	m_pObject2D->BindTexture(pTexture);

	return S_OK;
}
//<=====================================
//番号の終了処理
//<=====================================
void CNumber::Uninit(void)
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Uninit();
		m_pObject2D = nullptr;
	}
}
//<=====================================
//番号の更新処理
//<=====================================
void CNumber::Update(void)
{
	//個数を取得
	m_nNum = GetNum();

	//頂点座標設定
	SetVtx();

	//個数を設定
	SetNum(&m_nNum);
}
//<=====================================
//番号の頂点情報設定
//<=====================================
void CNumber::SetVtx(void)
{
	//中身があれば
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->SetVtx();

		VERTEX_2D *pVtx;

		m_pObject2D->GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < m_nNum; nCnt++)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(m_nNum*0.1f + 0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(m_nNum*0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(m_nNum*0.1f + 0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(m_nNum*0.1f + 0.1f, 1.0f);

		}

		m_pObject2D->GetVtxBuff()->Unlock();
	}
}