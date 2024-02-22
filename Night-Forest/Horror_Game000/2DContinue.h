//<==================================================
//2D�ł̃R���e�B�j���[�\���ɓ�����������(2DContinue.h)
//
//Author:kazuki watanabe
//<==================================================
#ifndef _2DCONTINUE_H_
#define _2DCONTINUE_H_

#include "main.h"
#include "object2D.h"

//<*************************************************
//
//<*************************************************
class C2DContinue : public CObject
{
public:

	//<==================================
	//
	//<==================================
	enum TYPE
	{
		TYPE_FRAME = 0,		//�t���[������
		TYPE_CONTINUE,		//�R���e�B�j���[����
		TYPE_SELECT_YES,	//�I����YES����
		TYPE_SELECT_NO,		//�I����NO����
		TYPE_MAX
	};

	//<==================================
	//
	//<==================================
	enum SELECT
	{
		SELECT_YES = 0,
		SELECT_NO,
		SELECT_MAX,
	};

	C2DContinue(int nPriority = FIX_PRIORITY);
	~C2DContinue();

	static C2DContinue *Create(void);

	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override;
	void Draw(void)		override;
	void SetVtx(void)	override {}

	//���݂̑I����
	int GetSelect(void) { return m_nSelect; }

	void SetUpdatefalse(void) { m_bUpdate = false; }	//�`��̃I���I�t
	void SetUpdatetrue(void) { m_bUpdate = true; }	//�`��̃I���I�t

private:

	void SelectUpdate(void);

	D3DXVECTOR2 m_rPos;
	D3DXVECTOR2 m_rSize;
	D3DXCOLOR m_rCol;

	CObject2D *m_apObject2D[TYPE::TYPE_MAX];
	CObject2D *m_apSelect[SELECT::SELECT_MAX];
	int m_nNumSelect;

	static	LPDIRECT3DTEXTURE9	m_apTexture[TYPE::TYPE_MAX];		//�e�N�X�`���ւ̃|�C���^
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//�t�@�C����

	int m_nSelect;
	int m_nOldSelect;

	bool m_bUpdate;

};

#endif
