//<===========================================
//リザルト画面の処理(Result.cpp)
//
//Author:kazuki watanabe
//<===========================================
#include "Result.h"
#include "input.h"
#include "manager.h"
#include "Texture.h"
#include "fade.h"
#include "Sound.h"

LPDIRECT3DTEXTURE9	CResult::m_apTexture[CScene::TYPE_RESULT_MAX] = {};
const char*			CResult::m_acFilename[CScene::TYPE_RESULT_MAX]= 
{
	"data\\TEXTURE\\GameClear000.png",
	"data\\TEXTURE\\GameOver000.png",
};
const char*			CResult::m_EnemyName = "data\\MODEL\\Monster002.x";
namespace
{
	const D3DXVECTOR2 YES_POS = D3DXVECTOR2(500.0f, 750.0f);
	const D3DXVECTOR2 CHAR_POS = D3DXVECTOR2(625.0f, 150.0f);
	const D3DXVECTOR2 CHAR_SIZE = D3DXVECTOR2(350.0f, 150.0f);
	const float DISTANCE_Y = 235.0f;
	const float DISTANCE_X = 200.0f;

}
CLight *CResult::m_pLight = nullptr;
CField *CResult::m_pField = nullptr;

Ccamera *CResult::m_pCamera = nullptr;
CXObject *CResult::m_apXObject[XTYPE_MAX] = {};
CObject3D *CResult::m_pObject3D = nullptr;
C2DContinue *CResult::m_pContinue = nullptr;
CFog *CResult::m_pFog = nullptr;
CFont *CResult::m_pFont = nullptr;

//<===========================================
//リザルト画面のコンストラクタ
//<===========================================
CResult::CResult()
{
	m_pObject2D = nullptr;
	m_eState = STATE::STATE_MAX;
}
//<===========================================
//リザルト画面のデストラクタ
//<===========================================
CResult::~CResult()
{

}
//<===========================================
//リザルト画面の初期化処理
//<===========================================
HRESULT CResult::Init(void)
{
	LPDIRECT3DTEXTURE9 pTexture = nullptr;	//テクスチャへのポインタ

	m_eState = STATE::STATE_NONE;

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

	m_pCamera = Ccamera::Create();

	//ライト生成
	m_pLight = CLight::Create(CLight::MODE::MODE_DIRECTIONAL);

	//地面生成
	CField::ReadCreate(&m_pField);

	//失敗していたら
	if (CScene::GetRes() == CScene::TYPE_RESULT_FAILED)
	{
		//ゲームオーバー音楽を流す
		CManager::GetSound()->PlaySound(CSound::LABEL_BGM_GAMEOVER);

		//フォグ生成
		m_pFog = CFog::Create(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), D3DFOGMODE::D3DFOG_LINEAR, CFog::TYPE::TYPE_PIXEL, 0.001f);

		m_apXObject[0] = CXObject::Create(INIT_VECTOR, D3DXVECTOR3(1.56f, 0.0f, 0.0f), "data\\MODEL\\Enemy001.x");

		m_apXObject[1] = CXObject::Create(D3DXVECTOR3(m_apXObject[0]->GetPosition().x,
			m_apXObject[0]->GetPosition().y,
			m_apXObject[0]->GetPosition().z + 250.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_EnemyName);

		CManager::GetTex()->Regist("data\\TEXTURE\\Blood000.png", pTexture);

		m_pObject3D = CObject3D::Create(D3DXVECTOR3(m_apXObject[0]->GetPosition().x,
			m_apXObject[0]->GetPosition().y + 1.0f,
			m_apXObject[0]->GetPosition().z),
			D3DXVECTOR3(50.0f, 50.0f, 50.0f),
			INIT_VECTOR, INIT_COL, CObject3D::TYPE::TYPE_PLANE, pTexture);
	}
	//成功していたら
	else if (CScene::GetRes() == CScene::TYPE_RESULT_SUCCEEDED)
	{
		//ゲームクリア音楽を流す
		CManager::GetSound()->PlaySound(CSound::LABEL_BGM_CLEAR);

		m_apXObject[0] = CXObject::Create(INIT_VECTOR, D3DXVECTOR3(0.0f, 1.56f, 0.0f), "data\\MODEL\\Enemy001.x");

		m_apXObject[1] = CXObject::Create(D3DXVECTOR3(m_apXObject[0]->GetPosition().x, 
			m_apXObject[0]->GetPosition().y,
			m_apXObject[0]->GetPosition().z + 250.0f), 
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\House.x");
	}

	m_pObject2D = CObject2D::Create(CHAR_POS, CHAR_SIZE, INIT_COL, m_apTexture[CScene::GetRes()]);
	m_pFont = CFont::Create({ 85,500,SCREEN_WIDTH,SCREEN_HEIGHT },60, 100,
		FW_DONTCARE, OEM_CHARSET, D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f), CFont::TYPE::TYPE_BLINK, "PRESS B TO CONTINUE");
	m_pContinue = C2DContinue::Create();

	return S_OK;
}
//<===========================================
//リザルト画面の終了処理
//<===========================================
void CResult::Uninit(void)
{
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
	//ライトの破棄
	//<******************************************
	//もしメモリ確保がされていたら
	if (m_pFog != nullptr)
	{
		//メモリの解放を行う
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
	for (int nCnt = 0; nCnt < XTYPE_MAX; nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_apXObject[nCnt] != nullptr)
		{
			//メモリの解放を行う
			m_apXObject[nCnt]->Uninit();
			m_apXObject[nCnt] = nullptr;
		}
	}
	//もしメモリ確保がされていたら
	if (m_pObject3D != nullptr)
	{
		//メモリの解放を行う
		m_pObject3D->Uninit();
		m_pObject3D = nullptr;
	}
	//もしメモリ確保がされていたら
	if (m_pFont != nullptr)
	{
		//メモリの解放を行う
		m_pFont->Uninit();
		m_pFont = nullptr;
	}
	//もしメモリ確保がされていたら
	if (m_pObject2D != nullptr)
	{
		//メモリの解放を行う
		m_pObject2D->Uninit();
		m_pObject2D = nullptr;
	}

	//もしメモリ確保がされていたら
	if (m_pContinue != nullptr)
	{
		//メモリの解放を行う
		m_pContinue->Uninit();
		m_pContinue = nullptr;
	}
	Release();
}
//<===========================================
//リザルト画面の更新処理
//<===========================================
void CResult::Update(void)
{
	m_pCamera->Update();

	//生成していなかったら
	if (m_pObject3D != nullptr)
	{
		m_pObject3D->SetVtx();
	}

	m_pObject2D->SetVtx();

	//
	if (m_eState == STATE_NONE)
	{
		m_pContinue->SetUpdatefalse();
		//<========================================================
		//
		//<========================================================
		if (CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0)||
			CManager::GetKeyboard()->bGetTrigger(DIK_RETURN))
		{
			m_eState = STATE_SELECT;
		}
	}
	//
	else if (m_eState == STATE_SELECT)
	{
		m_pContinue->SetUpdatetrue();

		//フェード状態が何もしていない状態だったら
		if (CManager::GetFade()->GetType() == CFade::TYPE_FADE_NONE)
		{
			//<========================================================
			//
			//<========================================================
			if (CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0)
				&& m_pContinue->GetSelect() == C2DContinue::SELECT_YES)
			{
				//
				CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
				CManager::SetFade(CScene::MODE::MODE_GAME);
			}
			//
			else if (CManager::GetKeyboard()->bGetTrigger(DIK_RETURN) == true
				&& m_pContinue->GetSelect() == C2DContinue::SELECT_YES)
			{
				//
				CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
				CManager::SetFade(CScene::MODE::MODE_GAME);
			}
			//<========================================================
			//
			//<========================================================
			if (CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0)
				&& m_pContinue->GetSelect() == C2DContinue::SELECT_NO)
			{
				//
				CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
				CManager::SetFade(CScene::MODE::MODE_TITLE);
			}
			//
			else if (CManager::GetKeyboard()->bGetTrigger(DIK_RETURN) == true
				&& m_pContinue->GetSelect() == C2DContinue::SELECT_NO)
			{
				//
				CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
				CManager::SetFade(CScene::MODE::MODE_TITLE);
			}
		}

	}
}