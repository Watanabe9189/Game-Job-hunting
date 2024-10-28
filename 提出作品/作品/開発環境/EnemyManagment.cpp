//<======================================
//敵管理の処理(EnemyManagement.cpp)
//
//Author:Kazuki Watanabe
//<======================================
#include "EnemyManagment.h"
#include "Item.h"
#include "game.h"

//<*************************************
//名前宣言
//<*************************************
namespace
{
	const int MAX_ENEMY = 20;			//敵の最大数

//デバッグ
#if _DEBUG
	const int SPAWN_TIME_MAX = 5;	//スポーンまでにかかる時間の最大値
//リリース
#else
	const int SPAWN_TIME_MAX = 3000;	//スポーンまでにかかる時間の最大値
#endif

	const int MAX_SPAWN_ENE = 4;		//最初からランダムで生成する敵の数
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
	//ランダム決定
	int nNum = Calculate::CalculeteRandInt(MAX_SPAWN_ENE,1);

	//生成する敵の数を設定
	for (int nCnt = 0; nCnt < nNum; ++nCnt)
	{
		//ランダム種類
		int nRand = Calculate::CalculeteRandInt(1, 0);

		//通常型敵を生成する
		if (nRand == 0){m_pNorEnemy.insert(m_pNorEnemy.begin() + CNorEnemy::GetNum(), CNorEnemy::Create());}

		//透明型敵を生成する
		else{ m_pInvEnemy.insert(m_pInvEnemy.begin() + CInvEnemy::GetNum(), CInvEnemy::Create()); }
	}
}
//<=====================================
//終了処理
//<=====================================
void CEnemyManagement::Uninit()
{
	//高速型敵の破棄
	if (m_pFastEnemy) { m_pFastEnemy->Uninit(); m_pFastEnemy = nullptr; }

	//通常型敵の破棄
	for (unsigned int nCnt = 0, size = m_pNorEnemy.size(); nCnt != size; ++nCnt)
	{
		if (m_pNorEnemy.at(nCnt))
		{
			m_pNorEnemy.at(nCnt)->Uninit();
			m_pNorEnemy.at(nCnt) = nullptr;
		}
	}
	m_pNorEnemy.clear();

	//透明型敵の破棄
	for (unsigned int nCnt = 0,size = m_pInvEnemy.size(); nCnt != size; ++nCnt)
	{
		if (m_pInvEnemy.at(nCnt))
		{
			m_pInvEnemy.at(nCnt)->Uninit();
			m_pInvEnemy.at(nCnt) = nullptr;
		}
	}
	m_pInvEnemy.clear();
}
//<=====================================
//登場管理処理
//<=====================================
void CEnemyManagement::Appear(void)
{
	CManager::GetDebugProc()->Print("現在のスポーン時間->%d",m_nSpawnTime);

	m_nNumEnemy = CNorEnemy::GetNum() + CInvEnemy::GetNum();

	//一個目をゲットしていたら
	if (CItem::GetNumCollect() == 1
		&& !m_bFastFlag)
	{
		//フラグをオンにして高速型を登場させる
		m_bFastFlag = true;
		m_pFastEnemy = CFastEnemy::Create();
	}
	//もし最大数まで行っていなければ
	if (!(m_nNumEnemy >= MAX_ENEMY))
	{
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
//登場処理
//<=====================================
void CEnemyManagement::Spawn(void)
{
	//ランダム種類
	int nRand = Calculate::CalculeteRandInt(1, 0);

	//通常型敵を生成する
	if (nRand == 0) { m_pNorEnemy.insert(m_pNorEnemy.begin() + CNorEnemy::GetNum(), CNorEnemy::Create()); }

	//透明型敵を生成する
	else{ m_pInvEnemy.insert(m_pInvEnemy.begin() + CInvEnemy::GetNum(), CInvEnemy::Create()); }
}