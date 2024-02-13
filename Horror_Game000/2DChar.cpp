//<==============================================
//2D文字処理(2DChar.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "2DChar.h"
#include "Texture.h"
#include "manager.h"

int C2DChar::m_nNumAll = INITIAL_INT;

LPDIRECT3DTEXTURE9 C2DChar::m_apTexture[INT_VALUE::MAX_TEX] = {};
const char			*C2DChar::m_acFilename[CHAR_TYPE_MAX] =
{

	"data/TEXTURE/HORROR_TITLE.png",						//目的
	"data/TEXTURE/HORROR_INFO000.png",
	"data/TEXTURE/HORROR_INFO002.png",
	"data/TEXTURE/HORROR_INFO003.png"

};
//<======================================
//
//<======================================
C2DChar::C2DChar(int nPriority)
{
	m_nNumAll++;
	m_pos = D3DXVECTOR2(0.0f,0.0f);

	//目的位置の最大値分
	for (int nCnt = 0; nCnt < MAX_DEST; nCnt++)
	{
		m_posDest[nCnt] = D3DXVECTOR2(0.0f, 0.0f);
	}
	m_bArrived = false;

	m_Size = D3DXVECTOR2(0.0f, 0.0f);

	m_eCType = CHAR_TYPE_MAX;
	m_bDisp = true;

	m_nLiveTime = INITIAL_INT;

	m_eFromMove = MOVE_FROM_MAX;
}
//<======================================
//
//<======================================
C2DChar::~C2DChar()
{
	m_nNumAll--;
}
//<======================================
//
//<======================================
C2DChar *C2DChar::Create(const D3DXVECTOR2 pos, const D3DXVECTOR2 Size, const int CType, const MOVE_FROM eMoveFrom, const bool bDisp)
{
	C2DChar *p2DChar = new C2DChar;

	assert(p2DChar != nullptr);

	assert(SUCCEEDED(p2DChar->Init()));

	p2DChar->m_eFromMove = eMoveFrom;

	//移動方法によって処理を分ける
	switch (eMoveFrom)
	{
		//移動しない場合
	case MOVE_FROM_NONE:

		//その位置にする
		p2DChar->SetPosition(pos);

		break;

		//上からくる場合
	case MOVE_FROM_UP:

		//目的のY座標を設定する
		p2DChar->m_posDest[0].y = pos.y;

		//位置の設定
		p2DChar->SetPosition(pos);

		break;

		//下からくる場合
	case MOVE_FROM_DOWN:

		//目的のY座標を設定する
		p2DChar->m_posDest[0].y = pos.y;

		//位置の設定
		p2DChar->SetPosition(pos);

		break;

		//右からくる場合
	case MOVE_FROM_RIGHT:

		//目的のX座標を設定する
		p2DChar->m_posDest[0].x = pos.x;

		//位置の設定
		p2DChar->SetPosition(pos);

		break;					   
				
		//左からくる場合
	case MOVE_FROM_LEFT:		   
				
		//目的のX座標を設定する
		p2DChar->m_posDest[0].x = pos.x;

		//位置の設定
		p2DChar->SetPosition(pos);

		break;
	}

	p2DChar->SetSize(Size);
	p2DChar->m_bDisp = bDisp;

	p2DChar->BindTexture(m_apTexture[CType]);

	return p2DChar;
}
//<======================================
//
//<======================================
HRESULT C2DChar::Init(void)
{
	//テクスチャの初期化
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		//最初だけ読み込む
		if (m_apTexture[nCnt] == nullptr)
		{
			//テクスチャの読み込み
			if ((CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt])) <= -1)
			{
				return E_FAIL;
			}
		}
	}

	CObject2D::Init();

	return S_OK;
}
//<======================================
//
//<======================================
void C2DChar::Update(void)
{
	if (m_bDisp != false)
	{
		m_pos = GetPosition();

		//もし二番目の目的の位置に
		if (m_pos.x != m_posDest[1].x)
		{
			SetVtx();

			//移動方法によって通るか
			MoveVer();
			MoveSide();

			SetPosition(m_pos);
		}
	}
}
//<======================================
//
//<======================================
void C2DChar::SetVtx(void)
{ 
	CObject2D::SetVtx();

	VERTEX_2D *pVtx;

	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	GetVtxBuff()->Unlock();

}
//<======================================
//横から移動の処理
//<======================================
void C2DChar::MoveSide(void)
{
	//マジックナンバー防止用	
	const float MAX_INATIA = 0.015f;	//慣性の最大値
	const int MAX_LIVE = 170;			//滞在時間の最大値

	//右からくる場合
	if (m_eFromMove == MOVE_FROM_RIGHT)
	{
		//まだ到着していなければ
		if (m_bArrived == false)
		{
			//目的の位置に行くまで加算し続け、止まりそうになったら慣性で止まる
			m_pos.x -= (m_posDest[0].x + m_pos.x) * MAX_INATIA;

			//もし目的の位置を超えそうになったら
			if (m_pos.x <= m_posDest[0].x)
			{
				//その位置にする
				m_pos.x = m_posDest[0].x;
			}

			//目的の位置に到着していたら
			if (m_pos.x == m_posDest[0].x)
			{
				//滞在している時間を加算する
				m_nLiveTime++;

				//滞在時間の最大値を超えていたら
				if (m_nLiveTime >= MAX_LIVE)
				{
					//次の目的地を決める
					m_posDest[1].x = 500.0f;

					//ついている判定をする
					m_bArrived = true;

					//初期化しておく
					m_nLiveTime = 0;
				}
			}
		}
		//もし到着していれば
		else if (m_bArrived == true)
		{
			//目的の位置に行くまで加算し続け、止まりそうになったら慣性で止まる
			m_pos.x -= (m_posDest[1].x + m_pos.x) * MAX_INATIA;

			//もし目的の位置を超えそうになったら
			if (m_pos.x <= -m_posDest[1].x)
			{
				//その位置にする
				m_pos.x = -m_posDest[1].x;
			}
		}

	}
	//左からくる場合
	else if (m_eFromMove == MOVE_FROM_LEFT)
	{
		//まだ到着していなければ
		if (m_bArrived == false)
		{
			//目的の位置に行くまで加算し続け、止まりそうになったら慣性で止まる
			m_pos.x += (m_posDest[0].x + m_pos.x) * MAX_INATIA;

			//もし目的の位置を超えそうになったら
			if (m_pos.x >= m_posDest[0].x)
			{
				//その位置にする
				m_pos.x = m_posDest[0].x;
			}

			//目的の位置に到着していたら
			if (m_pos.x == m_posDest[0].x)
			{
				//滞在している時間を加算する
				m_nLiveTime++;

				//滞在時間の最大値を超えていたら
				if (m_nLiveTime >= MAX_LIVE)
				{
					//次の目的地を決める
					m_posDest[1].x = 1700.0f;

					//ついている判定をする
					m_bArrived = true;

					//初期化しておく
					m_nLiveTime = 0;
				}
			}
		}
		//もし到着していれば
		else if (m_bArrived == true)
		{
			//目的の位置に行くまで加算し続け、止まりそうになったら慣性で止まる
			m_pos.x += (m_posDest[1].x + m_pos.x) * MAX_INATIA;

			//もし目的の位置を超えそうになったら
			if (m_pos.x >= m_posDest[1].x)
			{
				//その位置にする
				m_pos.x = m_posDest[1].x;
			}
		}
	}
}
//<======================================
//縦から移動の処理
//<======================================
void C2DChar::MoveVer(void)
{
	//マジックナンバー防止用	
	const float MAX_INATIA = 0.015f;	//慣性の最大値
	const int MAX_LIVE = 170;			//滞在時間の最大値

	//上からくる場合
	if (m_eFromMove == MOVE_FROM_UP)
	{
		//まだ到着していなければ
		if (m_bArrived == false)
		{
			//目的の位置に行くまで加算し続け、止まりそうになったら慣性で止まる
			m_pos.y += (m_posDest[0].y + m_pos.y) * MAX_INATIA;

			//もし目的の位置を超えそうになったら
			if (m_pos.y >= m_posDest[0].y)
			{
				//その位置にする
				m_pos.y = m_posDest[0].y;
			}

			//目的の位置に到着していたら
			if (m_pos.y == m_posDest[0].y)
			{
				//滞在している時間を加算する
				m_nLiveTime++;

				//滞在時間の最大値を超えていたら
				if (m_nLiveTime >= MAX_LIVE)
				{
					//次の目的地を決める
					m_posDest[1].y = 1000.0f;

					//ついている判定をする
					m_bArrived = true;

					//初期化しておく
					m_nLiveTime = 0;
				}
			}
		}
		//もし到着していれば
		else if (m_bArrived == true)
		{
			//目的の位置に行くまで加算し続け、止まりそうになったら慣性で止まる
			m_pos.y += (m_posDest[1].y + m_pos.y) * MAX_INATIA;

			//もし目的の位置を超えそうになったら
			if (m_pos.y >= m_posDest[1].y)
			{
				//その位置にする
				m_pos.y = m_posDest[1].y;
			}
		}
	}
	//下からくる場合
	else if (m_eFromMove == MOVE_FROM_DOWN)
	{
		//まだ到着していなければ
		if (m_bArrived == false)
		{
			//目的の位置に行くまで加算し続け、止まりそうになったら慣性で止まる
			m_pos.y -= (m_posDest[0].y + m_pos.y) * MAX_INATIA;

			//もし目的の位置を超えそうになったら
			if (m_pos.y <= m_posDest[0].y)
			{
				//その位置にする
				m_pos.y = m_posDest[0].y;
			}

			//目的の位置に到着していたら
			if (m_pos.y == m_posDest[0].y)
			{
				//滞在している時間を加算する
				m_nLiveTime++;

				//滞在時間の最大値を超えていたら
				if (m_nLiveTime >= MAX_LIVE)
				{
					//次の目的地を決める
					m_posDest[1].y = 100.0f;

					//ついている判定をする
					m_bArrived = true;

					//初期化しておく
					m_nLiveTime = 0;
				}
			}
		}
		//もし到着していれば
		else if (m_bArrived == true)
		{
			//目的の位置に行くまで加算し続け、止まりそうになったら慣性で止まる
			m_pos.y -= (m_posDest[1].y + m_pos.y) * MAX_INATIA;

			//もし目的の位置を超えそうになったら
			if (m_pos.y <= -m_posDest[1].y)
			{
				//その位置にする
				m_pos.y = -m_posDest[1].y;
			}
		}
	}
}