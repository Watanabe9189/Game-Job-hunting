//==========================================================
//
//�f�o�b�O�\������ [debugproc.h]
//Author Ibuki Okusada
//
//==========================================================
#ifndef _DEBUGPROC_H_		//���̃}�N������`����Ă��Ȃ��ꍇ
#define _DEBUGPROC_H_

#include "main.h"

//**********************************************************
//�v���g�^�C�v�錾
//**********************************************************
class CDebug
{
public:


#define MAX_DEBUGSTRING	(5120)	//�f�o�b�O�\���̍ő啶����


	//**********************************************************
	//�X�C�b�`�񋓌^�̒�`
	//**********************************************************
	typedef enum
	{
		DEBUGTYPE_OFF = 0,	//�Ώۋ@�\�����삵�Ă��Ȃ����
		DEBUGTYPE_ON,		//�Ώۋ@�\�����삵�Ă�����
		DEBUGTYPE_MAX

	}DEBUGTYPE;

	CDebug();
	~CDebug();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Print(const char *fmt, ...);
	static void SetManual(void);

private:

	static LPD3DXFONT			m_pFont;						//�t�H���g�ւ̃|�C���^
	char						m_aStrDebug[MAX_DEBUGSTRING];	//�f�o�b�O�\���p�̕�����
	bool						m_bDispDebug;					//�f�o�b�O�\����ON/OFF
	static const char*			m_acNowScreen[];				//�t�@�C����

};

#endif