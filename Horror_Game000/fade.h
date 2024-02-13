//<==============================================
//�t�F�[�h����(fade.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _FADE_H_
#define _FADE_H_

#include "object2D.h"
#include "manager.h"

//<***********************************************
//
//<***********************************************
class CFade
{
public:

	//<=======================================
	//�t�F�[�h�^�C�v�񋓌^
	//<=======================================
	enum TYPE
	{
		TYPE_FADE_NONE = 0,		//�����Ȃ�
		TYPE_FADE_OUT,			//�t�F�[�h�A�E�g
		TYPE_FADE_IN,			//�t�F�[�h�C��
		TYPE_MAX,
	};

	CFade();
	~CFade();

	static CFade *Create(void);

	HRESULT Init(void);
	void Uninit(void) {};
	void Update(void);
	void Draw(void) 
	{ 
		m_pObject2D->Draw();
	}
	void SetVtx(void);

	void SetFade(CScene::MODE modeNext);		
	D3DXCOLOR GetCol(void) { return m_Col; }	//�F�̎擾
	TYPE GetType(void) {return m_eType;}		//�^�C�v�̎擾

private:

	void SetFadeOut(void);
	void SetFadeIn(void);

	int m_nWaitTime;			//�ҋ@����
	D3DXVECTOR2 m_rPos;			//�ʒu
	D3DXCOLOR m_Col;			//�F
	CScene::MODE m_ModeNext;	//���̃��[�h
	TYPE m_eType;				//�t�F�[�h�^�C�v
	CObject2D *m_pObject2D;		//�I�u�W�F�N�g2D�̃|�C���^
};


#endif
