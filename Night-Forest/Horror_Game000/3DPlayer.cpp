//<============================================
//3Dプレイヤー処理(3DPlayer.cpp)
//
//Author:kazuki watanabe
//<============================================
#include "3DPlayer.h"
#include "Camera.h"
#include "Title.h"
#include "Light.h"
#include "game.h"
#include "Building.h"
#include "2DGauge.h"
//<*******************************************
//静的メンバ変数の宣言
//<*******************************************
//マテリアル関連
//テクスチャ関連

namespace
{
	const float VALUE_REVISE	= 0.15f;	//補正の値
	const float GROUND			= 0.0f;		//地面の位置
	const float ROTATE_VALUE	= 0.05f;	//回転量
	const float REVISE_ROT		= 0.5f;
	const float NO_DASH_VALUE	= 0.3f;		//斜め移動込みの移動量(1.0fがちょうどいい)
	const float DASH_VALUE		= 1.0f;		//斜め移動込みの移動量(1.0fがちょうどいい)
	const int	MAX_STAMINA		= 500;		//スタミナの最大値
}

//<==================================
//3Dプレイヤーのコンストラクタ
//<==================================
C3DPlayer::C3DPlayer(int nPriority)
{
	//値のクリア
	m_pos = INIT_VECTOR;
	m_rot = INIT_VECTOR;
	m_move = INIT_VECTOR;

	//角度関連
	m_fRotMove = NULL;
	m_fRotDest = NULL;
	m_fRotDiff = NULL;

	//ファイル名
	m_bJump = false;
	m_bDash = false;
	m_bMove = false;
	m_rRad = INIT_VECTOR;
	m_fMoveValue = INITIAL_FLOAT;
	m_sState = STATE_NONE;
	m_fCollidRad = INITIAL_FLOAT;

	m_nStamina = INITIAL_INT;

	m_sModel = {};
}
//<==================================
//3Dプレイヤーのデストラクタ
//<==================================
C3DPlayer::~C3DPlayer()
{
	
}
//<==================================
//3Dプレイヤーの生成処理
//<==================================
C3DPlayer *C3DPlayer::Create(const D3DXVECTOR3 pos)
{
	//インスタンス生成用のオブジェクト
	C3DPlayer *pPlayer3D = new C3DPlayer;

	//もしメモリ確保に成功したら
	if (pPlayer3D != NULL)
	{
		pPlayer3D->Init();

		//位置を代入
		pPlayer3D->SetPosition(pos);

		//
		pPlayer3D->SetType3D(TYPE_3D::TYPE_PLAYER3D);
	}
	//
	else
	{
		return NULL;

	}

	return pPlayer3D;
}
//<==================================
//3Dプレイヤーの初期化処理
//<==================================
HRESULT C3DPlayer::Init(void)
{
	//スタミナの値設定
	m_nStamina = C2DGauge::GetFixed();
	m_fCollidRad = 50.0f;
	m_sModel = BindModel("data\\MODEL\\Enemy001.x");

	return S_OK;
}
//<==================================
//3Dプレイヤーの更新処理
//<==================================
void C3DPlayer::Update(void)
{
	//まだゲームが終わっていなければ
	if (CManager::GetScene()->GetGame()->GetGame()->GetState() == CGame::STATE_NONE)
	{
		//前回の位置を保存
		m_posOld = m_pos;

		//位置を取得
		m_pos = GetPosition();

		//移動量の取得
		m_move = GetMove();

		//向きを取得
		m_rot = GetRotation();

		//アクション時の操作
		Controll();

		//限界位置を設定する
		m_pos = Correction::LimitPos(m_pos, D3DXVECTOR3(4000.0f, 0.0f, 4000.0f),true,true,true);

		SetVector3(m_pos, m_rot, m_move);

		CScene::GetGame()->GetLight()->SetPosition(m_pos);

	}
	//自分自身へのポインタがNULLではなければ
	if (this != NULL)
	{
		//<====================================================
		//デバッグ関連
		//<====================================================
		/*CManager::GetDebugProc()->Print("<=====================================================\n");
		CManager::GetDebugProc()->Print("[プレイヤー関連のデバッグ表示]\n");
		CManager::GetDebugProc()->Print("<=====================================================\n");
		CManager::GetDebugProc()->Print("[位置]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_pos.x, m_pos.y, m_pos.z);
		CManager::GetDebugProc()->Print("[向き]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_rot.x, m_rot.y, m_rot.z);
		CManager::GetDebugProc()->Print("[移動量]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_move.x, m_move.y, m_move.z);
		CManager::GetDebugProc()->Print("[スタミナ]：%d\n", m_nStamina);*/
	}
}
//<==================================
//3Dプレイヤーのアクション時の操作
//<==================================
void C3DPlayer::Controll(void)
{

	//向き関連の値の挿入
	m_fRotMove = m_rot.y;	//現在の角度
	m_fRotDest = m_rot.y;	//目標の角度
	m_fRotDiff = 0.0f;		//角度の補正

	Dash();

	//隠れているステート以外の場合
	if (m_sState != STATE_HIDE)
	{
		Movement();
	}

	Hide();
	
#if 1

	//追従処理
	CManager::GetScene()->GetGame()->GetCamera()->SetFollow(m_pos,m_rot,Ccamera::VISIBILITY_FPV);

#endif
	//現在と目標の差分を求め、
	m_fRotDiff = m_fRotDest - m_fRotMove;

	//角度の補正をする
	m_rot.y += m_fRotDiff * REVISE_ROT;

	//位置を更新
	m_pos += m_move;

	//慣性をつける
	m_move.x += (0.0f - m_move.x) *VALUE_REVISE;//X軸
	m_move.y += (0.0f - m_move.y) *VALUE_REVISE;//Y軸
	m_move.z += (0.0f - m_move.z) *VALUE_REVISE;//Z軸

}
//<===================================================================
//ダッシュ
//<===================================================================
void C3DPlayer::Dash(void)
{
	//隠れている状態以外だったら
	if (m_sState != STATE_HIDE)
	{
		//離していたら
		if (!CManager::GetKeyboard()->bGetPress(DIK_LSHIFT)
			&& !CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_LB, 0))
		{
			//ダッシュしていない状態にする
			m_bDash = false;

		}
	}
	//隠れている状態だったら
	else if (m_sState == STATE_HIDE)
	{
		//スタミナが最大値以上になったら
		if (m_nStamina >= C2DGauge::GetFixed())
		{
			//その値にする
			m_nStamina = C2DGauge::GetFixed();
		}
		//最大値以上ではなければ
		else
		{
			//スタミナを増やしていく
			m_nStamina++;
		}
	}
	//ダッシュしていれば
	if (m_bDash == true)
	{
		//スタミナが0以下になったら
		if (m_nStamina <= 0)
		{
			//その値にする
			m_nStamina = 0;
		}
		//0以下ではなければ
		else
		{
			//スタミナを減らしていく
			m_nStamina--;
		}
	}
	//ダッシュしていなければ
	else
	{
		//スタミナが最大値以上になったら
		if (m_nStamina >= C2DGauge::GetFixed())
		{
			//その値にする
			m_nStamina = C2DGauge::GetFixed();
		}
		//最大値以上ではなければ
		else
		{
			//スタミナを増やしていく
			m_nStamina++;
		}
	}

	//ゲージの値設定
	CManager::GetScene()->GetGame()->GetGauge()->SetNum(m_nStamina);
}
//<===================================================================
//隠れる際の挙動
//<===================================================================
void C3DPlayer::Hide(void)
{
	//建物の数分回す
	for (int nCnt = 0; nCnt < CBuilding::GetNum(); nCnt++)
	{
		Collision::CollidXZ
		(CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetPosition(),
			CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetModel().rSizeX,
			CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetModel().rSizeZ,
			CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetModel().vtxMax,
			CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetModel().vtxMin,
			&m_pos, m_posOld, &m_move, m_sModel.vtxMax, m_sModel.vtxMin);

		//<****************************************
		//隠れる処理
		//<****************************************
		//当たっていたら
		if (Collision::CollidAll(CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetPosition(),
			CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetHideRad(), m_pos, m_sModel.vtxMax, m_sModel.vtxMin))
		{
			//隠れ状態だったら
			if (m_sState == STATE_HIDE)
			{
				//表示をさせる
				CManager::GetScene()->GetGame()->Get2DChar(CGame::CHAR2D_COMEOUT)->SetDisptrue();

				//表示をさせない
				CManager::GetScene()->GetGame()->Get2DChar(CGame::CHAR2D_HIDE)->SetDispfalse();
			}
			//隠れ状態では無ければ
			else if (m_sState == STATE_NONE)
			{

				//表示をさせる
				CManager::GetScene()->GetGame()->Get2DChar(CGame::CHAR2D_HIDE)->SetDisptrue();

				//表示をさない
				CManager::GetScene()->GetGame()->Get2DChar(CGame::CHAR2D_COMEOUT)->SetDispfalse();
			}

			//範囲内に入っている際にキーを押すと
			if (CManager::GetKeyboard()->bGetTrigger(DIK_SPACE) == true
				|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0))
			{
			
				//ステートが何もなしなら隠れ状態になり、隠れ状態なら何もなしにする
				m_sState == STATE_NONE ? m_sState = STATE_HIDE : m_sState = STATE_NONE;
				CManager::GetSound()->PlaySound(CSound::LABEL_SE_HIDE);
			}

			break;
		}
		//いなければ
		else
		{
			//表示をさせない
			CManager::GetScene()->GetGame()->Get2DChar(CGame::CHAR2D_HIDE)->SetDispfalse();

			//表示をさない
			CManager::GetScene()->GetGame()->Get2DChar(CGame::CHAR2D_COMEOUT)->SetDispfalse();
		}
	}
}
//<==================================
//3Dプレイヤーのアクション時の動き
//<==================================
void C3DPlayer::MoveAction(void)
{
//<************************
//この関数限定のマクロ定義
//<************************

#define GRAVITY			(3.14f)		//重力値
#define JUMP_VALUE		(55.0f)		//ジャンプの値	

	//<*****************************************************
	//ジャンプアクション関連
	//<*****************************************************
	if (CManager::GetKeyboard()->bGetTrigger(DIK_SPACE) == true)//もしAキーが押されていたら下の処理を実行
	{
		//もしジャンプしていなければ
		if (m_bJump == false)
		{
			//ジャンプする
			m_move.y += JUMP_VALUE;

			//ジャンプした判定にする
			m_bJump = true;
		}
	}

#if 1
	//もし地面の下に落ちそうだったら
	if (m_pos.y <= GROUND)
	{
		//地面の位置に補正
		m_pos.y = GROUND;
	
		//ジャンプ可能にする
		m_bJump = false;

	}
	//それ以外
	else
	{
		//重力を付加
		m_move.y -= GRAVITY;

		//ジャンプしている判定にする
		m_bJump = true;
	}
#else

#endif

}
//<===================================================
//3Dプレイヤーの移動処理
//<===================================================
void C3DPlayer::Movement(void)
{
	//ダッシュしていなければ
	if (m_bDash == false
		||m_nStamina <= 0)
	{
		//ダッシュしていない値にする
		m_fMoveValue = NO_DASH_VALUE;
	}
	//していたら
	else if(m_bDash == true
		|| !(m_nStamina <= 0))
	{
		//ダッシュしている値にする
		m_fMoveValue = DASH_VALUE;
	}

	//<***************************************************
	//移動関連
	//<***************************************************
	//上移動
	if (CManager::GetKeyboard()->bGetPress(DIK_W) == true || CManager::GetJoyPad()->YGetStickPressL(BUTTON_LY, 0) > 0)
	{
		//カメラの向きに合わせて移動する
		m_move.x += sinf(-D3DX_PI * MOVE_DOWN + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;
		m_move.z += cosf(-D3DX_PI * MOVE_DOWN + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;

		m_fRotDest = D3DX_PI * MOVE_UP + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y;

		//RSHIFTが押されている状態だったら
		if (CManager::GetKeyboard()->bGetPress(DIK_LSHIFT)
			|| CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_LB, 0))
		{

			//ダッシュしていない状態だったら
			if (m_bDash == false)
			{
				//ダッシュしている状態にする
				m_bDash = true;
			}
		}

	}
	//離していたら
	else if (!(CManager::GetKeyboard()->bGetPress(DIK_W) == true || CManager::GetJoyPad()->YGetStickPressL(BUTTON_LY, 0) > 0))
	{
		//W押してLSHIFT押したままダッシュ発動を防ぐ
		m_bDash = false;
	}
	//<===================================================
	//下移動
	//<===================================================
	if (CManager::GetKeyboard()->bGetPress(DIK_S) == true || CManager::GetJoyPad()->YGetStickPressL(BUTTON_LY, 0) < 0)
	{
		//カメラの向きに合わせて移動する
		m_move.x += sinf(-D3DX_PI * MOVE_UP + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;
		m_move.z += cosf(-D3DX_PI * MOVE_UP + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;

		m_fRotDest = D3DX_PI * MOVE_DOWN + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y;

		//RSHIFTが押されている状態だったら
		if (CManager::GetKeyboard()->bGetPress(DIK_LSHIFT)
			|| CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_LB, 0))
		{

			//ダッシュしていない状態だったら
			if (m_bDash == false)
			{
				//ダッシュしている状態にする
				m_bDash = true;
			}
		}
	
	}
	//<=======================================
	//キー入力(Dキー)
	//<=======================================
	if (CManager::GetKeyboard()->bGetPress(DIK_D) == true || CManager::GetJoyPad()->XGetStickPressL(BUTTON_LX, 0) > 0)//もしAキーが押されていたら下の処理を実行
	{
		//左に移動
		m_move.x -= sinf(-D3DX_PI * MOVE_LR + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;
		m_move.z -= cosf(-D3DX_PI * MOVE_LR + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;

		//モデルの左側にカメラを向ける
		m_fRotDest = -D3DX_PI * MOVE_LR + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y;

		//RSHIFTが押されている状態だったら
		if (CManager::GetKeyboard()->bGetPress(DIK_LSHIFT)
			|| CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_LB, 0))
		{
			//ダッシュしていない状態だったら
			if (m_bDash == false)
			{
				//ダッシュしている状態にする
				m_bDash = true;
			}
		}

	}
	//<=======================================
	//キー入力(Aキー)
	//<=======================================
	if (CManager::GetKeyboard()->bGetPress(DIK_A) == true || CManager::GetJoyPad()->XGetStickPressL(BUTTON_LX, 0) < 0)//もしAキーが押されていたら下の処理を実行
	{
		//左に移動
		m_move.x += sinf(-D3DX_PI * MOVE_LR + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;
		m_move.z += cosf(-D3DX_PI * MOVE_LR + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;

		//モデルの右側にカメラを向ける
		m_fRotDest = D3DX_PI * MOVE_LR + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y;

		//RSHIFTが押されている状態だったら
		if (CManager::GetKeyboard()->bGetPress(DIK_LSHIFT)
			|| CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_LB, 0))
		{

			//ダッシュしていない状態だったら
			if (m_bDash == false)
			{
				//ダッシュしている状態にする
				m_bDash = true;
			}
		}
	}
}