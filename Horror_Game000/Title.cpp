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
C2DChar *CTitle::m_ap2DChar[INT_VALUE::MAX_SIZE] = {};								//2D文字

LPDIRECT3DTEXTURE9	CTitle::m_apTexture[INT_VALUE::MAX_TEX] = {};	//テクスチャポインタ
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
	const int MAX_COLCOUNT = 50;
}

CLight *CTitle::m_pLight = nullptr;
CField *CTitle::m_pField = nullptr;

Ccamera *CTitle::m_pCamera = nullptr;
CFog *CTitle::m_pFog = nullptr;

C3DEnemy *CTitle::m_ap3DEnemy[INT_VALUE::MAX_SIZE] = {};

C2DSelect *CTitle::m_pSelect = nullptr;

//<====================================
//タイトルのコンストラクタ
//<====================================
CTitle::CTitle()
{

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

	//フォグ生成
	m_pFog = CFog::Create(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), D3DFOGMODE::D3DFOG_LINEAR, CFog::TYPE::TYPE_PIXEL,0.001f);

	C3DEnemy::ReadCreate(m_ap3DEnemy);

	//2D文字を生成
	m_ap2DChar[0] = C2DChar::Create(D3DXVECTOR2(625.0f, 150.0f), D3DXVECTOR2(350.0f, 100.0f), C2DChar::CHAR_TYPE_TITLE);

	m_pSelect = C2DSelect::Create(SELECT_POS, SELECT_MAX);

	//テクスチャの初期化
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); nCnt++)
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
	for (int nCnt = 0; nCnt < C2DChar::GetNum(); nCnt++)
	{
		if (m_ap2DChar[nCnt] != nullptr)
		{
			m_ap2DChar[nCnt]->Uninit();
			m_ap2DChar[nCnt] = nullptr;
		}
	}
	//もしメモリ確保がされていたら
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//<******************************************
	//ライトの破棄
	//<******************************************
	//もしメモリ確保がされていたら
	if (m_pLight != nullptr)
	{
		//メモリの解放を行う
		delete m_pLight;
		m_pLight = nullptr;
	}
	//<******************************************
	//フォグの破棄
	//<******************************************
	if (m_pFog != nullptr)
	{
		m_pFog->Uninit();
		m_pFog = nullptr;
	}
	//<******************************************
	//ライトの破棄
	//<******************************************
	//もしメモリ確保がされていたら
	if (m_pField != nullptr)
	{
		//メモリの解放を行う
		m_pField->Uninit();
		m_pField = nullptr;
	}
	//<******************************************
	//ライトの破棄
	//<******************************************
	//もしメモリ確保がされていたら
	if (m_pSelect != nullptr)
	{
		//メモリの解放を行う
		m_pSelect->Uninit();
		m_pSelect = nullptr;
	}

	//フォントの数分繰り返す
	for (int nCnt = 0; nCnt < C3DEnemy::GetNum(); nCnt++)
	{
		if (m_ap3DEnemy[nCnt] != nullptr)
		{
			m_ap3DEnemy[nCnt]->Uninit();
			m_ap3DEnemy[nCnt] = nullptr;
		}
	}

	Release();
}
//<====================================
//タイトルの更新処理
//<====================================
void CTitle::Update(void)
{
	m_pCamera->Update();

	//フェード状態が何もしていない状態だったら
	if (CManager::GetFade()->GetType() == CFade::TYPE_FADE_NONE)
	{
		//<========================================================
		//操作タイプ変更処理
		//<========================================================
		//SPACEキーが押されたら
		if (CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0) && m_pSelect->GetSelect() == SELECT::SELECT_START)
		{
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
			CManager::SetFade(CScene::MODE::MODE_GAME);
		}
		else if (CManager::GetKeyboard()->bGetTrigger(DIK_RETURN) == true && m_pSelect->GetSelect() == SELECT::SELECT_START)
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
		else if (CManager::GetKeyboard()->bGetTrigger(DIK_RETURN) == true && m_pSelect->GetSelect() == SELECT::SELECT_OPTION)
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
		else if (CManager::GetKeyboard()->bGetTrigger(DIK_RETURN) == true && m_pSelect->GetSelect() == SELECT::SELECT_EXIT)
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