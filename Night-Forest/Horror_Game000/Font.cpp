//<============================================
//DirectXでのフォント処理(Font.cpp)
//
//Author:kazuki watanabe
//<============================================
#include "Font.h"
#include "manager.h"

//<****************************************************
//マクロ定義
//<****************************************************
#define MAX_FLOATNUM	(2)		//小数点以下の表示桁数

//<****************************************************
//静的メンバ変数宣言
//<****************************************************
int CFont::m_nNumAll = NULL;									//数

//<====================================================
//フォントのコンストラクタ
//<====================================================
CFont::CFont(int nPriority)
{
	m_nNumAll++;

	//値の初期化
	m_pFont = nullptr;
	m_Rect = { NULL, NULL, NULL, NULL };
	memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));
	m_nWeight = FW_DONTCARE;
	m_Height = NULL;
	m_Width = NULL;
	m_nWaitTime = NULL;
	m_Color = INIT_COL;
	m_nCharSet = SHIFTJIS_CHARSET;
	m_Type = TYPE_NONE;
	m_pString = nullptr;
	m_rDestRect = { NULL, NULL, NULL, NULL };
	
	m_nNum = INITIAL_INT;								//時間の
	m_nCntTime = INITIAL_INT;							//経過時間
}
//<====================================================
//フォントのデストラクタ
//<====================================================
CFont::~CFont()
{
	m_nNumAll--;
}
//<====================================================
//フォントの生成処理
//<====================================================
CFont *CFont::Create(const RECT Rect, const UINT Width,const UINT Height,
	const int nWeight,const int nCharSet, 
	const D3DXCOLOR col, TYPE Type, const char *aString,...)
{
	//生成用のオブジェクト
	CFont *PFont = new CFont;

	assert(PFont != nullptr);

	//<*********************************
	//情報設定処理
	//<*********************************
	PFont->m_Rect = Rect;				//四角形の情報

	PFont->m_Height = Height;			//文字の高さ
	PFont->m_Width = Width;				//文字の幅
	PFont->m_nWeight = nWeight;			//文字の太さ


	//<*********************************
	//情報設定処理
	//<*********************************
	PFont->m_nCharSet = nCharSet;		//文字セット
	PFont->m_Color = col;				//色
	PFont->m_Type = Type;				//タイプ設定
	PFont->m_pString = aString;
	PFont->Print(aString);					//文字判別

	assert(SUCCEEDED(PFont->Init()));

	return PFont;
}
//<====================================================
//Int引数のフォントの生成処理
//<====================================================
CFont *CFont::WithIntCreate(const RECT Rect, const UINT Width, const UINT Height,
	const int nWeight, const int nCharSet, const D3DXCOLOR col, TYPE Type, const char *aString, const int nValue)
{
	//生成用のオブジェクト
	CFont *PFont = new CFont;

	assert(PFont != nullptr);

	//<*********************************
	//情報設定処理
	//<*********************************
	PFont->m_Rect = Rect;				//四角形の情報
	PFont->m_Height = Height;			//文字の高さ
	PFont->m_Width = Width;				//文字の幅
	PFont->m_nWeight = nWeight;			//文字の太さ


										//<*********************************
										//情報設定処理
										//<*********************************
	PFont->m_nCharSet = nCharSet;		//文字セット
	PFont->m_Color = col;				//色
	PFont->m_Type = Type;				//タイプ設定

	PFont->m_pString = aString;
	PFont->Print(aString,nValue);					//文字判別


	assert(SUCCEEDED(PFont->Init()));
	
	return PFont;
}
//<====================================================
//フォントの初期化処理
//<====================================================
HRESULT CFont::Init(void)
{
	//デバッグ表示用フォントの生成
	if ((D3DXCreateFont(CManager::GetRenderer()->GetDevice()
		, m_Height, m_Width, m_nWeight, D3DX_DEFAULT, FALSE, m_nCharSet,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont))!= S_OK)
	{
		return E_FAIL;
	}

	return S_OK;
}
//<====================================================
//
//<====================================================
void CFont::Uninit(void)
{
	Release();

	//フォントの破棄
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}

	//デバッグ表示情報のクリア
	memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));
}
//<====================================================
//フォントの更新処理
//<====================================================
void CFont::Update(void)
{
	//点滅タイプだったら
	if (m_Type == TYPE::TYPE_BLINK)
	{
		//ここでしか使わないローカル変数の宣言
		const int MAX_WAIT[2] = { 100,200 };	//待機時間の最大値[2個]
		const float VALUE_COL = 0.05f;			//色を変更する値

		//待機時間を増やす
		m_nWaitTime++;

		//もし100秒を超えている&&200秒を超えていなければ
		if (m_nWaitTime >= MAX_WAIT[0]&&!(m_nWaitTime >= MAX_WAIT[1]))
		{
			//透明度を減らす
			m_Color.a -= VALUE_COL;

			//その値を下回りそうだったら
			if (m_Color.a <= 0.3f)
			{
				//その値にする
				m_Color.a = 0.3f;
			}
		}
		//もし200秒を超えていたら
		if (m_nWaitTime >= MAX_WAIT[1])
		{
			m_nWaitTime = MAX_WAIT[1];

			//透明度を増やす
			m_Color.a += VALUE_COL;

			//色が最大を超えそうだったら
			if (m_Color.a >= COLOR_VALUE::ALPHA_OPACITY)
			{
				//最大値にする
				m_Color.a = COLOR_VALUE::ALPHA_OPACITY;

				//リセットする
				m_nWaitTime = INITIAL_INT;
			}

		}	
	}
	//フェードタイプだったら
	else if (m_Type == TYPE::TYPE_FADE)
	{
		//ここでしか使わないローカル変数の宣言
		const int MAX_WAIT = 200;			//待機時間の最大値
		const float VALUE_DECRE = 0.005f;	//減らしていく値の量

		//透明になっていなければ
		if (!(m_Color.a <= 0.0f))
		{
			//待機時間を増やす
			m_nWaitTime++;

			//その時間になったら
			if (m_nWaitTime >= MAX_WAIT)
			{
				//透明にしていく
				m_Color.a -= 0.005f;

				//透明より下になりそうだったら
				if (m_Color.a <= COLOR_VALUE::ALPHA_CLEANNESS)
				{
					//その値にする
					m_Color.a = COLOR_VALUE::ALPHA_CLEANNESS;

					//初期化する
					m_nWaitTime = INITIAL_INT;
				}
			}
		}
	}
}
//<====================================================
//フォントの描画処理
//<====================================================
void CFont::Draw(void)
{
	//デバッグ情報を描画する
	m_pFont->DrawText(NULL, &m_aStrDebug[0], -1, &m_Rect, DT_LEFT, m_Color);
}
//<====================================================
//フォントの文字判別処理
//<====================================================
void CFont::Print(const char *aStr,...)
{
	va_list args = nullptr;
	char aString[MAX_STRING] = {};
	char aSaveString[MAX_STRING] = {};
	int nLength = 0;
	int nStopLength = 0;

	//文字列の代入
	strcpy(&aString[0], aStr);

	va_start(args, aStr);

	for (char *p = &aString[0]; *p != '\0'; p++)
	{
		if (*p == '%')
		{//確認文字がある場合
			p++;	//確認文字まで進める

					//数字だった場合
			if (*p == 'd')
			{
				sprintf(&aSaveString[0], "%d", va_arg(args, int));

				//文字列の長さを取得
				nLength = (int)strlen(&aSaveString[0]);
			}
			//小数だった場合
			if (*p == 'f'&&*p != NULL)
			{
				sprintf(&aSaveString[0], "%f", va_arg(args, double));

				//文字列の長さを取得
				nLength = (int)strlen(&aSaveString[0]);

				//小数点以下の文字目まで確認
				for (int nCntlength = 0; aSaveString[nCntlength] != '\0'; nCntlength++)
				{
					if (aSaveString[nCntlength] == '.')
					{//小数点があった場合

					 //小数点以下の桁数を求める
						int nMin = (int)strlen(&aSaveString[nCntlength + 1]);

						//小数点より先の文字数と指定した値までの差分を求める
						nMin -= MAX_FLOATNUM;

						//文字列の長さを小数点以下第二位までに補正
						nLength -= nMin;
					}
				}

			}
			//文字だった場合
			if (*p == 'c'&&*p != NULL)
			{
				sprintf(&aSaveString[0], "%c", va_arg(args, char));

				//文字列の長さを取得
				nLength = (int)strlen(&aSaveString[0]);
			}
			//文字列だった場合
			if (*p == 's'&&*p != NULL)
			{
				//文字列
				sprintf(&aSaveString[0], "%s", va_arg(args, const char*));

				//文字列の長さを取得
				nLength = (int)strlen(&aSaveString[0]);
			}

			nStopLength = (int)strlen(p) + 1;
			//メモリ内の確認文字より後ろの文字列をずらす
			memmove(p + nLength - 2, p, nStopLength);

			p--;	//ポインタを%まで戻す

					//可変引数を指定された場所に挿入
			memcpy(p, &aSaveString[0], nLength);
		}
	}

	va_end(args);

	//文字列を連結する
	strcat(&m_aStrDebug[0], &aString[0]);
}