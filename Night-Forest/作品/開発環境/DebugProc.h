//==========================================================
//
//デバッグ表示処理 [debugproc.h]
//Author Ibuki Okusada
//
//==========================================================
#ifndef _DEBUGPROC_H_		//このマクロが定義されていない場合
#define _DEBUGPROC_H_

#include "main.h"

//**********************************************************
//プロトタイプ宣言
//**********************************************************
class CDebug
{
public:


#define MAX_DEBUGSTRING	(5120)	//デバッグ表示の最大文字数


	//**********************************************************
	//スイッチ列挙型の定義
	//**********************************************************
	typedef enum
	{
		DEBUGTYPE_OFF = 0,	//対象機能が動作していない状態
		DEBUGTYPE_ON,		//対象機能が動作している状態
		DEBUGTYPE_MAX

	}DEBUGTYPE;

	CDebug();
	~CDebug();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Print(const char *fmt, ...);
	static void SetManual(void);

private:

	static LPD3DXFONT			m_pFont;						//フォントへのポインタ
	char						m_aStrDebug[MAX_DEBUGSTRING];	//デバッグ表示用の文字列
	bool						m_bDispDebug;					//デバッグ表示のON/OFF
	static const char*			m_acNowScreen[];				//ファイル名

};

#endif