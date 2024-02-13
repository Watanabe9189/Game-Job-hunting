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

	static int GetNum(void) { return m_nNumAll; }
	static int GetMax(void) { return m_MaxNum; }
	static int GetNumCollect(void) { return m_NumCollect; }
	static void SetNumCollect(const int nNumCollect) {m_NumCollect = nNumCollect;}
	static int GetNumLeft(void) { return m_nLeft; }

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
	//�}�e���A���֘A
	//<==============
	LPD3DXMESH	m_pMesh;							//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER	m_pBuffMat;							//�}�e���A���ւ̃|�C���^
	DWORD		m_dwNumMat;							//�}�e���A���̐�
	D3DXMATERIAL*	m_pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

													//<==============
													//�e�N�X�`���֘A
													//<==============
	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//�e�N�X�`���ւ̃|�C���^
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//�t�@�C����

																			//<=============
																			//���_���֘A
																			//<=============
	D3DXVECTOR3			m_vtxMin;					//���_�̍ŏ��l
	D3DXVECTOR3			m_vtxMax;					//���_�̍ő�l

	D3DXVECTOR3 m_rSize;
	D3DXVECTOR3 m_rSizeX;
	D3DXVECTOR3 m_rSizeZ;

	bool m_bGet;
	bool m_bAppro;
	TYPE m_eType;

	C3DPlayer *m_pPlayer;
};


#endif
