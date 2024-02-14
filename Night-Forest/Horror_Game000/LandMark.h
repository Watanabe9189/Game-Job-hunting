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
	//��ޕʂ̗񋓌^
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
	//�I�[�o�[���[�h�����o�֐�
	//<==========================
	HRESULT Init(void);
	void Uninit(void) 
	{ 
		CXObject::Uninit();
	
		//�������g�������
		if (m_pBillBIcon != nullptr)
		{
			//�\��������
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
	//�ʒu���֘A
	//<==============
	D3DXVECTOR3 m_pos;										//�ʒu
	D3DXVECTOR3 m_posOld;									//�O��̈ʒu
	D3DXVECTOR3 m_rot;										//����
	D3DXVECTOR3 m_move;										//�ړ��l

	//<==============
	//�e�N�X�`���֘A
	//<==============
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//�t�@�C����
	static int m_nNumAll;	//����

	TYPE m_eType;

	CBilBIcon *m_pBillBIcon;
	DataModel m_sModel;

};
#endif
