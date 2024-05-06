//=============================================================================
//サウンド処理(sound.cpp)
//
//Author:kazuki watanabe
//=============================================================================
#include "sound.h"
#include "Manager.h"

//*****************************************************************************
//名前宣言
//*****************************************************************************
namespace
{
	const float START_VOL_BGM = 2.0f;	//BGMの初期音量
	const float START_VOL_SE = 1.0f;	//効果音の初期量
	const float MAX_VOLUME = 5.0f;		//最大音量
	const float MIN_VOLUME = 5.0f;		//最小音量

}
//<********************************
//静的メンバ変数宣言
//<********************************
CSound::INFO CSound::m_aSoundInfo[LABEL_MAX] =
{
	{ "data/SE/walk_on_ground-OneLoop.wav",LABEL::LABEL_SE_HIDE,TYPE_SE },//プレイヤーの弾発射音
	{ "data/BGM/Title-BGM.wav",LABEL::LABEL_BGM_TITLE,TYPE_BGM },//プレイヤーの弾発射音
	{ "data/BGM/Option-BGM.wav",LABEL::LABEL_BGM_OPTION,TYPE_BGM },//プレイヤーの弾発射音
	{ "data/BGM/Night-Forest.wav",LABEL::LABEL_BGM_GAME,TYPE_BGM },//プレイヤーの弾発射音
	{ "data/BGM/Clear-BGM.wav",LABEL::LABEL_BGM_CLEAR,TYPE_BGM },//プレイヤーの弾発射音
	{ "data/BGM/GameOver.wav",LABEL::LABEL_BGM_GAMEOVER,TYPE_BGM },//プレイヤーの弾発射音
	{ "data/BGM/Approch-BGM.wav",LABEL::LABEL_BGM_APPROACH,TYPE_BGM },//プレイヤーの弾発射音
	{ "data/SE/3_zon_warau.wav",LABEL::LABEL_SE_MOAN0,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/mamono_kaibutu1.wav",LABEL::LABEL_SE_MOAN1,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/monster_groan3.wav",LABEL::LABLE_SE_MOAN2,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/3_zon_hoeru.wav",LABEL::LABEL_SE_DEATH0,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/kaibutu_gaaa.wav",LABEL::LABEL_SE_DEATE1,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/Death002.wav",LABEL::LABEL_SE_DEATE2,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/ItemGet000.wav",LABEL::LABEL_SE_ITEMGET,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/Select.wav",LABEL::LABEL_SE_SELECT,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/Selected.wav",LABEL::LABEL_SE_SELECTED,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/Aura000.wav",LABEL::LABEL_SE_ESCAPED,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/crude_laughter.wav",LABEL::LABEL_SE_NOTICED1,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/wind_monster3.wav",LABEL::LABEL_SE_NOTICED2,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/se_mysterious.wav",LABEL::LABEL_SE_NOTICED3,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/se_mysterious2.wav",LABEL::LABEL_SE_FOUND,TYPE_SE },//プレイヤーの弾発射音
	{ "data/SE/se_mysterious3.wav",LABEL::LABEL_SE_UNSEALED,TYPE_SE },//プレイヤーの弾発射音
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
//サウンドのコンストラクタ
//<=============================================================================
CSound::CSound()
{
	//値のクリア
	m_rDistance = INIT_VECTOR;

	//ラベル数分繰り返す
	for (int nCnt = 0; nCnt < LABEL_MAX; nCnt++)
	{
		//音量の初期化をする
		m_VolumeType[nCnt] = { START_VOL_SE,START_VOL_BGM };
		m_apDataAudio[nCnt] = NULL;						//オーディオデータ
		m_aSizeAudio[nCnt] = NULL;							//オーディオデータサイズ

		m_pXAudio2 = NULL;								//XAudio2オブジェクトへのインターフェイス
		m_pMasteringVoice = NULL;						//マスターボイス
		m_apSourceVoice[nCnt] = {};				//ソースボイス
		m_VolumeBuff = {};								//DirectSoundのバッファ情報設定の構造体
	}
}
//<=============================================================================
//サウンドのデストラクタ
//<=============================================================================
CSound::~CSound()
{

}
//<=============================================================================
//初期化処理
//<=============================================================================
HRESULT CSound::Init(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	(void)CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// マスターボイスの生成
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if (m_pXAudio2 != NULL)
		{
			// XAudio2オブジェクトの開放
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(m_aSoundInfo[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// フォーマットチェック
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);

		if (FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);

		if (FAILED(hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition)))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// ソースボイスの生成
		hr = m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// バッファの値設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_aSoundInfo[nCntSound].Label;

		// オーディオバッファの登録
		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// ファイルをクローズ
		CloseHandle(hFile);
	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CSound::Uninit(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);

			// ソースボイスの破棄
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = NULL;

			// オーディオデータの開放
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = NULL;
		}
	}

	// マスターボイスの破棄
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;

	if (m_pXAudio2 != NULL)
	{
		// XAudio2オブジェクトの開放
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}

	// COMライブラリの終了処理
	CoUninitialize();
}

//=============================================================================
// セグメント再生(再生中なら停止)
//=============================================================================
HRESULT CSound::PlaySound(LABEL label)
{
	XAUDIO2_BUFFER buffer;
	DSBUFFERDESC VolumeBuff;

	//バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aSoundInfo[label].Type;
	VolumeBuff.dwFlags = DSBCAPS_CTRLVOLUME;//音量調整フラグ

											// 状態取得
	m_apSourceVoice[label]->GetState(&m_XVoiceState);

	if (m_XVoiceState.BuffersQueued != 0)
	{// 再生中

		//もし種類が効果音だった場合
		if (buffer.LoopCount == TYPE_SE)
		{
			// 一時停止
			m_apSourceVoice[label]->Stop(0);
		}

		// オーディオバッファの削除
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	//もし種類が効果音だった場合
	if (buffer.LoopCount == TYPE_SE)
	{
		//音量をセットする(0.0fなら無音・5.0fあたりから音割れらしきものが発生し、値が大きくなるほど、音割れも激しくなる)
		//おそらく20.0fまでなら音割れの影響はほぼ少ない
		m_apSourceVoice[label]->SetVolume(m_VolumeType[label].SEvolume);

	}
	//もし種類が背景音楽だった場合
	if (buffer.LoopCount == TYPE_BGM)
	{

		//音量をセットする(0.0fなら無音・5.0fあたりから音割れらしきものが発生し、値が大きくなるほど、音割れも激しくなる)
		//おそらく20.0fまでなら音割れの影響はほぼ少ない
		m_apSourceVoice[label]->SetVolume(m_VolumeType[label].BGMvolume);
	}

	// 再生
	m_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=============================================================================
// セグメント再生(再生中なら停止)
//=============================================================================
HRESULT CSound::PlaySoundWithVolume(const LABEL label, const float fVolume)
{
	XAUDIO2_BUFFER buffer;
	DSBUFFERDESC VolumeBuff;

	//バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aSoundInfo[label].Type;
	VolumeBuff.dwFlags = DSBCAPS_CTRLVOLUME;//音量調整フラグ

											// 状態取得
	m_apSourceVoice[label]->GetState(&m_XVoiceState);

	if (m_XVoiceState.BuffersQueued != 0)
	{// 再生中

	 //もし種類が効果音だった場合
		if (buffer.LoopCount == TYPE_SE)
		{
			// 一時停止
			m_apSourceVoice[label]->Stop(0);
		}

		// オーディオバッファの削除
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	//もし種類が効果音だった場合
	if (buffer.LoopCount == TYPE_SE)
	{
		m_VolumeType[label].SEvolume = fVolume;
		//音量をセットする(0.0fなら無音・5.0fあたりから音割れらしきものが発生し、値が大きくなるほど、音割れも激しくなる)
		//おそらく20.0fまでなら音割れの影響はほぼ少ない
		m_apSourceVoice[label]->SetVolume(m_VolumeType[label].SEvolume);

	}
	//もし種類が背景音楽だった場合
	if (buffer.LoopCount == TYPE_BGM)
	{
		m_VolumeType[label].BGMvolume = fVolume;
		//音量をセットする(0.0fなら無音・5.0fあたりから音割れらしきものが発生し、値が大きくなるほど、音割れも激しくなる)
		//おそらく20.0fまでなら音割れの影響はほぼ少ない
		m_apSourceVoice[label]->SetVolume(m_VolumeType[label].BGMvolume);
	}

	// 再生
	m_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=============================================================================
//距離に影響されるサウンド再生
//=============================================================================
HRESULT CSound::PlaySoundWithDis(const LABEL label,const D3DXVECTOR3 rPos, const D3DXVECTOR3 rTargetPos)
{
	//距離を出す
	m_rDistance = D3DXVECTOR3(rPos.x - rTargetPos.x, rPos.y - rTargetPos.y, rPos.z - rTargetPos.z);

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	//バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aSoundInfo[label].Type;
	m_VolumeBuff.dwFlags =DSBCAPS_CTRLVOLUME;//音量調整フラグ

	// 状態取得
	m_apSourceVoice[label]->GetState(&xa2state);

	if (xa2state.BuffersQueued != 0)
	{// 再生中

		// オーディオバッファの削除
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	//距離によって音を再生させる
	SetDistance(rPos, buffer.LoopCount,label);

	//もし種類が効果音だった場合
	if (buffer.LoopCount == TYPE_SE)
	{

		//音量をセットする(0.0fなら無音・5.0fあたりから音割れらしきものが発生し、値が大きくなるほど、音割れも激しくなる)
		//おそらく20.0fまでなら音割れの影響はほぼ少ない
		m_apSourceVoice[label]->SetVolume(m_VolumeType[label].SEvolume);

	}
	//もし種類が背景音楽だった場合
	if (buffer.LoopCount == TYPE_BGM)
	{

		//音量をセットする(0.0fなら無音・5.0fあたりから音割れらしきものが発生し、値が大きくなるほど、音割れも激しくなる)
		//おそらく20.0fまでなら音割れの影響はほぼ少ない
		m_apSourceVoice[label]->SetVolume(m_VolumeType[label].BGMvolume);
	}

	// 再生
	m_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=============================================================================
// セグメント停止(ラベル指定)
//=============================================================================
void CSound::StopSound(LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	m_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 // 一時停止
		m_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//=============================================================================
// セグメント停止(全て)
//=============================================================================
void CSound::StopSound(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}
//=============================================================================
// チャンクのチェック
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
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
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
// チャンクデータの読み込み
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
//<=============================================================================
//距離による音量調整
//<=============================================================================
void CSound::SetDistance(const D3DXVECTOR3 Pos, const int nType, const LABEL Label)
{
	//<***********************************************************************
	//ここでしか使わない変数宣言
	//X軸
	const float Dis_NEAR		= 350.0f;		//近い場合の距離
	const float Dis_LIT_NEAR	= 750.0f;		//少し近い場合の距離
	const float Dis_LIT_FAR		= 1000.0f;		//少し遠い場合の距離
	const float Dis_FAR			= 1500.0f;		//遠い場合の距離
	//
	//<***********************************************************************

	//もし近づいていたら
	if (m_rDistance.x <= Dis_NEAR&&
		m_rDistance.z <= Dis_NEAR &&
		!(-m_rDistance.x >= Dis_NEAR) &&
		!(-m_rDistance.z >= Dis_NEAR))
	{
		if (nType == TYPE::TYPE_SE)
		{
			//大音量にする
			m_VolumeType[Label].SEvolume = 2.0f;
		}
		else if (nType == TYPE::TYPE_BGM)
		{
			//大音量にする
			m_VolumeType[Label].BGMvolume = 2.0f;
		}
	}
	//もし少し近づいていたら
	else if (m_rDistance.x <= Dis_LIT_NEAR&&
		m_rDistance.z <= Dis_LIT_NEAR &&
		!(-m_rDistance.x >= Dis_LIT_NEAR) &&
		!(-m_rDistance.z >= Dis_LIT_NEAR))
	{
		if (nType == TYPE::TYPE_SE)
		{
			//大音量にする
			m_VolumeType[Label].SEvolume = 1.0f;

		}
		else if (nType == TYPE::TYPE_BGM)
		{
			//大音量にする
			m_VolumeType[Label].BGMvolume = 1.0f;

		}
	}
	//もし少し遠かったら
	else if (m_rDistance.x <= Dis_LIT_FAR&&
		m_rDistance.z <= Dis_LIT_FAR &&
		!(-m_rDistance.x >= Dis_LIT_FAR) &&
		!(-m_rDistance.z >= Dis_LIT_FAR))
	{
		if (nType == TYPE::TYPE_SE)
		{
			//大音量にする
			m_VolumeType[Label].SEvolume = 0.5f;

		}
		else if (nType == TYPE::TYPE_BGM)
		{
			//大音量にする
			m_VolumeType[Label].BGMvolume = 0.5f;

		}
	}
	//もし遠かったら
	else if (m_rDistance.x <= Dis_FAR&&
		m_rDistance.z <= Dis_FAR &&
		!(-m_rDistance.x >= Dis_FAR) &&
		!(-m_rDistance.z >= Dis_FAR))
	{
		if (nType == TYPE::TYPE_SE)
		{
			//大音量にする
			m_VolumeType[Label].SEvolume = 0.2f;

		}
		else if (nType == TYPE::TYPE_BGM)
		{
			//大音量にする
			m_VolumeType[Label].BGMvolume = 0.2f;

		}
	}
	//距離が遠すぎている場合は
	else
	{
		//無音にする
		m_VolumeType[Label].SEvolume = 0.0f;
		m_VolumeType[Label].BGMvolume = 0.0f;
	}
}
//<=============================================================================
//距離による音量調整
//<=============================================================================
//bool CSound::CheckSoundStop(const LABEL Label)
//{
//	bool bStoped = false;
//
//	if(m_)
//}