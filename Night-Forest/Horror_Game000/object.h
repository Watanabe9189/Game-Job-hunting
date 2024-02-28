//<==============================================
//�I�u�W�F�N�g����(object.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _OBJECT_H_
#define _OBJECT_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "Stencil.h"
class CObject2D;
class CStencil;

//<**********************************************
//�}�N����`(�萔�܂�)
//<**********************************************
static const int			MAX_OBJECT = 1024;									//�I�u�W�F�N�g�̍ő吔
static const int			INITIAL_INT = 0;									//Int�^�̏����l
static const float			INITIAL_FLOAT = 0.0f;								//float�^�̏����l
static const D3DXVECTOR3	INIT_VECTOR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//D3DXVECTOR3�^�̏����l
static const D3DXVECTOR2	INIT_VECTOR2 = D3DXVECTOR2(0.0f, 0.0f);				//D3DXVECTOR2�^�̏����l
static const D3DXCOLOR		INIT_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//�F�̏����l

static const float MOVE_UP	 =	(1.0f);		//��ړ�
static const float MOVE_LRUP =	(0.75f);	//�΂ߏ�ړ�
static const float MOVE_LR	 =	(0.5f);		//�����ړ�
static const float MOVE_LRDW =	(0.25f);	//�΂ߏ�ړ�
static const float MOVE_DOWN =	(0.0f);		//���ړ�

//<==================================================================================
//���_�t�H�[�}�b�g�֘A
//<==================================================================================
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)					//2D���_�t�H�[�}�b�g
#define FVF_VERTEX_2D_MULTI	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX8)					//�}���`�e�N�X�`���p��2D���_�t�H�[�}�b�g
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//���_�t�H�[�}�b�g,�@��
#define FVF_VERTEX_3D_MULTI	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX8)		//�}���`�e�N�X�`���p��3D���_�t�H�[�}�b�g

//<==================================================================================
//�T�C�Y�֘A(Int�^�̒l)
//<==================================================================================
namespace INT_VALUE
{
	static const int MAX_MAT = (512);	//�}�e���A���T�C�Y
	static const int MAX_TEX = (512);	//�e�N�X�`���̍ő吔
	static const int FRONT_MAX_TEX = (511);	//�e�N�X�`���̍ő吔�̎�O�̒l
	static const int NUM_MULTEX = (8);	//�}���`�e�N�X�`���̐�
	static const int MAX_TOP = (4);	//���_��
	static const int MAX_CHAR = (256);	//char�^�̔z��̍ő吔
	static const int MAX_SIZE = (256);	//���I�������m�ۂ����邽�߂ɕK�v�ȃ������̍ő吔

	static const int NO_LIFE = (0);	//�̗�(����)�̃[���̒l
}

//<==================================================================================
//�F�֘A
//<==================================================================================
namespace COLOR_VALUE
{
	static const D3DXCOLOR COLOR_RED = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//�ԐF
	static const D3DXCOLOR COLOR_GREEN = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);	//�F
	static const D3DXCOLOR COLOR_BLUE = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);	//�ΐF
	static const D3DXCOLOR COLOR_INIT = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F�̏����l

	static const float ALPHA_OPACITY = 1.0f;								//�s�����F
	static const float ALPHA_CLEANNESS = 0.0f;								//�����F
}

//<==================================================================================
//�D�揇�ʊ֘A
//<==================================================================================
static const int FIX_PRIORITY	= 3;			//�D�揇�ʂ̌Œ�l
static const int NEED_PRIORITY	= 8;			//�D�揇�ʂ̕K�v��

//<==================================================================================
//��]�֘A
//<==================================================================================
namespace FLOAT_VALUE
{
	static const float FRONT_HARF_CIRCLE = (1.56f);		//���~�̎�O�̐��l
	static const float HARF_CIRCLE = (1.57f);		//���~�ɉ�]����ۂ̒l
	static const float BACK_HARF_CIRCLE = (1.58f);		//���~�̉��̐��l
	static const float NO_ROTATION = (0.0f);			//��]���Ȃ��l

	static const float ROT_RIGHT = (-1.57f);				//�E�̌���
	static const float ROT_LEFT = (1.57f);				//���̌���
}

//<**********************************************
//���_���[2D]�̍\���̂�錾
//<**********************************************
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W

};
//<**********************************************
////���_���[3D]�̍\���̂�錾
//<**********************************************
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W

};
//==========================================================================
//�I�u�W�F�N�g�N���X�̒�`
//==========================================================================
class CObject
{
public:

	//<=================================
	//2D�I�u�W�F�N�g�̎�ނ̗񋓌^
	//<=================================
	enum TYPE_2D
	{
		TYPE_PARTICLE,		//�p�[�e�B�N��
		TYPE_NUMBER,
		TYPE_SCORE,
		TYPE_TIMER,
		TYPE_2DLIFE,
		TYPE_MAX
	};

	//<=================================
	//3D�I�u�W�F�N�g�̎�ނ̗񋓌^
	//<=================================
	enum TYPE_3D
	{
		TYPE_NONE = 0,	
		TYPE_PLAYER3D,	//�v���C���[
		TYPE_ENEMY3D,	//�G
		TYPE_BLOCK3D,	//�u���b�N
		TYPE_EFFECT3D,	//�G�t�F�N�g
		TYPE_FIELD,		//�n��
		TYPE_WALL,		//��
		TYPE_BUILDING,	//����
		TYPE_ITEM,		//�A�C�e��
		TYPE_MAX3D
	};

	//<=======================================
	//�R���X�g���N�^�E�f�X�g���N�^
	//<=======================================
	CObject(int nPriotity= FIX_PRIORITY);
	virtual ~CObject();

	//<=======================================
	//�������z�֐��ɂ���
	//<=======================================
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void SetVtx(void) = 0;

	//<=======================================
	//�ÓI�����o�֐�
	//<=======================================
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static int GetNumObj(void) { return m_nNumAll; };

	//<=======================================
	//�����o�֐�(Set�n)
	//<=======================================
	void SetType(const TYPE_2D Type) { m_2DTYpe = Type; }
	void SetType3D(const TYPE_3D Type) { m_3DType = Type; }

	//<=======================================
	//�����o�֐�(Get�n)
	//<=======================================
	TYPE_2D GetType(void)	const { return m_2DTYpe; }

	TYPE_3D GetType3D(void)	const
	{
		if ((unsigned int)this == 0xdddddddd)
		{
			//�x������\��
			MessageBox(NULL, "DUMPRING POINTER IN GetType3D", "ERROR", MB_ICONWARNING);

			exit(EXIT_FAILURE);
		}
		else
		{
			return m_3DType;
		}
	}
	void SetPrio(const int nPrio) { m_nPriority = nPrio; }

	//�`�悷�邩�ǂ���
	void SetUpdatefalse(void) { m_bUpdate = false; }	//�`��̃I���I�t
	void SetUpdatetrue(void) { m_bUpdate = true; }	//�`��̃I���I�t
	bool GetbUpdate(void) { return m_bUpdate; }

	//�`�悷�邩�ǂ���
	void SetDrawfalse(void) { m_bDraw = false; }	//�`��̃I���I�t
	void SetDrawtrue(void) { m_bDraw = true; }	//�`��̃I���I�t
	bool GetbDraw(void) { return m_bDraw; }

	//<=======================================
	//�ÓI�����o�֐�(Get�n)
	//<=======================================
#if 0
	static CObject *GetObject(int nPriority,int nIdx) { return m_apObject[nPriority][nIdx]; };
#endif

	//<====================================
	//
	//<====================================
	static CObject *GetTop(int nPriority) 
	{ 
		if (m_apTop[nPriority] != nullptr)
		{
			return m_apTop[nPriority];
		}
		return nullptr;
	}
	//<====================================
	//
	//<====================================
	CObject *GetNext(void)
	{

		if ((unsigned int)this == 0xdddddddd)
		{
			//�x������\��
			MessageBox(NULL, "DUMPRING POINTER IN GetNext", "ERROR", MB_ICONWARNING);

			exit(EXIT_FAILURE);
		}
		else
		{
			return m_pNext;
		}

	}

	//<=======================================
	//�����蔻��֘A
	//<=======================================
	virtual bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,D3DXVECTOR3 *pMove ,D3DXVECTOR2 pSize, bool bJump,TYPE_2D type) { return false; }
	virtual bool Collision3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, bool bJump,TYPE_3D Type3D) { return false; }
	virtual void Collision3DNoBool(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, bool bJump, TYPE_3D Type3D) { return; }
	virtual bool CollisionDestroy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, bool bJump, TYPE_3D Type3D) { return false; }
	virtual bool CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, TYPE_3D Type3D) {return false;}
	virtual bool CollisionField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, TYPE_3D Type3D) { return false; }
	virtual bool CollisionWithHP(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, int nLife, TYPE_3D Type3D) { return false; }

	CStencil *GetStencil(void) { return m_pStencil; }	//�X�e���V���I�u�W�F�N�g���擾����

	void Release(void);

protected:

private:

	//<=======================================
	//�ÓI�����o�ϐ�
	//<=======================================
#if 0
	static CObject *m_apObject[NEED_PRIORITY][MAX_OBJECT];		//�I�u�W�F�N�g���
#endif

	static CObject *m_pObject;
	static CObject *m_pObjNext;

	static CObject *m_apTop[NEED_PRIORITY];		//�擪�I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_apCur[NEED_PRIORITY];		//�Ō���I�u�W�F�N�g�ւ̃|�C���^

	CObject *m_pNext;							//���̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pPrev;							//�O�̃I�u�W�F�N�g�ւ̃|�C���^

	bool m_bDestru;

	static int m_nNumAll;						//�I�u�W�F�N�g�̑���
	int m_nPriority;							//�I�u�W�F�N�g�̗D�揇��

	TYPE_2D m_2DTYpe;							//2D�I�u�W�F�N�g�̃^�C�v
	TYPE_3D m_3DType;							//3D�I�u�W�F�N�g�̃^�C�v
	bool m_bDraw;
	bool m_bUpdate;

	CStencil *m_pStencil;

	//<****************************************
	//���̗D�揇�ʂ�3D�ł͂��܂�Ӗ����Ȃ�
	//<****************************************

};
#endif