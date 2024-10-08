//<======================================
//敵管理の処理(EnemyManagement.h)
//
//Author:Kazuki Watanabe
//<======================================
#ifndef _ENEMY_MANAGEMENT_H_
#define _ENEMY_MANAGEMENT_H_

#include "NormalEnemy.h"
#include "FastEnemy.h"

//<**************************************
//クラス定義
//<**************************************
class CEnemyManagement
{
//公に公開
public:



	//コンスト・デストラ
	CEnemyManagement();
	~CEnemyManagement();

	void Init();									//初期化
	void Uninit();									//終了
	void Appear(void);								//登場管理処理

	//ここだけしか使わない
private:

	void Spawn(void);

	CFastEnemy* m_pFastEnemy;						//一体だけの高速型敵
	std::vector<CNorEnemy*>m_pNorEnemy;				//複数対用意する用の通常型敵
	std::vector<CInvEnemy*>m_pInvEnemy;				//複数対用意する用の透明型敵

	bool m_bFastFlag;								//高速型敵のフラグ

	int m_nSpawnTime;								//通常型・透明型が出てくるまでの時間

	int m_SumEnemy;									//敵の合計数
};

#endif

