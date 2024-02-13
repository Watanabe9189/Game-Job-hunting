//<==============================================
//マネージャ処理(manager.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "manager.h"

#include "Title.h"
#include "Tutorial.h"
#include "game.h"
#include "Result.h"
#include "Option.h"

#include "fade.h"

//<**********************************************
//2D関連のインクルード
//<**********************************************
#include "object2D.h"

//<*********************************
//3D関連のインクルード
//<*********************************
#include "Object3D.h"
#include "Light.h"
#include "Camera.h"
#include "BilB.h"
#include "XObject.h"
#include "Pause.h"

//<*********************************************
// 静的メンバ変数宣言
//<*********************************************
CRenderer *CManager::m_pRenderer = nullptr;
//入力関連
CKeyboard *CManager::m_pKeyboard = nullptr;
CJoyPad *CManager::m_pJoyPad = nullptr;
CMouse *CManager::m_pMouse = nullptr;
//2D関連
CBG *CManager::m_pBg = nullptr;
//その他関連
CTexture *CManager::m_pTexture = nullptr;
CDebug *CManager::m_pDebug = nullptr;
CSound *CManager::m_pSound = nullptr;

CFade *CManager::m_pFade = nullptr;
CPause *CManager::m_pPause = nullptr;

//画面遷移関連
#ifdef _DEBUG
CScene::MODE CScene::m_Mode = CScene::MODE::MODE_TITLE;
#else 
CScene::MODE CScene::m_Mode = CScene::MODE::MODE_TITLE;
#endif

//<*****************************************************************************
//シーン関連
//<*****************************************************************************
CTitle *CScene::m_pTitle = nullptr;
CTutorial *CScene::m_pTutorial = nullptr;
CGame *CScene::m_pGame = nullptr;
CResult *CScene::m_pResult = nullptr;
COption *CScene::m_pOption = nullptr;
int CScene::m_nCount = INITIAL_INT;
CScene::TYPE_RESULT CScene::m_eTypeRes = CScene::TYPE_RESULT::TYPE_RESULT_FAILED;

//bool型の静的メンバ変数宣言
bool CManager::m_bPause = false;

HINSTANCE CManager::m_hInstance = nullptr;

//シーン関連
CScene *CManager::m_pScene = nullptr;									
CScene::MODE CManager::m_NowMode = CScene::MODE::MODE_MAX;						//現在のモード

//<==================================================================================
//マネージャのコンストラクタ
//<==================================================================================
CManager::CManager()
{
	
}

//<==================================================================================
//マネージャのデストラクタ
//<==================================================================================
CManager::~CManager()
{

}
//<==================================================================================
//マネージャの初期化処理
//<==================================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	m_hInstance = hInstance;

	//メモリ確保
	m_pRenderer = new CRenderer;

	//どちらも達成されていたら
	assert(m_pRenderer != nullptr && SUCCEEDED(m_pRenderer->Init(hWnd, TRUE)));

	//メモリ確保
	m_pDebug = new CDebug;

	//どちらも達成されていたら
	assert(m_pDebug != nullptr && SUCCEEDED(m_pDebug->Init()));

	//メモリ確保
	m_pSound = new CSound;

	//どちらも達成されていたら
	assert(m_pSound != nullptr && SUCCEEDED(m_pSound->Init(hWnd)));

	//入力処理関連の初期化
	InitInput(hInstance, hWnd);

	//メモリ確保
	m_pTexture = new CTexture;

	//どちらも達成されていたら
	assert(m_pTexture != nullptr && SUCCEEDED(m_pTexture->Load()));

#if 1

	//
	m_pScene = CScene::Create(GetMode());

	//生成する
	m_pFade = CFade::Create();

	m_pPause = new CPause;

	m_pPause->Init();

	//カーソルを表示させなくする
	ShowCursor(FALSE);

#endif

	return S_OK;
}
//<==================================================================================
//マネージャの終了処理
//<==================================================================================
void CManager::Uninit(void)
{
	//全てのオブジェクトの破棄
	CObject::ReleaseAll();

	m_pSound->StopSound();

	//メモリ確保がされていたら
	if (m_pRenderer != nullptr)
	{
		//メモリの解放を行う
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	//もしメモリ確保がされていたら
	if (m_pTexture != nullptr)
	{
		m_pTexture->UnloadAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	//もしメモリ確保がされていたら
	if (m_pDebug != nullptr)
	{
		m_pDebug->Uninit();
		delete m_pDebug;
		m_pDebug = nullptr;
	}
	//もしメモリ確保がされていたら
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}
	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = nullptr;
	}
	
	//入力機器の終了処理
	UninitInput();

}
//<==================================================================================
//マネージャの更新処理
//<==================================================================================
void CManager::Update(void)
{
	UpdateInput();

	m_pDebug->Update();

	////Pキーが押されたら
	//if (m_pKeyboard->bGetTrigger(DIK_0) == true)
	//{
	//	SetD_SPEED();
	//}
	////Pキーが押されたら
	//if (m_pKeyboard->bGetTrigger(DIK_9) == true)
	//{
	//	SetS_SPEED();
	//}

	//もしポーズされていなければ
	if (!m_bPause&&m_pScene != nullptr)
	{
		if (m_pFade != nullptr&&m_pFade->GetType() != CFade::TYPE_FADE_NONE)
		{
			m_pFade->Update();
		}

		//レンダラーの更新処理
		m_pRenderer->Update();
	}
	//ゲーム画面の場合のみでしか反応しないようにする
	if (m_pScene->GetMode() == CScene::MODE::MODE_GAME)
	{
		//Pキーが押されたら
		if (m_pKeyboard->bGetTrigger(DIK_P) == true)
		{
			//三項演算子でポーズ状態を切り替える
			m_bPause == false ? m_bPause = true : m_bPause = false;
		}
		/*m_pPause->Update();*/
	}
	if (m_pKeyboard->bGetTrigger(DIK_Y) == true)
	{
		m_pRenderer->ScreenShot("data\\TEST.png");
	}
}
//<==================================================================================
//マネージャの描画処理
//<==================================================================================
void CManager::Draw(void)
{
	
	if (m_pScene != nullptr)
	{
		//レンダラーの描画処理
		m_pRenderer->Draw();
	}

}
//<================================================
//フェード設定
//<================================================
void CManager::SetFade(const CScene::MODE modeNext)
{
	//もし中身があれば
	if (m_pFade != nullptr)
	{
		//フェードしていない状態の時のみ通るようにする
		if (m_pFade->GetType() == CFade::TYPE_FADE_NONE)
		{
			//中身を破棄する
			m_pFade->Uninit();
			delete m_pFade;
			m_pFade = nullptr;

			//生成する
			m_pFade = CFade::Create();

			//中身があることを確認
			assert(m_pFade != nullptr);

			//フェードを開始する
			m_pFade->SetFade(modeNext);
		}
	}
}
//<==================================================================================
//入力処理関連の初期化
//<==================================================================================
HRESULT CManager::InitInput(HINSTANCE hInstance, HWND hWnd)
{
	//もし中身が何もなければ
	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CKeyboard;

		//メモリ確保が成功したかの確認をする
		assert(m_pKeyboard != nullptr);

		//初期化処理に失敗したら
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}
	//もし中身が何もなければ
	if (m_pJoyPad == nullptr)
	{
		m_pJoyPad = new CJoyPad;

		//メモリ確保が成功したかの確認をする
		assert(m_pJoyPad != nullptr);

		//初期化処理に失敗したら
		if (FAILED(m_pJoyPad->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//もし中身が何もなければ
	if (m_pMouse == nullptr)
	{
		m_pMouse = new CMouse;

		//メモリ確保が成功したかの確認をする
		assert(m_pMouse != nullptr);

		//初期化処理に失敗したら
		if (FAILED(m_pMouse->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}
//<==================================================================================
//入力処理関連の終了
//<==================================================================================
void CManager::UninitInput(void)
{
	//メモリ確保がされていたら
	if (m_pKeyboard != nullptr)
	{
		//メモリの解放を行う
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	//メモリ確保がされていたら
	if (m_pJoyPad != nullptr)
	{
		//メモリの解放を行う
		m_pJoyPad->Uninit();
		delete m_pJoyPad;
		m_pJoyPad = nullptr;
	}

	//メモリ確保がされていたら
	if (m_pMouse != nullptr)
	{
		//メモリの解放を行う
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}
}
//<==================================================================================
//入力処理関連の更新
//<==================================================================================
void CManager::UpdateInput(void)
{
	m_pKeyboard->Update();

	m_pJoyPad->Update();

	m_pMouse->Update();
}
//<==================================================================================
//モードの設定
//<==================================================================================
void CManager::SetMode(CScene::MODE Mode)
{
	m_pSound->StopSound();

	//現在のシーンの破棄をする
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		m_pScene = nullptr;
	}

	//破棄されたかのチェックをする
	assert(m_pScene == nullptr);

	//現在のシーンの破棄が成功したら
	if (m_pScene == nullptr)
	{
		//生成を行う
		m_pScene = CScene::Create(Mode);
	}
			
	//破棄されたかのチェックをする
	assert(m_pScene != nullptr);
}
//<==================================================================================
//
//<==================================================================================
CScene::CScene()
{
	//値のクリア
	m_pTitle = nullptr;
	m_pTutorial = nullptr;
	m_pGame = nullptr;
	m_pResult = nullptr;
	m_pOption = nullptr;
}
//<==================================================================================
//
//<==================================================================================
CScene::~CScene()
{
	
}
//<==================================================================================
//
//<==================================================================================
CScene *CScene::Create(MODE Mode)
{
	//インスタンス生成用のオブジェクト(まず自分自身のポインタを返す)
	CScene *pScene = new CScene;

	//メモリ確保に入る前にモードを設定しておく
	pScene->SetMode(Mode);

	//モードによって処理を分ける
	switch (Mode)
	{
		//タイトルだった場合
	case MODE::MODE_TITLE:

		//中身があったら
		if (m_pTitle != nullptr)
		{
			//2週目以降に入った際の無効変数へのアクセスを防ぐ
			delete m_pTitle;
			m_pTitle = nullptr;
		}

		//nullptrだったら
		if (m_pTitle == nullptr)
		{
			//代入用のメモリ確保をする
			m_pTitle = new CTitle;

			//チェック
			assert(m_pTitle != nullptr);

			//初期化処理
			m_pTitle->Init();
		}

		//今の生成用のオブジェクトに代入する
		pScene = m_pTitle;

		break;

		//オプションだった場合
	case MODE::MODE_OPTION:

		//中身があったら
		if (m_pOption != nullptr)
		{
			//2週目以降に入った際の無効変数へのアクセスを防ぐ
			delete m_pOption;
			m_pOption = nullptr;
		}

		//nullptrだったら
		if (m_pOption == nullptr)
		{
			//代入用のメモリ確保をする
			m_pOption = new COption;

			//チェック
			assert(m_pOption != nullptr);

			//初期化処理
			m_pOption->Init();
		}

		//今の生成用のオブジェクトに代入する
		pScene = m_pOption;

		break;

		//チュートリアルだった場合
	case MODE::MODE_TUTORIAL:

		//中身があったら
		if (m_pTutorial != nullptr)
		{
			//2週目以降に入った際の無効変数へのアクセスを防ぐ
			delete m_pTutorial;
			m_pTutorial = nullptr;
		}

		//nullptrだったら
		if (m_pTutorial == nullptr)
		{
			//代入用のメモリ確保をする
			m_pTutorial = new CTutorial;
		}

		//中身があったら
		if (m_pTutorial != nullptr)
		{
			//今の生成用のオブジェクトに代入する
			pScene = m_pTutorial;

			//初期化処理
			pScene->Init();

			return pScene;
		}

		break;

		//ゲームだった場合
	case MODE::MODE_GAME:

		//中身があったら
		if (m_pGame != nullptr)
		{
			//2週目以降に入った際の無効変数へのアクセスを防ぐ
			delete m_pGame;
			m_pGame = nullptr;
		}

		//nullptrだったら
		if (m_pGame == nullptr)
		{
			//代入用のメモリ確保をする
			m_pGame = new CGame;

			//チェック
			assert(m_pGame != nullptr);

			//初期化
			m_pGame->Init();
		}

		//今の生成用のオブジェクトに代入する
		pScene = m_pGame;

		break;

		//リザルトだった場合
	case MODE::MODE_RESULT:

		m_nCount++;

		//中身があったら
		if (m_pResult != nullptr)
		{
			//2週目以降に入った際の無効変数へのアクセスを防ぐ
			delete m_pResult;
			m_pResult = nullptr;
		}

		//nullptrだったら
		if (m_pResult == nullptr)
		{
			//代入用のメモリ確保をする
			m_pResult = new CResult;

			//チェック
			assert(m_pResult != nullptr);

			//初期化処理
			m_pResult->Init();
		}

		//今の生成用のオブジェクトに代入する
		pScene = m_pResult;

		break;
	}
			
	return pScene;
}
//<==================================================================================
//
//<==================================================================================
HRESULT CScene::Init(void)
{
	return S_OK;
}
//<==================================================================================
//
//<==================================================================================
void CScene::Uninit(void)
{
	
}
//<==================================================================================
//
//<==================================================================================
void CScene::Update(void)
{

}
//<==================================================================================
//
//<==================================================================================
void CScene::Draw(void)
{
	
}