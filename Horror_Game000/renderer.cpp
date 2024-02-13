//<==============================================
//レンダラー処理(renderer.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "DebugProc.h"
#include "Useful.h"
//<==================================================================================
//レンダラーのコンストラクタ
//<==================================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;			//Direct3Dオブジェクトへのポインタ
	m_pD3DDevice = NULL;	//Direct3Dデバイスへのポインタ
	m_pPixShade = nullptr;
	m_bUsePix = false;
	m_nStencil = INITIAL_INT;
}
//<==================================================================================
//レンダラーのデストラクタ
//<==================================================================================
CRenderer::~CRenderer()
{

}

//<==================================================================================
//レンダラーの初期化処理
//<==================================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm = {};			//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp = {};	//プレゼンテーションモード
	HRESULT hStencil = E_FAIL;


									//Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//中身がNULLだったら
	if (m_pD3D == NULL)
	{
		return E_FAIL;//エラーメッセージを表示
	}

	//現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{//失敗したとき
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;		//バックバッファの形式
	d3dpp.BackBufferCount = 1;					//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;		//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	//デバイスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;					//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//インターバル
																//Direct3Dデバイスの生成

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//ステンシルバッファが使えるかチェック
	if ((m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)!=S_OK))
	{
		return E_FAIL;
	}

	m_hWnd = hWnd;

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3DDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);		//ディザリング有効化
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//テクスチャステージステート
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//乱数の種を設定
	srand((unsigned int)time(0));

	//<**************************
	//ピクセルシェーダー関連
	//<**************************
	CheckPixShade();
	/*m_pPixShade = LoadPixShade();*/
	//<**************************

	return S_OK;
}
//<==================================================================================
//レンダラーの終了処理
//<==================================================================================
void CRenderer::Uninit(void)
{
CObject::ReleaseAll();

//Direct3Dデバイスの破棄
if (m_pD3DDevice != NULL)
{
	m_pD3DDevice->Release();
	m_pD3DDevice = NULL;
}

//Direct3Dオブジェクトの破棄
if (m_pD3D != NULL)
{
	m_pD3D->Release();
	m_pD3D = NULL;
}

}
//<==================================================================================
//レンダラーの更新処理
//<==================================================================================
void CRenderer::Update(void)
{
	//Iボタンが押されていたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_I))
	{
		//フルスクリーンに移動する
		SetWindowLong(m_hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);

		//画面にウィンドウを合わせる
		MoveWindow(m_hWnd, GetSystemMetrics(SM_XVIRTUALSCREEN),
			GetSystemMetrics(SM_YVIRTUALSCREEN),
			GetSystemMetrics(SM_CXVIRTUALSCREEN),
			GetSystemMetrics(SM_CYVIRTUALSCREEN), TRUE);
	}
	//Iボタンが押されていたら
	else if (CManager::GetKeyboard()->bGetTrigger(DIK_O))
	{
		//フルスクリーンに移動する
		SetWindowLong(m_hWnd, GWL_STYLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW);

		//画面にウィンドウを合わせる
		MoveWindow(m_hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TRUE);
	}

	CObject::UpdateAll();
}
//<==================================================================================
//レンダラーの描画処理
//<==================================================================================
void CRenderer::Draw(void)
{
	//画面クリア(バックバッファとZバッファとステンシルバッフアのクリア)
	m_pD3DDevice->Clear
	(	0,														//矩形の数を指定
		NULL,													//描画領域全体をクリア
		(D3DCLEAR_STENCIL|D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),	//クリア対象を指定
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f),						//画面描画色を指定
		1.0f,													//深度バッファに保存するZ値を指定
		0														//ステンシルバッファに保存する値を指定
	);

	//描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CObject::DrawAll();

		CManager::GetDebugProc()->Draw();

		//ピクセルシェーダーを使うなら描画する
		//if (m_bUsePix) { m_pD3DDevice->SetPixelShader(m_pPixShade); }

		CDebug::SetManual();

		//描画終了
		m_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//<==================================================================================
//レンダラーのピクセルシェーダーチェック
//<==================================================================================
void CRenderer::CheckPixShade(void)
{
	D3DCAPS9 caps;						//
	m_pD3DDevice->GetDeviceCaps(&caps);	//

	//ピクセルシェーダーバージョンが使えるかどうか
	if (caps.PixelShaderVersion < D3DPS_VERSION(2, 0)&& caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
	{
		//警告文を表示
		MessageBox(NULL, "対応していません", "ERROR", MB_ICONWARNING);
	}
}
//<===================================================
//
//<===================================================
LPDIRECT3DPIXELSHADER9 CRenderer::LoadPixShade(void)
{

	LPDIRECT3DPIXELSHADER9 shader = NULL;
	HRESULT hr = E_FAIL;

	//シェーダプログラムの読み込み
	LPD3DXBUFFER pShaderSource = nullptr;
	LPD3DXBUFFER pErrMessage = NULL;

	hr = D3DXAssembleShaderFromFile("data\\TEXT\\Monochrome.txt", NULL, NULL, 0, &pShaderSource, &pErrMessage);

	if (FAILED(hr)) 
	{
		//エラーメッセージ表示 文字コードはANSIでした
		::MessageBoxA(NULL, (LPCSTR)(pErrMessage->GetBufferPointer()), "エラー", MB_OK);
		pErrMessage->Release();
		return NULL;
	}

	//ピクセルシェーダ作成
	hr = m_pD3DDevice->CreatePixelShader((DWORD*)pShaderSource->GetBufferPointer(), &shader);

	if (FAILED(hr)) 
	{
		return NULL;
	}

	//ピクセルシェーダを作ったらソースは解放して良い
	pShaderSource->Release();

	return shader;
}
//<==================================================================================
//レンダラーのスクリーンショット作成関数
//<==================================================================================
void CRenderer::ScreenShot(const char *cName)
{
	//ここでしか使わないローカル変数宣言
	D3DXIMAGE_FILEFORMAT FileFormat = D3DXIFF_FORCE_DWORD;	//ファイルフォーマット
	LPDIRECT3D9 pdirect3d9 = nullptr;						//IDirect3D9インターフェイスを取得するための変数
	LPDIRECT3DSURFACE9 pSurface = nullptr;					//サーフェイス変数
	D3DDISPLAYMODE dmode = {};								//ディスプレイモード
	TCHAR fileName[INT_VALUE::MAX_CHAR] = {};							//コピー用のファイル名変数
	FILE* pFile = nullptr;									//ファイル変数

	//もし".png"という拡張子になっていたら
	if (strstr(cName, ".png"))
	{
		////その文字列の中に".png"という文字列があるかのチェックをする
		//assert(strstr(cName, ".png") != nullptr);

		//PNG形式にする
		FileFormat = D3DXIFF_PNG;

		//文字列(ファイル名)をコピーする
		sprintf(fileName, cName);
	}
	//もし".jpg"という拡張子になっていたら
	else if (strstr(cName, ".jpg"))
	{
		////その文字列の中に".jpg"という文字列があるかのチェックをする
		//assert(strstr(cName, ".jpg") != nullptr);

		//JPG方式にする
		FileFormat = D3DXIFF_JPG;

		//文字列(ファイル名)をコピーする
		sprintf(fileName, cName);

	}
	
	//もしファイルが開けていたら
	if (pFile != nullptr)
	{
		//ファイルを閉じる
		fclose(pFile);
	}

	//IDirect3D9インターフェイスを取得する
	m_pD3DDevice->GetDirect3D(&pdirect3d9);

	//現在のディスプレイフォーマットを取得
	if (FAILED(pdirect3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dmode)))
	{
		//IDirect3D9インターフェイスの破棄
		if (pdirect3d9 != nullptr)
		{
			pdirect3d9->Release();
			pdirect3d9 = nullptr;
		}
	}

	//IDirect3D9インターフェイスの破棄
	if (pdirect3d9 != nullptr)
	{
		//これしないとメモリリークする
		pdirect3d9->Release();
		pdirect3d9 = nullptr;
	}

	//キャプチャ用のサーフェイスを作成
	assert(SUCCEEDED(m_pD3DDevice->CreateOffscreenPlainSurface(dmode.Width,
		dmode.Height,
		D3DFMT_A8R8G8B8,
		D3DPOOL_SCRATCH,
		&pSurface,
		NULL)));

	//サーフェイスにフロントバッファのイメージを保存する
	if (FAILED(m_pD3DDevice->GetFrontBufferData(0, pSurface)))
	{
		//サーフェイスの破棄
		if (pSurface != nullptr)
		{
			pSurface->Release();
			pSurface = nullptr;
		}
	}

	//ファイル出力
	if ((D3DXSaveSurfaceToFile(fileName, FileFormat, pSurface, NULL, NULL))!=D3D_OK)
	{
		//サーフェイスの破棄
		if (pSurface != nullptr)
		{
			pSurface->Release();
			pSurface = nullptr;
		}
	}

	//サーフェイスの破棄
	if (pSurface != nullptr)
	{
		pSurface->Release();
		pSurface = nullptr;
	}
}
//<==================================================
//
//<==================================================
void CRenderer::SetBoolPix(const BOOL bBool)
{
	m_bUsePix = Change::Changebool(m_bUsePix, bBool); 
}
