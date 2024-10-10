//<======================================
//“GŠÇ—‚Ìˆ—(EnemyManagement.cpp)
//
//Author:Kazuki Watanabe
//<======================================
#include "EnemyManagment.h"
#include "Item.h"
#include "game.h"

//<*************************************
//–¼‘OéŒ¾
//<*************************************
namespace
{
	const int MAX_ENEMY = 15;			//“G‚ÌÅ‘å”
	const int SPAWN_TIME_MAX = 3000;	//ƒXƒ|[ƒ“‚Ü‚Å‚É‚©‚©‚éŠÔ‚ÌÅ‘å’l

	const int MAX_SPAWN_ENE = 4;		//Å‰‚©‚çƒ‰ƒ“ƒ_ƒ€‚Å¶¬‚·‚é“G‚Ì”
}

//<=====================================
//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//<=====================================
CEnemyManagement::CEnemyManagement()
{
	//’l‚Ì‰Šú‰»
	m_pFastEnemy = nullptr;
	m_pNorEnemy.clear();
	m_pInvEnemy.clear();

	m_bFastFlag = false;
	m_nSpawnTime = INITIAL_INT;
}
//<=====================================
//ƒfƒXƒgƒ‰ƒNƒ^
//<=====================================
CEnemyManagement::~CEnemyManagement()
{

}
//<=====================================
//‰Šú‰»ˆ—
//<=====================================
void CEnemyManagement::Init()
{
	//ƒ‰ƒ“ƒ_ƒ€Œˆ’è
	int nNum = Calculate::CalculeteRandInt(1, MAX_SPAWN_ENE);

	//¶¬‚·‚é“G‚Ì”‚ğİ’è
	for (int nCnt = 0; nCnt > nNum; nCnt++)
	{
		//ƒ‰ƒ“ƒ_ƒ€í—Ş
		int nRand = Calculate::CalculeteRandInt(0, 1);

		//’ÊíŒ^“G‚ğ¶¬‚·‚é
		if (nRand = 0){m_pNorEnemy.insert(m_pNorEnemy.begin() + CNorEnemy::GetNum(), CNorEnemy::Create());}

		//“§–¾Œ^“G‚ğ¶¬‚·‚é
		else { m_pInvEnemy.insert(m_pInvEnemy.begin() + CInvEnemy::GetNum(), CInvEnemy::Create()); }
	}
}
//<=====================================
//I—¹ˆ—
//<=====================================
void CEnemyManagement::Uninit()
{
	//‚‘¬Œ^“G‚Ì”jŠü
	if (m_pFastEnemy) { m_pFastEnemy->Uninit(); m_pFastEnemy = nullptr; }

	//’ÊíŒ^“G‚Ì”jŠü
	for (unsigned int nCnt = 0; nCnt < m_pNorEnemy.size(); nCnt++)
	{
		if (m_pNorEnemy.at(nCnt))
		{
			m_pNorEnemy.at(nCnt)->Uninit();
			m_pNorEnemy.at(nCnt) = nullptr;
		}
	}

	//“§–¾Œ^“G‚Ì”jŠü
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
//“oêŠÇ—ˆ—
//<=====================================
void CEnemyManagement::Appear(void)
{
	CManager::GetDebugProc()->Print("Œ»İ‚ÌƒXƒ|[ƒ“ŠÔ->%d",m_nSpawnTime);

	//ˆêŒÂ–Ú‚ğƒQƒbƒg‚µ‚Ä‚¢‚½‚ç
	if (CItem::GetNumCollect() == 1
		&& !m_bFastFlag)
	{
		//ƒtƒ‰ƒO‚ğƒIƒ“‚É‚µ‚Ä‚‘¬Œ^‚ğ“oê‚³‚¹‚é
		m_bFastFlag = true;
		m_pFastEnemy = CFastEnemy::Create();
	}

	//ŠÔ‚É’B‚µ‚Ä‚¢‚½‚ç
	if (m_nSpawnTime >= SPAWN_TIME_MAX)
	{
		//‰Šú‰»+’ÊíŒ^or“§–¾Œ^“G‚ğ¢Š«
		m_nSpawnTime = 0;
		m_pNorEnemy.insert(m_pNorEnemy.begin()+ CNorEnemy::GetNum(), CNorEnemy::Create());
		m_pInvEnemy.insert(m_pInvEnemy.begin() + CInvEnemy::GetNum(), CInvEnemy::Create());
	}
	//ŠÔ‚És‚Á‚Ä‚È‚©‚Á‚½‚ç‰ÁZ‚·‚é
	else { m_nSpawnTime++; }

}