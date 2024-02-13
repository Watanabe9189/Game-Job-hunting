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


															//<==============
															//�}�e���A���֘A
															//<==============
	LPD3DXMESH			m_pMesh;							//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER		m_pBuffMat;							//�}�e���A���ւ̃|�C���^
	DWORD				m_dwNumMat;							//�}�e���A���̐�
	D3DXMATERIAL*		m_pMat;								//�}�e���A���f�[�^�ւ̃|�C���^

													//<==============
													//�e�N�X�`���֘A
													//<==============
	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];			//�e�N�X�`���ւ̃|�C���^
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//�t�@�C����

															//<=============
															//���_���֘A
															//<=============
	D3DXVECTOR3			m_vtxMin;					//���_�̍ŏ��l
	D3DXVECTOR3			m_vtxMax;					//���_�̍ő�l

	D3DXVECTOR3 m_rHideRad;

	D3DXVECTOR3 m_rSize;
	D3DXVECTOR3 m_rSizeX;
	D3DXVECTOR3 m_rSizeZ;

	TYPE m_eType;

};

#endif
