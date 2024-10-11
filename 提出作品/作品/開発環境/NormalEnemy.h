//<======================================
//’ÊíŒ^‚Æ‚‘¬Œ^“G‚Ìˆ—(NormalEnemy.h)
//
//Author:Kazuki Watanabe
//<======================================
#ifndef _NORMAL_ENEMY_H_
#define _NORMAL_ENEMY_H_

#include "3DEnemy.h"

//<***************************************
//’ÊíŒ^“G‚ÌƒNƒ‰ƒX’è‹`
//<***************************************
class CNorEnemy : public C3DEnemy
{
public:

	//<=========================================
	//“GƒXƒe[ƒg‚Ì—ñ‹“Œ^
	//<=========================================
	enum STATE
	{
		STATE_NORMAL = 0,		//‰½‚à‚È‚¢ó‘Ô
		STATE_SEARCH,			//’Tõó‘Ô
		STATE_WAIT,				//‘Ò‹@ó‘Ô
		STATE_CHASE,			//’ÇÕó‘Ô
		STATE_MAX

	};

	CNorEnemy();
	~CNorEnemy();

	static CNorEnemy *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//ƒQƒbƒgŒn‚Ìˆ—
	STATE GetState(void) { return m_sState; }			//ƒXƒe[ƒg
	static int GetNum(void) { return m_nNumAll-1; }		//”

protected:

	void Movement(const CSound::LABEL MOANLabel,const CSound::LABEL FoundLabel);
	void SetSound(const CSound::LABEL Label, const int nMaxCount, const D3DXVECTOR3 rTargetPos);
	void SerachRot(const D3DXVECTOR3 rRandPos);

	STATE m_sState;			//ƒXƒe[ƒg

	int m_nSoundCount;		//‰¹‚ªo‚é‚Ü‚Å‚ÌƒJƒEƒ“ƒg
	int m_nSoundMax;		//‰¹‚ªo‚é‚Ü‚Å‚ÌÅ‘å’l
	int m_nInterval;		//U‚èŒü‚­‚Ü‚Å‚ÌŽžŠÔ
	float m_fSearchRad;		//’Tõ‰~

private:

	static int m_nNumAll;	//‘”
};

//<***************************************
//“§–¾Œ^“G‚ÌƒNƒ‰ƒX’è‹`
//<***************************************
class CInvEnemy : public CNorEnemy
{
public:

	static CInvEnemy *Create(void);

	CInvEnemy() {}
	~CInvEnemy() { m_nNumAll=0; }

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) { CNorEnemy::Draw(); }

	static int GetNum(void) { return m_nNumAll-1; }

private:

	static int m_nNumAll;	//‘”
	
};
#endif