#ifndef _LANDMARK_H_
#define _LANDMARK_H_

#include "XObject.h"
#include "BillBIcon.h"

//<************************************************
//
//<************************************************
class CLandMark :public CXObject
{
public:

	//<****************************************
	//種類別の列挙型
	//<****************************************
	enum TYPE
	{
		TYPE_FIRST = 0,
		TYPE_SECOND,
		TYPE_THIRD,
		TYPE_FOURTH,
		TYPE_MAX
	};

	CLandMark(int nPriority = FIX_PRIORITY);
	~CLandMark();

	//<==========================
	//オーバーロードメンバ関数
	//<==========================
	HRESULT Init(void);
	void Uninit(void) 
	{ 
		CXObject::Uninit();
	
		//もし中身があれば
		if (m_pBillBIcon != nullptr)
		{
			//表示させる
			m_pBillBIcon->Uninit();
			m_pBillBIcon = nullptr;
		}

	}
	void Update(void);
	void Draw(void) { CXObject::Draw(); }

	static CLandMark *FixedCreate(CLandMark *apLandMark[MAX_OBJECT]);
	static int GetNum(void) { return m_nNumAll; }

private:

	void Collid(void);

	//<==============
	//位置情報関連
	//<==============
	D3DXVECTOR3 m_pos;										//位置
	D3DXVECTOR3 m_posOld;									//前回の位置
	D3DXVECTOR3 m_rot;										//向き
	D3DXVECTOR3 m_move;										//移動値

	//<==============
	//テクスチャ関連
	//<==============
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//ファイル名
	static int m_nNumAll;	//総数

	TYPE m_eType;

	CBilBIcon *m_pBillBIcon;
	DataModel m_sModel;

};
#endif
