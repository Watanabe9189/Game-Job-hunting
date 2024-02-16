//<===========================================
//ゲーム画面の処理(game.cpp)
//
//Author:kazuki watanabe
//<===========================================
#include "game.h"
#include "manager.h"
//<*****************************************
//その他関連
//<*****************************************
#include "Texture.h"
#include "DebugProc.h"
#include "input.h"
#include "fade.h"
#include "2DParticle.h"
#include "3DParticle.h"
#include "Sound.h"
#include "BillBIcon.h"
#include "Pause.h"
//<================================================
//静的メンバ変数宣言
//<================================================
int CGame::m_nWaitTime = INITIAL_INT;
//<*****************************************
//3D関連
//<*****************************************
CLight *CGame::m_pLight = nullptr;					//
C3DPlayer *CGame::m_p3DPlayer = nullptr;
CField *CGame::m_apField[INT_VALUE::MAX_SIZE] = {};
CFog *CGame::m_pFog = nullptr;
CBuilding *CGame::m_apBuilding[INT_VALUE::MAX_SIZE] = {};
C2DGauge *CGame::m_p2DGauge = nullptr;
C3DEnemy *CGame::m_ap3DEnemy[INT_VALUE::MAX_SIZE];
CItem *CGame::m_apItem[INT_VALUE::MAX_SIZE] = {};
C2DInfo *CGame::m_pInfo = nullptr;
Ccover *CGame::m_pCover = nullptr;
C2DChar *CGame::m_ap2DChar[CGame::CHAR2D::CHAR2D_MAX] = {};
CPlant *CGame::m_apPlant[INT_VALUE::MAX_SIZE] = {};
CLandMark *CGame::m_apLandMark[INT_VALUE::MAX_SIZE] = {};
CDestArrowX *CGame::m_pDestArrowX = nullptr;
Ccamera *CGame::m_pCamera = nullptr;

namespace
{
	const int NUM_BUILDING = 20;
	const int NUM_ITEM = 5;
	const int NUM_PLANT = 35;
	const D3DXVECTOR3 PLAYER_POS = D3DXVECTOR3(3750.0f, 0.0f, 3640.0f);
	const D3DXVECTOR2 GAUGE_POS = D3DXVECTOR2(720.0f,660.0f);
}

//<====================================
//ゲーム画面のコンストラクタ
//<====================================
CGame::CGame()
{
	
}
//<====================================
//ゲーム画面のデストラクタ
//<====================================
CGame::~CGame()
{

}
//<====================================
//ゲーム画面の初期化処理
//<====================================
HRESULT CGame::Init(void)
{
	m_sState = STATE_NONE;
	m_nWaitTime = INITIAL_INT;
	CManager::GetRenderer()->SetBoolPix(FALSE);
	CManager::GetSound()->PlaySound(CSound::LABEL_BGM_GAME);
	//<******************************************
	//ライトの生成
	//<******************************************
	m_pCamera = Ccamera::Create();

	//ライト生成
	m_pLight = CLight::Create(CLight::MODE::MODE_DIRECTIONAL);

	//プレイヤー生成
	m_p3DPlayer = C3DPlayer::Create(PLAYER_POS);

	//フォグ生成
	m_pFog = CFog::Create(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), D3DFOGMODE::D3DFOG_LINEAR, CFog::TYPE::TYPE_PIXEL,0.002f);

	//地面生成
	CField::ReadCreate(m_apField);

	//建物生成
	CBuilding::RandCreate(m_apBuilding, NUM_BUILDING);

	//敵生成
	C3DEnemy::RandCreate(m_ap3DEnemy);

	//アイテム生成
	CItem::RandCreate(m_apItem, NUM_ITEM);

	CPlant::RandCreate(m_apPlant, NUM_PLANT);

	CLandMark::FixedCreate(m_apLandMark);

	m_pDestArrowX = CDestArrowX::Create();

	//ゲージ生成
	m_p2DGauge = C2DGauge::Create(GAUGE_POS, m_p3DPlayer->GetStamina(), C2DGauge::VERTEX_X, C2DGauge::MODE_ONLY_USE);

	//情報生成
	m_pInfo = C2DInfo::Create(C2DInfo::Class::CLASS_NUMBER);

	m_ap2DChar[CHAR2D_HIDE] = C2DChar::Create(D3DXVECTOR2(1150.0f, 675.0f),
		D3DXVECTOR2(125.0f, 125.0f), C2DChar::CHAR_TYPE::CHAR_TYPE_HIDEINFO, C2DChar::MOVE_FROM_NONE, false);

	m_ap2DChar[CHAR2D_PICKUP] = C2DChar::Create(D3DXVECTOR2(1150.0f, 
		m_ap2DChar[CHAR2D_HIDE]->GetPosition().y), D3DXVECTOR2(125.0f, 125.0f),
		C2DChar::CHAR_TYPE::CHAR_TYPE_PICKUP_INFO, C2DChar::MOVE_FROM_NONE, false);

	m_ap2DChar[CHAR2D_COMEOUT] = C2DChar::Create(D3DXVECTOR2(1150.0f, 675.0f),
		D3DXVECTOR2(125.0f, 125.0f), C2DChar::CHAR_TYPE::CHAR_TYPE_COMEOUT_INFO, C2DChar::MOVE_FROM_NONE, false);

	return S_OK;
}
//<====================================
//ゲーム画面の終了処理
//<====================================
void CGame::Uninit(void)
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
	//プレイヤーの破棄
	//<******************************************
	if (m_p3DPlayer != nullptr)
	{
		m_p3DPlayer->Uninit();
		m_p3DPlayer = nullptr;
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
	//ゲージの破棄
	//<******************************************
	if (m_p2DGauge != nullptr)
	{
		m_p2DGauge->Uninit();
		m_p2DGauge = nullptr;
	}
	//<******************************************
	//インフォの破棄
	//<******************************************
	if (m_pInfo != nullptr)
	{
		m_pInfo->Uninit();
		m_pInfo = nullptr;
	}
	//<******************************************
	//カバーの破棄
	//<******************************************
	if (m_pCover != nullptr)
	{
		m_pCover->Uninit();
		m_pCover = nullptr;
	}
	//<******************************************
	//カバーの破棄
	//<******************************************
	if (m_pDestArrowX != nullptr)
	{
		m_pDestArrowX->Uninit();
		m_pDestArrowX = nullptr;
	}
	
	//<******************************************
	//壁の破棄
	//<******************************************
	for (int nCnt = 0; nCnt < CField::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_apField[nCnt] != nullptr)
		{
			//メモリの解放を行わず、終了処理をする
			m_apField[nCnt]->Uninit();
			m_apField[nCnt] = nullptr;
		}
	}
	//<******************************************
	//壁の破棄
	//<******************************************
	for (int nCnt = 0; nCnt < C3DEnemy::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_ap3DEnemy[nCnt] != nullptr)
		{
			//メモリの解放を行わず、終了処理をする
			m_ap3DEnemy[nCnt]->Uninit();
			m_ap3DEnemy[nCnt] = nullptr;
		}
	}
	//<******************************************
	//壁の破棄
	//<******************************************
	for (int nCnt = 0; nCnt < CBuilding::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_apBuilding[nCnt] != nullptr)
		{
			//メモリの解放を行わず、終了処理をする
			m_apBuilding[nCnt]->Uninit();
			m_apBuilding[nCnt] = nullptr;
		}
	}
	//<******************************************
	//壁の破棄
	//<******************************************
	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_apItem[nCnt] != nullptr)
		{
			//メモリの解放を行わず、終了処理をする
			m_apItem[nCnt]->Uninit();
			m_apItem[nCnt] = nullptr;
		}
	}
	//<******************************************
	//壁の破棄
	//<******************************************
	for (int nCnt = 0; nCnt < C2DChar::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_ap2DChar[nCnt] != nullptr)
		{
			//メモリの解放を行わず、終了処理をする
			m_ap2DChar[nCnt]->Uninit();
			m_ap2DChar[nCnt] = nullptr;
		}
	}
	//<******************************************
	//壁の破棄
	//<******************************************
	for (int nCnt = 0; nCnt < CPlant::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_apPlant[nCnt] != nullptr)
		{
			//メモリの解放を行わず、終了処理をする
			m_apPlant[nCnt]->Uninit();
			m_apPlant[nCnt] = nullptr;
		}
	}
	//<******************************************
	//壁の破棄
	//<******************************************
	for (int nCnt = 0; nCnt < CLandMark::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_apLandMark[nCnt] != nullptr)
		{
			//メモリの解放を行わず、終了処理をする
			m_apLandMark[nCnt]->Uninit();
			m_apLandMark[nCnt] = nullptr;
		}
	}
	Release();
}
//<====================================
//ゲーム画面の更新処理
//<====================================
void CGame::Update(void)
{
#define MAX_WAIT	(100)	//待機時間の最大値

	m_pLight->Update();
	m_pCamera->Update();

	//死亡状態だったら
	if (m_p3DPlayer->GetState() == C3DPlayer::STATE::STATE_DEATH)
	{
		//中身なしだったら
		if (m_pCover == nullptr)
		{
			m_pCover = Ccover::Create(Ccover::TYPE::TYPE_BLOOD_COV);
		}

		CScene::SetResult(TYPE_RESULT_FAILED);

		//終わっている状態にする
		m_sState = STATE_END;

		//待機時間の最大値を超えていたら
		if (m_nWaitTime >= MAX_WAIT)
		{
			//リザルト画面を失敗モードにする
			CManager::SetFade(CScene::MODE::MODE_RESULT);
			m_nWaitTime = 0;
		}
		//いなければ
		else
		{
			//加算していく
			m_nWaitTime++;
		}

	}
	//アイテムを拾い終えていたら
	if (CItem::GetNumCollect() == CItem::GetMax())
	{
		//終了状態じゃない場合
		if (m_sState != STATE_END)
		{
			//その他の音楽を止め、効果音を再生する
			CManager::GetSound()->StopSound();
			CManager::GetSound()->PlaySound(CSound::LABEL::LABEL_SE_ESCAPED);
		}
		CScene::SetResult(TYPE_RESULT::TYPE_RESULT_SUCCEEDED);

		//中身なしだったら
		if (m_pCover == nullptr)
		{
			m_pCover = Ccover::Create(Ccover::TYPE::TYPE_SAFE_COV);
		}

		//終わっている状態にする
		m_sState = STATE_END;

		//待機時間の最大値を超えていたら
		if (m_nWaitTime >= MAX_WAIT)
		{
			//リザルト画面を成功モードにする
			CManager::SetFade(CScene::MODE::MODE_RESULT);
			m_nWaitTime = 0;
		}
		//いなければ
		else
		{
			//加算していく
			m_nWaitTime++;
		}
	}

	//アイテムの数分回す
	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		//アイテムを取得していなければ
		if (!m_apItem[nCnt]->bGet())
		{
			//近づいていたら
			if (m_apItem[nCnt]->GetAppro())
			{
				//表示をさせ、処理から抜ける
				m_ap2DChar[CHAR2D_PICKUP]->SetDrawtrue();
				break;
			}
			//離れていたら
			else if (!m_apItem[nCnt]->GetAppro())
			{
				//表示をさせない
				m_ap2DChar[CHAR2D_PICKUP]->SetDrawfalse();
			}
		}
	}
	
	if (m_ap2DChar[CHAR2D_HIDE]->GetbDraw()|| m_ap2DChar[CHAR2D_COMEOUT]->GetbDraw())
	{
		m_ap2DChar[CHAR2D::CHAR2D_PICKUP]->SetPosition(D3DXVECTOR2(1080.0f,
			m_ap2DChar[CHAR2D_HIDE]->GetPosition().y - 140.0f));
	}
	if (!m_ap2DChar[CHAR2D_HIDE]->GetbDraw() &&!m_ap2DChar[CHAR2D_COMEOUT]->GetbDraw())
	{
		m_ap2DChar[CHAR2D::CHAR2D_PICKUP]->SetPosition(D3DXVECTOR2(1080.0f,
			m_ap2DChar[CHAR2D_HIDE]->GetPosition().y));
	}

#ifdef _DEBUG

	//<========================================================
	//操作タイプ変更処理
	//<========================================================
	//SPACEキーが押されたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_1) == true ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_BACK, 0) == true)
	{
		CItem::SetNumCollect(CItem::GetMax());
	}
	//<========================================================
	//操作タイプ変更処理
	//<========================================================
	//SPACEキーが押されたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_2) == true ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_BACK, 0) == true)
	{
		m_pFog->ChangeUse();
	}
#endif
}
//<====================================
//ゲーム画面の描画処理
//<====================================
void CGame::Draw(void)
{
	//<***************************************************
	//CObjectを通しているオブジェクトは自動で処理が行われる為、
	//ここに処理を書く必要はない
	//<***************************************************
	m_pCamera->SetCamera();
}