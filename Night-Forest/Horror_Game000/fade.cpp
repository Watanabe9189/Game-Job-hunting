//<==============================================
//フェード処理(fade.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "fade.h"

//<****************************************************
//名前宣言
//<****************************************************
namespace Fade
{
	const float VALUE_ALPHA = 0.07f;									//透明値変更値
	const int MAX_WAIT = 100;											//待機時間の最大値
	const D3DXCOLOR INIT_FADECOL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);	//フェードの色初期値
}

//<====================================================
//コンストラクタ
//<====================================================
CFade::CFade()
{
	//値のクリア
	m_pObject2D = nullptr;
	m_nWaitTime = Fade::MAX_WAIT;
	m_Col = Fade::INIT_FADECOL;
	m_ModeNext = CScene::MODE::MODE_TITLE;
	m_eType = TYPE_FADE_NONE;
	m_rPos = D3DXVECTOR2(0.0f, 0.0f);
}
//<====================================================
//
//<====================================================
CFade::~CFade()
{

}
//<====================================================
//生成処理
//<====================================================
CFade *CFade::Create(void)
{
	//生成用のオブジェクト
	CFade *pFade = new CFade;

	//生成チェック
	assert(pFade != nullptr);

	//初期化チェック
	assert(SUCCEEDED(pFade->Init()));

	return pFade;
}
//<====================================================
//初期化処理
//<====================================================
HRESULT CFade::Init(void)
{
	//中身がなければ
	if (m_pObject2D == nullptr)
	{
		//生成する
		m_pObject2D = new CObject2D;
	}

	m_pObject2D->Init();

	return S_OK;
}
//<====================================================
//更新処理
//<====================================================
void CFade::Update(void)
{
	SetVtx();

	if (m_eType != TYPE_FADE_NONE)
	{
		if (m_eType == TYPE_FADE_OUT)
		{
			SetFadeOut();
		}

		if (m_eType == TYPE_FADE_IN)
		{
			if (m_nWaitTime > 0)
			{
				m_nWaitTime--;
			}

			SetFadeIn();
		}
	}
}
//<====================================================
//頂点情報設定処理
//<====================================================
void CFade::SetVtx(void)
{
	m_pObject2D->SetVtx();

	VERTEX_2D *pVtx;

	m_pObject2D->GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//色の設定
	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pObject2D->GetVtxBuff()->Unlock();
}
//<====================================================
//フェードアウト処理
//<====================================================
void CFade::SetFadeOut(void)
{
	//色を加算していく
	m_Col.a += Fade::VALUE_ALPHA;

	//透明度が
	if (m_Col.a >= 1.0f)
	{
		m_Col.a = 1.0f;

		m_eType = TYPE_FADE_IN;
	}

}
//<====================================================
//フェードイン処理
//<====================================================
void CFade::SetFadeIn(void)
{
	//待機時間がなくなっていたら
	if (m_nWaitTime <= 0)
	{
		//透明度があったら
		if (m_Col.a == 1.0f)
		{
			//モードを設定する
			CManager::SetMode(m_ModeNext);
		}

		//色を減らしていく
		m_Col.a -= Fade::VALUE_ALPHA;

		//透明ではなければ
		if (m_Col.a <= 0.0f)
		{
			//その値にする
			m_Col.a = 0.0f;

			m_eType = TYPE_FADE_NONE;

			m_pObject2D->SetDrawfalse();
		}
	}
}
//<====================================================
//フェードの設定
//<====================================================
void CFade::SetFade(CScene::MODE modeNext)
{
	//フェード何もなし状態だったら
	if (m_eType == TYPE_FADE_NONE)
	{
		//画面全体を覆う
		m_pObject2D->SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));

		m_nWaitTime = Fade::MAX_WAIT;	//待機時間を最大値にする
		m_ModeNext = modeNext;			//次のモードを設定する
		m_eType = TYPE_FADE_OUT;		//フェードアウト状態にする

		m_pObject2D->SetDrawtrue();
	}
}