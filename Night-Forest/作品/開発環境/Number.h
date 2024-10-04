//<===================================
//番号関連の処理(Number.h)
//
//Author:kazuki watanabe
//<===================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "object2D.h"

//<***********************************
//番号のクラス定義
//<***********************************
class CNumber : public CObject2D
{

public:

//マクロ定義
#define NUMBER_PRI	(6)		//番号の優先順位

	CNumber(int nPriority = NUMBER_PRI);
	~CNumber();

	static CNumber *Create(const D3DXVECTOR2 rPos = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2 rSize = D3DXVECTOR2(0.0f, 0.0f),const LPDIRECT3DTEXTURE9 pTexture = nullptr);

	HRESULT Init(const D3DXVECTOR2 rPos = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2 rSize = D3DXVECTOR2(0.0f, 0.0f), const LPDIRECT3DTEXTURE9 pTexture = nullptr);
	void Uninit(void);
	void Update(void);
	void Draw(void) {}
	void SetVtx(void);

	//<===============================================================
	//GetSet系の関数
	//<===============================================================
	void SetNum(const int *nNum) { m_nNum = *nNum; }	//番号の数設定
	int GetNum(void) const { return m_nNum; }			//番号の数取得 

private:


	CObject2D *m_pObject2D;

	int m_nNum;											//番号の数

};
#endif