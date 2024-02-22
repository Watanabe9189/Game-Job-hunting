#ifndef _3DFONT_H_
#define _3DFONT_H_

#include "main.h"

class C3DFont : public CObject
{
public:

	C3DFont();
	~C3DFont();

	HRESULT Init();
	void Uninit();
	void Draw();

	//<============================================
	//����g�p���Ȃ��I�[�o�[���[�h�����o�֐�
	//<============================================
	void Update(void) { return; }
	void SetVtx(void) { return; }

	static C3DFont *Create(const char *pName, const D3DXVECTOR3 rPos , 
		const float fZextrusion, const float fMaxdevi, const GLYPHMETRICSFLOAT eGlyph);

private:

	const char*			m_cName;
	float m_fZextrusion;			//����Z���ւ̉��o��
	float m_fMaxdevi;				//�ő�͍�


	LPD3DXMESH			m_pMesh;
	D3DXMATRIX			m_mtxWorld;					//���[���h�}�g���b�N�X

													//�x�N�g���֘A
	D3DXVECTOR3			m_pos;						//�ʒu
	D3DXVECTOR3			m_rot;						//����
	D3DXVECTOR3			m_move;						//�ړ���

	LPGLYPHMETRICSFLOAT m_Glyph;
	HDC m_Hdc;
};

#endif
