//<==================================================
//2Dでのコンティニュー表示に特化した処理(2DContinue.cpp)
//
//Author:kazuki watanabe
//<==================================================
#include "2DContinue.h"
#include "manager.h"

//<*************************************************************************
//
//<*************************************************************************
LPDIRECT3DTEXTURE9	C2DContinue::m_apTexture[TYPE::TYPE_MAX] = {};
const char*			C2DContinue::m_acFilename[TYPE::TYPE_MAX] =
{
	NULL,
	"data\\TEXTURE\\GameOver001.png",
	"data\\TEXTURE\\GameOver-Yes.png",
	"data\\TEXTURE\\GameOver-No.png",
};
//<*************************************************************************
//名前宣言
//<*************************************************************************
namespace
{
	const float			DISTANCE_VALUE	= 250.0f;								//距離の値
	const D3DXCOLOR		FRAME_COL		= D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.6f);	//フレームの色
	const D3DXVECTOR2	FRAME_POS		= D3DXVECTOR2(625.0f, 375.0f);			//フレームの位置
	const D3DXVECTOR2	FRAME_SIZE		= D3DXVECTOR2(300.0f, 300.0f);			//フレームのサイズ
	const D3DXVECTOR2	CONTINUE_POS	= D3DXVECTOR2(625.0f, 175.0f);			//コンティニュー文字の位置
	const D3DXVECTOR2	CONTINUE_SIZE	= D3DXVECTOR2(300.0f, 200.0f);			//コンティニュー文字のサイズ
	const D3DXVECTOR2	YESNO_POS		= D3DXVECTOR2(500.0f, 500.0f);			//YESNO文字の位置
	const D3DXVECTOR2	YESNO_SIZE		= D3DXVECTOR2(150.0f, 150.0f);			//YESNO文字のサイズ
}
//<======================================================================
//
//<======================================================================
C2DContinue::C2DContinue(int nPriority)
{
	//初期化
	for (int nCnt = 0; nCnt < TYPE::TYPE_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = {};
	}

	//初期化
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_apSelect[nCnt] = {};
	}
	m_nNumSelect = INITIAL_INT;
	m_nSelect = INITIAL_INT;
	m_nOldSelect = INITIAL_INT;

	m_rPos = D3DXVECTOR2(0.0f, 0.0f);
	m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	m_rCol = INIT_COL;
	m_bUpdate = false;
}
//<======================================================================
//
//<======================================================================
C2DContinue::~C2DContinue()
{

}
//<======================================================================
//
//<======================================================================
C2DContinue *C2DContinue::Create(void)
{
	C2DContinue *p2DSelect = new C2DContinue;

	assert(p2DSelect != nullptr);

	p2DSelect->Init();

	return p2DSelect;
}
//<======================================================================
//
//<======================================================================
HRESULT C2DContinue::Init(void)
{
	//テクスチャの初期化
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		//最初だけ読み込む
		if (m_apTexture[nCnt] == nullptr)
		{
			//テクスチャの読み込み
			if (CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt]) <= -1)
			{
				return E_FAIL;
			}
		}
	}

	m_rPos = FRAME_POS;

	//セレクトの数分繰り返す
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		//
		if (nCnt == TYPE::TYPE_FRAME)
		{
			m_rCol = FRAME_COL;
			m_rSize = FRAME_SIZE;
		}
		else if (nCnt != TYPE::TYPE_FRAME)
		{
			m_rPos = CONTINUE_POS;
			m_rCol = INIT_COL;
			m_rSize = CONTINUE_SIZE;
		}

		//生成する
		m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR2(m_rPos.x, m_rPos.y), m_rSize, m_rCol,m_apTexture[nCnt]);

		assert(m_apObject2D[nCnt] != nullptr);
	}
	//セレクトの数分繰り返す
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_rSize = YESNO_SIZE;
		m_rPos = YESNO_POS;

		//生成する
		m_apSelect[nCnt] = CObject2D::Create(D3DXVECTOR2(m_rPos.x + DISTANCE_VALUE *nCnt, m_rPos.y), m_rSize, m_rCol, m_apTexture[nCnt+2]);

		assert(m_apSelect[nCnt] != nullptr);
	}
	return S_OK;
}
//<======================================================================
//
//<======================================================================
void C2DContinue::Uninit(void)
{
	//セレクトの数分繰り返す
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		//
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
		//
		if (m_apSelect[nCnt] != nullptr)
		{
			m_apSelect[nCnt]->Uninit();
			m_apSelect[nCnt] = nullptr;
		}
	}
	Release();
}
//<======================================================================
//
//<======================================================================
void C2DContinue::Update(void)
{
	if (m_bUpdate)
	{
		//セレクト更新
		SelectUpdate();

		//セレクトの数分繰り返す
		for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
		{
			if (m_apSelect[nCnt] != nullptr)
			{
				m_apSelect[nCnt]->SetVtx();

				//情報の取得
				m_rPos = m_apSelect[nCnt]->GetPosition();
				m_rSize = m_apSelect[nCnt]->GetSize();

				//設定
				m_apSelect[nCnt]->SetPosition(m_rPos);
				m_apSelect[nCnt]->SetSize(m_rSize);

			}
		}

		//セレクトの数分繰り返す
		for (int nCnt = 0; nCnt < TYPE::TYPE_MAX; nCnt++)
		{
			if (m_apObject2D[nCnt] != nullptr)
			{
				m_apObject2D[nCnt]->SetVtx();

				//情報の取得
				m_rPos = m_apObject2D[nCnt]->GetPosition();
				m_rSize = m_apObject2D[nCnt]->GetSize();

				//設定
				m_apObject2D[nCnt]->SetPosition(m_rPos);
				m_apObject2D[nCnt]->SetSize(m_rSize);
			}

		}
	}
}
//<======================================================================
//
//<======================================================================
void C2DContinue::Draw(void)
{

}
//<======================================================================
//
//<======================================================================
void C2DContinue::SelectUpdate(void)
{
	//前回の選択を保存する
	m_nOldSelect = m_nSelect;

	//色を変える
	m_rCol = Change::ChangeColInter(m_rCol, 1.0f, 0.3f, 0.025f);

	//左キーが押されていたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_LEFTARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_LEFT, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + (SELECT::SELECT_MAX - 1)) % SELECT::SELECT_MAX;
		m_rCol.a = 1.0f;
	}
	//右キーが押されていたら
	else if (CManager::GetKeyboard()->bGetTrigger(DIK_RIGHTARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_RIGHT, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + 1) % SELECT::SELECT_MAX;
		m_rCol.a = 1.0f;
	}

	//カラーを設定する
	m_apSelect[m_nOldSelect]->SetColor(INIT_COL);
	m_apSelect[m_nSelect]->SetColor(m_rCol);
}