//<======================================================
//�X�e���V������(Stencil.h)
//
//Author:kazuki watanabe
//<======================================================
#ifndef _STENCIL_H_
#define _STENCIL_H_

#include "main.h"

//���O�錾
namespace STENCIL_VALUE
{
	static const int STENCIL_FAIL = -1;				//�X�e���V���e�X�g�Ɏ��s����l
	static const int STENCIL_SUCCEES = 4;			//�X�e���V���e�X�g�ɐ�������l
}

//<******************************************************
//���O�錾
//<******************************************************
class CStencil
{
public:

	CStencil();
	~CStencil();

	static CStencil *Create(const bool bUse,const int nStencil=0);

	void Init(void);
	void Uninit(void);

	void DrawStencilTest(void);

	void Setting(const bool bUse, const int nStencil);

private:

	bool m_bUse;			//�X�e���V�����g�p���邩�ǂ���
	int m_nStencil;			//�X�e���V���l
};


#endif
