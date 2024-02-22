//<==============================================
//2D�I�u�W�F�N�g���̏���(2DObject.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _2DOBJECT_H_//�������̖��O���ʂ�.h�ɂ�������A�ȉ��̏��������s���Ȃ�
#define _2DOBJECT_H_

#include "main.h"

//<**********************************************
//2D�I�u�W�F�N�g�̃N���X��`(�p��)
//<**********************************************
class CObject2D : public CObject
{
public:

	//<=======================================
	//2D�I�u�W�F�N�g�̍\����
	//<=======================================
	struct Object2D
	{

		D3DXVECTOR2 pos;	//�ʒu
		D3DXVECTOR3 rot;	//����
		D3DXVECTOR2 move;	//�ړ��l
		D3DXVECTOR2 Size;	//�T�C�Y
		D3DXCOLOR Col;		//�F
		float fAngle;		//�p�x
		float fLength;		//����


	};

	CObject2D(int nPriority = FIX_PRIORITY);
	~CObject2D();

	//�I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	HRESULT InitWith(const D3DXVECTOR2 rPos = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2 rSize = D3DXVECTOR2(0.0f, 0.0f),
		const D3DXCOLOR rColor = INIT_COL, const LPDIRECT3DTEXTURE9 pTexture = nullptr);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObject2D *Create(const D3DXVECTOR2 rPos = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2 rSize = D3DXVECTOR2(0.0f,0.0f),
		const D3DXCOLOR rColor = INIT_COL,const LPDIRECT3DTEXTURE9 pTexture = nullptr);

	virtual void SetVtx(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; };

	void SetPosition(const D3DXVECTOR2& pos) { m_aObj.pos = pos; }			//�ʒu�ݒ�
	void SetRotation(const D3DXVECTOR3& rot) { m_aObj.rot = rot; }			//�����ݒ�
	void SetMove(const D3DXVECTOR2& move)	{ m_aObj.move = move; }			//�ړ��ʐݒ�
	void SetSize(const D3DXVECTOR2& size);									//�T�C�Y�̐ݒ�
	void SetLength(const float& fLength)		{ m_aObj.fLength = fLength; }	//�Ίp���̒����ݒ�
	void SetAngle(const float& fAngle)		{ m_aObj.fAngle = fAngle; }		//�Ίp���̌����ݒ�
	void SetColor(const D3DXCOLOR& rCol)		{ m_aObj.Col = rCol; }			//�F�̐ݒ�
	void SetDrawfalse(void) { m_bDraw = false; }	//�`��̃I���I�t
	void SetDrawtrue(void) { m_bDraw = true; }	//�`��̃I���I�t

	bool GetDraw(void) { return m_bDraw; }

	//<=======================================================
	//�����o�֐�(Get�n)
	//<=======================================================
	D3DXVECTOR2 GetPosition(void) const { return m_aObj.pos; }		//�ʒu�擾
	D3DXVECTOR3 GetRotation(void) const { return m_aObj.rot;}		//�����擾
	D3DXVECTOR2 GetMove(void) const		{ return m_aObj.move; }		//�ړ��ʎ擾
	D3DXVECTOR2 GetSize(void) const		{ return m_aObj.Size; }		//�T�C�Y�̎擾
	float GetLength(void) const			{ return m_aObj.fLength; }	//�Ίp���̒����擾
	float GetAngle(void) const			{ return m_aObj.fAngle; }	//�Ίp���̌����擾
	D3DXCOLOR GetColor(void) const		{ return m_aObj.Col; }		//�F�̎擾
	CObject2D *GetObject2D(void) { return this; }							//�������g�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) const { return m_pVtxBuff; }	//���_�o�b�t�@�̎擾
	int GetNumTex(void) {return m_nNumTex; }

private:

	Object2D m_aObj;					//2D�I�u�W�F�N�g�̏��	
	int m_nNumTex;
	bool m_bDraw;

	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@
};



#endif