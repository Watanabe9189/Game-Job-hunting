//=============================================================================
//�T�E���h����(sound.cpp)
//
//Author:kazuki watanabe
//=============================================================================
#include "sound.h"
#include "Manager.h"

//*****************************************************************************
//���O�錾
//*****************************************************************************
namespace
{
	const float START_VOL_BGM = 2.0f;	//BGM�̏�������
	const float START_VOL_SE = 1.0f;	//���ʉ��̏�����
	const float MAX_VOLUME = 5.0f;		//�ő剹��
	const float MIN_VOLUME = 5.0f;		//�ŏ�����

}
//<********************************
//�ÓI�����o�ϐ��錾
//<********************************
CSound::INFO CSound::m_aSoundInfo[LABEL_MAX] =
{
	{ "data/SE/walk_on_ground-OneLoop.wav",LABEL::LABEL_SE_HIDE,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/BGM/Title-BGM.wav",LABEL::LABEL_BGM_TITLE,TYPE_BGM },//�v���C���[�̒e���ˉ�
	{ "data/BGM/Option-BGM.wav",LABEL::LABEL_BGM_OPTION,TYPE_BGM },//�v���C���[�̒e���ˉ�
	{ "data/BGM/Night-Forest.wav",LABEL::LABEL_BGM_GAME,TYPE_BGM },//�v���C���[�̒e���ˉ�
	{ "data/BGM/Clear-BGM.wav",LABEL::LABEL_BGM_CLEAR,TYPE_BGM },//�v���C���[�̒e���ˉ�
	{ "data/BGM/GameOver.wav",LABEL::LABEL_BGM_GAMEOVER,TYPE_BGM },//�v���C���[�̒e���ˉ�
	{ "data/BGM/Approch-BGM.wav",LABEL::LABEL_BGM_APPROACH,TYPE_BGM },//�v���C���[�̒e���ˉ�
	{ "data/SE/3_zon_warau.wav",LABEL::LABEL_SE_MOAN0,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/mamono_kaibutu1.wav",LABEL::LABEL_SE_MOAN1,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/monster_groan3.wav",LABEL::LABLE_SE_MOAN2,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/3_zon_hoeru.wav",LABEL::LABEL_SE_DEATH0,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/kaibutu_gaaa.wav",LABEL::LABEL_SE_DEATE1,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/Death002.wav",LABEL::LABEL_SE_DEATE2,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/ItemGet000.wav",LABEL::LABEL_SE_ITEMGET,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/Select.wav",LABEL::LABEL_SE_SELECT,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/Selected.wav",LABEL::LABEL_SE_SELECTED,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/Aura000.wav",LABEL::LABEL_SE_ESCAPED,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/crude_laughter.wav",LABEL::LABEL_SE_NOTICED1,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/wind_monster3.wav",LABEL::LABEL_SE_NOTICED2,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/se_mysterious.wav",LABEL::LABEL_SE_NOTICED3,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/se_mysterious2.wav",LABEL::LABEL_SE_FOUND,TYPE_SE },//�v���C���[�̒e���ˉ�
	{ "data/SE/se_mysterious3.wav",LABEL::LABEL_SE_UNSEALED,TYPE_SE },//�v���C���[�̒e���ˉ�
};

float CSound::m_fMasterVolume = START_VOL_BGM;

//<=============================================================================
//
//<=============================================================================
CSound *CSound::Create(void)
{
	CSound *pSound = new CSound;

	assert(pSound != nullptr);

	pSound->Init(CManager::GetRenderer()->GetHwnd());

	return pSound;
}
//<=============================================================================
//�T�E���h�̃R���X�g���N�^
//<=============================================================================
CSound::CSound()
{
	//�l�̃N���A
	m_rDistance = INIT_VECTOR;

	//���x�������J��Ԃ�
	for (int nCnt = 0; nCnt < LABEL_MAX; nCnt++)
	{
		//���ʂ̏�����������
		m_VolumeType[nCnt] = { START_VOL_SE,START_VOL_BGM };
		m_apDataAudio[nCnt] = NULL;						//�I�[�f�B�I�f�[�^
		m_aSizeAudio[nCnt] = NULL;							//�I�[�f�B�I�f�[�^�T�C�Y

		m_pXAudio2 = NULL;								//XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
		m_pMasteringVoice = NULL;						//�}�X�^�[�{�C�X
		m_apSourceVoice[nCnt] = {};				//�\�[�X�{�C�X
		m_VolumeBuff = {};								//DirectSound�̃o�b�t�@���ݒ�̍\����
	}
}
//<=============================================================================
//�T�E���h�̃f�X�g���N�^
//<=============================================================================
CSound::~CSound()
{

}
//<=============================================================================
//����������
//<=============================================================================
HRESULT CSound::Init(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	(void)CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �}�X�^�[�{�C�X�̐���
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if (m_pXAudio2 != NULL)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(m_aSoundInfo[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);

		if (FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);

		if (FAILED(hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition)))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �\�[�X�{�C�X�̐���
		hr = m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_aSoundInfo[nCntSound].Label;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// �t�@�C�����N���[�Y
		CloseHandle(hFile);
	}

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CSound::Uninit(void)
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);

			// �\�[�X�{�C�X�̔j��
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = NULL;

			// �I�[�f�B�I�f�[�^�̊J��
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = NULL;
		}
	}

	// �}�X�^�[�{�C�X�̔j��
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;

	if (m_pXAudio2 != NULL)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}

	// COM���C�u�����̏I������
	CoUninitialize();
}

//=============================================================================
// �Z�O�����g�Đ�(�Đ����Ȃ��~)
//=============================================================================
HRESULT CSound::PlaySound(LABEL label)
{
	XAUDIO2_BUFFER buffer;
	DSBUFFERDESC VolumeBuff;

	//�o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aSoundInfo[label].Type;
	VolumeBuff.dwFlags = DSBCAPS_CTRLVOLUME;//���ʒ����t���O

											// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&m_XVoiceState);

	if (m_XVoiceState.BuffersQueued != 0)
	{// �Đ���

		//������ނ����ʉ��������ꍇ
		if (buffer.LoopCount == TYPE_SE)
		{
			// �ꎞ��~
			m_apSourceVoice[label]->Stop(0);
		}

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	//������ނ����ʉ��������ꍇ
	if (buffer.LoopCount == TYPE_SE)
	{
		//���ʂ��Z�b�g����(0.0f�Ȃ疳���E5.0f�����肩�特����炵�����̂��������A�l���傫���Ȃ�قǁA��������������Ȃ�)
		//�����炭20.0f�܂łȂ特����̉e���͂قڏ��Ȃ�
		m_apSourceVoice[label]->SetVolume(m_VolumeType[label].SEvolume);

	}
	//������ނ��w�i���y�������ꍇ
	if (buffer.LoopCount == TYPE_BGM)
	{

		//���ʂ��Z�b�g����(0.0f�Ȃ疳���E5.0f�����肩�特����炵�����̂��������A�l���傫���Ȃ�قǁA��������������Ȃ�)
		//�����炭20.0f�܂łȂ特����̉e���͂قڏ��Ȃ�
		m_apSourceVoice[label]->SetVolume(m_VolumeType[label].BGMvolume);
	}

	// �Đ�
	m_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=============================================================================
// �Z�O�����g�Đ�(�Đ����Ȃ��~)
//=============================================================================
HRESULT CSound::PlaySoundWithVolume(const LABEL label, const float fVolume)
{
	XAUDIO2_BUFFER buffer;
	DSBUFFERDESC VolumeBuff;

	//�o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aSoundInfo[label].Type;
	VolumeBuff.dwFlags = DSBCAPS_CTRLVOLUME;//���ʒ����t���O

											// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&m_XVoiceState);

	if (m_XVoiceState.BuffersQueued != 0)
	{// �Đ���

	 //������ނ����ʉ��������ꍇ
		if (buffer.LoopCount == TYPE_SE)
		{
			// �ꎞ��~
			m_apSourceVoice[label]->Stop(0);
		}

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	//������ނ����ʉ��������ꍇ
	if (buffer.LoopCount == TYPE_SE)
	{
		m_VolumeType[label].SEvolume = fVolume;
		//���ʂ��Z�b�g����(0.0f�Ȃ疳���E5.0f�����肩�特����炵�����̂��������A�l���傫���Ȃ�قǁA��������������Ȃ�)
		//�����炭20.0f�܂łȂ特����̉e���͂قڏ��Ȃ�
		m_apSourceVoice[label]->SetVolume(m_VolumeType[label].SEvolume);

	}
	//������ނ��w�i���y�������ꍇ
	if (buffer.LoopCount == TYPE_BGM)
	{
		m_VolumeType[label].BGMvolume = fVolume;
		//���ʂ��Z�b�g����(0.0f�Ȃ疳���E5.0f�����肩�特����炵�����̂��������A�l���傫���Ȃ�قǁA��������������Ȃ�)
		//�����炭20.0f�܂łȂ特����̉e���͂قڏ��Ȃ�
		m_apSourceVoice[label]->SetVolume(m_VolumeType[label].BGMvolume);
	}

	// �Đ�
	m_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=============================================================================
//�����ɉe�������T�E���h�Đ�
//=============================================================================
HRESULT CSound::PlaySoundWithDis(const LABEL label,const D3DXVECTOR3 rPos, const D3DXVECTOR3 rTargetPos)
{
	//�������o��
	m_rDistance = D3DXVECTOR3(rPos.x - rTargetPos.x, rPos.y - rTargetPos.y, rPos.z - rTargetPos.z);

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	//�o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aSoundInfo[label].Type;
	m_VolumeBuff.dwFlags =DSBCAPS_CTRLVOLUME;//���ʒ����t���O

	// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&xa2state);

	if (xa2state.BuffersQueued != 0)
	{// �Đ���

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	//�����ɂ���ĉ����Đ�������
	SetDistance(rPos, buffer.LoopCount,label);

	//������ނ����ʉ��������ꍇ
	if (buffer.LoopCount == TYPE_SE)
	{

		//���ʂ��Z�b�g����(0.0f�Ȃ疳���E5.0f�����肩�特����炵�����̂��������A�l���傫���Ȃ�قǁA��������������Ȃ�)
		//�����炭20.0f�܂łȂ特����̉e���͂قڏ��Ȃ�
		m_apSourceVoice[label]->SetVolume(m_VolumeType[label].SEvolume);

	}
	//������ނ��w�i���y�������ꍇ
	if (buffer.LoopCount == TYPE_BGM)
	{

		//���ʂ��Z�b�g����(0.0f�Ȃ疳���E5.0f�����肩�特����炵�����̂��������A�l���傫���Ȃ�قǁA��������������Ȃ�)
		//�����炭20.0f�܂łȂ特����̉e���͂قڏ��Ȃ�
		m_apSourceVoice[label]->SetVolume(m_VolumeType[label].BGMvolume);
	}

	// �Đ�
	m_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=============================================================================
// �Z�O�����g��~(���x���w��)
//=============================================================================
void CSound::StopSound(LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
	 // �ꎞ��~
		m_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//=============================================================================
// �Z�O�����g��~(�S��)
//=============================================================================
void CSound::StopSound(void)
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}
//=============================================================================
// �`�����N�̃`�F�b�N
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}
//=============================================================================
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
//<=============================================================================
//�����ɂ�鉹�ʒ���
//<=============================================================================
void CSound::SetDistance(const D3DXVECTOR3 Pos, const int nType, const LABEL Label)
{
	//<***********************************************************************
	//�����ł����g��Ȃ��ϐ��錾
	//X��
	const float Dis_NEAR		= 350.0f;		//�߂��ꍇ�̋���
	const float Dis_LIT_NEAR	= 750.0f;		//�����߂��ꍇ�̋���
	const float Dis_LIT_FAR		= 1000.0f;		//���������ꍇ�̋���
	const float Dis_FAR			= 1500.0f;		//�����ꍇ�̋���
	//
	//<***********************************************************************

	//�����߂Â��Ă�����
	if (m_rDistance.x <= Dis_NEAR&&
		m_rDistance.z <= Dis_NEAR &&
		!(-m_rDistance.x >= Dis_NEAR) &&
		!(-m_rDistance.z >= Dis_NEAR))
	{
		if (nType == TYPE::TYPE_SE)
		{
			//�剹�ʂɂ���
			m_VolumeType[Label].SEvolume = 2.0f;
		}
		else if (nType == TYPE::TYPE_BGM)
		{
			//�剹�ʂɂ���
			m_VolumeType[Label].BGMvolume = 2.0f;
		}
	}
	//���������߂Â��Ă�����
	else if (m_rDistance.x <= Dis_LIT_NEAR&&
		m_rDistance.z <= Dis_LIT_NEAR &&
		!(-m_rDistance.x >= Dis_LIT_NEAR) &&
		!(-m_rDistance.z >= Dis_LIT_NEAR))
	{
		if (nType == TYPE::TYPE_SE)
		{
			//�剹�ʂɂ���
			m_VolumeType[Label].SEvolume = 1.0f;

		}
		else if (nType == TYPE::TYPE_BGM)
		{
			//�剹�ʂɂ���
			m_VolumeType[Label].BGMvolume = 1.0f;

		}
	}
	//������������������
	else if (m_rDistance.x <= Dis_LIT_FAR&&
		m_rDistance.z <= Dis_LIT_FAR &&
		!(-m_rDistance.x >= Dis_LIT_FAR) &&
		!(-m_rDistance.z >= Dis_LIT_FAR))
	{
		if (nType == TYPE::TYPE_SE)
		{
			//�剹�ʂɂ���
			m_VolumeType[Label].SEvolume = 0.5f;

		}
		else if (nType == TYPE::TYPE_BGM)
		{
			//�剹�ʂɂ���
			m_VolumeType[Label].BGMvolume = 0.5f;

		}
	}
	//��������������
	else if (m_rDistance.x <= Dis_FAR&&
		m_rDistance.z <= Dis_FAR &&
		!(-m_rDistance.x >= Dis_FAR) &&
		!(-m_rDistance.z >= Dis_FAR))
	{
		if (nType == TYPE::TYPE_SE)
		{
			//�剹�ʂɂ���
			m_VolumeType[Label].SEvolume = 0.2f;

		}
		else if (nType == TYPE::TYPE_BGM)
		{
			//�剹�ʂɂ���
			m_VolumeType[Label].BGMvolume = 0.2f;

		}
	}
	//�������������Ă���ꍇ��
	else
	{
		//�����ɂ���
		m_VolumeType[Label].SEvolume = 0.0f;
		m_VolumeType[Label].BGMvolume = 0.0f;
	}
}
//<=============================================================================
//�����ɂ�鉹�ʒ���
//<=============================================================================
//bool CSound::CheckSoundStop(const LABEL Label)
//{
//	bool bStoped = false;
//
//	if(m_)
//}