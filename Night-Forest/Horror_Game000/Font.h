//<============================================
//DirectX�ł̃t�H���g����(Font.cpp)
//
//Author:kazuki watanabe
//<============================================
#ifndef _FONT_H_
#define _FONT_H_

#include "main.h"
#include "object.h"

//<********************************************
//�t�H���g�̃N���X��`
//<********************************************
class CFont : public CObject
{

	//���Ɏg�p�\
public:

	//<===============================================
	//���������̃}�N����`
	//<===============================================
#define MAX_STRING	(5120)	//�f�o�b�O�\���̍ő啶����

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_BLINK,
		TYPE_TIMER,
		TYPE_FADE,
		TYPE_MAX,
	};
	
	//�R���X�g���N�^�E�f�X�g���N�^
	CFont(int nPriority = 7);
	~CFont();

	//�����֐�
	static CFont *Create(const RECT Rect, const UINT Width, const UINT Height,
		const int nWeight, const int nCharSet, const D3DXCOLOR col, TYPE Type, const char *aString,...);

	//�����֐�
	static CFont *WithIntCreate(const RECT Rect, const UINT Width, const UINT Height,
		const int nWeight, const int nCharSet, const D3DXCOLOR col, TYPE Type, const char *aString,const int nValue);

	//�I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Print(const char *aStr,...);
	static int GetNum(void) { return m_nNumAll; }

	//<===========================================
	//�s�v�֐�
	//<===========================================
	void SetVtx(void) { return; }
	CObject2D *GetObject2D(void) { return NULL; }

	//�l�����g���Ȃ�
private:

	//�����o�ϐ�
	LPD3DXFONT					m_pFont;					//
	RECT						m_Rect;						//�����̈ʒu
	UINT						m_Height;					//
	UINT						m_Width;					//
	int							m_nWeight;					//�����̑���
	int							m_nWaitTime;				//
	int							m_nCharSet;					//�����Z�b�g
	char						m_aStrDebug[MAX_STRING];	//������
	const char					*m_pString;
	D3DXCOLOR					m_Color;					//�����̐F
	TYPE						m_Type;
	static int m_nNumAll;									//����
	
	int m_nNum;								//���Ԃ�
	int m_nCntTime;							//�o�ߎ���
	RECT m_rDestRect;

	va_list m_args = nullptr;
	char m_aString[MAX_STRING] = {};
	char m_aSaveString[MAX_STRING] = {};
	int m_nLength = 0;
	int m_nStopLength = 0;

};

#endif
