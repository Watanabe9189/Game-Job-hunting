//==========================================================
//
// デバッグ表示処理 [debugproc.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "DebugProc.h"
#include "manager.h"
#include "input.h"
#include "Texture.h"
#include "Sound.h"
#include "Result.h"

//**********************************************************
//マクロ定義
//**********************************************************
#define MAX_FLOATNUM	(2)		//小数点以下の表示桁数

LPD3DXFONT CDebug::m_pFont = NULL;

//現在の画面
const char *CDebug::m_acNowScreen[]
{
	"タイトル画面",
	"オプション画面",
	"チュートリアル画面",
	"ゲーム画面",
	"リザルト画面",
	"ランキング画面",
};
//<==========================================================
//デバッグ表示のコンストラクタ
//<==========================================================
CDebug::CDebug()
{
	memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));

	m_bDispDebug = true;
}
//<==========================================================
//デバッグ表示のデストラクタ
//<==========================================================
CDebug::~CDebug()
{

}
//==========================================================
//デバッグ表示の初期化処理
//==========================================================
HRESULT CDebug::Init(void)
{
	//デバッグ表示用フォントの生成
	if (FAILED(D3DXCreateFont(CManager::GetRenderer()->GetDevice()
		,18 , 0, FW_MEDIUM, D3DX_DEFAULT, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont)))
	{
		return E_FAIL;
	}

	return S_OK;

}
//==========================================================
//デバッグ表示の終了処理
//==========================================================
void CDebug::Uninit(void)
{
	//デバッグ表示用フォントの廃棄
	if (m_pFont != NULL)
	{	
		m_pFont->Release();
		m_pFont = NULL;
	}
}
//==========================================================
//デバッグ表示の更新処理
//==========================================================
void CDebug::Update(void)
{
	//TABキーが押されたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_TAB) == true)
	{
		//三項演算子
		m_bDispDebug == true ? m_bDispDebug = false : m_bDispDebug = true;
	}
}
//==========================================================
//デバッグ表示の描画処理
//==========================================================
void CDebug::Draw(void)
{
	//場所を決める
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//
	if (m_bDispDebug == true)
	{
		//デバッグ情報を描画する
		m_pFont->DrawText(NULL, &m_aStrDebug[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	}
	
	//デバッグ表示情報のクリア
	memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));

}
//==========================================================
//デバッグ表示の設定処理
//==========================================================
void CDebug::Print(const char *fmt, ...)
{
#ifdef _DEBUG

	va_list args;
	char aString[MAX_DEBUGSTRING];
	char aSaveString[MAX_DEBUGSTRING];
	int nLength = 0;
	int nStopLength;

	//文字列の代入
	strcpy(&aString[0], fmt);

	va_start(args, fmt);

	for (char *p = &aString[0]; *p != '\0'; p++)
	{
		if (*p == '%')
		{//確認文字がある場合
			p++;	//確認文字まで進める

			//数字だった場合
			if (*p == 'd'&&*p != NULL)
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

#endif
}
//==========================================================
//表示するテキスト設定
//==========================================================
void CDebug::SetManual(void)
{
	//デバッグ表示とFPS
	CManager::GetDebugProc()->Print("/<=====================================================\n");
	CManager::GetDebugProc()->Print("デバッグ表示の変更：[TABキー]\n");
	CManager::GetDebugProc()->Print("FPS：%d\n",GetFPS());
	CManager::GetDebugProc()->Print("現在のオブジェクトの総数[%d]\n", CObject::GetNumObj());
	CManager::GetDebugProc()->Print("現在のテクスチャの総数[%d]\n", CTexture::GetNumAll());
	CManager::GetDebugProc()->Print("マウス座標X->[%f],マウス座標Y->[%f]\n", CManager::GetMouse()->GetMousePos().x, CManager::GetMouse()->GetMousePos().y);
	CManager::GetDebugProc()->Print("破壊可能なブロックの色->[青色]\n");
	CManager::GetDebugProc()->Print("現在の画面[%s]\n",m_acNowScreen[CScene::GetMode()]);
	CManager::GetDebugProc()->Print("タイトルからゲーム遷移[ENTERキー]\n");
	CManager::GetDebugProc()->Print("チュートリアルからゲーム遷移[右矢印キー]\n");
	CManager::GetDebugProc()->Print("ゲームからリザルト遷移[奥のボスを倒す]\n");
	CManager::GetDebugProc()->Print("リザルトからタイトル遷移[2キー]\n");
	CManager::GetDebugProc()->Print("現在の周回数[%d]\n",CScene::GetCount());
}