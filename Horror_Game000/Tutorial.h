//<==================================================================================
//�`���[�g���A����ʏ���(Tutorial.h)
//
//Author:kazuki watanabe
//<==================================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "manager.h"

class CLight;

//<===================================================
//
//<===================================================
class CTutorial : public CScene
{
public:

	//<=====================================
	//�`���[���A���X�e�b�v�̗񋓌^
	//<=====================================
	enum TUTORIAL_STEP
	{
		TUTORIAL_STEP_1 = 0,
		TUTORIAL_STEP_2,
		TUTORIAL_STEP_3,
		TUTORIAL_STEP_4,
		TUTORIAL_STEP_MAX
	};

	CTutorial();
	~CTutorial();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	//<==============
	//�e�N�X�`���֘A
	//<==============
	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//�e�N�X�`���ւ̃|�C���^
	static const char*			m_acFilename[];				//�t�@�C����

	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@

	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_Size;
	D3DXCOLOR m_col;

	static int m_nTutorialStep;

	static CLight *m_pLight;					//

};

#endif
