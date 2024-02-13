//<===============================================
//3D�I�u�W�F�N�g���̏���[X�t�@�C��](XObject.h)
//
//Author:kazuki watanabe
//<===============================================
#ifndef _XOBJECT_H_//��d�C���N���[�h�h�~
#define _XOBJECT_H_

#include "main.h"
#include "Sound.h"
#include "manager.h"
#include "DebugProc.h"
#include "input.h"
#include "Texture.h"

//<***************************************
//X�t�@�C���I�u�W�F�N�g�̃N���X��`
//<***************************************
class CXObject : public CObject
{
public:

//<==============================================
//���_�l�֘A�̃}�N����`(�p���I�u�W�F�N�g�Ƌ��L)
//<==============================================
#define INITIAL_VTX_MIN	(D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f))	//���_�̍ŏ��l�̏����l
#define INITIAL_VTX_MAX	(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))		//���_�̍ő�l�̏����l

	//<================================
	//�R���X�g���N�^�E�f�X�g���N�^
	//<================================
	CXObject(int nPriority = FIX_PRIORITY);
	~CXObject();

	//<==========================
	//�I�[�o�[���[�h�����o�֐�
	//<==========================
	HRESULT Init(void);
	void Uninit(void);
	void Draw(void);
	HRESULT CheckVtx(D3DXVECTOR3 *VtxMax, D3DXVECTOR3 *VtxMin,float fRot);
	void SetSize(D3DXVECTOR3 &rSize, D3DXVECTOR3 &rSizeX, D3DXVECTOR3 &rSizeZ);

	static CXObject *Create(const D3DXVECTOR3 rPos,const D3DXVECTOR3 rRot,const char *pFileName);

	//<============================================
	//����g�p���Ȃ��I�[�o�[���[�h�����o�֐�
	//<============================================
	void Update(void) { return; }
	CObject2D *GetObject2D(void) { return NULL; }
	void SetVtx(void) { return; }
	//<====================================================================================
	//
	//<====================================================================================
	void SetVector3(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move)
	{
		//�����ǂ��炩��nullptr�łȂ����
		if (pos != nullptr)
		{
			m_pos = pos;
		}
		if (rot != nullptr)
		{
			m_rot = rot;
		}
		if (move != nullptr)
		{
			m_move = move;
		}
	}

	void BindMat(D3DXMATERIAL *pMat,
				LPDIRECT3DTEXTURE9 const *pTex);					

	//<==========================================
	//�ݒ�n�̃����o�֐�
	//<==========================================
	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }					//�ʒu�ݒ�
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }					//�����ݒ�
	void SetMove(const D3DXVECTOR3& move) { m_move = move; }						//�ړ��ʐݒ�
	void SetMaterial(D3DXMATERIAL *pMat) { m_pMat = pMat; }						//�}�e���A�����P�̂ł̐ݒ�
	HRESULT LoadMesh(const char *pFileName, LPD3DXBUFFER *pBuffMat, DWORD *pDwNumMat, LPD3DXMESH *pMesh, 
		D3DXMATERIAL *pMat,LPDIRECT3DTEXTURE9 const *pTex);

	void SetDrawfalse(void) { m_bDraw = false; }	//�`��̃I���I�t
	void SetDrawtrue(void) { m_bDraw = true; }	//�`��̃I���I�t

	//<==========================================
	//Get�n�̃����o�֐�
	//<==========================================
	D3DXVECTOR3		GetPosition(void)	const	{ return m_pos; }				//�ʒu�擾
	D3DXVECTOR3		GetMove(void)		const	{ return m_move; }				//�ړ��ʎ擾
	D3DXVECTOR3		GetRotation(void)	const	{ return m_rot; }				//�����擾
	DWORD			GetdwNumMat(void)	const	{ return m_dwNumMat; }			//�}�e���A�����擾
	LPD3DXMESH		GetMesh(void)		const	{ return m_pMesh; }				//���b�V���̎擾
	LPD3DXBUFFER	GetBuffMat(void)	const	{ return m_pBuffMat; }			//�}�e���A���̎擾
	D3DXVECTOR3		GetVtxMax(void)		const	{ return m_vtxMax; }			//���_���̍ő�l�擾
	D3DXVECTOR3		GetVtxMin(void)		const	{ return m_vtxMin; }			//���_���̍ŏ��l�擾

	D3DXVECTOR3		GetSize(void)		const	{ return m_rSize; }				//�T�C�Y�擾
	D3DXVECTOR3		GetSizeX(void)		const	{ return m_rSizeX; }			//����pX�T�C�Y�̎擾
	D3DXVECTOR3		GetSizeZ(void)		const	{ return m_rSizeZ; }			//����pZ�T�C�Y�̎擾

	D3DXMATERIAL*	GetMaterial(void)	const	{ return m_pMat; }				//�}�e���A�����̎擾

private:

	//�}�e���A���֘A
	LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//�e�N�X�`���ւ̃|�C���^
	LPD3DXMESH			m_pMesh;					//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER		m_pBuffMat;					//�}�e���A���ւ̃|�C���^
	DWORD				m_dwNumMat;					//�}�e���A���̐�
	D3DXMATERIAL		*m_pMat;					//�}�e���A���f�[�^�ւ̃|�C���^

	//���_���֘A
	int					m_nNumVtx;					//���_��
	DWORD				m_dwSizeFVF;				//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE				*m_pVtxBuff;				//���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3			m_vtxMin;					//���_�̍ŏ��l
	D3DXVECTOR3			m_vtxMax;					//���_�̍ő�l

	D3DXMATRIX			m_mtxWorld;					//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_rSize;							//�T�C�Y
	D3DXVECTOR3 m_rSizeX;							//����p��X�T�C�Y
	D3DXVECTOR3 m_rSizeZ;							//����p��Z�T�C�Y

	//�x�N�g���֘A
	D3DXVECTOR3			m_pos;						//�ʒu
	D3DXVECTOR3			m_rot;						//����
	D3DXVECTOR3			m_move;						//�ړ���

	static int m_nNumAll;
	bool m_bDraw;
};

#endif
