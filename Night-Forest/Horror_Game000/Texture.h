//<================================================
//テクスチャ関連処理(Texture.h)
//
//Author:kazuki watanabe
//<================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

//<**************************************
//テクスチャのクラス定義
//<**************************************
class CTexture
{
public:

	//<============================
	//コンストラクタ・デストラクタ
	//<============================
	CTexture();
	~CTexture();

	//<============================
	//メンバ関数
	//<============================
	HRESULT Load(void);
	void UnloadAll(void);
	void Unload(void);
	int Regist(const char *pTexName, LPDIRECT3DTEXTURE9 &pTex);

	//<====================================
	//メンバ関数(Get)
	//<====================================
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx) { return m_pTexture.at(nIdx); }	//テクスチャ番号の取得
	const char* GetAddressName(int nIdx)	{ return m_pFileName.at(nIdx); }	//何番目のテクスチャ名を取得するか

	static int GetNumAll(void) { return m_nNumAll; }

private:

	//<============================
	//メンバ変数
	//<============================
	std::vector<LPDIRECT3DTEXTURE9>m_pTexture;			//テクスチャへのポインタ
	std::vector<const char*>m_pFileName;				//
	static int m_nNumAll;								//テクスチャの総数

};

#endif
