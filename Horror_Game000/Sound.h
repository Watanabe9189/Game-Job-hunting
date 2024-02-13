//=============================================================================
//�T�E���h����(sound.h)
//
//Author:kazuki watanabe
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
class CSound
{
public:

	//<================================
	//�T�E���h�^�C�v�̗񋓌^��`
	//<================================
	enum TYPE
	{
		TYPE_SE = 0,
		TYPE_BGM,
		TYPE_MAX
	};
	//*****************************************************************************
	// �T�E���h�ꗗ
	//*****************************************************************************
	enum LABEL
	{
		LABEL_SE_HIDE = 0,		//�W�����v��
		LABEL_BGM_TITLE,		//�^�C�g��BGM
		LABEL_BGM_OPTION,		//�I�v�V����BGM
		LABEL_BGM_GAME,			//����
		LABEL_BGM_CLEAR,		//�N���A��
		LABEL_BGM_GAMEOVER,		//�Q�[���I�[�o�[��
		LABEL_BGM_APPROACH,		//�߂Â��Ă��鉹
		LABEL_SE_MOAN0,			//���߂����P
		LABEL_SE_MOAN1,			//���߂����Q
		LABLE_SE_MOAN2,			//���߂����R
		LABEL_SE_DEATH0,			//
		LABEL_SE_DEATE1,			//
		LABEL_SE_DEATE2,			//
		LABEL_SE_ITEMGET,
		LABEL_SE_SELECT,
		LABEL_SE_SELECTED,
		LABEL_SE_ESCAPED,
		LABEL_SE_NOTICED1,
		LABEL_SE_NOTICED2,
		LABEL_MAX,

	};

	//<================================
	//BGM��SE�̉��ʏ��̍\���̒�`
	//<================================
	struct VOLUMETYPE
	{
		float SEvolume;
		float BGMvolume;
	};
	//<================================
	//�T�E���h���̍\���̒�`
	//<================================
	struct INFO
	{
		char *pFilename;	// �t�@�C����
		LABEL Label;
		TYPE Type;

	};

	CSound();
	~CSound();

	static CSound *Create(void);

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void UninitWithOut(void);
	HRESULT PlaySound(LABEL label);
	HRESULT PlaySoundWithVolume(const LABEL label, const float fVolume);
	HRESULT PlaySoundWithDis(const LABEL label, const D3DXVECTOR3 rPos, const D3DXVECTOR3 rTargetPos);
	void StopSound(LABEL label);
	void StopSound(void);

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	void SetBgm(const float& BgmVolume, const LABEL Label) { m_VolumeType[Label].BGMvolume = BgmVolume; }
	void SetSE(const float& SEVolume, const LABEL Label) { m_VolumeType[Label].SEvolume = SEVolume; }
	void SetMasterVolume(const float& fMasterVolume) { m_fMasterVolume = fMasterVolume; }

	float GetVolumeSE(const LABEL Label) { return m_VolumeType[Label].SEvolume; }
	float GetVolumeBGM(const LABEL Label) { return m_VolumeType[Label].BGMvolume; }
	static float GetVolumeMaster(void) { return m_fMasterVolume; }

	IXAudio2SourceVoice *GetSource(const LABEL Label) { return m_apSourceVoice[Label]; }
	static INFO GetInfo(int nCnt) { return m_aSoundInfo[nCnt]; }

	XAUDIO2_VOICE_STATE GetXVoiceState(void) { return m_XVoiceState; }

private:

	void SetDistance(const D3DXVECTOR3 Pos, const int nType, const LABEL Label);

	IXAudio2 *m_pXAudio2 = NULL;								//XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			//�}�X�^�[�{�C�X
	IXAudio2MasteringVoice *m_pMasteringVoiceSE = NULL;			//�}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];			//�\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX];						//�I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];							//�I�[�f�B�I�f�[�^�T�C�Y
	DSBUFFERDESC m_VolumeBuff;									//DirectSound�̃o�b�t�@���ݒ�̍\����
	static float m_fMasterVolume;										//�}�X�^�[�{�����[��

																//�{�����[���̎��
	VOLUMETYPE m_VolumeType[LABEL_MAX];

	XAUDIO2_VOICE_STATE m_XVoiceState;

	static INFO m_aSoundInfo[LABEL_MAX];
	D3DXVECTOR3 m_rDistance;
};

#endif
