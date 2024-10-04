//<======================================================
//ステンシル処理(Stencil.h)
//
//Author:kazuki watanabe
//<======================================================
#ifndef _STENCIL_H_
#define _STENCIL_H_

#include "main.h"

//名前宣言
namespace STENCIL_VALUE
{
	static const int STENCIL_FAIL = -1;				//ステンシルテストに失敗する値
	static const int STENCIL_SUCCEES = 4;			//ステンシルテストに成功する値
}

//<******************************************************
//名前宣言
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

	bool m_bUse;			//ステンシルを使用するかどうか
	int m_nStencil;			//ステンシル値
};


#endif
