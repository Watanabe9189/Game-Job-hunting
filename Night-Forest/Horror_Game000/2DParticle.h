//<================================================
//2D�p�[�e�B�N������(2DParticle.h)
//
//Author:kazuki watanabe
//<================================================
#ifndef _2DPARTICLE_H_
#define _2DPARTICLE_H_

#include "main.h"
#include "object.h"

class C2DParticle : public CObject
{
public:

	//<================================
	//�^�C�v
	//<================================
	enum TYPE
	{
		TYPE_TEST = 0,
		TYPE_EXPLOSION,
		TYPE_MAX
	};

	C2DParticle();
	~C2DParticle();

	//�I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Uninit(void)override;
	void Update(void)override;

	static C2DParticle *Create(const D3DXVECTOR2 rPos, const D3DXCOLOR rCol, const TYPE eType);

	//<===========================================
	//�s�v�֐�
	//<===========================================
	void Draw(void)override {};
	void SetVtx(void) { return; }
	CObject2D *GetObject2D(void) { return NULL; }


private:

	void Test(void);

	D3DXVECTOR2 m_rPos;
	D3DXCOLOR m_rCol;
	int m_nLife;
	TYPE m_eType;

	bool m_bDisp;

};

#endif
