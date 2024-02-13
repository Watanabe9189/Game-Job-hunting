//<================================================
//2Dエフェクト処理(2DEffect.cpp)
//
//Author:kazuki watanabe
//<================================================
#include "3DEffect.h"
#include "manager.h"
#include "Texture.h"

//<***********************************************
//エフェクトテクスチャ
//<***********************************************
LPDIRECT3DTEXTURE9 C3DEffect::m_apTexture[INT_VALUE::MAX_TEX] = {};

const char	*C3DEffect::m_acFilename[]
{
	"data/TEXTURE/effect/effect000.jpg",	//エフェクト１
	"data/TEXTURE/effect/effect001.png",	//エフェクト２
	"data/TEXTURE/effect/effect002.jpg",	//エフェクト３
};

//<=====================================
//
//<=====================================
C3DEffect::C3DEffect(int nPriority)
{
	//値のクリア
	m_rPos = INIT_VECTOR;
	m_rmove = INIT_VECTOR;
	m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	m_nLife = INT_VALUE::NO_LIFE;
	m_rCol = INIT_COL;
	m_bAdd = true;
	m_bDisp = true;
}
//<=====================================
//
//<=====================================
C3DEffect::~C3DEffect()
{

}
//<=====================================
//
//<=====================================
C3DEffect *C3DEffect::Create(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rMove, const int nLife, const D3DXVECTOR2 rSize, const D3DXCOLOR rCol)
{
	C3DEffect *p3DEffect = new C3DEffect;

	assert(p3DEffect != nullptr);

	//初期化がしっかりされたかチェック
	assert(SUCCEEDED(p3DEffect->Init()));

	//情報の設定
	p3DEffect->SetVector3(rPos, rMove, D3DXVECTOR3(rSize.x, rSize.y, 0.0f));
	p3DEffect->SetColor(rCol);
	p3DEffect->m_nLife = nLife;

	p3DEffect->BindTexture(m_apTexture[1]);

	return p3DEffect;
}
//<=====================================
//
//<=====================================
HRESULT C3DEffect::Init(void)
{
	//テクスチャの初期化
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		//最初だけ読み込む
		if (m_apTexture[nCnt] == nullptr)
		{
			//テクスチャの読み込み
			if ((CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt])) <= -1)
			{
				return E_FAIL;
			}
		}
	}

	CBillB::Init();

	return S_OK;
}
//<=====================================
//
//<=====================================
void C3DEffect::Uninit(void)
{
	CBillB::Uninit();
}
//<=====================================
//
//<=====================================
void C3DEffect::Update(void)
{
	//表示状態になっていたら
	if (m_bDisp)
	{
		SetVtx();

		//情報の取得
		m_rPos = GetPos();
		m_rmove = GetMove();
		m_rSize.x = GetSize().x;
		m_rSize.y = GetSize().y;
		m_rCol = GetColor();

		//ライフがある場合
		if (!(m_nLife <= 0))
		{
			m_nLife--;
		}
		//ない場合
		else
		{
			//表示をさせない
			m_bDisp = false;

			return;
		}

		//位置を更新
		m_rPos += m_rmove;

		//情報の設定
		SetVector3(m_rPos, m_rmove, D3DXVECTOR3(m_rSize.x, m_rSize.y, 150.0f));
		SetColor(m_rCol);
	}
}
//<=====================================
//
//<=====================================
void C3DEffect::Draw(void)
{
	//表示状態になっていたら
	if (m_bDisp)
	{
		// 加算合成がONの場合
		if (m_bAdd)
		{
			//αブレンディングを加算合成に設定
			CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		CBillB::Draw();

		//αブレンディングを元に戻す
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}