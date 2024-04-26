#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "main.h"
#include "XObject.h"

class CBuilding : public CXObject
{
public:

	enum TYPE
	{
		TYPE_CABIN = 0,
		TYPE_TENT,
		TYPE_MAX
	};
	enum IMPORTANCE
	{
		IMPORTANCE_NONE = 0,
		IMPORTANCE_HIGH,
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

	void SetHide(void){ m_bHided == false ? m_bHided = true : m_bHided = false; }

private:

	//<==============
	//位置情報関連
	//<==============
	D3DXVECTOR3 m_pos;									//前回の位置
	D3DXVECTOR3 m_rot;										//向き
	D3DXVECTOR3 m_move;										//移動値

	static int m_nNumAll;	//総数

	static const char*			m_acFilename[TYPE::TYPE_MAX];				//ファイル名
	bool m_bHided;															//隠れているか

	D3DXVECTOR3 m_rHideRad;

	DataModel m_sModel;

	TYPE m_eType;
	IMPORTANCE m_eImportance;

};

#endif
