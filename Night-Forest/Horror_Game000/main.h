//<=============================================================================
//メイン処理(main.h)
//
//Author:kazuki watanabe
//<=============================================================================
#ifndef _MAIN_H_	//このマクロ定義がされていなかったら
#define _MAIN_H_	//二重インクルード防止のマクロを定義する

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
#define new(s)          _new_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)

#include <stdlib.h>
#include "Renderer.h"
#include "Object.h"
#include <string>   

//<***********************************************************
//ライブラリのリンク
//<***********************************************************
#pragma comment(lib, "d3d9.lib")		//描画処理に必要
#pragma comment(lib, "d3dx9.lib")		//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib, "dxguid.lib")		//DirectXコンポネート(部品)使用に必要
#pragma comment(lib, "winmm.lib")		//システム時刻取得に必要

//<***********************************************************
//マクロ定義集
//<***********************************************************
#define SCREEN_WIDTH		(1280)		//ウインドウの幅
#define SCREEN_HEIGHT		(720)		//ウインドウの高さ
#define MAX_COMMENT			(256)		//コメントの最大数

//<***********************************************************
//グローバル関数
//<***********************************************************
int GetFPS(void);
void SetD_SPEED(void);
void SetS_SPEED(void);

#endif
