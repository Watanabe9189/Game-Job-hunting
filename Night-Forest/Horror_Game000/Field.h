//<=====================================================
//�n�ʏ���(Field.h)
//
//Author:kazuki watanabe
//<=====================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"

//<*****************************************************
//�n�ʂ̃N���X��`
//<*****************************************************
class CField : public CObject
{
public:

	CField();
	~CField();

	static CField *Create(const D3DXVECTOR3 pos);
	static CField *ReadCreate(CField *apField[MAX_OBJECT]);

	//<==========================
	//�I�[�o�[���[�h�����o�֐�
	//<==========================
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtx(void);
	void SetIndex(void);

	static int GetNum(void) { return m_nNumAll; }
	static void SetNum(void) { m_nNumAll = 0; }

	//<==========================================
	//Get�n�̃����o�֐�
	//<==========================================
	CObject2D *GetObject2D(void) { return NULL; }
	bool CollisionField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, TYPE_3D Type3D);

private:

	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_Size;			//�T�C�Y
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	int m_Depth;				//�c
	int m_width;				//��
	int m_nNumIndex;			//�C���f�b�N�X��
	int m_NumVtx;				//���_��
	static int m_nNumAll;

	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

};

#endif
