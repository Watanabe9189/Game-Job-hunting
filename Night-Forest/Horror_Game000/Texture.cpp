//<================================================
//テクスチャ関連処理(Texture.cpp)
//
//Author:kazuki watanabe
//<================================================
#include "Texture.h"
#include "manager.h"

//<************************************************
//静的メンバ変数の宣言
//<************************************************
int CTexture::m_nNumAll = 0;	//テクスチャの総数

//<===============================
//テクスチャのコンストラクタ
//<===============================
CTexture::CTexture()
{
	//テクスチャのクリア
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_TEX; nCnt++)
	{
		m_apTexture[nCnt] = {nullptr};
		m_apFileName[nCnt] = { nullptr };
	}
}
//<===============================
//テクスチャのデストラクタ
//<===============================
CTexture::~CTexture()
{

}
//<===============================
//テクスチャの読み込み処理
//<===============================
HRESULT CTexture::Load(void)
{
	//LoadTxtTex();

	return S_OK;
}
//<===============================
//テクスチャの全破棄処理
//<===============================
void CTexture::UnloadAll(void)
{
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_TEX; nCnt++)
	{
		//全てのテクスチャの破棄
		if (m_apTexture[nCnt] != nullptr)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
		if (m_apFileName[nCnt] != nullptr)
		{
			m_apFileName[nCnt] = nullptr;
		}
		else if (m_apFileName[nCnt] == nullptr&&m_apTexture[nCnt] == nullptr)
		{
			break;
		}
	}

	m_nNumAll = 0;
}
//<===============================
//テクスチャの破棄処理
//<===============================
void CTexture::Unload(void)
{
	//総数保存用の変数
	int nNum = m_nNumAll;

	if (m_apTexture[nNum] != NULL)
	{
		m_apTexture[nNum]->Release();
		m_apTexture[nNum] = NULL;
	}
	//<*******************************
	//ここでテクスチャの破棄は行わない
	//<*******************************
}
//<===============================
//テキストからテクスチャを読み込む
//<===============================
void CTexture::LoadTxtTex(void)
{
	//必要以外の文字列読み込み用データ
	char aChar[INT_VALUE::MAX_CHAR] = { NULL };

	//ファイルの名前
	char apFileName[INT_VALUE::MAX_CHAR][INT_VALUE::MAX_CHAR];

	//ファイル情報
	FILE *pFile = fopen("data/TEXT/LoadTexture.txt", "r");;

	//ファイルが開けたら
	if (pFile != NULL)
	{
		//ずっと繰り返す
		while (strcmp(aChar, "EndFile") != 0)
		{
			//空字を読み込む
			(void)fscanf(pFile, "%s", &aChar[0]);

			//ENEMY-SETという文字列が存在したら
			if (strcmp(aChar, "TEX_NAME") == 0)
			{
				//空字を読み込む
				(void)fscanf(pFile, "%s", &aChar[0]);

				//ファイルパスを読み込む
				(void)fscanf(pFile, "%s", &apFileName[m_nNumAll][0]);

				//ファイルネームを登録する
				m_apFileName[m_nNumAll] = &apFileName[m_nNumAll][0];

				//総数を増やす
				m_nNumAll++;
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}
//<===============================
//テクスチャの登録処理
//<===============================
int CTexture::Regist(const char *pTexName, LPDIRECT3DTEXTURE9 &pTex)
{
	//総数保存用の変数
	int nNum = m_nNumAll;

	//テクスチャネームがある場合
	if (pTexName != nullptr)
	{
		//<*********************************************
		//テクスチャ要素のチェック
		//<*********************************************
		//数分繰り返す
		for (int nCnt = 0; nCnt < nNum; nCnt++)
		{
			if (m_apFileName[nCnt] != nullptr)
			{
				//もし保存されたファイル名と引数のファイル名が一緒だったら
				if (strcmp(m_apFileName[nCnt], pTexName) == 0)
				{
					//その番号を返し、すでに登録されているテクスチャ
					pTex = m_apTexture[nCnt];
					return nCnt;
				}
			}
		}

		m_apFileName[nNum] = pTexName;

		//もしなければ
		if (pTex == nullptr)
		{
			assert((D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),
				pTexName,
				&m_apTexture[nNum])) == D3D_OK);

			pTex = m_apTexture[nNum];

			m_apTexture[nNum] = pTex;

		}

		m_nNumAll++;

		//その番号を返す
		return nNum;

	}

	//NULLを返す
	return NULL;
}