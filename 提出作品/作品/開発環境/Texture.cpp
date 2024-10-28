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
int CTexture::m_nNumAll = INITIAL_INT;	//テクスチャの総数

//<===============================
//テクスチャのコンストラクタ
//<===============================
CTexture::CTexture()
{
	//値のクリア
	m_pTexture.clear();			
	m_pFileName.clear();
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
	for (unsigned int nCnt = 0; nCnt < m_pTexture.size(); ++nCnt)
	{
		//全てのテクスチャの破棄
		if (!m_pTexture.empty())
		{
			m_pTexture.at(nCnt)->Release();
			m_pTexture.at(nCnt) = nullptr;
		}

		if (!m_pFileName.empty())
		{
			m_pFileName.at(nCnt) = nullptr;
		}
	}

	//クリア
	m_pFileName.clear();
	m_pTexture.clear();
	m_nNumAll = 0;
}
//<===============================
//テクスチャの破棄処理
//<===============================
void CTexture::Unload(void)
{
	////総数保存用の変数
	//int nNum = m_nNumAll;

	//if (m_apTexture[nNum] != NULL)
	//{
	//	m_apTexture[nNum]->Release();
	//	m_apTexture[nNum] = NULL;
	//}
	//<*******************************
	//ここでテクスチャの破棄は行わない
	//<*******************************
}
//<===============================
//テクスチャの登録処理
//<===============================
int CTexture::Regist(const char *pTexName, LPDIRECT3DTEXTURE9 &pTex)
{
	//総数保存用の変数
	int nNum = m_nNumAll;

	//テクスチャネームがある場合
	if (pTexName )
	{
		//<*********************************************
		//テクスチャ要素のチェック
		//<*********************************************
		//数分繰り返す
		for (int nCnt = 0; nCnt < nNum; ++nCnt)
		{
			if (!(m_pFileName.empty()))
			{
				//もし保存されたファイル名と引数のファイル名が一緒だったら
				if (strcmp(m_pFileName.at(nCnt), pTexName) == 0)
				{
					//その番号を返し、すでに登録されているテクスチャ
					pTex = m_pTexture.at(nCnt);
					return nCnt;
				}
			}
		}

		//情報挿入
		m_pFileName.insert(m_pFileName.begin() + nNum, pTexName);

		//もしなければ
		if (!pTex)
		{

			assert((D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),
				m_pFileName.at(nNum),
				&pTex)) == D3D_OK);

			//情報挿入
			m_pTexture.insert(m_pTexture.begin() + nNum, pTex);
		}

		m_nNumAll++;

		//その番号を返す
		return nNum;

	}

	//NULLを返す
	return NULL;
}