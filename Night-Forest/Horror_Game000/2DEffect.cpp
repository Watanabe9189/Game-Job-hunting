//<================================================
//2Dエフェクト処理(2DEffect.cpp)
//
//Author:kazuki watanabe
//<================================================
#include "2DEffect.h"
#include "manager.h"
#include "Texture.h"

//<***********************************************
//エフェクトテクスチャ
//<***********************************************
LPDIRECT3DTEXTURE9 C2DEffect::m_apTexture[INT_VALUE::MAX_TEX] = {};

const char	*C2DEffect::m_acFilename[]
{
	"data/TEXTURE/effect/effect000.jpg",	//エフェクト１
	"data/TEXTURE/effect/effect001.png",	//エフェクト２
	"data/TEXTURE/effect/effect002.jpg",	//エフェクト３
};

//<=====================================
//
//<=====================================
C2DEffect::C2DEffect(int nPriority)
{
	//値のクリア
	m_rPos = D3DXVECTOR2(0.0f,0.0f);
	m_rmove = D3DXVECTOR2(0.0f, 0.0f);
	m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	m_nLife = INT_VALUE::NO_LIFE;
	m_rCol = INIT_COL;
	m_bAdd = true;
	m_bDisp = true;
}
//<=====================================
//
//<=====================================
C2DEffect::~C2DEffect()
{

}
//<=====================================
//
//<=====================================
C2DEffect *C2DEffect::Create(const D3DXVECTOR2 rPos, const D3DXVECTOR3 rMove, const int nLife, const D3DXVECTOR2 rSize, const D3DXCOLOR rCol)
{
	C2DEffect *p2DEffect = new C2DEffect;

	assert(p2DEffect != nullptr);

	//初期化がしっかりされたかチェック
	assert(SUCCEEDED(p2DEffect->Init()));

	//情報の設定
	p2DEffect->SetPosition(rPos);
	p2DEffect->SetSize(rSize);
	p2DEffect->SetColor(rCol);

	p2DEffect->m_rmove = D3DXVECTOR2(rMove.x, rMove.y);
	p2DEffect->m_nLife = nLife;

	/*p2DEffect->BindTexture(m_apTexture[1]);*/

	return p2DEffect;
}
//<=====================================
//
//<=====================================
HRESULT C2DEffect::Init(void)
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

	CObject2D::Init();

	return S_OK;
}
//<=====================================
//
//<=====================================
void C2DEffect::Uninit(void)
{
	CObject2D::Uninit();
}
//<=====================================
//
//<=====================================
void C2DEffect::Update(void)
{
	//表示状態になっていたら
	if (m_bDisp)
	{
		SetVtx();

		//情報の取得
		m_rPos = GetPosition();
		m_rSize = GetSize();
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
		SetPosition(m_rPos);
		SetSize(m_rSize);
		SetColor(m_rCol);
	}
}
//<=====================================
//
//<=====================================
void C2DEffect::Draw(void)
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


		CObject2D::Draw();

		//αブレンディングを元に戻す
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}
//<=====================================
//
//<=====================================
void C2DEffect::SetVtx(void)
{
	CObject2D::SetVtx();
}