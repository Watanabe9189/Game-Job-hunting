//<======================================
//“GŠÇ—‚Ìˆ—(EnemyManagement.cpp)
//
//Author:Kazuki Watanabe
//<======================================
#include "EnemyManagment.h"
#include "Item.h"

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
		if (m_pInvEnemy.at(nCnt))
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
	const int SPAWN_TIME_MAX = 150;

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