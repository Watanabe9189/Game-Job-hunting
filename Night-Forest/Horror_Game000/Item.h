#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "XObject.h"
#include "3DPlayer.h"

//<===========================================
//�N���X�錾
//<===========================================
class CItem : public CXObject
{
public:

	//<********************************
	//�^�C�v�񋓌^
	//<********************************
	enum TYPE
	{
		TYPE_ITEM0 = 0,	//�A�C�e���P
		TYPE_ITEM1,		//�A�C�e���Q
		TYPE_ITEM2,		//�A�C�e���R
		TYPE_ITEM3,		//�A�C�e���S
		TYPE_ITEM4,		//�A�C�e���T
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
		//�Q�b�g���Ă��Ȃ���Ԃ�������
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

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_rot;			//����
	static int m_nNumAll;		//����
	static int m_NumCollect;	//���l��������
	static int m_MaxNum;		//�ő吔
	static int m_nLeft;			//���c���Ă��邩
													//<==============
													//�e�N�X�`���֘A
													//<==============
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//�t�@�C����

	bool m_bGet;
	bool m_bSealed;		//���󂳂�Ă��邩�ǂ���
	bool m_bAppro;
	int m_nColCount;
	static bool m_bFlag;
	TYPE m_eType;

	C3DPlayer *m_pPlayer;
	DataModel m_sModel;
};


#endif
