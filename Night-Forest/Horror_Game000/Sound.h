//=============================================================================
//サウンド処理(sound.h)
//
//Author:kazuki watanabe
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//サウンドに必要なインクルードファイル
#include "xaudio2.h"					//サウンド処理に必要
#include <dsound.h>						//ダイレクトサウンド

//ライブラリファイル
#pragma comment(lib, "dsound.lib")		//サウンドに必要

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
		TYPE_BGM = -1,
		TYPE_SE,
		TYPE_MAX
	};
	//*****************************************************************************
	// サウンド一覧
	//*****************************************************************************
	enum LABEL
	{
		LABEL_SE_HIDE = 0,		//隠れる音
		LABEL_BGM_TITLE,		//タイトルBGM
		LABEL_BGM_OPTION,		//オプションBGM
		LABEL_BGM_GAME,			//環境音
		LABEL_BGM_CLEAR,		//クリア音
		LABEL_BGM_GAMEOVER,		//ゲームオーバー音
		LABEL_BGM_APPROACH,		//近づいてくる音
		LABEL_SE_MOAN0,			//うめき声１
		LABEL_SE_MOAN1,			//うめき声２
		LABLE_SE_MOAN2,			//うめき声３
		LABEL_SE_DEATH0,		//死んだときの音１
		LABEL_SE_DEATE1,		//死んだときの音２
		LABEL_SE_DEATE2,		//死んだときの音３
		LABEL_SE_ITEMGET,		//アイテム取得音
		LABEL_SE_SELECT,		//選択音
		LABEL_SE_SELECTED,		//選択された音
		LABEL_SE_ESCAPED,		//アイテムがすべて集まった時の音
		LABEL_SE_NOTICED1,		//こちらに気づいた１
		LABEL_SE_NOTICED2,		//こちらに気づいた２
		LABEL_SE_NOTICED3,		//こちらに気づいた３
		LABEL_SE_FOUND,			//封印されている光の玉が見つかった時の音
		LABEL_SE_UNSEALED,		//封印されている光の玉が解呪されたときの音
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
	HRESULT InitAll(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(LABEL label);
	HRESULT PlaySoundWithVolume(const LABEL label, const float fVolume);
	HRESULT PlaySoundWithDis(const LABEL label, const D3DXVECTOR3 rPos, const D3DXVECTOR3 rTargetPos);
	void StopSound(LABEL label);
	void StopSound(void);

	HRESULT CheckChunkSound(const LABEL Label);
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

	int m_nNumSound;
};

#endif
