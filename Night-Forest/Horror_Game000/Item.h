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
	bool bGetSealed(void) { return m_bSealed; }

	static int GetNum(void) { return m_nNumAll; }
	static int GetMax(void) { return m_MaxNum; }
	static int GetNumCollect(void) { return m_NumCollect; }
	static void SetNumCollect(const int nNumCollect) {m_NumCollect = nNumCollect;}
	static int GetNumLeft(void) { return m_nLeft; }

	static bool bGetFlag(void) { return m_bFlag; }

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
													//テクスチャ関連
													//<==============
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//ファイル名

	bool m_bGet;
	bool m_bSealed;		//封印されているかどうか
	bool m_bAppro;
	int m_nColCount;
	static bool m_bFlag;
	TYPE m_eType;

	C3DPlayer *m_pPlayer;
	DataModel m_sModel;
};


#endif
