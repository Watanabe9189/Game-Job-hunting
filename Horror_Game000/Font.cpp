//<============================================
//DirectX�ł̃t�H���g����(Font.cpp)
//
//Author:kazuki watanabe
//<============================================
#include "Font.h"
#include "manager.h"

//<****************************************************
//�}�N����`
//<****************************************************
#define MAX_FLOATNUM	(2)		//�����_�ȉ��̕\������

//<****************************************************
//�ÓI�����o�ϐ��錾
//<****************************************************
int CFont::m_nNumAll = NULL;									//��

//<====================================================
//�t�H���g�̃R���X�g���N�^
//<====================================================
CFont::CFont(int nPriority)
{
	m_nNumAll++;

	//�l�̏�����
	m_pFont = nullptr;
	m_Rect = { NULL, NULL, NULL, NULL };
	memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));
	m_nWeight = FW_DONTCARE;
	m_Height = NULL;
	m_Width = NULL;
	m_nWaitTime = NULL;
	m_Color = INIT_COL;
	m_nCharSet = SHIFTJIS_CHARSET;
	m_Type = TYPE_NONE;
	m_pString = nullptr;
	m_rDestRect = { NULL, NULL, NULL, NULL };
	
	m_nNum = INITIAL_INT;								//���Ԃ�
	m_nCntTime = INITIAL_INT;							//�o�ߎ���
}
//<====================================================
//�t�H���g�̃f�X�g���N�^
//<====================================================
CFont::~CFont()
{
	m_nNumAll--;
}
//<====================================================
//�t�H���g�̐�������
//<====================================================
CFont *CFont::Create(const RECT Rect, const UINT Width,const UINT Height,
	const int nWeight,const int nCharSet, 
	const D3DXCOLOR col, TYPE Type, const char *aString,...)
{
	//�����p�̃I�u�W�F�N�g
	CFont *PFont = new CFont;

	assert(PFont != nullptr);

	//<*********************************
	//���ݒ菈��
	//<*********************************
	PFont->m_Rect = Rect;				//�l�p�`�̏��

	PFont->m_Height = Height;			//�����̍���
	PFont->m_Width = Width;				//�����̕�
	PFont->m_nWeight = nWeight;			//�����̑���


	//<*********************************
	//���ݒ菈��
	//<*********************************
	PFont->m_nCharSet = nCharSet;		//�����Z�b�g
	PFont->m_Color = col;				//�F
	PFont->m_Type = Type;				//�^�C�v�ݒ�
	PFont->m_pString = aString;
	PFont->Print(aString);					//��������

	assert(SUCCEEDED(PFont->Init()));

	return PFont;
}
//<====================================================
//Int�����̃t�H���g�̐�������
//<====================================================
CFont *CFont::WithIntCreate(const RECT Rect, const UINT Width, const UINT Height,
	const int nWeight, const int nCharSet, const D3DXCOLOR col, TYPE Type, const char *aString, const int nValue)
{
	//�����p�̃I�u�W�F�N�g
	CFont *PFont = new CFont;

	assert(PFont != nullptr);

	//<*********************************
	//���ݒ菈��
	//<*********************************
	PFont->m_Rect = Rect;				//�l�p�`�̏��
	PFont->m_Height = Height;			//�����̍���
	PFont->m_Width = Width;				//�����̕�
	PFont->m_nWeight = nWeight;			//�����̑���


										//<*********************************
										//���ݒ菈��
										//<*********************************
	PFont->m_nCharSet = nCharSet;		//�����Z�b�g
	PFont->m_Color = col;				//�F
	PFont->m_Type = Type;				//�^�C�v�ݒ�

	PFont->m_pString = aString;
	PFont->Print(aString,nValue);					//��������


	assert(SUCCEEDED(PFont->Init()));
	
	return PFont;
}
//<====================================================
//�t�H���g�̏���������
//<====================================================
HRESULT CFont::Init(void)
{
	//�f�o�b�O�\���p�t�H���g�̐���
	if ((D3DXCreateFont(CManager::GetRenderer()->GetDevice()
		, m_Height, m_Width, m_nWeight, D3DX_DEFAULT, FALSE, m_nCharSet,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont))!= S_OK)
	{
		return E_FAIL;
	}

	return S_OK;
}
//<====================================================
//
//<====================================================
void CFont::Uninit(void)
{
	Release();

	//�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}

	//�f�o�b�O�\�����̃N���A
	memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));
}
//<====================================================
//�t�H���g�̍X�V����
//<====================================================
void CFont::Update(void)
{
	//�_�Ń^�C�v��������
	if (m_Type == TYPE::TYPE_BLINK)
	{
		//�����ł����g��Ȃ����[�J���ϐ��̐錾
		const int MAX_WAIT[2] = { 100,200 };	//�ҋ@���Ԃ̍ő�l[2��]
		const float VALUE_COL = 0.05f;			//�F��ύX����l

		//�ҋ@���Ԃ𑝂₷
		m_nWaitTime++;

		//����100�b�𒴂��Ă���&&200�b�𒴂��Ă��Ȃ����
		if (m_nWaitTime >= MAX_WAIT[0]&&!(m_nWaitTime >= MAX_WAIT[1]))
		{
			//�����x�����炷
			m_Color.a -= VALUE_COL;

			//���̒l������肻����������
			if (m_Color.a <= 0.3f)
			{
				//���̒l�ɂ���
				m_Color.a = 0.3f;
			}
		}
		//����200�b�𒴂��Ă�����
		if (m_nWaitTime >= MAX_WAIT[1])
		{
			m_nWaitTime = MAX_WAIT[1];

			//�����x�𑝂₷
			m_Color.a += VALUE_COL;

			//�F���ő�𒴂�������������
			if (m_Color.a >= COLOR_VALUE::ALPHA_OPACITY)
			{
				//�ő�l�ɂ���
				m_Color.a = COLOR_VALUE::ALPHA_OPACITY;

				//���Z�b�g����
				m_nWaitTime = INITIAL_INT;
			}

		}	
	}
	//�t�F�[�h�^�C�v��������
	else if (m_Type == TYPE::TYPE_FADE)
	{
		//�����ł����g��Ȃ����[�J���ϐ��̐錾
		const int MAX_WAIT = 200;			//�ҋ@���Ԃ̍ő�l
		const float VALUE_DECRE = 0.005f;	//���炵�Ă����l�̗�

		//�����ɂȂ��Ă��Ȃ����
		if (!(m_Color.a <= 0.0f))
		{
			//�ҋ@���Ԃ𑝂₷
			m_nWaitTime++;

			//���̎��ԂɂȂ�����
			if (m_nWaitTime >= MAX_WAIT)
			{
				//�����ɂ��Ă���
				m_Color.a -= 0.005f;

				//������艺�ɂȂ肻����������
				if (m_Color.a <= COLOR_VALUE::ALPHA_CLEANNESS)
				{
					//���̒l�ɂ���
					m_Color.a = COLOR_VALUE::ALPHA_CLEANNESS;

					//����������
					m_nWaitTime = INITIAL_INT;
				}
			}
		}
	}
}
//<====================================================
//�t�H���g�̕`�揈��
//<====================================================
void CFont::Draw(void)
{
	//�f�o�b�O����`�悷��
	m_pFont->DrawText(NULL, &m_aStrDebug[0], -1, &m_Rect, DT_LEFT, m_Color);
}
//<====================================================
//�t�H���g�̕������ʏ���
//<====================================================
void CFont::Print(const char *aStr,...)
{
	va_list args = nullptr;
	char aString[MAX_STRING] = {};
	char aSaveString[MAX_STRING] = {};
	int nLength = 0;
	int nStopLength = 0;

	//������̑��
	strcpy(&aString[0], aStr);

	va_start(args, aStr);

	for (char *p = &aString[0]; *p != '\0'; p++)
	{
		if (*p == '%')
		{//�m�F����������ꍇ
			p++;	//�m�F�����܂Ői�߂�

					//�����������ꍇ
			if (*p == 'd')
			{
				sprintf(&aSaveString[0], "%d", va_arg(args, int));

				//������̒������擾
				nLength = (int)strlen(&aSaveString[0]);
			}
			//�����������ꍇ
			if (*p == 'f'&&*p != NULL)
			{
				sprintf(&aSaveString[0], "%f", va_arg(args, double));

				//������̒������擾
				nLength = (int)strlen(&aSaveString[0]);

				//�����_�ȉ��̕����ڂ܂Ŋm�F
				for (int nCntlength = 0; aSaveString[nCntlength] != '\0'; nCntlength++)
				{
					if (aSaveString[nCntlength] == '.')
					{//�����_���������ꍇ

					 //�����_�ȉ��̌��������߂�
						int nMin = (int)strlen(&aSaveString[nCntlength + 1]);

						//�����_����̕������Ǝw�肵���l�܂ł̍��������߂�
						nMin -= MAX_FLOATNUM;

						//������̒����������_�ȉ����ʂ܂łɕ␳
						nLength -= nMin;
					}
				}

			}
			//�����������ꍇ
			if (*p == 'c'&&*p != NULL)
			{
				sprintf(&aSaveString[0], "%c", va_arg(args, char));

				//������̒������擾
				nLength = (int)strlen(&aSaveString[0]);
			}
			//�����񂾂����ꍇ
			if (*p == 's'&&*p != NULL)
			{
				//������
				sprintf(&aSaveString[0], "%s", va_arg(args, const char*));

				//������̒������擾
				nLength = (int)strlen(&aSaveString[0]);
			}

			nStopLength = (int)strlen(p) + 1;
			//���������̊m�F���������̕���������炷
			memmove(p + nLength - 2, p, nStopLength);

			p--;	//�|�C���^��%�܂Ŗ߂�

					//�ψ������w�肳�ꂽ�ꏊ�ɑ}��
			memcpy(p, &aSaveString[0], nLength);
		}
	}

	va_end(args);

	//�������A������
	strcat(&m_aStrDebug[0], &aString[0]);
}