#ifndef _FOG_H_
#define _FOG_H_

#include "main.h"
#include "object.h"
#include "manager.h"

class CFog : public CObject
{
public:

	enum TYPE
	{
		TYPE_VERTEX = 0,		//���_�t�H�O
		TYPE_PIXEL,			//�s�N�Z���t�H�O
		TYPE_NONE,			//�Ȃ�
		TYPE_MAX

	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CFog(int nPriority = FIX_PRIORITY);
	~CFog();

	//�����֐�
	static CFog *Create(const D3DXCOLOR Col,const D3DFOGMODE Mode,const TYPE Type,const float fDensity);

	//�I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void) 
	{ 
		//���̃u�����h�𖳌��ɂ���
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

		Release(); 
	};
	void Update(void);
	void Draw(void) {};

	//<===========================================
	//�s�v�֐�
	//<===========================================
	void SetVtx(void) { return; }
	CObject2D *GetObject2D(void) { return NULL; }

	void SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange);
	void SetupPixelFog(DWORD Mode);

private:

	D3DXCOLOR m_Col;
	TYPE m_Type;
	D3DFOGMODE m_dMode;

	float m_fStart;
	float m_fEnd;
	float m_fDensity;

};

#endif