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
#include "Sound.h"
#include "BillBIcon.h"
//<================================================
//静的メンバ変数宣言
//<================================================
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
CDestArrow *CGame::m_pDestArrow = nullptr;
Ccamera *CGame::m_pCamera = nullptr;

//<**********************************************************
//名前宣言
//<**********************************************************
namespace
{
	const int NUM_BUILDING = 20;											//生成する建物の数
	const int NUM_ITEM = 5;													//生成するアイテムの数
	const int NUM_PLANT = 35;												//生成する植物の数
	const D3DXVECTOR3 PLAYER_POS = D3DXVECTOR3(-4000.0f, 0.0f, 3640.0f);	//プレイヤーの初期地点
	const D3DXVECTOR2 GAUGE_POS = D3DXVECTOR2(720.0f,660.0f);				//ゲージの位置

	const int	MAX_TIME = 4500;											//アイテムテレポートまでの時間の最大値
	const float MAX_DESTTiME = 7500;										//敵が目的地をプレイヤーの位置の周辺にするまでの時間の最大値
	const int	MAX_SPAWNTIME = 10000;										//スポーンまでの時間の最大値
}
//<====================================
//ゲーム画面のコンストラクタ
//<====================================
CGame::CGame()
{
	//値のクリア
	m_nWaitTime = INITIAL_INT;
	m_bMoved = false;
	m_nSpawnTime = INITIAL_INT;
	m_nDestTime = INITIAL_INT;
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
	CManager::GetRenderer()->SetBoolPix(FALSE);
	CManager::GetSound()->PlaySound(CSound::LABEL_BGM_GAME);

	Creating();

	return S_OK;
}
//<====================================
//ゲーム画面の終了処理
//<====================================
void CGame::Uninit(void)
{
	//<******************************************
	//カメラの破棄
	//<******************************************
	if (m_pCamera )
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//<******************************************
	//ライトの破棄
	//<******************************************
	if (m_pLight )
	{
		//メモリの解放を行う
		delete m_pLight;
		m_pLight = nullptr;
	}
	//<******************************************
	//プレイヤーの破棄
	//<******************************************
	if (m_p3DPlayer )
	{
		m_p3DPlayer->Uninit();
		m_p3DPlayer = nullptr;
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
	//ゲージの破棄
	//<******************************************
	if (m_p2DGauge )
	{
		m_p2DGauge->Uninit();
		m_p2DGauge = nullptr;
	}
	//<******************************************
	//インフォの破棄
	//<******************************************
	if (m_pInfo )
	{
		m_pInfo->Uninit();
		m_pInfo = nullptr;
	}
	//<******************************************
	//カバーの破棄
	//<******************************************
	if (m_pCover )
	{
		m_pCover->Uninit();
		m_pCover = nullptr;
	}
	//<******************************************
	//Xモデル目的矢印の破棄
	//<******************************************
	if (m_pDestArrowX )
	{
		m_pDestArrowX->Uninit();
		m_pDestArrowX = nullptr;
	}
	//<******************************************
	//2D目的矢印の破棄
	//<******************************************
	if (m_pDestArrow )
	{
		m_pDestArrow->Uninit();
		m_pDestArrow = nullptr;
	}
	//<******************************************
	//地面の破棄
	//<******************************************
	for (int nCnt = 0; nCnt < CField::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_apField[nCnt] )
		{
			//メモリの解放を行わず、終了処理をする
			m_apField[nCnt]->Uninit();
			m_apField[nCnt] = nullptr;
		}
	}
	//<******************************************
	//敵の破棄
	//<******************************************
	for (int nCnt = 0; nCnt < C3DEnemy::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_ap3DEnemy[nCnt] )
		{
			//メモリの解放を行わず、終了処理をする
			m_ap3DEnemy[nCnt]->Uninit();
			m_ap3DEnemy[nCnt] = nullptr;
		}
	}
	//<******************************************
	//建物の破棄
	//<******************************************
	for (int nCnt = 0; nCnt < CBuilding::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_apBuilding[nCnt] )
		{
			//メモリの解放を行わず、終了処理をする
			m_apBuilding[nCnt]->Uninit();
			m_apBuilding[nCnt] = nullptr;
		}
	}
	//<******************************************
	//アイテムの破棄
	//<******************************************
	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_apItem[nCnt] )
		{
			//メモリの解放を行わず、終了処理をする
			m_apItem[nCnt]->Uninit();
			m_apItem[nCnt] = nullptr;
		}
	}
	//<******************************************
	//2D文字の破棄
	//<******************************************
	for (int nCnt = 0; nCnt < C2DChar::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_ap2DChar[nCnt] )
		{
			//メモリの解放を行わず、終了処理をする
			m_ap2DChar[nCnt]->Uninit();
			m_ap2DChar[nCnt] = nullptr;
		}
	}
	//<******************************************
	//植物の破棄
	//<******************************************
	for (int nCnt = 0; nCnt < CPlant::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_apPlant[nCnt] )
		{
			//メモリの解放を行わず、終了処理をする
			m_apPlant[nCnt]->Uninit();
			m_apPlant[nCnt] = nullptr;
		}
	}
	//<******************************************
	//目印モデルの破棄
	//<******************************************
	for (int nCnt = 0; nCnt < CLandMark::GetNum(); nCnt++)
	{
		//もしメモリ確保がされていたら
		if (m_apLandMark[nCnt] )
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

	CManager::GetDebugProc()->Print("[今のスポーンタイム]：{%d}\n", m_nSpawnTime);
	CManager::GetDebugProc()->Print("[今の目的タイム]：{%d}\n", m_nDestTime);
	CManager::GetDebugProc()->Print("[現在の敵の数]：{%d}\n", C3DEnemy::GetNum());

	//動いていれば
	if (Bool::bMove(m_p3DPlayer->GetMove())
		&& !m_bMoved)
	{
		//敵生成
		C3DEnemy::RandCreate(m_ap3DEnemy);

		//フラグを立て、二回目の生成がないようにする
		m_bMoved = true;
	}
	//動いた判定になっていたら
	if (m_bMoved)
	{
		m_nSpawnTime++;
		m_nDestTime++;
		EnemySpawn();
		DestToPlayer();
	}
	
	Fading();
	ItemUpdate();

#ifdef _DEBUG

	//<========================================================
	//操作タイプ変更処理
	//<========================================================
	//SPACEキーが押されたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_1) ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_BACK, 0))
	{
		CItem::SetNumCollect(CItem::GetMax());
	}
	//<========================================================
	//操作タイプ変更処理
	//<========================================================
	//SPACEキーが押されたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_2) ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_BACK, 0))
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
//<====================================
//生成するオブジェクトのまとめ
//<====================================
void CGame::Creating(void)
{
	//<******************************************
	//カメラの生成
	//<******************************************
	m_pCamera = Ccamera::Create();

	//<******************************************
	//ライトの生成
	//<******************************************
	m_pLight = CLight::Create(CLight::MODE::MODE_DIRECTIONAL);

	//<******************************************
	//フォグの生成
	//<******************************************
	m_pFog = CFog::Create(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), D3DFOGMODE::D3DFOG_LINEAR, CFog::TYPE::TYPE_PIXEL, 0.002f);

	//<******************************************
	//地面の生成
	//<******************************************
	CField::ReadCreate(m_apField);

	//<******************************************
	//プレイヤーの生成
	//<******************************************
	m_p3DPlayer = C3DPlayer::Create(PLAYER_POS);

	//<******************************************
	//建物の生成
	//<******************************************
	CBuilding::RandCreate(m_apBuilding, NUM_BUILDING);

	//<******************************************
	//アイテムの生成
	//<******************************************
	CItem::RandCreate(m_apItem, NUM_ITEM);

	//<******************************************
	//植物の生成
	//<******************************************
	CPlant::RandCreate(m_apPlant, NUM_PLANT);

	//<******************************************
	//目印モデルの生成
	//<******************************************
	CLandMark::FixedCreate(m_apLandMark);

	//<******************************************
	//Xモデルでの目的矢印の生成
	//<******************************************
	m_pDestArrowX = CDestArrowX::Create();

	//<******************************************
	//スタミナゲージの生成
	//<******************************************
	m_p2DGauge = C2DGauge::Create(GAUGE_POS, m_p3DPlayer->GetStamina(), C2DGauge::VERTEX_X, C2DGauge::MODE_ONLY_USE);

	//<******************************************
	//スタミナゲージの生成
	//<******************************************
	m_pInfo = C2DInfo::Create(C2DInfo::Class::CLASS_NUMBER);

	//<******************************************
	//[隠れる]文字の生成
	//<******************************************
	m_ap2DChar[CHAR2D_HIDE] = C2DChar::Create(D3DXVECTOR2(1150.0f, 675.0f),
		D3DXVECTOR2(125.0f, 125.0f), C2DChar::CHAR_TYPE::CHAR_TYPE_HIDEINFO, C2DChar::MOVE_FROM_NONE, false);

	//<******************************************
	//[拾う]文字の生成
	//<******************************************
	m_ap2DChar[CHAR2D_PICKUP] = C2DChar::Create(D3DXVECTOR2(1150.0f,
		m_ap2DChar[CHAR2D_HIDE]->GetPosition().y), D3DXVECTOR2(125.0f, 125.0f),
		C2DChar::CHAR_TYPE::CHAR_TYPE_PICKUP_INFO, C2DChar::MOVE_FROM_NONE, false);

	//<******************************************
	//[出る]文字の生成
	//<******************************************
	m_ap2DChar[CHAR2D_COMEOUT] = C2DChar::Create(D3DXVECTOR2(1150.0f, 675.0f),
		D3DXVECTOR2(125.0f, 125.0f), C2DChar::CHAR_TYPE::CHAR_TYPE_COMEOUT_INFO, C2DChar::MOVE_FROM_NONE, false);

	//<******************************************
	//[封印されている]文字の生成
	//<******************************************
	m_ap2DChar[CHAR2D_SEALED] = C2DChar::Create(D3DXVECTOR2(575.0f, 500.0f),
		D3DXVECTOR2(140.0f, 120.0f), C2DChar::CHAR_TYPE::CHAR_TYPE_SEALED_INFO, C2DChar::MOVE_FROM_NONE, false);

	//<******************************************
	//2Dでの目的矢印の生成
	//<******************************************
	m_pDestArrow = CDestArrow::Create();
}
//<====================================
//フェード関連の更新処理
//<====================================
void CGame::Fading(void)
{
	//死亡状態だったら
	if (m_p3DPlayer->GetState() == C3DPlayer::STATE::STATE_DEATH)
	{
		//中身なしだったら
		if (!m_pCover)
		{
			m_pCover = Ccover::Create(Ccover::TYPE::TYPE_BLOOD_COV);
		}

		//リザルトタイプを失敗にする
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

		//リザルトタイプを成功にする
		CScene::SetResult(TYPE_RESULT::TYPE_RESULT_SUCCEEDED);

		//中身なしだったら
		if (!m_pCover)
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
}
//<====================================
//アイテム関連の更新処理
//<====================================
void CGame::ItemUpdate(void)
{
	//アイテムの数分回す
	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		//アイテムを取得していなければ
		if (!m_apItem[nCnt]->bGet())
		{
			//近づいていたら&&封印されていたら
			if (m_apItem[nCnt]->GetAppro()
				&& m_apItem[nCnt]->bGetSealed())
			{
				//表示をさせ、処理から抜ける
				m_ap2DChar[CHAR2D_SEALED]->SetDrawtrue();
				break;

			}
			//封印されていなければ
			else if(m_apItem[nCnt]->GetAppro()
				&& !m_apItem[nCnt]->bGetSealed())
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
				//表示をさせない
				m_ap2DChar[CHAR2D_SEALED]->SetDrawfalse();
			}
		}
		//近づいていたら
		if (!m_apItem[nCnt]->bGetSealed())
		{
			//表示をさせない
			m_ap2DChar[CHAR2D_SEALED]->SetDrawfalse();
		}
	}

	if (m_ap2DChar[CHAR2D_HIDE]->GetbDraw() || m_ap2DChar[CHAR2D_COMEOUT]->GetbDraw())
	{
		m_ap2DChar[CHAR2D::CHAR2D_PICKUP]->SetPosition(D3DXVECTOR2(1080.0f,
			m_ap2DChar[CHAR2D_HIDE]->GetPosition().y - 140.0f));
	}
	if (!m_ap2DChar[CHAR2D_HIDE]->GetbDraw() && !m_ap2DChar[CHAR2D_COMEOUT]->GetbDraw())
	{
		m_ap2DChar[CHAR2D::CHAR2D_PICKUP]->SetPosition(D3DXVECTOR2(1080.0f,
			m_ap2DChar[CHAR2D_HIDE]->GetPosition().y));
	}
	//
	if (m_p3DPlayer->GetUnsealed())
	{
		if (!m_ap2DChar[CHAR2D_FOUND])
		{
			m_ap2DChar[CHAR2D_FOUND] = C2DChar::Create(D3DXVECTOR2(600.0f, 425.0f),
				D3DXVECTOR2(200.0f, 200.0f), C2DChar::CHAR_TYPE::CHAR_TYPE_FOUND_INFO, C2DChar::MOVE_FROM_LEFT, true);
		}
	}
}
//<====================================
//敵スポーン関連の更新処理
//<====================================
void CGame::EnemySpawn(void)
{
	//既定値にいっていたら
	if (m_nSpawnTime >= MAX_SPAWNTIME)
	{
		for (int nCnt = 0; nCnt < INT_VALUE::MAX_CHAR; nCnt++)
		{
			//中身がなければ
			if (!m_ap3DEnemy[nCnt])
			{
				//敵をスポーンさせる
				m_ap3DEnemy[nCnt] = C3DEnemy::RandCreateWithNum(m_ap3DEnemy, 1);
				m_nSpawnTime = INITIAL_INT;
				return;
			}
		}
	}
}
//<====================================
//目的関連の更新処理
//<====================================
void CGame::DestToPlayer(void)
{
	int nRand = INITIAL_INT;			//乱数をするための変数
	const float DISTANCE_POS = 350.0f;	//プレイヤーの位置から離れる距離

	//基底の時間になったら
	if (m_nDestTime >= MAX_DESTTiME)
	{
		for(int nCnt =0;nCnt < C3DEnemy::GetNum();nCnt++)
		{

			//高速型ではなければ
			if (m_ap3DEnemy[nCnt] &&
				m_ap3DEnemy[nCnt]->GetType() != C3DEnemy::TYPE::TYPE_ENEMY_HIGHSPEED)
			{
				//0から2までの数をランダムで決める
				nRand = Calculate::CalculeteRandInt(5, 0);

				//当てはまったら
				if (nRand == 3)
				{
					//プレイヤーの方向に移動する
					m_ap3DEnemy[nCnt]->SetDest(D3DXVECTOR3(m_p3DPlayer->GetPosition().x + DISTANCE_POS,
						0.0f, m_p3DPlayer->GetPosition().z + DISTANCE_POS));

					m_nDestTime = INITIAL_INT;
					return;
				}
			}
		}
	}
}