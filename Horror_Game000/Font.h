//<============================================
//DirectXでのフォント処理(Font.cpp)
//
//Author:kazuki watanabe
//<============================================
#ifndef _FONT_H_
#define _FONT_H_

#include "main.h"
#include "object.h"

//<********************************************
//フォントのクラス定義
//<********************************************
class CFont : public CObject
{

	//公に使用可能
public:

	//<===============================================
	//ここだけのマクロ定義
	//<===============================================
#define MAX_STRING	(5120)	//デバッグ表示の最大文字数

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_BLINK,
		TYPE_TIMER,
		TYPE_FADE,
		TYPE_MAX,
	};
	
	//コンストラクタ・デストラクタ
	CFont(int nPriority = 7);
	~CFont();

	//生成関数
	static CFont *Create(const RECT Rect, const UINT Width, const UINT Height,
		const int nWeight, const int nCharSet, const D3DXCOLOR col, TYPE Type, const char *aString,...);

	//生成関数
	static CFont *WithIntCreate(const RECT Rect, const UINT Width, const UINT Height,
		const int nWeight, const int nCharSet, const D3DXCOLOR col, TYPE Type, const char *aString,const int nValue);

	//オーバーライドされた関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Print(const char *aStr,...);
	static int GetNum(void) { return m_nNumAll; }

	//<===========================================
	//不要関数
	//<===========================================
	void SetVtx(void) { return; }
	CObject2D *GetObject2D(void) { return NULL; }

	//個人しか使えない
private:

	//メンバ変数
	LPD3DXFONT					m_pFont;					//
	RECT						m_Rect;						//文字の位置
	UINT						m_Height;					//
	UINT						m_Width;					//
	int							m_nWeight;					//文字の太さ
	int							m_nWaitTime;				//
	int							m_nCharSet;					//文字セット
	char						m_aStrDebug[MAX_STRING];	//文字列
	const char					*m_pString;
	D3DXCOLOR					m_Color;					//文字の色
	TYPE						m_Type;
	static int m_nNumAll;									//総数
	
	int m_nNum;								//時間の
	int m_nCntTime;							//経過時間
	RECT m_rDestRect;

	va_list m_args = nullptr;
	char m_aString[MAX_STRING] = {};
	char m_aSaveString[MAX_STRING] = {};
	int m_nLength = 0;
	int m_nStopLength = 0;

};

#endif
