//<================================================
//2Dパーティクル処理(2DParticle.h)
//
//Author:kazuki watanabe
//<================================================
#ifndef _3DPARTICLE_H_
#define _3DPARTICLE_H_

#include "main.h"
#include "object.h"

class C3DParticle : public CObject
{
public:

	//<================================
	//タイプ
	//<================================
	enum TYPE
	{
		TYPE_TEST = 0,
		TYPE_EXPLOSION,
		TYPE_MAX
	};

	C3DParticle();
	~C3DParticle();

	//オーバーライドされた関数
	HRESULT Init(void) override;
	void Uninit(void)override;
	void Update(void)override;

	static C3DParticle *Create(const D3DXVECTOR3 rPos, const D3DXCOLOR rCol, const TYPE eType);

	//<===========================================
	//不要関数
	//<===========================================
	void Draw(void)override {};
	void SetVtx(void) { return; }
	CObject2D *GetObject2D(void) { return NULL; }


private:

	void Test(void);

	D3DXVECTOR3 m_rPos;
	D3DXVECTOR3 m_rMove;
	D3DXCOLOR m_rCol;
	int m_nLife;
	TYPE m_eType;

	bool m_bDisp;

};

#endif
