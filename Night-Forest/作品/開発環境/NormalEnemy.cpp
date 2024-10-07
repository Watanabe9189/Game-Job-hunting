//<======================================
//通常型と高速型敵の処理(NormalEnemy.cpp)
//
//Author:Kazuki Watanabe
//<======================================
#include "NormalEnemy.h"

//<**************************************************************
//名前宣言
//<**************************************************************
namespace
{
	const float ALPHA_VALUE = 0.08f;		//透明度の値
	const float ALPHA_VALUE_HIGH = 0.005f;	//高速型の透明度の値
	const float ROTATE_VALUE = 0.1f;		//回転値
}
//<**************************************************************
//静的メンバ変数
//<**************************************************************
int CNorEnemy::m_nNumAll = NULL;			//通常型敵の数
int CInvEnemy::m_nNumAll = NULL;			//透明型敵の数
//<================================
//通常型敵のコンストラクタ
//<================================
CNorEnemy::CNorEnemy()
{
	//値のクリア
	m_sState = STATE::STATE_SEARCH;

	m_nSoundCount = INITIAL_INT;
	m_nSoundMax = INITIAL_INT;
	m_nInterval = INITIAL_INT;
	m_fSearchRad = INITIAL_FLOAT;
}
//<================================
//通常型敵のデストラクタ
//<================================
CNorEnemy::~CNorEnemy()
{
	
}
//<================================
//通常型敵の生成処理
//<================================
CNorEnemy *CNorEnemy::Create(void)
{
	//総数追加と初期化
	m_nNumAll++;
	CNorEnemy *pNorEnemy = new CNorEnemy;
	D3DXVECTOR3 rRandDest = Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), 
		D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false);

	//チェック
	assert(pNorEnemy);

	//初期化+位置設定
	pNorEnemy->Init();
	pNorEnemy->SetPosition(rRandDest);
	pNorEnemy->m_OldPos = pNorEnemy->GetPosition();

	return pNorEnemy;
}
//<================================
//通常型敵の初期化処理
//<================================
HRESULT CNorEnemy::Init(void)
{
	const float RADIUSE_VALUE = 650.0f;	//半径の値

	SetDest();

	m_fSearchRad = RADIUSE_VALUE;

	m_nSoundMax = Calculate::CalculeteRandInt(200, 100);

	m_sModel = BindModel("data/MODEL/Monster000.x", true);

	C3DEnemy::Init();

	return S_OK;
}
//<================================
//通常型敵の終了処理
//<================================
void CNorEnemy::Uninit(void)
{
	C3DEnemy::Uninit();
	m_nNumAll--;
}
//<================================
//通常型敵の更新処理
//<================================
void CNorEnemy::Update(void)
{
	C3DEnemy::Update();

	m_pos = GetPosition();
	m_rot = GetRotation();
	m_move = GetMove();

	CollidPlayer();
	Movement();

	//ベクトルの三要素の設定
	SetVector3(m_pos, m_rot, m_move);
}
//<================================
//通常型敵の描画処理
//<================================
void CNorEnemy::Draw(void)
{
	////モードがゲームの時のみ
	//if (CManager::GetMode() == CScene::MODE_GAME)
	//{
	//	//プレイヤー中身チェック&&近づいていたらまたは高速型だったら
	//	if (m_pPlayer != nullptr
	//		&&BoolDis(m_pos, m_pPlayer->GetPosition()))
	//	{
			CXObject::Draw();
	//	}
	//}
}
//<================================
//行動処理
//<================================
void CNorEnemy::Movement(void)
{
	const float SEARCH_MOVE = 0.0045f;	//探索している時の移動量
	const float CHASE_VALUE = 0.012f;	//追跡している時の移動値

	//向きの目的地
	D3DXVECTOR3 rRotDest = Calculate::CalculateDest(m_pos, m_rDestPos);

	//距離を計算する(その位置-目的とする位置)
	m_rDis = Calculate::CalculateDest(m_pos, m_pPlayer->GetPosition());

	//2000まで生成し、1000を引く
	D3DXVECTOR3 rRandDest = Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false);

	//サウンドセット
	SetSound(CSound::LABEL_SE_MOAN0, m_nSoundMax, m_pPlayer->GetPosition());

	//追跡状態だったら
	if (m_sState == STATE::STATE_CHASE)
	{
		//目的地をプレイヤーに設定して追跡
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
	}
	//探索モードだったら
	else if (m_sState == STATE_SEARCH)
	{
		//探索時の移動値に設定
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
		//プレイヤーが隠れていなければ
		if (m_pPlayer->GetState() != C3DPlayer::STATE_HIDE)
		{
			//プレイヤーとの距離が近かったら
			if (m_rDis.x <= m_fSearchRad
				&& !(-m_rDis.x >= m_fSearchRad)
				&& m_rDis.z <= m_fSearchRad
				&& !(-m_rDis.z >= m_fSearchRad))
			{
				//サウンドセット
				m_pSound->PlaySoundWithVolume(CSound::LABEL_SE_NOTICED1, 2.0f);

				//追跡モードにする
				m_sState = STATE_CHASE;
			}
		}
	}
}
//<=======================================
//のサウンド設定
//<=======================================
void CNorEnemy::SetSound(const CSound::LABEL Label, const int nMaxCount, const D3DXVECTOR3 rTargetPos)
{
	//最大カウントに行ったら
	if (m_nSoundCount >= nMaxCount)
	{
		//サウンドを流す
		m_pSound->PlaySoundWithDis(Label, m_pos, rTargetPos);
		m_nSoundCount = 0;
	}
	//カウントする
	else{m_nSoundCount++;}
}
//<=======================================
//見失った時の見渡し処理
//<=======================================
void CNorEnemy::SerachRot(const D3DXVECTOR3 rRandPos)
{
	const int ROTATE_INTERVAL[2] = { 150,350 };		//方向を向くまでのインターバル
	const int INTER_MAX = 500;						//インターバルまでの時間の最大値
	const float ROTATE_VALUE = 0.045f;				//向く速さ

	m_fMoveValue = 0.0f;

	//最大インターバルまで行っていたら
	if (m_nInterval >= INTER_MAX)
	{
		//捜索モードに移行させる
		m_sState = STATE_SEARCH;
		SetDest(rRandPos);
		m_nInterval = 0;
	}
	//それ以外の場合
	else
	{
		m_nInterval++;

		//一番目のインターバルを超えている&&二番目のインターバルを超えていない場合
		if (m_nInterval >= ROTATE_INTERVAL[0]
			&& !(m_nInterval >= ROTATE_INTERVAL[1]))
		{
			m_rot.y += ROTATE_VALUE;
		}
		//二番目のインターバルを超えている場合
		else if (m_nInterval >= ROTATE_INTERVAL[1])
		{
			m_rot.y -= ROTATE_VALUE;
		}
	}
}
//<=======================================
//透明型敵の生成処理
//<=======================================
CInvEnemy *CInvEnemy::Create(void)
{
	//総数追加と初期化
	m_nNumAll++;
	CInvEnemy * pInvEnemy = new CInvEnemy;
	D3DXVECTOR3 rRandDest = Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), 
		D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false);

	//中身チェック
	assert(pInvEnemy);

	//初期化+位置設定
	pInvEnemy->Init();
	pInvEnemy->SetPosition(rRandDest);
	pInvEnemy->m_OldPos = pInvEnemy->GetPosition();

	return pInvEnemy;
}
//<=======================================
//透明型敵の初期化処理
//<=======================================
HRESULT CInvEnemy::Init(void)
{
	//初期化とモデルセット
	CNorEnemy::Init();
	m_sModel = BindModel("data/MODEL/Monster002.x", true);

	//モードがゲームの時のみ
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		//頂点数分繰り返し
		for (int nCntMaxMat = 0; nCntMaxMat < (int)m_sModel.dwNumMat; nCntMaxMat++)
		{
			//初期の透明度を透明色にする
			m_sModel.pMat[nCntMaxMat].MatD3D.Diffuse.a = COLOR_VALUE::ALPHA_CLEANNESS;
			m_sModel.pMat[nCntMaxMat].MatD3D.Ambient.a = COLOR_VALUE::ALPHA_CLEANNESS;
		}
	}

	return S_OK;
}
//<=======================================
//透明型敵の終了処理
//<=======================================
void CInvEnemy::Uninit(void)
{
	//終了する
	m_nNumAll--;
	C3DEnemy::Uninit();
}
//<=======================================
//透明型敵の更新処理
//<=======================================
void CInvEnemy::Update(void)
{
	CNorEnemy::Update();

	//サウンドセット
	SetSound(CSound::LABEL_SE_MOAN1, m_nSoundMax, m_pPlayer->GetPosition());

	//追跡状態だったら
	if (m_sState == STATE::STATE_CHASE)
	{
		//姿を現す
		m_sModel.pMat = Color::AlphaChangeMaterial(m_sModel.pMat, ALPHA_VALUE, m_sModel.dwNumMat);
	}
	//探索モードだったら
	else if (m_sState == STATE_SEARCH)
	{
		//プレイヤーが隠れていなければ
		if (m_pPlayer->GetState() != C3DPlayer::STATE_HIDE)
		{
			//プレイヤーとの距離が近かったら
			if (m_rDis.x <= m_fSearchRad
				&& !(-m_rDis.x >= m_fSearchRad)
				&& m_rDis.z <= m_fSearchRad
				&& !(-m_rDis.z >= m_fSearchRad))
			{
				//サウンドを流す
				m_pSound->PlaySoundWithVolume(CSound::LABEL_SE_NOTICED2, 2.0f);
			}
		}

		//透明化する
		m_sModel.pMat = Color::AlphaChangeMaterial(m_sModel.pMat, -ALPHA_VALUE_HIGH, m_sModel.dwNumMat);
	}

}