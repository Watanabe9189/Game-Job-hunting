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
															//�}�e���A���֘A
															//<==============
	LPD3DXMESH	m_pMesh;							//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER	m_pBuffMat;							//�}�e���A���ւ̃|�C���^
	DWORD		m_dwNumMat;							//�}�e���A���̐�
	D3DXMATERIAL	*m_pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	//<==============
	//�e�N�X�`���֘A
	//<==============
	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//�e�N�X�`���ւ̃|�C���^
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//�t�@�C����
	static int m_nNumAll;	//����
	//<=============
	//���_���֘A
	//<=============
	D3DXVECTOR3			m_vtxMin;					//���_�̍ŏ��l
	D3DXVECTOR3			m_vtxMax;					//���_�̍ő�l

	TYPE m_eType;

	D3DXVECTOR3 m_rSize;
	D3DXVECTOR3 m_rSizeX;
	D3DXVECTOR3 m_rSizeZ;

	CBilBIcon *m_pBillBIcon;

};
#endif
