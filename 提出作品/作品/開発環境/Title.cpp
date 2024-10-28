//<===========================================
//タイトル画面の処理(Title.cpp)
//
//Author:kazuki watanabe
//<===========================================
#include "Title.h"
#include "input.h"
#include "object2D.h"
#include "manager.h"
#include "Texture.h"
#include "DebugProc.h"
#include "fade.h"

//<******************************************************************************
//静的メンバ変数
//<******************************************************************************
C2DChar *CTitle::m_ap2DChar[INT_VALUE::MAX_SIZE] = {nullptr};								//2D文字

LPDIRECT3DTEXTURE9	CTitle::m_apTexture[INT_VALUE::MAX_TEX] = {NULL};	//テクスチャポインタ
const char*			CTitle::m_acFilename[SELECT_MAX] =				//ファイルの名前
{
		"data\\TEXTURE\\HORROR-SELECT000.png",
		"data\\TEXTURE\\HORROR-SELECT001.png",
		"data\\TEXTURE\\HORROR-SELECT002.png",
};
//<******************************************************************************
//名前宣言
//<******************************************************************************
namespace
{
	const float			DISTANCE_VALUE	= 350.0f;								//距離
	const D3DXVECTOR2	SELECT_POS		= D3DXVECTOR2(250.0f, 500.0f);			//位置
	const D3DXVECTOR2	SELECT_SIZE		= D3DXVECTOR2(150.0f, 150.0f);			//サイズ
	const D3DXCOLOR		SELECT_COL		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);	//選択されている時の色
	const int			MAX_COLCOUNT = 50;

	const float			ALPHA_VALUE = 0.007f;
}

CLight *CTitle::m_pLight = nullptr;
CField *CTitle::m_pField = nullptr;

Ccamera *CTitle::m_pCamera = nullptr;
CFog *CTitle::m_pFog = nullptr;

C2DSelect *CTitle::m_pSelect = nullptr;

//<====================================
//タイトルのコンストラクタ
//<====================================
CTitle::CTitle()
{
	m_rTitleCol = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
	m_sState = STATE::STATE_TITLE;
}
//<====================================
//タイトルのデストラクタ
//<====================================
CTitle::~CTitle()
{

}
//<====================================
//タイトルの初期化処理
//<====================================
HRESULT CTitle::Init(void)
{
	CManager::GetSound()->PlaySound(CSound::LABEL_BGM_TITLE);
	//<******************************************
	//ライトの生成
	//<******************************************
	m_pCamera = Ccamera::Create();
	//ライト生成
	m_pLight = CLight::Create(CLight::MODE::MODE_DIRECTIONAL);

	//地面生成
	CField::ReadCreate(&m_pField);
	m_pField->SetDrawfalse();

	//フォグ生成
	m_pFog = CFog::Create(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), D3DFOGMODE::D3DFOG_LINEAR, CFog::TYPE::TYPE_PIXEL, 0.001f);

	//2D文字を生成
	m_ap2DChar[0] = C2DChar::Create(D3DXVECTOR2(625.0f, 150.0f), D3DXVECTOR2(350.0f, 100.0f), C2DChar::CHAR_TYPE_TITLE);
	m_ap2DChar[0]->SetColor(m_rTitleCol);

	m_pSelect = C2DSelect::Create(SELECT_POS, SELECT_MAX);
	m_pSelect->SetUpdatefalse();

	//テクスチャの初期化
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); ++nCnt)
	{
		//テクスチャネームを設定する
		m_pSelect->SetTexName(m_acFilename[nCnt], nCnt);
	}

	return S_OK;
}
//<====================================
//タイトルの終了処理
//<====================================
void CTitle::Uninit(void)
{
	//フォントの数分繰り返す
	for (int nCnt = 0; nCnt < C2DChar::GetNum(); ++nCnt)
	{
		if (m_ap2DChar[nCnt] )
		{
			m_ap2DChar[nCnt]->Uninit();
			m_ap2DChar[nCnt] = nullptr;
		}
	}
	//もしメモリ確保がされていたら
	if (m_pCamera )
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//<******************************************
	//ライトの破棄
	//<******************************************
	//もしメモリ確保がされていたら
	if (m_pLight )
	{
		//メモリの解放を行う
		delete m_pLight;
		m_pLight = nullptr;
	}
	//<******************************************
	//フォグの破棄
	//<******************************************
	if (m_pFog )
	{
		m_pFog->Uninit();
		m_pFog = nullptr;
	}
	//<******************************************
	//ライトの破棄
	//<******************************************
	//もしメモリ確保がされていたら
	if (m_pField )
	{
		//メモリの解放を行う
		m_pField->Uninit();
		m_pField = nullptr;
	}
	//<******************************************
	//ライトの破棄
	//<******************************************
	//もしメモリ確保がされていたら
	if (m_pSelect)
	{
		//メモリの解放を行う
		m_pSelect->Uninit();
		m_pSelect = nullptr;
	}

	Release();
}
//<====================================
//タイトルの更新処理
//<====================================
void CTitle::Update(void)
{
	SetAppear();

	//フェード状態が何もしていない状態だったら
	if (m_sState == STATE::STATE_APPEARED&&
		CManager::GetFade()->GetType() == CFade::TYPE_FADE_NONE)
	{
		m_pCamera->Update();
		//<========================================================
		//操作タイプ変更処理
		//<========================================================
		//SPACEキーが押されたら
		if (CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0) && m_pSelect->GetSelect() == SELECT::SELECT_START)
		{
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
			CManager::SetFade(CScene::MODE::MODE_GAME);
		}
		else if (CManager::GetKeyboard()->bGetTrigger(DIK_RETURN) && m_pSelect->GetSelect() == SELECT::SELECT_START)
		{
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
			CManager::SetFade(CScene::MODE::MODE_GAME);
		}
		//<========================================================
		//操作タイプ変更処理
		//<========================================================
		//SPACEキーが押されたら
		if (CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0) && m_pSelect->GetSelect() == SELECT::SELECT_OPTION)
		{
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
			CManager::SetFade(CScene::MODE::MODE_OPTION);
		}
		else if (CManager::GetKeyboard()->bGetTrigger(DIK_RETURN) && m_pSelect->GetSelect() == SELECT::SELECT_OPTION)
		{
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
			CManager::SetFade(CScene::MODE::MODE_OPTION);
		}
		//<========================================================
		//操作タイプ変更処理
		//<========================================================
		//SPACEキーが押されたら
		if (CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0) && m_pSelect->GetSelect() == SELECT::SELECT_EXIT)
		{
			PostQuitMessage(0);
		}
		else if (CManager::GetKeyboard()->bGetTrigger(DIK_RETURN) && m_pSelect->GetSelect() == SELECT::SELECT_EXIT)
		{
			PostQuitMessage(0);
		}
	}
}
//<====================================
//タイトルの描画処理
//<====================================
void CTitle::Draw(void)
{
	m_pCamera->SetCamera();
}
//<====================================
//タイトルの描画処理
//<====================================
void CTitle::SetAppear(void)
{
	if (CManager::GetFade()->GetType() == CFade::TYPE_FADE_NONE)
	{
		if (CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0)
			|| CManager::GetKeyboard()->bGetTrigger(DIK_RETURN))
		{
			m_rTitleCol.a = 1.0f;
		}

		//タイトルステート
		if (m_sState == STATE::STATE_TITLE)
		{
			m_rTitleCol.a += ALPHA_VALUE;

			//透明度の上限に達していたら
			if (m_ap2DChar[0]->GetColor().a >= 1.0f)
			{
				m_sState = STATE_APPEARED;

				//<***************************************************
				//見えていない部分のオブジェクトの表示をする
				//フォントの数分繰り返す
				m_pField->SetDrawtrue();
				m_pSelect->SetUpdatetrue();
				//<***************************************************

			}

			m_ap2DChar[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_rTitleCol.a));
		}
	}
}