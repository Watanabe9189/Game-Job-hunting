#ifndef _DESTARROWX_H_
#define _DESTARROWX_H_

#include "XObject.h"
#include "3DPlayer.h"
#include "Item.h"

class CDestArrowX : public CXObject
{
public:

	CDestArrowX(int nPriority = FIX_PRIORITY);
	~CDestArrowX();

	static CDestArrowX *Create(void);

	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override;
	void Draw(void)		override
	{
		if (m_bFind == true)
		{
			CXObject::Draw();
		}
	}

	void RotateToDest(void);

	void SetBool(void) { m_bFind == false ? m_bFind = true : m_bFind = false; }
	bool GetFind(void) { return m_bFind; }

private:

	D3DXVECTOR3 m_rPos;
	D3DXVECTOR3 m_rRot;
	
	D3DXVECTOR3 m_rRotDest;

	float m_fRotDest;
	float m_fRotDiff;
	float m_fSearch;

	D3DXVECTOR3 m_rDis;

	bool m_bFind;
	int m_nNum;

	CItem *m_apItem[INT_VALUE::MAX_SIZE];
	C3DPlayer *m_p3DPlayer;

	DataModel m_sModel;

};

#endif
