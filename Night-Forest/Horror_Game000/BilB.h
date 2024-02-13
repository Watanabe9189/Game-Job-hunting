//<==============================================
//�r���{�[�h����(BillB.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _BILLB_H_		//���̃}�N����`������Ă��Ȃ�������
#define _BILLB_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//<********************************************
//�r���{�[�h�̃N���X��`
//<********************************************
class CBillB : public CObject
{
public:

	CBillB(int nPriority = FIX_PRIORITY);
	~CBillB();

	HRESULT Init(void);
	HRESULT InitWith(const D3DXVECTOR3 rPos = INIT_VECTOR, const D3DXVECTOR2 rSize = D3DXVECTOR2(0.0f, 0.0f),
		const D3DXCOLOR rColor = INIT_COL, const LPDIRECT3DTEXTURE9 pTex = nullptr);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtx(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }

	static CBillB *Create(const D3DXVECTOR3 rPos = INIT_VECTOR, const D3DXVECTOR2 rSize = D3DXVECTOR2(0.0f, 0.0f),
		const D3DXCOLOR rColor = INIT_COL, const LPDIRECT3DTEXTURE9 pTex = nullptr);

	//<==========================================
	//�g��Ȃ��I�|�o�[���[�h�����o�֐�
	//<==========================================
	CObject2D *GetObject2D(void) { return NULL; }

	void SetVector3(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXVECTOR3& Size);

	void SetColor(const D3DXCOLOR& col)		{ m_col = col; }

	void SetDrawfalse(void) { m_bDraw = false; }	//�`��̃I���I�t
	void SetDrawtrue(void) { m_bDraw = true; }	//�`��̃I���I�t

	D3DXVECTOR3 GetPos(void) const			{ return m_pos; }			//�ʒu�擾
	D3DXVECTOR3 GetSize(void) const			{ return m_Size; }			//�����擾
	D3DXVECTOR3 GetMove(void) const			{ return m_move; }			//�ړ��ʎ擾
	D3DXCOLOR GetColor(void)const			{ return m_col; }			//�F�擾
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) const { return m_pVtxBuff; }	//���_�o�b�t�@�̎擾

private:

	LPDIRECT3DTEXTURE9	m_pTexture;	//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;	//���_�o�b�t�@


	D3DXVECTOR3					m_pos;		//�ʒu
	D3DXVECTOR3					m_move;		//�ړ���
	D3DXVECTOR3					m_Size;		//�T�C�Y
	D3DXCOLOR					m_col;		//�F
	D3DXMATRIX					m_mtxWorld;	//���[���h�}�g���b�N�X
	D3DXMATRIX					m_mtxview;	//�}�g���b�N�X�r���[
		
	bool m_bDraw;

};

#endif
