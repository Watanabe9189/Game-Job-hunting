//<==================================
//カメラ処理(Camera.cpp)
//
//Author:kazuki watanabe
//<==================================
#include "Camera.h"
#include "manager.h"
#include "input.h"
#include "DebugProc.h"

//<**************************************************
//名前宣言
//<**************************************************
namespace
{
	const float MOVE = 5.0f;					//移動量
	const float START_LENGTH = 800.0f;			//元の距離
	const float MAX_LENGTH = 10000.0f;			//最大距離
	const float MIN_LENGTH = 10.0f;				//最少距離
	const float ROT_MOVE = 0.025f;				//回転移動量
	const float MIN_ROT = -D3DX_PI * 0.499f;	//カメラ固定用
	const float MAX_ROT = D3DX_PI * 0.499f;		//カメラ固定用

	
	const float REVISE_POSV = 0.12f;	//視点の補正値
	const float REVISE_POSR = 0.8f;	//注視点の補正値
	const float POSY_MAX = 90.0f;	//高さ(?)の最大値
	const float DIS_Y = 150.0f;	//Y軸が離れている値

	const float MAX_DISTANCE = 5000.0f;
	const float MIN_DISTANCE = 1.0f;
}

//<=================================
//カメラのコンストラクタ
//<=================================
Ccamera::Ccamera()
{
	//値のクリア
	m_posV = INIT_VECTOR;	//視点
	m_posR = INIT_VECTOR;	//注視点
	m_vecU = INIT_VECTOR;	//上方向ベクトル
	m_rot =  INIT_VECTOR;	//向き
	m_move = INIT_VECTOR;	//移動量

	m_fDistance = NULL;			//距離

	m_rotVDiff = NULL;			//目標の視点の差分

	m_mtxProjection = {};		//マトリックスプロジェクション
	m_mtxView = {};				//マトリックスビュー

	m_Type = TYPE_XRAY;			//投影タイプ
}
//<=================================
//カメラのデストラクタ
//<=================================
Ccamera::~Ccamera()
{

}
//<=================================
//カメラの生成処理
//<=================================
Ccamera *Ccamera::Create(void)
{
	Ccamera *pCamera = NULL;

	if (pCamera == NULL)
	{
		pCamera = new Ccamera();
	}

	if (pCamera != NULL)
	{
		pCamera->Init();
	}

	return pCamera;
}
//<=================================
//カメラの初期化処理
//<=================================
HRESULT Ccamera::Init(void)
{
	m_posV = D3DXVECTOR3(-183.0f, 290.0f, 100.0f);	//視点
	m_posR = D3DXVECTOR3(0.0f, 200.0f, 0.0f);		//注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//上方向ベクトル
	m_rot = INIT_VECTOR;							//向き
	m_move = INIT_VECTOR;							//移動量

	m_posROld = m_posR;								//注視点
	m_fDistance = START_LENGTH;						//距離

	m_posVDest = m_posV;							//目標の視点
	m_posRDest = m_posR;							//目標の注視
				
	m_rotVDest = m_rot;								//目標の向き
	m_rotVDiff = 0.0f;								//目標の視点の差分

	m_bFollow = false;								//追尾する

	m_mtxProjection = {};
	m_mtxView = {};

	return S_OK;
}
//<=================================
//カメラの終了処理
//<=================================
void Ccamera::Uninit(void)
{

}
//<=================================
//カメラの更新処理
//<=================================
void Ccamera::Update(void)
{
	CManager::GetDebugProc()->Print("<=====================================================\n");
	CManager::GetDebugProc()->Print("[カメラ関連のデバッグ表示]\n");
	CManager::GetDebugProc()->Print("<=====================================================\n");
	CManager::GetDebugProc()->Print("[視点]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_posV.x, m_posV.y, m_posV.z);
	CManager::GetDebugProc()->Print("[注視点]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_posR.x, m_posR.y, m_posR.z);
	CManager::GetDebugProc()->Print("[向き]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_rot.x, m_rot.y, m_rot.z);
	CManager::GetDebugProc()->Print("[距離]：%f\n",m_fDistance);

	//CManager::GetDebugProc()->Print("追従の切り替え[Mキー]\n");
	//CManager::GetDebugProc()->Print("投影方法の切り替え[LSHIFT]\n");

	//ゲーム画面だったら
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		//ジャンプしていれば
		if (m_bFollow == true)
		{
			CManager::GetDebugProc()->Print("追従しているかどうか[している]\n\n");
			SetMoveFollow();
		}
		//していなければ
		else
		{
			CManager::GetDebugProc()->Print("追従しているかどうか[していない]\n\n");

			MoveVR();
		}
	}
	//ゲーム画面だったら
	if (CManager::GetMode() == CScene::MODE_TITLE)
	{
		//回転する
		m_rot.y += 0.005f;
		SetRot();
		SetV();
	}
	//ゲーム画面だったら
	if (CManager::GetMode() == CScene::MODE_RESULT)
	{
		//リザルトが失敗状態だったら
		if (CScene::GetRes() == CScene::TYPE_RESULT_FAILED)
		{
			m_posV = D3DXVECTOR3(-78.0f, 21.0f, -78.0f);
			m_posR = D3DXVECTOR3(-77.0f, 21.0f, -77.0f);
			m_rot = D3DXVECTOR3(0.0f, 0.46f, 0.17f);
			m_fDistance = 1.0f;
		}
		//リザルトが成功状態だったら
		else if (CScene::GetRes() == CScene::TYPE_RESULT_SUCCEEDED)
		{
			m_posV = D3DXVECTOR3(6.0f, 27.0f, -113.0f);
			m_posR = D3DXVECTOR3(6.0f, 46.0f, 5.9f);
			m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.16f);
			m_fDistance = 121.0f;
		}
		/*ControllMouse();*/
	}

#ifdef _DEBUG
	////<***************************
	////投影方法のチェンジ
	////<***************************
	//if (CManager::GetKeyboard()->bGetTrigger(DIK_LSHIFT) == true)
	//{
	//	//三項演算子
	//	m_Type == TYPE_XRAY ? m_Type = TYPE_PARALLEL : m_Type = TYPE_XRAY;

	//	//<*************************************************
	//	//式内容：式１?式２:式３
	//	//もし式１が真なら式２を実行し、偽なら式３を実行する
	//	//<*************************************************
	//}
#endif
}
//<=================================
//
//<=================================
void Ccamera::ControllMouse(void)
{
	m_fDistance -= CManager::GetMouse()->GetMouseMove().z;

	//
	if (CManager::GetMouse()->GetMousePress(CMouse::MOUSE_BUTTON_RIGHT))
	{
		m_rot.y += CManager::GetMouse()->GetMouseRotate().x;
		m_rot.z += CManager::GetMouse()->GetMouseRotate().y;
	}
	//
	if (CManager::GetMouse()->GetMousePress(CMouse::MOUSE_BUTTON_WHEEL))
	{
		m_posR.x += CManager::GetMouse()->GetMouseMove().x;
		m_posR.z += CManager::GetMouse()->GetMouseMove().z;
		m_posR.y += CManager::GetMouse()->GetMouseMove().y;
	}

	//
	if (m_fDistance >= MAX_DISTANCE)
	{
		m_fDistance = MAX_DISTANCE;
	}
	//
	if (m_fDistance <= MIN_DISTANCE)
	{
		m_fDistance = MIN_DISTANCE;
	}

	SetRot();
	SetV();
	SetR();
}
//<=================================
//
//<=================================
void Ccamera::SetMoveFollow(void)
{

	//<**************************************************
	//Z方向回転
	//<**************************************************
	//上方向に回転する
	if (CManager::GetKeyboard()->bGetPress(DIK_R) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LX, 0) > 0)
	{

		m_rot.z += ROT_MOVE;

	}
	//下方向に回転する
	else if (CManager::GetKeyboard()->bGetPress(DIK_F) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LX, 0) < 0)
	{

		m_rot.z -= ROT_MOVE;

	}

	m_rot.y += CManager::GetMouse()->GetMouseRotate().x;
	m_rot.z += CManager::GetMouse()->GetMouseRotate().y;

	//<**************************************************
	//Y方向回転
	//<**************************************************
	//左方向に回転する
	if (CManager::GetKeyboard()->bGetPress(DIK_Z) == true || CManager::GetJoyPad()->XGetStickPressR(BUTTON_LY, 0) < 0)
	{
		m_rot.y -= ROT_MOVE;
	}
	//右方向に回転する
	else if (CManager::GetKeyboard()->bGetPress(DIK_C) == true || CManager::GetJoyPad()->XGetStickPressR(BUTTON_LY, 0) > 0)
	{
		m_rot.y += ROT_MOVE;
	}
	SetRot();
	SetV();
}
//<=================================
//
//<=================================
void Ccamera::MoveRot(void)
{
	CJoyPad *pJoyPad = CManager::GetJoyPad();

	//追従していなければ
	if (m_bFollow == false)
	{
		//z軸方向に回転する
		if (CManager::GetKeyboard()->bGetPress(DIK_R) == true || pJoyPad->XGetStickPressR(BUTTON_LX, 0) < 0)
		{

			m_rot.z += ROT_MOVE;

		}
		//z軸方向に逆回転する
		if (CManager::GetKeyboard()->bGetPress(DIK_F) == true || pJoyPad->XGetStickPressR(BUTTON_LX, 0) > 0)
		{

			m_rot.z -= ROT_MOVE;

		}
	}
	//Y軸方向に回転する
	if (CManager::GetKeyboard()->bGetPress(DIK_Z) == true || pJoyPad->XGetStickPressR(BUTTON_LY, 0) < 0)
	{

		m_rot.y += ROT_MOVE;

	}
	//Y軸方向に逆回転する
	if (CManager::GetKeyboard()->bGetPress(DIK_C) == true || pJoyPad->XGetStickPressR(BUTTON_LY, 0) > 0)
	{
		m_rot.y -= ROT_MOVE;
	}

	//回転の補正
	SetRot();

	//視点の代入処理
	MoveVR();
}
//<=================================
//
//<=================================
void Ccamera::MoveVR(void)
{
	//追従していなければ
	if (m_bFollow == false)
	{
		//<**************************************
		//左移動関連
		//<**************************************
		if (CManager::GetKeyboard()->bGetPress(DIK_LEFTARROW) == true || CManager::GetJoyPad()->XGetStickPressR(BUTTON_LX, 0) < 0)
		{
			//左上移動
			if (CManager::GetKeyboard()->bGetPress(DIK_UPARROW) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LY, 0) > 0)
			{

				m_move.x += sinf(-D3DX_PI * MOVE_LRDW + m_rot.y) * MOVE;
				m_move.y += cosf(-D3DX_PI * MOVE_LRDW + m_rot.y) * MOVE;
			}
			//左下移動
			else if (CManager::GetKeyboard()->bGetPress(DIK_DOWNARROW) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LY, 0) < 0)
			{

				m_move.x += sinf(-D3DX_PI * MOVE_LRUP + m_rot.y) * MOVE;
				m_move.y += cosf(-D3DX_PI * MOVE_LRUP + m_rot.y) * MOVE;
			}
			//左移動
			else
			{

				m_move.x += sinf(-D3DX_PI * MOVE_LR + m_rot.y) * MOVE;
				m_move.y += cosf(-D3DX_PI * MOVE_LR + m_rot.y) * MOVE;
			}

		}
		//<**************************************
		//右移動関連
		//<**************************************
		else if (CManager::GetKeyboard()->bGetPress(DIK_RIGHTARROW) == true || CManager::GetJoyPad()->XGetStickPressR(BUTTON_LX, 0) > 0)
		{

			//右上移動
			if (CManager::GetKeyboard()->bGetPress(DIK_UPARROW) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LY, 0) > 0)
			{

				m_move.x += sinf(D3DX_PI * MOVE_LRDW + m_rot.y) * MOVE;
				m_move.y += cosf(D3DX_PI * MOVE_LRDW + m_rot.y) * MOVE;
			}
			//右下移動
			else if (CManager::GetKeyboard()->bGetPress(DIK_DOWNARROW) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LY, 0) < 0)
			{

				m_move.x += sinf(D3DX_PI * MOVE_LRUP + m_rot.y) * MOVE;
				m_move.y += cosf(D3DX_PI * MOVE_LRUP + m_rot.y) * MOVE;
			}
			//右移動
			else
			{

				m_move.x += sinf(D3DX_PI * MOVE_LR + m_rot.y) * MOVE;
				m_move.y += cosf(D3DX_PI * MOVE_LR + m_rot.y) * MOVE;
			}

		}
		//<***************************
		//前移動
		//<***************************
		else if (CManager::GetKeyboard()->bGetPress(DIK_UPARROW) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LY, 0) > 0)
		{

			m_move.x += sinf(m_rot.y) * MOVE;
			m_move.y += cosf(m_rot.y) * MOVE;
		}

		//<***************************
		//手前移動
		//<***************************
		else if (CManager::GetKeyboard()->bGetPress(DIK_DOWNARROW) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LY, 0) < 0)
		{

			m_move.x += sinf(D3DX_PI + m_rot.y) * MOVE;
			m_move.y += cosf(D3DX_PI + m_rot.y) * MOVE;
		}
	}
#ifdef _DEBUG
	//<***************************
	//投影方法のチェンジ
	//<***************************
	if (CManager::GetKeyboard()->bGetTrigger(DIK_M) == true)
	{
		m_bFollow == true ? m_bFollow = false : m_bFollow = true;
	}
#endif
	//移動量分を加算
	m_posV.x += m_move.x;
	m_posV.y += m_move.y;
	m_posV.z += m_move.z;

	//移動量をリセット
	m_move.x = 0.0f;
	m_move.y = 0.0f;
	m_move.z = 0.0f;
}
//<=================================
//
//<=================================
void Ccamera::SetV(void)
{
	//追従していなければ
	if (m_bFollow == false)
	{
		//視点の代入処理
		m_posV.x = m_posR.x + cosf(m_rot.z) * sinf(m_rot.y) * -m_fDistance;
		m_posV.y = m_posR.y + sinf(m_rot.z) * -m_fDistance;
		m_posV.z = m_posR.z + cosf(m_rot.z) * cosf(m_rot.y) * -m_fDistance;
	}

	//<=================================
	//追従処理は追従対象の処理内で行う
	//<=================================
}
//<=================================
//
//<=================================
void Ccamera::SetR(void)
{
	//追従していなければ
	if (m_bFollow == false)
	{
		//注視点の代入処理
		m_posR.x = m_posV.x + cosf(m_rot.z) * sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.z) * cosf(m_rot.y) * m_fDistance;
		m_posR.y = m_posV.y + sinf(m_rot.z) * m_fDistance;
	}

	//<=================================
	//追従処理は追従対象の処理内で行う
	//<=================================
}
//<=================================
//
//<=================================
void Ccamera::SetRot(void)
{
	//<*******************
	//Y軸の補正
	//<*******************
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	//<*******************
	//Z軸の補正
	//<*******************
	if (m_rot.z > MAX_ROT)
	{
		m_rot.z = MAX_ROT;
	}
	else if (m_rot.z < MIN_ROT)
	{
		m_rot.z = MIN_ROT;
	}
}
//<=================================
//カメラの追従処理
//<=================================
void Ccamera::SetFollow(const D3DXVECTOR3 rTargetPos, const D3DXVECTOR3 rTargetRot, const VISIBILITY eVisibility)
{
	//
	float PosY = INITIAL_FLOAT;			//

	if (!m_bFollow)
	{
		m_bFollow = true;
	}

	//三人称視点だったら
	if (eVisibility == VISIBILITY::VISIBILITY_TPS)
	{
		//もし高さが上だったら
		if (rTargetPos.y >= POSY_MAX)
		{
			PosY = rTargetPos.y - POSY_MAX;
		}
		//<*************************************************************************************
		//視点の代入処理
		m_posVDest.x = (rTargetPos.x + sinf(D3DX_PI + rTargetRot.y) * POSY_MAX) + cosf(m_rot.z) *
			sinf(m_rot.y) * -m_fDistance;

		m_posVDest.y = PosY + DIS_Y + sinf(m_rot.z) * -m_fDistance;

		m_posVDest.z = (rTargetPos.z + cosf(D3DX_PI + rTargetRot.y) * POSY_MAX) + cosf(m_rot.z) *
			cosf(m_rot.y) * -m_fDistance;

		//視点の補正をする
		m_posV += (m_posVDest - m_posV) * REVISE_POSV;
		//<*************************************************************************************
		//注視点の代入処理
		m_posRDest.x = m_posV.x + cosf(m_rot.z) *
			sinf(m_rot.y) * m_fDistance;

		m_posRDest.y = m_posV.y + sinf(m_rot.z) *
			m_fDistance;

		m_posRDest.z = m_posV.z + cosf(m_rot.z) *
			cosf(m_rot.y) * m_fDistance;

		//注視点の補正をする
		m_posR += (m_posRDest - m_posR) * REVISE_POSR;
	}
	//一人称視点だったら
	else if (eVisibility == VISIBILITY::VISIBILITY_FPV)
	{
		//もし高さが上だったら
		if (rTargetPos.y >= POSY_MAX)
		{
			PosY = rTargetPos.y - POSY_MAX;
		}
		//<*************************************************************************************
		//視点の代入処理
		m_posVDest.x = (rTargetPos.x + sinf(D3DX_PI + m_rot.y));

		m_posVDest.y = PosY + DIS_Y + sinf(m_rot.z);

		m_posVDest.z = (rTargetPos.z + cosf(D3DX_PI + m_rot.y));

		//視点の補正をする
		m_posV += (m_posVDest - m_posV) * REVISE_POSV;
		//<*************************************************************************************
		//注視点の代入処理
		m_posRDest.x = m_posV.x + cosf(m_rot.z) *
			sinf(m_rot.y) * m_fDistance;

		m_posRDest.y = m_posV.y + sinf(m_rot.z) *
			m_fDistance;

		m_posRDest.z = m_posV.z + cosf(m_rot.z) *
			cosf(m_rot.y) * m_fDistance;

		//注視点の補正をする
		m_posR += (m_posRDest - m_posR) * REVISE_POSR;
	}
}
//<=================================
//カメラの設置処理
//<=================================
void Ccamera::SetCamera(void)
{
//<************************
//この関数限定のマクロ定義
//<************************
#define MAX_Z	(1000.0f)	//プロジェクションマトリックス作成時のZ軸の最大値
#define MIN_Z	(10.0f)		//プロジェクションマトリックス作成時のZ軸の最小値

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//タイプが透視投影だった場合
	if (m_Type == TYPE_XRAY)
	{
		//プロジェクションマトリックスの作成(透視投影)
		//※オブジェクトの距離の影響を受ける
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(45.0f),						//視野
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//縦横比
			MIN_Z,										//Z軸の最小値
			MAX_Z);										//Z軸の最大値
	}
	//タイプが平行投影だった場合
	else if (m_Type == TYPE_PARALLEL)
	{
		//プロジェクションマトリックスの作成(平行投影)
		//※オブジェクトの距離の影響を受けない
		D3DXMatrixOrthoLH(&m_mtxProjection,
			SCREEN_WIDTH,	//幅
			SCREEN_HEIGHT,	//高さ
			MIN_Z,			//Z軸の最小値
			MAX_Z);			//Z軸の最大値
	}		

	//プロジェクションマトリックスの設定
	CManager::GetRenderer()->GetDevice()->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//ビューマトリックスの設定
	CManager::GetRenderer()->GetDevice()->SetTransform(D3DTS_VIEW, &m_mtxView);

}