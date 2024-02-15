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

	//<=================================
	//���f���f�[�^��
	//<=================================
	struct DataModel
	{
		//�}�e���A���֘A
		LPDIRECT3DTEXTURE9	apTexture[INT_VALUE::MAX_TEX];		//�e�N�X�`���ւ̃|�C���^
		LPD3DXMESH			pMesh;					//���b�V��(���_���)�ւ̃|�C���^
		LPD3DXBUFFER		pBuffMat;					//�}�e���A���ւ̃|�C���^
		DWORD				dwNumMat;					//�}�e���A���̐�
		D3DXMATERIAL		*pMat;

		//���_���֘A
		int					nNumVtx;					//���_��
		DWORD				dwSizeFVF;				//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE				*pVtxBuff;				//���_�o�b�t�@�̃|�C���^
		D3DXVECTOR3			vtxMin;					//���_�̍ŏ��l
		D3DXVECTOR3			vtxMax;					//���_�̍ő�l

		D3DXVECTOR3 rSize;							//�T�C�Y
		D3DXVECTOR3 rSizeX;							//����p��X�T�C�Y
		D3DXVECTOR3 rSizeZ;							//����p��Z�T�C�Y
	};


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

	void CheckVtxNo(void);

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

	//<==========================================
	//�ݒ�n�̃����o�֐�
	//<==========================================
	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }					//�ʒu�ݒ�
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }					//�����ݒ�
	void SetMove(const D3DXVECTOR3& move) { m_move = move; }						//�ړ��ʐݒ�
	void SetMaterial(D3DXMATERIAL *pMat) { m_asModel.pMat = pMat; }

	DataModel BindModel(const char *pFileName, const bool bMatChange = false);
	void LoadModel(void);

	void SetDrawfalse(void) { m_bDraw = false; }	//�`��̃I���I�t
	void SetDrawtrue(void) { m_bDraw = true; }	//�`��̃I���I�t

	//<==========================================
	//Get�n�̃����o�֐�
	//<==========================================
	int GetModelId(void) { return m_nModelId; }
	D3DXVECTOR3		GetPosition(void)	const	{ return m_pos; }				//�ʒu�擾
	D3DXVECTOR3		GetMove(void)		const	{ return m_move; }				//�ړ��ʎ擾
	D3DXVECTOR3		GetRotation(void)	const	{ return m_rot; }				//�����擾

	D3DXMATERIAL*	GetMaterial(void)	const	{ return m_pMat; }				//�}�e���A�����̎擾

	void SetModel(const DataModel sModel) {m_asModel = sModel;};
	DataModel GetModel(void) { return m_asModel; }
	static int GetNum(void) { return m_nNumAll; }

private:

	DataModel m_asModel;
	static DataModel m_asaveModel[INT_VALUE::MAX_SIZE];
	static const char *m_apFileName[INT_VALUE::MAX_SIZE];				//
	int m_nModelId;

	D3DXMATRIX			m_mtxWorld;					//���[���h�}�g���b�N�X
	D3DXMATERIAL		*m_pMat;

	//�x�N�g���֘A
	D3DXVECTOR3			m_pos;						//�ʒu
	D3DXVECTOR3			m_rot;						//����
	D3DXVECTOR3			m_move;						//�ړ���

	static int m_nNumAll;
	bool m_bDraw;
};

#endif
