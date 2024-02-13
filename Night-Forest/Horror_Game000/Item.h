#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "XObject.h"
#include "3DPlayer.h"

//<===========================================
//クラス宣言
//<===========================================
class CItem : public CXObject
{
public:

	//<********************************
	//タイプ列挙型
	//<********************************
	enum TYPE
	{
		TYPE_ITEM0 = 0,	//アイテム１
		TYPE_ITEM1,		//アイテム２
		TYPE_ITEM2,		//アイテム３
		TYPE_ITEM3,		//アイテム４
		TYPE_ITEM4,		//アイテム５
		TYPE_MAX
	};

	CItem(int nPriority = FIX_PRIORITY);
	~CItem();

	HRESULT Init(void);

	void Uninit(void) 
	{ 
		CXObject::Uninit(); 
	
		if (m_pPlayer != nullptr)
		{
			m_pPlayer->Uninit();
			m_pPlayer = nullptr;
		}	
	}

	void Update(void);
	void Draw(void) 
	{
		//ゲットしていない状態だったら
		if (!m_bGet)
		{
			CXObject::Draw();
		}
	}

	static CItem *Create(const D3DXVECTOR3 pos = INIT_VECTOR,const TYPE eType = TYPE::TYPE_ITEM0);
	static CItem *RandCreate(CItem *apItem[MAX_OBJECT], int nNum);

	bool GetAppro(void) { return m_bAppro; }
	bool bGet(void) { return m_bGet; }

	static int GetNum(void) { return m_nNumAll; }
	static int GetMax(void) { return m_MaxNum; }
	static int GetNumCollect(void) { return m_NumCollect; }
	static void SetNumCollect(const int nNumCollect) {m_NumCollect = nNumCollect;}
	static int GetNumLeft(void) { return m_nLeft; }

private:

	void Collid(void);


	//メンバ変数
	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_rot;			//向き
	static int m_nNumAll;		//総数
	static int m_NumCollect;	//何個獲得したか
	static int m_MaxNum;		//最大数
	static int m_nLeft;			//何個残っているか
	//<==============
	//マテリアル関連
	//<==============
	LPD3DXMESH	m_pMesh;							//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER	m_pBuffMat;							//マテリアルへのポインタ
	DWORD		m_dwNumMat;							//マテリアルの数
	D3DXMATERIAL*	m_pMat;							//マテリアルデータへのポインタ

													//<==============
													//テクスチャ関連
													//<==============
	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//テクスチャへのポインタ
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//ファイル名

																			//<=============
																			//頂点情報関連
																			//<=============
	D3DXVECTOR3			m_vtxMin;					//頂点の最小値
	D3DXVECTOR3			m_vtxMax;					//頂点の最大値

	D3DXVECTOR3 m_rSize;
	D3DXVECTOR3 m_rSizeX;
	D3DXVECTOR3 m_rSizeZ;

	bool m_bGet;
	bool m_bAppro;
	TYPE m_eType;

	C3DPlayer *m_pPlayer;
};


#endif
