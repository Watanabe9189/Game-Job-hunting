//<======================================
//敵管理の処理(EnemyManagement.cpp)
//
//Author:Kazuki Watanabe
//<======================================
#include "EnemyManagment.h"
#include "Item.h"
#include "game.h"

//<*************************************
//
//<*************************************
namespace
{
	const int MAX_ENEMY = 20;			//敵の最大数
}

//<=====================================
//コンストラクタ
//<=====================================
CEnemyManagement::CEnemyManagement()
{
	//値の初期化
	m_pFastEnemy = nullptr;
	m_pNorEnemy.clear();
	m_pInvEnemy.clear();

	m_bFastFlag = false;
	m_nSpawnTime = INITIAL_INT;
}
//<=====================================
//デストラクタ
//<=====================================
CEnemyManagement::~CEnemyManagement()
{

}
//<=====================================
//初期化処理
//<=====================================
void CEnemyManagement::Init()
{

}
//<=====================================
//終了処理
//<=====================================
void CEnemyManagement::Uninit()
{
	//高速型敵の破棄
	if (m_pFastEnemy) { m_pFastEnemy->Uninit(); m_pFastEnemy = nullptr; }

	//通常型敵の破棄
	for (unsigned int nCnt = 0; nCnt < m_pNorEnemy.size(); nCnt++)
	{
		if (m_pInvEnemy.at(nCnt))
		{
			m_pNorEnemy.at(nCnt)->Uninit();
			m_pNorEnemy.at(nCnt) = nullptr;
		}
	}

	//透明型敵の破棄
	for (unsigned int nCnt = 0; nCnt < m_pInvEnemy.size(); nCnt++)
	{
		if (m_pInvEnemy.at(nCnt))
		{
			m_pInvEnemy.at(nCnt)->Uninit();
			m_pInvEnemy.at(nCnt) = nullptr;
		}
	}
}
//<=====================================
//登場管理処理
//<=====================================
void CEnemyManagement::Appear(void)
{
	const int SPAWN_TIME_MAX = 150;

	//死亡していなければ
	if (CScene::GetGame()->Get3DPlayer()->GetState() != C3DPlayer::STATE_DEATH)
	{
		//合計する
		m_SumEnemy = CNorEnemy::GetNum() + CInvEnemy::GetNum();

		//一個目をゲットしていたら
		if (CItem::GetNumCollect() == 1
			&& !m_bFastFlag)
		{
			//フラグをオンにして高速型を登場させる
			m_bFastFlag = true;
			m_pFastEnemy = CFastEnemy::Create();
		}

		//時間に達していたら
		if (m_nSpawnTime >= SPAWN_TIME_MAX)
		{
			//初期化+通常型or透明型敵を召喚
			m_nSpawnTime = 0;
			Spawn();
		}
		//時間に行ってなかったら加算する
		else { m_nSpawnTime++; }
	}
}
//<=====================================
//敵スポーン処理
//<=====================================
void CEnemyManagement::Spawn(void)
{
	//もし最大数まで行っていなければ
	if (!(m_SumEnemy >= MAX_ENEMY))
	{
		//ランダム決定
		int nRand = Calculate::CalculeteRandInt(0, 1);

		//通常型だったら
		if (nRand = 0)
		{
			//サウンドセット
			CManager::GetSound()->PlaySoundWithVolume(CSound::LABEL::LABEL_SE_NOTICED1,1.0f); 
			m_pNorEnemy.insert(m_pNorEnemy.begin() + CNorEnemy::GetNum(), CNorEnemy::Create());
		}
		//透明型だったら
		else
		{
			//サウンドセット
			CManager::GetSound()->PlaySoundWithVolume(CSound::LABEL::LABEL_SE_NOTICED2, 1.0f);
			m_pInvEnemy.insert(m_pInvEnemy.begin() + CInvEnemy::GetNum(), CInvEnemy::Create());
		}
	}
}