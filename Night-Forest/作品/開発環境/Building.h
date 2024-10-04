//<==============================================
//建物処理(Building.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "main.h"
#include "XObject.h"

//<************************************************
//クラス宣言
//<************************************************
class CBuilding : public CXObject
{
public:

	//<======================
	//建物種類
	//<======================
	enum TYPE
	{
		TYPE_CABIN = 0,	//小屋
		TYPE_TENT,		//テント
		TYPE_MAX
	};
	//<======================
	//封印のカギとなる建物
	//<======================
	enum IMPORTANCE
	{
		IMPORTANCE_NONE = 0,	//カギとなっていない
		IMPORTANCE_HIGH,		//カギとなっている
		IMPORTANCE_MAX
	};

	CBuilding();
	~CBuilding();

	//<==========================
	//オーバーロードメンバ関数
	//<==========================
	HRESULT Init(void);
	void Uninit(void) { CXObject::Uninit(); }
	void Update(void);
	void Draw(void) 
	{ 
		//隠れていたら
		if (!m_bHided)
		{
			CXObject::Draw();
		}
	}

	static CBuilding *Create(const D3DXVECTOR3 pos,const TYPE eType);
	static CBuilding *ReadCreate(CBuilding *apBuilding[MAX_OBJECT]);
	static CBuilding *RandCreate(CBuilding *apBuilding[MAX_OBJECT], const int nNum);

	D3DXVECTOR3 GetHideRad(void) { return m_rHideRad; }
	static int GetNum(void) { return m_nNumAll; }

	IMPORTANCE GetImportance(void) { return m_eImportance; }

	void SetHide(void){ !m_bHided ? m_bHided = true : m_bHided = false; }

private:

	//<==============
	//位置情報関連
	//<==============
	D3DXVECTOR3 m_pos;														//前回の位置
	D3DXVECTOR3 m_rot;														//向き
	D3DXVECTOR3 m_move;														//移動値

	static int m_nNumAll;													//総数

	static const char*			m_acFilename[TYPE::TYPE_MAX];				//ファイル名
	bool m_bHided;															//隠れているか
	D3DXVECTOR3 m_rHideRad;													//隠れられる範囲
	DataModel m_sModel;														//モデル情報
	TYPE m_eType;															//タイプ
	IMPORTANCE m_eImportance;												//重要度
};

#endif
