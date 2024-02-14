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

	CBuilding();
	~CBuilding();

	//<==========================
	//�I�[�o�[���[�h�����o�֐�
	//<==========================
	HRESULT Init(void);
	void Uninit(void) { CXObject::Uninit(); }
	void Update(void);
	void Draw(void) { CXObject::Draw(); }

	static CBuilding *Create(const D3DXVECTOR3 pos,const TYPE eType);
	static CBuilding *ReadCreate(CBuilding *apBuilding[MAX_OBJECT]);
	static CBuilding *RandCreate(CBuilding *apBuilding[MAX_OBJECT], const int nNum);

	D3DXVECTOR3 GetHideRad(void) { return m_rHideRad; }
	static int GetNum(void) { return m_nNumAll; }

private:

	//<==============
	//�ʒu���֘A
	//<==============
	D3DXVECTOR3 m_pos;									//�O��̈ʒu
	D3DXVECTOR3 m_rot;										//����
	D3DXVECTOR3 m_move;										//�ړ��l

	static int m_nNumAll;	//����

	static const char*			m_acFilename[TYPE::TYPE_MAX];				//�t�@�C����

	D3DXVECTOR3 m_rHideRad;

	DataModel m_sModel;

	TYPE m_eType;

};

#endif
