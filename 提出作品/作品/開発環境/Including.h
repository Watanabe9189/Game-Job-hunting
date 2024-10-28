//<====================================
//インクルード用のファイル(Including.h)
//
//Author:Kazuki watanabe
//<====================================
//<***********************************************************
//ヘッダーファイルのインクルード
//<***********************************************************

#include <Windows.h>
#include <stdio.h>
#include <assert.h>
#include "time.h"
#include "d3dx9.h"						//描画処理に必要 
#define DIRECTINPUT_VERSION	(0x0800)	//build時の警告用マクロ
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <stdlib.h>
#include <iostream>
#include "Renderer.h"
#include "Object.h"
#include <string>   
#include <vector>
#include <algorithm>
#include <list>
#include <new>

//サウンドに必要なインクルードファイル
#include "xaudio2.h"					//サウンド処理に必要
#include <dsound.h>						//ダイレクトサウンド
//<***********************************************************
//ライブラリのリンク
//<***********************************************************
#pragma comment(lib, "d3d9.lib")		//描画処理に必要
#pragma comment(lib, "d3dx9.lib")		//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib, "dxguid.lib")		//DirectXコンポネート(部品)使用に必要
#pragma comment(lib, "winmm.lib")		//システム時刻取得に必要
#pragma comment(lib, "dsound.lib")		//サウンドに必要

