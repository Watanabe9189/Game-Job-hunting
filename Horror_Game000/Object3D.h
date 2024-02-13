//<==============================================
//3D�I�u�W�F�N�g���̏���[X�t�@�C���Ȃ�](Object3D.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"

//<******************************************
//3D�I�u�W�F�N�g�̃N���X��`
//<******************************************
class CObject3D : public CObject
{
public:

	enum TYPE
	{
		TYPE_PLANE = 0,
		TYPE_PLANE_Y,
		TYPE_MAX


	};

	//<================================
	//�R���X�g���N�^�E�f�X�g���N�^
	//<================================
	CObject3D(int nPriority = FIX_PRIORITY);
	~CObject3D();

	static CObject3D *Create(const D3DXVECTOR3 rPos = INIT_VECTOR, const D3DXVECTOR3 rSize = INIT_VECTOR, 
		const D3DXVECTOR3 rRot = INIT_VECTOR, const D3DXCOLOR rColor = INIT_COL,const TYPE eType = TYPE::TYPE_PLANE,const LPDIRECT3DTEXTURE9 pTexture = nullptr);



	//<==========================
	//�I�[�o�[���[�h�����o�֐�
	//<==========================
	HRESULT Init(void);
	HRESULT InitWith(const D3DXVECTOR3 rPos = INIT_VECTOR, const D3DXVECTOR3 rSize = INIT_VECTOR,
		const D3DXVECTOR3 rRot = INIT_VECTOR, const D3DXCOLOR rColor = INIT_COL, const TYPE eType = TYPE::TYPE_PLANE, const LPDIRECT3DTEXTURE9 pTexture = nullptr);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtx(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) {m_pTexture = pTexture;}

	//<==========================================
	//Set�n�̃����o�֐�
	//<==========================================
	void SetPosition(const D3DXVECTOR3& pos)		{ m_pos = pos; }			//�ʒu�ݒ�
	void SetRotation(const D3DXVECTOR3& rot)		{ m_rot = rot; }			//�����ݒ�
	void SetSize	(const D3DXVECTOR3& Size)		
	{ 
		//�T�C�Y�̐ݒ�
		m_Size = Size; 
	
		//�����ƌ����̐ݒ�
		SetLength(sqrtf(m_Size.x *m_Size.x + m_Size.y * m_Size.y));
		SetAngle(atan2f(m_Size.x, m_Size.y));

	}			//�����ݒ�

	//�����l�ɂ�����
	void SetSizeToZero(void) { m_Size = INIT_VECTOR; }

	void SetColor	(const D3DXCOLOR& rCol)			{ m_rCol = rCol; }			//�����ݒ�

	void SetLength(const float& fLength) { m_fLength = fLength; }	//�Ίp���̒����ݒ�
	void SetAngle(const float& fAngle) { m_fAngle = fAngle; }		//�Ίp���̌����ݒ�

	void SetDrawfalse(void) { m_bDraw = false; }	//�`��̃I���I�t
	void SetDrawtrue(void) { m_bDraw = true; }	//�`��̃I���I�t


	//<==========================================
	//Get�n�̃����o�֐�
	//<==========================================
	CObject2D *GetObject2D(void) { return NULL; }
	CObject3D *GetObject3D(void) { return this; }

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }				//�ʒu�擾
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }				//�����擾
	D3DXVECTOR3 GetSize(void) const		{ return m_Size; }				//�����擾
	D3DXCOLOR GetColor(void) const { return m_rCol; }				//�ʒu�擾
	float GetAngle(void)const { return m_fAngle; }
	float GetLength(void)const {return m_fLength;}

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) const { return m_pVtxBuff; }		//���_�o�b�t�@�̎擾

private:

	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_rot;					//����
	D3DXVECTOR3 m_move;					//�ړ���
	D3DXVECTOR3 m_Size;					//�T�C�Y
	D3DXCOLOR m_rCol;

	TYPE m_eType;

	float m_fAngle;
	float m_fLength;

	bool m_bDraw;
};
#endif