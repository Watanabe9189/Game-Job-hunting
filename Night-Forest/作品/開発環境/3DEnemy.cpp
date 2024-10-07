//<============================================
//3Dエネミー処理(3DEnemy.cpp)
//
//Author:kazuki watanabe
//<============================================
#include "3DEnemy.h"
#include "game.h"
#include "Result.h"
//<*******************************************
//静的メンバ変数の宣言
//<*******************************************
//テクスチャ関
//<=======================================
//3Dエネミーのコンストラクタ
//<=======================================
C3DEnemy::C3DEnemy(int nPriority)
{

	//値のクリア
	m_pos = INIT_VECTOR;
	m_rDestPos = INIT_VECTOR;
	m_rot = INIT_VECTOR;
	m_move = INIT_VECTOR;
	m_fMoveValue = INITIAL_FLOAT;

	m_fFrontDest = INIT_VECTOR;
	m_fBackDest = INIT_VECTOR;

	m_sModel = {};

	m_pPlayer = nullptr;
	m_pSound = nullptr;
}
//<=======================================
//3Dエネミーのデストラクタ
//<=======================================
C3DEnemy::~C3DEnemy()
{

}
//<=======================================
//3Dエネミーの初期化処理
//<=======================================
HRESULT C3DEnemy::Init(void)
{
	//モードがゲームの時のみ
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		//音声の生成
		m_pSound = CSound::Create();

		assert(m_pSound );
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
	if (m_pSound )
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

			//移動する
			m_move.x = (m_rDestPos.x - m_pos.x - m_move.x)*m_fMoveValue;//X軸
			m_move.z = (m_rDestPos.z - m_pos.z - m_move.z)*m_fMoveValue;//Z軸

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
//<================================================
//プレイヤーとの当たり判定
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
//プレイヤーが死んだ際の音処理
//<================================================
void C3DEnemy::DeathSound(void)
{
	//死亡ステートにする
	m_pPlayer->SetState(C3DPlayer::STATE_DEATH);

	//すべての音楽を止める
	CManager::GetSound()->StopSound();
	m_pSound->StopSound();

	////通常型だったら
	//if (m_eType == TYPE::TYPE_ENEMY_NORMAL)
	//{
	//	//音を鳴らす
	//	CManager::GetSound()->SetSE(1.2f, CSound::LABEL::LABEL_SE_DEATH0);
	//	CManager::GetSound()->PlaySound(CSound::LABEL::LABEL_SE_DEATH0);
	//	CResult::SetName(m_acFilename[m_eType]);
	//}
	////透明型だったら
	//else if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
	//{
	//	//音を鳴らす
	//	CManager::GetSound()->SetSE(1.2f, CSound::LABEL::LABEL_SE_DEATE1);
	//	CManager::GetSound()->PlaySound(CSound::LABEL::LABEL_SE_DEATE1);
	//	CResult::SetName(m_acFilename[m_eType]);
	//}
	////高速型だったら
	//else if (m_eType == TYPE::TYPE_ENEMY_HIGHSPEED)
	//{
	//	//音を鳴らす
	//	CManager::GetSound()->SetSE(1.2f, CSound::LABEL::LABEL_SE_DEATE2);
	//	CManager::GetSound()->PlaySound(CSound::LABEL::LABEL_SE_DEATE2);
	//	CResult::SetName(m_acFilename[m_eType]);
	//}
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