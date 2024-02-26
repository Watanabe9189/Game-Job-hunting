//<============================================
//3Dエネミー処理(3DEnemy.cpp)
//
//Author:kazuki watanabe
//<============================================
#include "3DEnemy.h"
#include "game.h"
#include "Result.h"

//<**************************************************************
//名前宣言
//<**************************************************************
namespace
{
	const float SEARCH_MOVE				= 0.0045f;	//探索している時の移動量
	const float CHASE_VALUE				= 0.012f;	//追跡している時の移動値
	const float FACE_VALUE				= 0.075f;	//高速移動の時の移動量
	const float ALPHA_VALUE				= 0.08f;	//透明度の値
	const float ALPHA_VALUE_HIGH		= 0.005f;	//高速型の透明度の値
	const float DOUBLE_VALUE			= 1.7f;		//倍にする値
	const float ROTATE_VALUE			= 0.1f;		//回転値

	const float RADIUSE_VALUE_NORMAL	= 800.0f;	//通常型の半径の値
	const float RADIUSE_VALUE_INVISIBLE = 700.0f;	//透明型の半径の値

	const int	MAX_INTERVAL			= 500;		//間隔の最大値

	const int	DEFAULT_NUM_SET			= 3;		//敵の数のデフォルト値
	const int	MAX_NUM_SET = 9;		//敵の数のデフォルト値
	const int	MIN_NUM_SET = 1;		//敵の数のデフォルト値
}

//<*******************************************
//静的メンバ変数の宣言
//<*******************************************
																//テクスチャ関

int C3DEnemy::m_nNumAll = NULL;			//数
#ifdef _DEBUG

int C3DEnemy::m_nNumSet = MAX_NUM_SET;

#else

int C3DEnemy::m_nNumSet = DEFAULT_NUM_SET;

#endif
int C3DEnemy::m_nNumMax = MAX_NUM_SET;
int C3DEnemy::m_nNumMin = MIN_NUM_SET;

//<==========================================
//ファイル名指定
//<==========================================
const char		*C3DEnemy::m_acFilename[TYPE::TYPE_MAX] =
{
	"data/MODEL/Monster000.x",		//通常型
	"data/MODEL/Monster002.x",		//透明型
	"data/MODEL/Monster001.x",		//高速型
};

//<=======================================
//3Dエネミーのコンストラクタ
//<=======================================
C3DEnemy::C3DEnemy(int nPriority)
{
	m_nNumAll++;

	//値のクリア
	m_pos = INIT_VECTOR;
	m_rDestPos = INIT_VECTOR;
	m_rot = INIT_VECTOR;
	m_move = INIT_VECTOR;
 	m_fMoveValue = INITIAL_FLOAT;

	m_sState = STATE::STATE_SEARCH;
	m_sFastState = FAST_STATE::FAST_STATE_WAIT;

	m_nSoundCount = INITIAL_INT;
	m_nInterval = INITIAL_INT;
	m_nRandInter = INITIAL_INT;
	m_eType = TYPE::TYPE_MAX;

	m_fFrontDest = INIT_VECTOR;
	m_fBackDest = INIT_VECTOR;
	
	m_rTelportPos = INIT_VECTOR;
	m_sModel = {};

	m_pPlayer = nullptr;
	m_pSound = nullptr;
}
//<=======================================
//3Dエネミーのデストラクタ
//<=======================================
C3DEnemy::~C3DEnemy()
{
	m_nNumAll--;
}
//<=======================================
//3Dエネミーの生成処理
//<=======================================
C3DEnemy *C3DEnemy::Create(const D3DXVECTOR3 pos ,const int nLife, const int nType, const int CoolTime)
{
	return nullptr;
}
//<=======================================
//3Dエネミーの初期化処理
//<=======================================
HRESULT C3DEnemy::Init(void)
{
	m_sModel = BindModel(m_acFilename[m_eType], true);
	
	SetDest();

	//透明の敵だったら
	if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
	{
		//透明型の半径にする
		m_fSearchRad = RADIUSE_VALUE_INVISIBLE;
	}
	//通常型だったら
	else if (m_eType == TYPE::TYPE_ENEMY_NORMAL)
	{
		//通常型の半径にする
		m_fSearchRad = RADIUSE_VALUE_NORMAL;
	}

	m_nRandInter = Calculate::CalculeteRandInt(3500, 1000);
	m_nSoundMax = Calculate::CalculeteRandInt(200, 100);

	//モードがゲームの時のみ
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		//頂点数分繰り返し
		for (int nCntMaxMat = 0; nCntMaxMat < (int)m_sModel.dwNumMat; nCntMaxMat++)
		{
			//透明の敵だったら
			if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
			{
				//初期の透明度を透明色にする
				m_sModel.pMat[nCntMaxMat].MatD3D.Diffuse.a = COLOR_VALUE::ALPHA_CLEANNESS;
				m_sModel.pMat[nCntMaxMat].MatD3D.Ambient.a = COLOR_VALUE::ALPHA_CLEANNESS;
			}
		}
	}

	//モードがゲームの時のみ
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		//音声の生成
		m_pSound = CSound::Create();

		assert(m_pSound != nullptr);
	}

return S_OK;
}
//<=======================================
//3Dエネミーの終了処理
//<=======================================
void C3DEnemy::Uninit(void)
{
	//ここをなくすとメモリリークが発生する
	CXObject::Uninit();

	//サウンド破棄
	if (m_pSound != nullptr)
	{
		//破棄
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
}
//<=======================================
//3Dエネミーの更新処理
//<=======================================
void C3DEnemy::Update(void)
{		
	//モードがゲームの時のみ
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		//まだゲームが終わっていなければ
		if (CManager::GetScene()->GetGame()->GetGame()->GetState() == CGame::STATE_NONE)
		{
			m_pPlayer = CScene::GetGame()->Get3DPlayer();
			//<***********************************
			//それぞれの情報の取得
			//<***********************************
			m_pos = GetPosition();
			m_rot = GetRotation();
			m_move = GetMove();

			//加算していく
			m_pos += m_move;

			//CManager::GetDebugProc()->Print("[位置]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_pos.x, m_pos.y, m_pos.z);
			//CManager::GetDebugProc()->Print("[距離]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_rDis.x, m_rDis.y, m_rDis.z);
			//CManager::GetDebugProc()->Print("[目的の位置]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_rDestPos.x, m_rDestPos.y, m_rDestPos.z);
			//CManager::GetDebugProc()->Print("[前目的の位置]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_fFrontDest.x, m_fFrontDest.y, m_fFrontDest.z);
			//CManager::GetDebugProc()->Print("[あと目的の位置]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_fBackDest.x, m_fBackDest.y, m_fBackDest.z);

			//CManager::GetDebugProc()->Print("[今のインターバル]：%d\n", m_nInterval);
			//CManager::GetDebugProc()->Print("[今のランダムインターバル]：%d\n", m_nRandInter);
			//CManager::GetDebugProc()->Print("[今のステート]：%d\n", m_sState);
			CManager::GetDebugProc()->Print("[敵タイプ]：%d\n", m_eType);
			//CManager::GetDebugProc()->Print("[バッファ]：%d\n", m_sModel.pBuffMat);

			MoveMent();

			ChangeRot();

			m_move.x += (0.0f - m_move.x) *0.1f;
			m_move.z += (0.0f - m_move.z) *0.1f;

			//ベクトルの三要素の設定
			SetVector3(m_pos, m_rot, m_move);
		}
	}
	else
	{
		//<***********************************
		//それぞれの情報の取得
		//<***********************************
		m_pos = GetPosition();
		m_rot = GetRotation();
		m_move = GetMove();

		//加算していく
		m_pos += m_move;

		//ベクトルの三要素の設定
		SetVector3(m_pos, m_rot, m_move);
	}
}
//<=======================================
//3Dエネミーの描画処理
//<=======================================
void C3DEnemy::Draw(void)
{
	CXObject::Draw();
}
//<=======================================
//3Dエネミーの行動処理
//<=======================================
void C3DEnemy::MoveMent(void)
{
	D3DXVECTOR3 rRotDest = Calculate::CalculateDest(m_pos, m_rDestPos);

	//高速型だったら
	if (m_eType == TYPE::TYPE_ENEMY_HIGHSPEED)
	{
		//待機状態だったら
		if (m_sFastState == FAST_STATE::FAST_STATE_WAIT)
		{
			CManager::GetSound()->StopSound(CSound::LABEL_BGM_APPROACH);

			//間隔が一定値を超えていたら
			if (m_nInterval >= m_nRandInter)
			{
				//プレイヤーが隠れていなければ
				if (m_pPlayer->GetState() != C3DPlayer::STATE_HIDE)
				{
					//行動ステートに移行させる
					m_sFastState = FAST_STATE::FAST_STATE_INTERVAL;
					CManager::GetSound()->PlaySound(CSound::LABEL::LABLE_SE_MOAN2);

					//動いていれば
					if (Bool::bMove(m_pPlayer->GetMove()))
					{
						//プレイヤーの動いている位置にテレポートする
						m_rTelportPos = D3DXVECTOR3(m_pPlayer->GetPosition().x + 150.0f
							* m_pPlayer->GetMove().x, 
							+m_pPlayer->GetPosition().y,
							m_pPlayer->GetPosition().z + 
							150.0f*m_pPlayer->GetMove().z);

						//そのテレポート位置に行く
						m_pos = m_rTelportPos;
					}
					//動いていなければ
					else
					{
						m_pos = m_pPlayer->GetPosition();
					}
					CScene::GetGame()->GetCamera()->Shake();
				}

				//初期化する
				m_nInterval = 0;

			}
			//いなければ
			else
			{
				//動いていれば
				if (Bool::bMove(m_pPlayer->GetMove()))
				{
					//加算させる
					m_nInterval++;
				}
			}

			//頂点数分繰り返し
			for (int nCntMaxMat = 0; nCntMaxMat < (int)m_sModel.dwNumMat; nCntMaxMat++)
			{
				if (m_sModel.pMat[nCntMaxMat].MatD3D.Diffuse.a <= COLOR_VALUE::ALPHA_CLEANNESS
					&&m_sModel.pMat[nCntMaxMat].MatD3D.Ambient.a <= COLOR_VALUE::ALPHA_CLEANNESS)
				{
					m_sModel.pMat[nCntMaxMat].MatD3D.Diffuse.a = COLOR_VALUE::ALPHA_CLEANNESS;
					m_sModel.pMat[nCntMaxMat].MatD3D.Ambient.a = COLOR_VALUE::ALPHA_CLEANNESS;
				}
				else
				{
					//赤色に変える
					m_sModel.pMat[nCntMaxMat].MatD3D.Diffuse.a -= ALPHA_VALUE_HIGH;
					m_sModel.pMat[nCntMaxMat].MatD3D.Ambient.a -= ALPHA_VALUE_HIGH;
				}
			}
		}
		//ugoku状態だったら
		else if (m_sFastState == FAST_STATE::FAST_STATE_MOVE)
		{

			m_rot.y = Calculate::RotateToDest(m_rot.y, rRotDest, ROTATE_VALUE);
		
			//プレイヤーの位置を目的地とする
			SetDest(m_pPlayer->GetPosition());

			m_fMoveValue = 0.085f;

			//移動する
			m_move.x = (m_rDestPos.x - m_pos.x - m_move.x)*m_fMoveValue;//X軸
			m_move.z = (m_rDestPos.z - m_pos.z - m_move.z)*m_fMoveValue;//Z軸

			 //プレイヤーが隠れていれば
			if (m_pPlayer->GetState() == C3DPlayer::STATE_HIDE)
			{
				//間隔を設定する
				m_nInterval = MAX_INTERVAL;
			}

			 //間隔が一定値を超えていたら
			if (m_nInterval >= MAX_INTERVAL)
			{
				//行動ステートに移行させる
				m_sFastState = FAST_STATE_WAIT;
				m_nInterval = 0;
				m_nRandInter = Calculate::CalculeteRandInt(4000, 1000);
			}
			//いなければ
			else
			{
				//加算させる
				m_nInterval++;
			}

			CollidPlayer();
		}
		//ugoku状態だったら
		else if (m_sFastState == FAST_STATE::FAST_STATE_INTERVAL)
		{
			 //向き
			 m_rot.y =Calculate::RotateToDest(m_rot.y,rRotDest, ROTATE_VALUE);

			//プレイヤーの位置を目的地とする
			SetDest(m_pPlayer->GetPosition());

			CManager::GetSound()->SetBgm(2.0f, CSound::LABEL_BGM_APPROACH);
			CManager::GetSound()->PlaySound(CSound::LABEL_BGM_APPROACH);

			//プレイヤーが隠れていれば
			if (m_pPlayer->GetState() == C3DPlayer::STATE_HIDE)
			{
				//行動ステートに移行させる
				m_sFastState = FAST_STATE_WAIT;
				m_nInterval = 0;
				m_nRandInter = Calculate::CalculeteRandInt(4000,1000);
			}

			//間隔が一定値を超えていたら
			if (m_nInterval >= MAX_INTERVAL)
			{
				//行動ステートに移行させる
				m_sFastState = FAST_STATE_MOVE;
				m_nInterval = 0;
			}
			//いなければ
			else
			{
				//加算させる
				m_nInterval++;
			}
		}
		//待機状態以外だったら
		if (m_sFastState != FAST_STATE::FAST_STATE_WAIT)
		{
			//頂点数分繰り返し
			for (int nCntMaxMat = 0; nCntMaxMat < (int)m_sModel.dwNumMat; nCntMaxMat++)
			{
				//無駄な処理をしないようにする
				if (m_sModel.pMat[nCntMaxMat].MatD3D.Diffuse.a != COLOR_VALUE::ALPHA_OPACITY
					&&m_sModel.pMat[nCntMaxMat].MatD3D.Ambient.a != COLOR_VALUE::ALPHA_OPACITY)
				{
					m_sModel.pMat[nCntMaxMat].MatD3D.Diffuse.a = COLOR_VALUE::ALPHA_OPACITY;
					m_sModel.pMat[nCntMaxMat].MatD3D.Ambient.a = COLOR_VALUE::ALPHA_OPACITY;
				}
			}

		}
	}
	//それ以外の種類だったら
	else
	{
		//探索関数
		Search();
		CollidPlayer();
	}
#ifdef _DEBUG

	//<========================================================
	//操作タイプ変更処理
	//<========================================================
	//SPACEキーが押されたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_F2) == true ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_BACK, 0) == true)
	{
		m_nInterval = m_nRandInter;
	}

#endif
}
//<=======================================
//3Dエネミー
//<=======================================
void C3DEnemy::ChangeRot(void)
{

}
//<=======================================
//3Dエネミーの
//<=======================================
void C3DEnemy::Search(void)
{
	D3DXVECTOR3 rRotDest = Calculate::CalculateDest(m_pos, m_rDestPos);

	//距離を計算する(その位置-目的とする位置)
	m_rDis = Calculate::CalculateDest(m_pos, m_pPlayer->GetPosition());

	Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false);

	//2000まで生成し、1000を引く
	D3DXVECTOR3 rRandDest = Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false);

	//透明の敵だったら
	if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
	{
		//サウンドセット
		SetSound(CSound::LABEL_SE_MOAN1, m_nSoundMax, m_pPlayer->GetPosition());
	}
	//通常型だったら
	else if (m_eType == TYPE::TYPE_ENEMY_NORMAL)
	{
		//サウンドセット
		SetSound(CSound::LABEL_SE_MOAN0, m_nSoundMax, m_pPlayer->GetPosition());
	}

	m_move.x = (m_rDestPos.x -m_pos.x - m_move.x) *m_fMoveValue;//X軸
	m_move.z = (m_rDestPos.z - m_pos.z - m_move.z) *m_fMoveValue;//Z軸

	 
	//追跡状態だったら
	if (m_sState == STATE::STATE_CHASE)
	{
		SetDest(m_pPlayer->GetPosition());

		m_fMoveValue = CHASE_VALUE;

		//向き
		m_rot.y = Calculate::RotateToDest(m_rot.y, rRotDest, ROTATE_VALUE);

		//もし離れていたら
		if (m_rDis.x >= m_fSearchRad
			|| m_rDis.x <= -m_fSearchRad
			|| m_rDis.z >= m_fSearchRad
			|| m_rDis.z <= -m_fSearchRad)
		{
			//探索モードに移行する
			m_sState = STATE_SEARCH;
			SetDest(rRandDest);
		}
		//プレイヤーが隠れていたら
		if (m_pPlayer->GetState() == C3DPlayer::STATE_HIDE)
		{
			//探索モードに移行する
			SerachRot(rRandDest);
		}

		//透明型だったら
		if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
		{
			m_sModel.pMat = Color::AlphaChangeMaterial(m_sModel.pMat, ALPHA_VALUE, m_sModel.dwNumMat);
		}
	}
	//探索モードだったら
	else if (m_sState == STATE_SEARCH)
	{
		m_fMoveValue = SEARCH_MOVE;

		//向き
		m_rot.y = Calculate::RotateToDest(m_rot.y, rRotDest, ROTATE_VALUE);

		//目的の位置についたら
		if (m_pos.x >= m_fFrontDest.x&&m_pos.x <= m_fBackDest.x
			|| m_pos.x <= m_fFrontDest.x&&m_pos.x >= m_fBackDest.x
			&&m_pos.z >= m_fFrontDest.z&&m_pos.z <= m_fBackDest.z
			|| m_pos.z <= m_fFrontDest.z&&m_pos.z >= m_fBackDest.z)
		{
			SetDest(rRandDest);
		}
		if (m_pPlayer->GetState() != C3DPlayer::STATE_HIDE)
		{
			//もし近づいていたら
			if (m_rDis.x <= m_fSearchRad
				&& !(-m_rDis.x >= m_fSearchRad)
				&& m_rDis.z <= m_fSearchRad
				&& !(-m_rDis.z >= m_fSearchRad))
			{
				//透明の敵だったら
				if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
				{
					m_pSound->PlaySoundWithVolume(CSound::LABEL_SE_NOTICED2, 2.0f);
				}
				//通常型だったら
				else if (m_eType == TYPE::TYPE_ENEMY_NORMAL)
				{
					//サウンドセット
					m_pSound->PlaySoundWithVolume(CSound::LABEL_SE_NOTICED1, 2.0f);
				}

				//追跡モードにする
				m_sState = STATE_CHASE;
			}
		}
		//透明型だったら
		if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
		{
			m_sModel.pMat = Color::AlphaChangeMaterial(m_sModel.pMat, -ALPHA_VALUE, m_sModel.dwNumMat);
		}
	}
}
//<==========================================================================================================
//引数ありの目的地設定
//<==========================================================================================================
void C3DEnemy::SetDest(const D3DXVECTOR3 rDestPos)
{
	//位置を決める
	m_rDestPos = rDestPos;

	//手前と後ろの位置を設定
	m_fFrontDest = D3DXVECTOR3(m_rDestPos.x + 10.0f, m_rDestPos.y + 10.0f, m_rDestPos.z + 10.0f);
	m_fBackDest = D3DXVECTOR3(m_rDestPos.x - 10.0f, m_rDestPos.y - 10.0f, m_rDestPos.z - 10.0f);
	
}
//<========================================================
//引数なしの目的地設定
//<========================================================
void C3DEnemy::SetDest(void)
{
	//2000まで生成し、1000を引く
	D3DXVECTOR3 rRandDest = Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false);

	//位置をランダムで決める
	m_rDestPos = rRandDest;

	//手前と後ろの位置を設定
	m_fFrontDest = D3DXVECTOR3(m_rDestPos.x + 10.0f, m_rDestPos.y + 10.0f, m_rDestPos.z + 10.0f);
	m_fBackDest = D3DXVECTOR3(m_rDestPos.x - 10.0f, m_rDestPos.y - 10.0f, m_rDestPos.z - 10.0f);
}
//<=======================================
//3Dエネミーのサウンド設定
//<=======================================
void C3DEnemy::SetSound(const CSound::LABEL Label, const int nMaxCount, const D3DXVECTOR3 rTargetPos)
{
	//
	if (m_nSoundCount >= nMaxCount)
	{
		m_pSound->PlaySoundWithDis(Label, m_pos, rTargetPos);
		m_nSoundCount = 0;
	}
	//
	else
	{
		m_nSoundCount++;
	}
}
//<=======================================
//ファイル読み込みを使用した生成処理
//<=======================================
void C3DEnemy::SerachRot(const D3DXVECTOR3 rRandPos)
{
	m_fMoveValue = 0.0f;
	if (m_nInterval >= 500)
	{
		m_sState = STATE_SEARCH;
		SetDest(rRandPos);
		m_nInterval = 0;
	}
	if (m_nInterval >= 150
		&& !(m_nInterval >= 350))
	{
		m_rot.y = Calculate::RotateToDest(m_rot.y, D3DXVECTOR3(0.0f, 1.56f, 0.0f), 0.045f);
	}
	if (!(m_nInterval >= 150)
		&& m_nInterval >= 350)
	{
		m_rot.y = Calculate::RotateToDest(m_rot.y, D3DXVECTOR3(0.0f, 3.14f, 0.0f), 0.045f);
	}
	if (!(m_nInterval >= 500))
	{
		m_nInterval++;
	}
}
//<=======================================
//ファイル読み込みを使用した生成処理
//<=======================================
C3DEnemy *C3DEnemy::ReadCreate(C3DEnemy *apEnemy[MAX_OBJECT])
{
	//必要以外の文字列読み込み用データ
	char aChar[INT_VALUE::MAX_CHAR] = { NULL };

	//何個目かの情報
	int nCntMax = 0;

	//ファイル情報
	FILE *pFile = fopen("data/TEXT/SetEnemy.txt", "r");

	//ファイルが開けたら
	if (pFile != NULL)
	{
		//ずっと繰り返す
		while (strcmp(aChar, "EndFile") != 0)
		{
			//空字を読み込む
			(void)fscanf(pFile, "%s", &aChar[0]);

			//ENEMY-SETという文字列が存在したら
			if (strcmp(aChar, "ENEMY-SET") == 0)
			{
				//もし中身がなければ
				if (apEnemy[nCntMax] == nullptr)
				{
					apEnemy[nCntMax] = new C3DEnemy;
				}
			
				//End-Setという文字を認識するまで繰り返す
				while (strcmp(aChar, "End-Set"))
				{
					//空字を読み込む
					(void)fscanf(pFile, "%s", &aChar[0]);

					//メモリ確保されていたら
					if (apEnemy[nCntMax] != nullptr)
					{
						//TYPEという文字列が存在したら
						if (strcmp(aChar, "TYPE") == 0)
						{
							//空字を読み込む
							(void)fscanf(pFile, "%s", &aChar[0]);

							//タイプを読み込む
							(void)fscanf(pFile, "%d", &apEnemy[nCntMax]->m_eType);

						}
						apEnemy[nCntMax]->Init();

						//POSという文字列が存在したら
						if (strcmp(aChar, "POS") == 0)
						{
							//空字を読み込む
							(void)fscanf(pFile, "%s", &aChar[0]);

							//位置を読み込む
							(void)fscanf(pFile, "%f", &apEnemy[nCntMax]->m_pos.x);
							(void)fscanf(pFile, "%f", &apEnemy[nCntMax]->m_pos.y);
							(void)fscanf(pFile, "%f", &apEnemy[nCntMax]->m_pos.z);

							//位置を代入
							apEnemy[nCntMax]->SetPosition(apEnemy[nCntMax]->m_pos);

							//前回の位置を保存しておく
							apEnemy[nCntMax]->m_OldPos = apEnemy[nCntMax]->m_pos;
						}
					}
					//
					apEnemy[nCntMax]->SetType3D(TYPE_3D::TYPE_ENEMY3D);
				}
				//数を増やす
				nCntMax++;
			}
		}
		//ファイルを閉じる
		fclose(pFile);

	}
	return *apEnemy;
}
//<=================================================
//
//<=================================================
C3DEnemy *C3DEnemy::RandCreate(C3DEnemy *apEnemy[MAX_OBJECT])
{
	int nRandType = INITIAL_INT;
	D3DXVECTOR3 rRandPos = INIT_VECTOR;

	//セットする数分回す
	for (int nCnt = 0; nCnt < m_nNumSet; nCnt++)
	{
		//
		apEnemy[nCnt] = new C3DEnemy;

		assert(apEnemy[nCnt] != nullptr);

		//最大の手前まで行っていれば
		if (nCnt == m_nNumSet - 1)
		{
			apEnemy[nCnt]->m_eType = TYPE::TYPE_ENEMY_HIGHSPEED;
		}
		//まだ最大の手前まで行っていなければ
		else
		{
			nRandType = Calculate::CalculeteRandInt(TYPE::TYPE_ENEMY_INVISIBLE,
				TYPE::TYPE_ENEMY_NORMAL);

			apEnemy[nCnt]->m_eType = (TYPE)nRandType;
		}

		apEnemy[nCnt]->Init();

		rRandPos = D3DXVECTOR3(Calculate::CalculateRandfloat(4000, -4000), 0.0f, Calculate::CalculateRandfloat(2500, -4000));

		//位置を代入
		apEnemy[nCnt]->SetPosition(rRandPos);

		//前回の位置を保存しておく
		apEnemy[nCnt]->m_OldPos = apEnemy[nCnt]->GetPosition();

		//
		apEnemy[nCnt]->SetType3D(TYPE_3D::TYPE_ENEMY3D);
	}

	return *apEnemy;
}
//<================================================
//
//<================================================
void C3DEnemy::CollidPlayer(void)
{
	//隠れ状態では無ければ
	if (m_pPlayer->GetState() != C3DPlayer::STATE_HIDE)
	{
		//当たっていたら
		if (Collision::CollidAll(m_pPlayer->GetPosition(), m_pPlayer->GetModel().vtxMax,
			m_pos, m_sModel.vtxMax, m_sModel.vtxMin))
		{
			DeathSound();
		}
	}
}
//<================================================
//
//<================================================
void C3DEnemy::DeathSound(void)
{
	//死亡ステートにする
	m_pPlayer->SetState(C3DPlayer::STATE_DEATH);

	//すべての音楽を止める
	CManager::GetSound()->StopSound();
	m_pSound->StopSound();

	//通常型だったら
	if (m_eType == TYPE::TYPE_ENEMY_NORMAL)
	{
		//音を鳴らす
		CManager::GetSound()->SetSE(1.2f, CSound::LABEL::LABEL_SE_DEATH0);
		CManager::GetSound()->PlaySound(CSound::LABEL::LABEL_SE_DEATH0);
		CResult::SetName(m_acFilename[m_eType]);
	}
	//透明型だったら
	else if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
	{
		//音を鳴らす
		CManager::GetSound()->SetSE(1.2f, CSound::LABEL::LABEL_SE_DEATE1);
		CManager::GetSound()->PlaySound(CSound::LABEL::LABEL_SE_DEATE1);
		CResult::SetName(m_acFilename[m_eType]);
	}
	//高速型だったら
	else if (m_eType == TYPE::TYPE_ENEMY_HIGHSPEED)
	{	
		//音を鳴らす
		CManager::GetSound()->SetSE(1.2f, CSound::LABEL::LABEL_SE_DEATE2);
		CManager::GetSound()->PlaySound(CSound::LABEL::LABEL_SE_DEATE2);
		CResult::SetName(m_acFilename[m_eType]);
	}
}