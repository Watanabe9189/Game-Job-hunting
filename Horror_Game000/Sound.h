//=============================================================================
//サウンド処理(sound.h)
//
//Author:kazuki watanabe
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
class CSound
{
public:

	//<================================
	//サウンドタイプの列挙型定義
	//<================================
	enum TYPE
	{
		TYPE_SE = 0,
		TYPE_BGM,
		TYPE_MAX
	};
	//*****************************************************************************
	// サウンド一覧
	//*****************************************************************************
	enum LABEL
	{
		LABEL_SE_HIDE = 0,		//ジャンプ音
		LABEL_BGM_TITLE,		//タイトルBGM
		LABEL_BGM_OPTION,		//オプションBGM
		LABEL_BGM_GAME,			//環境音
		LABEL_BGM_CLEAR,		//クリア音
		LABEL_BGM_GAMEOVER,		//ゲームオーバー音
		LABEL_BGM_APPROACH,		//近づいてくる音
		LABEL_SE_MOAN0,			//うめき声１
		LABEL_SE_MOAN1,			//うめき声２
		LABLE_SE_MOAN2,			//うめき声３
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
	//BGMとSEの音量情報の構造体定義
	//<================================
	struct VOLUMETYPE
	{
		float SEvolume;
		float BGMvolume;
	};
	//<================================
	//サウンド情報の構造体定義
	//<================================
	struct INFO
	{
		char *pFilename;	// ファイル名
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

	IXAudio2 *m_pXAudio2 = NULL;								//XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			//マスターボイス
	IXAudio2MasteringVoice *m_pMasteringVoiceSE = NULL;			//マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];			//ソースボイス
	BYTE *m_apDataAudio[LABEL_MAX];						//オーディオデータ
	DWORD m_aSizeAudio[LABEL_MAX];							//オーディオデータサイズ
	DSBUFFERDESC m_VolumeBuff;									//DirectSoundのバッファ情報設定の構造体
	static float m_fMasterVolume;										//マスターボリューム

																//ボリュームの種類
	VOLUMETYPE m_VolumeType[LABEL_MAX];

	XAUDIO2_VOICE_STATE m_XVoiceState;

	static INFO m_aSoundInfo[LABEL_MAX];
	D3DXVECTOR3 m_rDistance;
};

#endif
