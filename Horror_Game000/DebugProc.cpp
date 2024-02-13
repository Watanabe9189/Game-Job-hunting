//==========================================================
//
// �f�o�b�O�\������ [debugproc.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "DebugProc.h"
#include "manager.h"
#include "input.h"
#include "Texture.h"
#include "Sound.h"
#include "Result.h"

//**********************************************************
//�}�N����`
//**********************************************************
#define MAX_FLOATNUM	(2)		//�����_�ȉ��̕\������

LPD3DXFONT CDebug::m_pFont = NULL;

//���݂̉��
const char *CDebug::m_acNowScreen[]
{
	"�^�C�g�����",
	"�I�v�V�������",
	"�`���[�g���A�����",
	"�Q�[�����",
	"���U���g���",
	"�����L���O���",
};
//<==========================================================
//�f�o�b�O�\���̃R���X�g���N�^
//<==========================================================
CDebug::CDebug()
{
	memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));

	m_bDispDebug = true;
}
//<==========================================================
//�f�o�b�O�\���̃f�X�g���N�^
//<==========================================================
CDebug::~CDebug()
{

}
//==========================================================
//�f�o�b�O�\���̏���������
//==========================================================
HRESULT CDebug::Init(void)
{
	//�f�o�b�O�\���p�t�H���g�̐���
	if (FAILED(D3DXCreateFont(CManager::GetRenderer()->GetDevice()
		,18 , 0, FW_MEDIUM, D3DX_DEFAULT, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont)))
	{
		return E_FAIL;
	}

	return S_OK;

}
//==========================================================
//�f�o�b�O�\���̏I������
//==========================================================
void CDebug::Uninit(void)
{
	//�f�o�b�O�\���p�t�H���g�̔p��
	if (m_pFont != NULL)
	{	
		m_pFont->Release();
		m_pFont = NULL;
	}
}
//==========================================================
//�f�o�b�O�\���̍X�V����
//==========================================================
void CDebug::Update(void)
{
	//TAB�L�[�������ꂽ��
	if (CManager::GetKeyboard()->bGetTrigger(DIK_TAB) == true)
	{
		//�O�����Z�q
		m_bDispDebug == true ? m_bDispDebug = false : m_bDispDebug = true;
	}
}
//==========================================================
//�f�o�b�O�\���̕`�揈��
//==========================================================
void CDebug::Draw(void)
{
	//�ꏊ�����߂�
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//
	if (m_bDispDebug == true)
	{
		//�f�o�b�O����`�悷��
		m_pFont->DrawText(NULL, &m_aStrDebug[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	}
	
	//�f�o�b�O�\�����̃N���A
	memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));

}
//==========================================================
//�f�o�b�O�\���̐ݒ菈��
//==========================================================
void CDebug::Print(const char *fmt, ...)
{
#ifdef _DEBUG

	va_list args;
	char aString[MAX_DEBUGSTRING];
	char aSaveString[MAX_DEBUGSTRING];
	int nLength = 0;
	int nStopLength;

	//������̑��
	strcpy(&aString[0], fmt);

	va_start(args, fmt);

	for (char *p = &aString[0]; *p != '\0'; p++)
	{
		if (*p == '%')
		{//�m�F����������ꍇ
			p++;	//�m�F�����܂Ői�߂�

			//�����������ꍇ
			if (*p == 'd'&&*p != NULL)
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

#endif
}
//==========================================================
//�\������e�L�X�g�ݒ�
//==========================================================
void CDebug::SetManual(void)
{
	//�f�o�b�O�\����FPS
	CManager::GetDebugProc()->Print("/<=====================================================\n");
	CManager::GetDebugProc()->Print("�f�o�b�O�\���̕ύX�F[TAB�L�[]\n");
	CManager::GetDebugProc()->Print("FPS�F%d\n",GetFPS());
	CManager::GetDebugProc()->Print("���݂̃I�u�W�F�N�g�̑���[%d]\n", CObject::GetNumObj());
	CManager::GetDebugProc()->Print("���݂̃e�N�X�`���̑���[%d]\n", CTexture::GetNumAll());
	CManager::GetDebugProc()->Print("�}�E�X���WX->[%f],�}�E�X���WY->[%f]\n", CManager::GetMouse()->GetMousePos().x, CManager::GetMouse()->GetMousePos().y);
	CManager::GetDebugProc()->Print("�j��\�ȃu���b�N�̐F->[�F]\n");
	CManager::GetDebugProc()->Print("���݂̉��[%s]\n",m_acNowScreen[CScene::GetMode()]);
	CManager::GetDebugProc()->Print("�^�C�g������Q�[���J��[ENTER�L�[]\n");
	CManager::GetDebugProc()->Print("�`���[�g���A������Q�[���J��[�E���L�[]\n");
	CManager::GetDebugProc()->Print("�Q�[�����烊�U���g�J��[���̃{�X��|��]\n");
	CManager::GetDebugProc()->Print("���U���g����^�C�g���J��[2�L�[]\n");
	CManager::GetDebugProc()->Print("���݂̎���[%d]\n",CScene::GetCount());
}