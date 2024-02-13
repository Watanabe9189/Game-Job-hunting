//<==================================================================================
//C++用プロジェクト[main.cpp]
//
//Author kazuki watanabe
//<==================================================================================
#include "main.h"
#include "Manager.h"

//マクロ定義
#define SLOW_SPEED			(0.5f)					//鈍足の値
#define NORMAL_SPEED		(1)						//等速の値
#define SPEED_UP_VALUE		(2)						//スピードアップの値

#define CLASS_NAME			"WindowsClass"			//ウインドウクラスの名前
#define WINDOW_NAME			"Night-Forest"	//ウインドウの名前(キャプション)

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//グローバル変数宣言
int g_nCountFPS = 0;						//FPSカウンタ
bool g_bDoubleSpeed = false;				//倍速するかしないかどうかの是非
bool g_bSlowSpeed = false;					//遅くするかの是非
//<==================================================================================t
//メイン関数
//<==================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmbLine, int nCmbShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSのメモリサイズ
		CS_CLASSDC,							//ウインドウのスタイル
		WindowProc,							//ウインドウプロシージャ
		0,									//0にする(通常は使用しない)
		0,									//0にする(通常は使用しない)
		hInstance,							//インスタンスハンドル
		LoadIcon(hInstance, IDI_APPLICATION),	//タスクバーのアイコン
		LoadCursor(NULL, IDC_ARROW),		//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			//クライアント領域の背景色
		NULL,								//メニューバー
		CLASS_NAME,							//ウインドウクラスの名前
		LoadIcon(hInstance,IDI_APPLICATION)		//ファイルのアイコン

	};

	HWND hWnd;								//ウインドウハンドル(識別子)
	MSG msg;								//メッセージを格納する変数

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	//画面サイズの構造体

														//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);


	//ウインドウの生成
	hWnd = CreateWindowEx(
		NULL,								//拡張ウインドウスタイル
		CLASS_NAME,							//ウインドウクラスの名前
		WINDOW_NAME,						//ウインドウの名前
		WS_OVERLAPPEDWINDOW,				//ウインドウスタイル
		CW_USEDEFAULT,						//ウインドウの左上X座標
		CW_USEDEFAULT,						//ウインドウの左上Y座標
		(rect.right - rect.left),			//ウインドウの幅
		(rect.bottom - rect.top),			//ウインドウの高さ
		NULL,								//親ウインドウのハンドル
		NULL,								//メニューハンドルまたは子ウインドウID
		hInstance,							//インスタンスハンドル
		NULL								//ウインドウ作成データ
	);


	ShowWindow(hWnd, nCmbShow);
	UpdateWindow(hWnd);

	CManager *pManager = nullptr;

	//メモリリークを出力
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (pManager == nullptr)
	{
		pManager = new CManager;				//メモリ確保を開始する
	}

	//もしメモリ確保に成功したら
	if (pManager != nullptr)
	{
		//初期化処理が失敗したら
		if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
		{
			return -1;
		}
	}
	


	//分解能を設定
	timeBeginPeriod(1);
	DWORD dwCurrentTime = 0;					//現在時刻を初期化する
	DWORD dwExecLastTime = timeGetTime();		//現在時刻を取得(保存)[最後に処理した時刻]

	DWORD dwFrameCount = 0;					//フレーム数のカウントを初期化する
	DWORD dwFPSLastTime = timeGetTime();	//現在時刻を取得(保存)[最後にFPSを計測した時刻]

											//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowの処理

		 //もしWM_QUITメッセージを受け取ったらメッセージループを抜ける
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);				//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);				//ウインドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理

			//どちらもfalseだったら
			if (g_bDoubleSpeed == false && g_bSlowSpeed == false)
			{
				dwCurrentTime = timeGetTime() * NORMAL_SPEED;		//現在時刻を取得
			}
			//倍速モードがtrue&&鈍足モードがfalse
			else if(g_bDoubleSpeed == true&&g_bSlowSpeed == false)
			{
				dwCurrentTime = timeGetTime() * SPEED_UP_VALUE;		//現在時刻を取得(2倍速する)
			}
			//鈍足モードがtrue&&倍速モードがfalse
			else if (g_bSlowSpeed == true && g_bDoubleSpeed == false)
			{
				dwCurrentTime = timeGetTime() / SPEED_UP_VALUE;		//現在時刻を取得(2倍速する)
			}
			//どちらもtrueだった場合
			else if (g_bSlowSpeed == true && g_bDoubleSpeed == true)
			{
				dwCurrentTime = timeGetTime() * NORMAL_SPEED;		//現在時刻を取得(どちらにしろ半減されるため)
			}
			
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過

				//どちらもfalseだったら
				if (g_bDoubleSpeed == false && g_bSlowSpeed == false)
				{
					g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime) * NORMAL_SPEED;		//通常のFPSにする
				}
				//倍速モードがtrue&&鈍足モードがfalse
				else if (g_bDoubleSpeed == true && g_bSlowSpeed == false)
				{
					g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime) * SPEED_UP_VALUE;		//2倍速の状態のFPSにする
				}
				//鈍足モードがtrue&&倍速モードがfalse
				else if (g_bSlowSpeed == true && g_bDoubleSpeed == false)
				{
					g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime) / 2;					//鈍足の状態のFPSにする
				}
				//どちらもtrueだった場合
				else if (g_bSlowSpeed == true && g_bDoubleSpeed == true)
				{
					g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime) * NORMAL_SPEED;		//通常のFPSにする(どちらにしろ半減されるため)
				}

				dwFPSLastTime = dwCurrentTime;		//FPSを測定した時刻を保存
				dwFrameCount = 0;					//フレームカウントをクリア
			}

			//このdwCurrentTimeは速さの鍵となっている
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過

				dwExecLastTime = dwCurrentTime;		//処理開始の時刻[現在時刻]を保存

				//もしメモリ確保に成功したら
				if (pManager != nullptr)
				{
					pManager->Update();				//更新処理

					pManager->Draw();				//描画処理

					//ヒープが破損していたら失敗したことを伝える
					_ASSERTE(_CrtCheckMemory());
				}
				

				dwFrameCount++;						//フレームカウントを加算
			}
		}
	}

	//<==========================
	//メモリ解放
	//<==========================
	//もしメモリ確保に成功したら
	if (pManager != nullptr)
	{
		//終了処理
		pManager->Uninit();
		delete pManager;
		pManager = nullptr;
	}

	//分解能を戻す
	timeEndPeriod(1);

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	_CrtDumpMemoryLeaks();

	return (int)msg.wParam;
}
//<==================================================================================
//ウインドウプロシージャ
//<==================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;	//返り値を格納
	int Width = 0, Height = 0;

	switch (uMsg)
	{
	case WM_DESTROY:				//ウインドウ破棄のメッセージ
									//WM_QUITメッセージを送る

		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:				//キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:				//ESCキー入力

			//ウインドウを破棄する(VK_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
	
			break;
		}
		break;

	case WM_CLOSE:				//バツ閉じ
								//メッセージボックスを表示
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{
			//ウインドウを破棄する(VK_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;			//0を返して終了を防ぐ
		}
		break;

	case WM_LBUTTONDOWN:		//マウス左クリック
								//対象ウインドウにフォーカスを合わせる

		SetFocus(hWnd);
		break;

	case WM_TIMER:				//タイマー発行のメッセージ
		break;

	case WM_MOVE:
		Width = LOWORD(lParam);
		Height = HIWORD(lParam);
		break;

	case WM_SIZE:
		InvalidateRect(hWnd, NULL, true);//画面更新
		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//既定の処理を返す
}
//<==================================================================================
//フレームレートを取得
//<==================================================================================
int GetFPS(void)
{
	return g_nCountFPS;
}
//<==================================================================================
//倍速するかしないかの入れ替え
//<==================================================================================
void SetD_SPEED(void)
{
	//三項演算子で入れ替えを行う
	g_bDoubleSpeed == false ? g_bDoubleSpeed = true : g_bDoubleSpeed = false;
}
//<==================================================================================
//鈍足するかしないかの入れ替え
//<==================================================================================
void SetS_SPEED(void)
{
	//三項演算子で入れ替えを行う
	g_bSlowSpeed == false ? g_bSlowSpeed = true : g_bSlowSpeed = false;
}