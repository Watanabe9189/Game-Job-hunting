//<======================================
//高速型敵の処理(FastEnemy.cpp)
//
//Author:Kazuki Watanabe
//<======================================
#include "FastEnemy.h"
#include "Item.h"

//<**************************************************************
//名前宣言
//<**************************************************************
namespace
{
	const float ALPHA_VALUE_HIGH = 0.005f;	//高速型の透明度の値
	const float ROTATE_VALUE = 0.1f;		//回転値

	const int	MAX_INTERVAL = 100;		//間隔の最大値
}

//<================================
//コンストラクタ
//<================================
CFastEnemy::CFastEnemy()
{
	//値のクリア
	m_sFastState = FAST_STATE::FAST_STATE_WAIT;
	m_rTelportPos = INIT_VECTOR;
	m_nInterval=INITIAL_INT;
	m_nRandInter = INITIAL_INT;
}
//<================================
//
//<================================
CFastEnemy *CFastEnemy::Create(void)
{
	//メモリ確保+中身チェック
	CFastEnemy *pFast = new CFastEnemy;
	assert(pFast);

	//初期化処理と値の代入
	pFast->Init();
	pFast->SetPosition(INIT_VECTOR);
	pFast->m_nInterval = pFast->m_nRandInter;
	pFast->m_OldPos = pFast->GetPosition();

	return pFast;
}
//<================================
//初期化処理
//<================================
HRESULT CFastEnemy::Init(void)
{
	//初期化とモデルチェック
	C3DEnemy::Init();
	m_sModel = BindModel("data/MODEL/Monster001.x", true);

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

	//インターバルを設定
	m_nRandInter = Calculate::CalculeteRandInt(3500, 1000);

	return S_OK;
}
//<================================
//更新処理
//<================================
void CFastEnemy::Update(void)
{
	C3DEnemy::Update();

	m_pos = GetPosition();
	m_rot = GetRotation();
	m_move = GetMove();
	if (m_pPlayer)
	{
		HighSpeedMove();
	}

	//ベクトルの三要素の設定
	SetVector3(m_pos, m_rot, m_move);
}
//<=======================================
//動き
//<=======================================
void CFastEnemy::HighSpeedMove(void)
{
	const float HIGHSPEED_VALUE = 0.085f;							//高速型の移動量
	const int nFixedInter = MAX_INTERVAL / CItem::GetNumCollect();	//固定インターバル

	//目的向き
	D3DXVECTOR3 rRotDest = Calculate::CalculateDest(m_pos, m_rDestPos);

	//高速型のステートによって行動を変化させる
	switch (m_sFastState)
	{
		//移動モードだったら
	case FAST_STATE::FAST_STATE_MOVE:

		m_rot.y = Calculate::RotateToDest(m_rot.y, rRotDest, ROTATE_VALUE);

		//プレイヤーの位置を目的地とする
		SetDest(m_pPlayer->GetPosition());
		m_fMoveValue = HIGHSPEED_VALUE;

		//プレイヤーが隠れていれば
		if (m_pPlayer->GetState() == C3DPlayer::STATE_HIDE)
		{
			//間隔を設定する
			m_nInterval = nFixedInter;
		}

		//間隔が一定値を超えていたら
		if (m_nInterval >= nFixedInter)
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

		CollidPlayer(CSound::LABEL::LABEL_SE_DEATE2);

		break;

		//待機状態だったら
	case FAST_STATE::FAST_STATE_INTERVAL:

		//向き
		m_rot.y = Calculate::RotateToDest(m_rot.y, rRotDest, ROTATE_VALUE);

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
			m_nRandInter = Calculate::CalculeteRandInt(4000, 1000);
		}

		//間隔が一定値を超えていたら
		if (m_nInterval >= nFixedInter)
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

		break;

		//待機状態だったら
	case FAST_STATE::FAST_STATE_WAIT:

		m_fMoveValue = INITIAL_FLOAT;
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

		m_sModel.pMat = Color::AlphaChangeMaterial(m_sModel.pMat, -ALPHA_VALUE_HIGH, m_sModel.dwNumMat);

		break;
	}

}