//<======================================================================
//2Dでの選択肢処理(2DSelect.cpp)
//
//Author:kazuki watanabe
//<======================================================================
#include "2DSelect.h"
#include "manager.h"

//<======================================================================
//
//<======================================================================
C2DSelect::C2DSelect(int nPriority)
{
	memset(&m_acFilename[0], NULL, sizeof(m_acFilename));
	memset(&m_apTexture[0], NULL, sizeof(m_apTexture));

	memset(&m_apObject2D[0], NULL, sizeof(m_apObject2D));
	m_nNumSelect = INITIAL_INT;
	m_nSelect = INITIAL_INT;
	m_nOldSelect = INITIAL_INT;

	m_fDistance = 350.0f;

	m_rPos = D3DXVECTOR2(0.0f,0.0f);
	m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	m_pChangeCol = nullptr;
}
//<======================================================================
//
//<======================================================================
C2DSelect::~C2DSelect()
{

}
//<======================================================================
//
//<======================================================================
C2DSelect *C2DSelect::Create(const D3DXVECTOR2 rPos,const int nNumSelect)
{
	C2DSelect *p2DSelect = new C2DSelect;

	assert(p2DSelect );

	//値の代入
	p2DSelect->m_rPos = rPos;
	p2DSelect->m_nNumSelect = nNumSelect;

	p2DSelect->Init();

	return p2DSelect;
}
//<======================================================================
//
//<======================================================================
HRESULT C2DSelect::Init(void)
{
	m_pChangeCol = ChangeCol::Create();

	assert(m_pChangeCol);

	//セレクトの数分繰り返す
	for (int nCnt = 0; nCnt < m_nNumSelect; nCnt++)
	{
		//生成する
		m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR2(m_rPos.x +m_fDistance *nCnt,m_rPos.y), D3DXVECTOR2(150.0f, 150.0f),m_pChangeCol->GetColor());

		assert(m_apObject2D[nCnt] );
	}

	return S_OK;
}
//<======================================================================
//
//<======================================================================
void C2DSelect::Uninit(void)
{
	//セレクトの数分繰り返す
	for (int nCnt = 0; nCnt < m_nNumSelect; nCnt++)
	{
		//
		if (m_apObject2D[nCnt] )
		{
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
	}

	//
	if (m_pChangeCol)
	{
		delete m_pChangeCol;
		m_pChangeCol = nullptr;
	}

	Release();
}
//<======================================================================
//
//<======================================================================
void C2DSelect::Update(void)
{
	//セレクト更新
	SelectUpdate();

	//セレクトの数分繰り返す
	for (int nCnt = 0; nCnt < m_nNumSelect; nCnt++)
	{
		if (m_apObject2D[nCnt] )
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
//<======================================================================
//
//<======================================================================
void C2DSelect::Draw(void) 
{
	
}
//<======================================================================
//
//<======================================================================
void C2DSelect::SelectUpdate(void)
{
	//前回の選択を保存する
	m_nOldSelect = m_nSelect;

	m_pChangeCol->ChangeColAdd();

	//左キーが押されていたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_LEFTARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_LEFT, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + (m_nNumSelect - 1)) % m_nNumSelect;
		m_pChangeCol->SetColor(INIT_COL);
	}
	//右キーが押されていたら
	else if (CManager::GetKeyboard()->bGetTrigger(DIK_RIGHTARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_RIGHT, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + 1) % m_nNumSelect;
		m_pChangeCol->SetColor(INIT_COL);
	}

	//カラーを設定する
	m_apObject2D[m_nOldSelect]->SetColor(D3DXCOLOR(1.0f,1.0f,1.0f, m_pChangeCol->GetMinAlpha()));
	m_apObject2D[m_nSelect]->SetColor(m_pChangeCol->GetColor());
}
//<=============================================
//
//<=============================================
void C2DSelect::SetTexName(const char *pFileName, int nCnt)
{
	//ファイル名の代入
	m_acFilename[nCnt] = pFileName;

	//テクスチャの読み込み
	CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt]);

	//中身があれば
	if (m_apObject2D[nCnt] )
	{
		//テクスチャの割り当て
		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

}