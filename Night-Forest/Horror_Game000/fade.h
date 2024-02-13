//<==============================================
//フェード処理(fade.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _FADE_H_
#define _FADE_H_

#include "object2D.h"
#include "manager.h"

//<***********************************************
//
//<***********************************************
class CFade
{
public:

	//<=======================================
	//フェードタイプ列挙型
	//<=======================================
	enum TYPE
	{
		TYPE_FADE_NONE = 0,		//何もなし
		TYPE_FADE_OUT,			//フェードアウト
		TYPE_FADE_IN,			//フェードイン
		TYPE_MAX,
	};

	CFade();
	~CFade();

	static CFade *Create(void);

	HRESULT Init(void);
	void Uninit(void) {};
	void Update(void);
	void Draw(void) 
	{ 
		m_pObject2D->Draw();
	}
	void SetVtx(void);

	void SetFade(CScene::MODE modeNext);		
	D3DXCOLOR GetCol(void) { return m_Col; }	//色の取得
	TYPE GetType(void) {return m_eType;}		//タイプの取得

private:

	void SetFadeOut(void);
	void SetFadeIn(void);

	int m_nWaitTime;			//待機時間
	D3DXVECTOR2 m_rPos;			//位置
	D3DXCOLOR m_Col;			//色
	CScene::MODE m_ModeNext;	//次のモード
	TYPE m_eType;				//フェードタイプ
	CObject2D *m_pObject2D;		//オブジェクト2Dのポインタ
};


#endif
