//<==============================================
//オブジェクト処理(object.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "object.h"
#include "Camera.h"
#include "Manager.h"
#include "Stencil.h"

//<*****************************************
//静的メンバ変数宣言
//<*****************************************
int CObject::m_nNumAll = 0;						//総数
CObject *CObject::m_apTop[NEED_PRIORITY] = { nullptr };
CObject *CObject::m_apCur[NEED_PRIORITY] = { nullptr };
CObject *CObject::m_pObject = nullptr;
CObject *CObject::m_pObjNext = nullptr;
//CObject *CObject::m_apObject[NEED_PRIORITY][MAX_OBJECT] = {};	//オブジェクトの情報

//<==================================================================================
//オブジェクトのコンストラクタ
//<==================================================================================
CObject::CObject(int nPriority)
{
	//もし優先順位がない、または必要数を超えていた場合
	if (nPriority < NO_PRIORITY || nPriority >= NEED_PRIORITY)
	{
		return;
	}

	//<*******************************************
	//自分自身へのポインタを代入
	//<*******************************************
	m_pNext = nullptr;
	m_pPrev = nullptr;
	m_bDestru = false;

#if 1

	//<******************************************
	//リストに追加する(先頭がなければ)
	//<******************************************
	if (m_apTop[nPriority] == nullptr)
	{
		//メモリ確保をする
		m_apTop[nPriority] = this;

		//できていなかったら
		if (m_apTop[nPriority] == nullptr)
		{
			//何もせずこの関数を抜ける
			return;
		}
		//できていたら
		else
		{
			//最後尾を先頭にする
			m_apCur[nPriority] = m_apTop[nPriority];

			//そのオブジェクトの前の先頭
			this->m_pPrev = this;

			//先頭の前のオブジェクト
			m_apTop[nPriority]->m_pPrev = this;

			//次のオブジェクトを先頭にする
			this->m_pNext = m_apTop[nPriority];

			//先頭をそのオブジェクトにする
			m_apTop[nPriority] = this;
		}
	}
	//<******************************************
	//リストに追加する(先頭があれば)
	//<******************************************
	else
	{
		//最後尾の次のオブジェクトのメモリ確保をする
		m_apCur[nPriority]->m_pNext = this;

		//できなかったら
		if (m_apCur[nPriority] == nullptr)
		{
			//何もせずこの関数を抜ける
			return;
		}
		//できたら
		else
		{
			//最後尾の次のオブジェクトを最後尾にする
			m_apCur[nPriority] = m_apCur[nPriority]->m_pNext;

			//
			m_apCur[nPriority] = this;

			//最後尾の次はないことを証明する
			m_apCur[nPriority]->m_pNext = nullptr;


		}

	}
	//優先順位を代入
	m_nPriority = nPriority;
	m_3DType = TYPE_3D::TYPE_NONE;
	m_2DTYpe = TYPE_2D::TYPE_MAX;
	m_bUpdate = true;
	m_bDraw = true;
	m_pStencil = CStencil::Create(true, STENCIL_VALUE::STENCIL_FAIL);

	m_nNumAll++;

#else

#endif

#if 0
	//オブジェクトの最大数分繰り返す
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		//もし中身がなければ
		if (m_apObject[nPriority][nCntObj] == nullptr)
		{
			//値の設定
			m_apObject[nPriority][nCntObj] = this;				//自分自身のポインタを受け取る
			m_nID = nCntObj;									//自分自身のID設定
			m_nPriority = nPriority;							//優先順位を設定
			m_nNumAll += m_nValue;
			break;
		}
	}
#endif
}
//<==================================================================================
//オブジェクトのデストラクタ(オーバーロード)
//<==================================================================================
CObject::~CObject()
{

}
//<==================================================================================
//オブジェクトの全開放処理
//<==================================================================================
void CObject::ReleaseAll(void)
{
	//<******************************************************
	//
	//<******************************************************5
	for (int nCntPri = 0; nCntPri < NEED_PRIORITY; nCntPri++)
	{
		//whileでも可能
		for (CObject *pObj = m_apTop[nCntPri]; pObj != nullptr; pObj = m_pObjNext)
		{
			m_pObjNext = pObj->m_pNext;

			//ステンシルの中身があれば
			if (pObj->m_pStencil != nullptr)
			{
				pObj->m_pStencil->Uninit();
				delete pObj->m_pStencil;
				pObj->m_pStencil = nullptr;
			}

			pObj->Uninit();
		}
	}
	//<******************************************************
	//
	//<******************************************************5
	for (int nCntPri = 0; nCntPri < NEED_PRIORITY; nCntPri++)
	{
		//whileでも可能
		for (CObject *pObj = m_apTop[nCntPri]; pObj != nullptr; pObj = m_pObjNext)
		{
			m_pObjNext = pObj->m_pNext;

			//オブジェクトの破棄を行う
			delete pObj;
			pObj = nullptr;

			if (m_apTop[nCntPri] != nullptr)
			{
				m_apTop[nCntPri] = nullptr;
				delete m_apTop[nCntPri];
			}
			//最後尾の削除
			if (m_apCur[nCntPri] != nullptr)
			{
				m_apCur[nCntPri] = nullptr;
				delete m_apCur[nCntPri];

			}

		}

	}

#if 0
	//優先順位の必要数分繰り返す
	for (int nCntPriotiry = 0; nCntPriotiry < NEED_PRIORITY; nCntPriotiry++)
	{
		//オブジェクトの最大数分繰り返す
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			//メモリ確保がされていたら
			if (m_apObject[nCntPriotiry][nCntObj] != nullptr)
			{
				//終了処理
				m_apObject[nCntPriotiry][nCntObj]->Uninit();

			}

		}
	}
#endif
}
//<==================================================================================
//オブジェクトの全更新処理
//<==================================================================================
void CObject::UpdateAll(void)
{

	//<******************************************************
	//
	//<******************************************************
	for (int nCntPri = 0; nCntPri < NEED_PRIORITY; nCntPri++)
	{
		//whileでも可能
		for (CObject *pObj = m_apTop[nCntPri]; pObj != nullptr; pObj = m_pObjNext)
		{
			//次のオブジェクト
			if ((unsigned int)(m_pObjNext = pObj->m_pNext) == 0xDDDDDDDD)
			{
				return;
			}

			//ポインタの有効性をチェック
			_ASSERTE(_CrtIsValidPointer(pObj, sizeof(CObject), TRUE));

			//もし初期化されていないメモリにアクセスしようとしたら
			if (pObj->m_bDestru > true)
			{
				//次のオブジェクトに進める
				pObj = m_pObjNext;
			}
			if (pObj != nullptr)
			{
				//もし状態がfalseだったら
				if (pObj->m_bDestru != true
					&& !(pObj->m_bDestru > true))
				{
					if (pObj->m_bUpdate)
					{
						pObj->Update();
					}
				}
			}
		}
	}
	//<******************************************************
	//破棄処理(Uninitではない方(先頭以外))
	//<******************************************************
	for (int nCntPri = 0; nCntPri < NEED_PRIORITY; nCntPri++)
	{
		//前のオブジェクト保存用
		CObject *pPrev = nullptr;

		if (m_apTop[nCntPri] != nullptr)
		{
			pPrev = m_apTop[nCntPri];

			//<*********************************
			//whileでも可能
			for (CObject *pObj = m_apTop[nCntPri]; pObj != nullptr; pObj = m_pObjNext)
			{
				m_pObjNext = pObj->m_pNext;

				//もし状態がfalseだったら
				if (pObj->m_bDestru == true
					&& !(pObj->m_bDestru > true))
				{
					//
					if (pObj == nullptr)
					{
						m_pObjNext = pPrev;
					}
					//次のオブジェクトが存在していたら
					if (m_pObjNext != nullptr)
					{
						pPrev->m_pNext = m_pObjNext;
					}
					//
					if (pObj->m_pNext != nullptr)
					{
						pPrev->m_pNext = pObj->m_pNext;
					}
					//
					if (pObj->m_pPrev != nullptr)
					{
						pPrev->m_pPrev = pObj->m_pPrev;
					}
					//次のオブジェクトが存在していたら
					if (m_apTop[nCntPri] == pObj)
					{
						m_apTop[nCntPri] = pPrev;
					}
					//次のオブジェクトが存在していたら
					if (m_apCur[nCntPri] == pObj)
					{
						m_apCur[nCntPri] = pPrev;
					}
					//次のオブジェクトが存在していたら
					if (m_pObjNext == pObj)
					{
						m_pObjNext = pPrev;
					}
					//次のオブジェクトが存在していたら
					if (pObj != nullptr)
					{
						//ステンシルの中身があれば
						if (pObj->m_pStencil != nullptr)
						{
							pObj->m_pStencil->Uninit();
							delete pObj->m_pStencil;
							pObj->m_pStencil = nullptr;
						}

						pObj->Uninit();
						delete pObj;
						pObj = nullptr;
						break;
					}
				}

				//一旦保存しておく
				pPrev = pObj;

			}
		}
	}
#if 0
	//優先順位の必要数分繰り返す
	for (int nCntPriotiry = 0; nCntPriotiry < NEED_PRIORITY; nCntPriotiry++)
	{
		//オブジェクトの最大数分繰り返す
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			//メモリの確保がされていたら
			if (m_apObject[nCntPriotiry][nCntObj] != nullptr)
			{
				//更新処理
				m_apObject[nCntPriotiry][nCntObj]->Update();
			}
		}
	}
#endif
}
//<==================================================================================
//オブジェクトの全描画処理
//<==================================================================================
void CObject::DrawAll(void)
{
	//<******************************************************
	//while文を使い、
	//<******************************************************
	for (int nCntPri = 0; nCntPri < NEED_PRIORITY; nCntPri++)
	{
		//whileでも可能
		for (CObject *pObj = m_apTop[nCntPri]; pObj != nullptr; pObj = m_pObjNext)
		{
			//次のオブジェクト
			if ((unsigned int)(m_pObjNext = pObj->m_pNext) == 0xDDDDDDDD)
			{
				return;
			}



			//もし破壊状態がfalseだったら
			if (pObj->m_bDestru == false)
			{
				//描画するようになっていたら
				if (!(pObj->m_nPriority >= NEED_PRIORITY))
				{
					if (pObj->m_bDraw)
					{
						pObj->m_pStencil->DrawStencilTest();
						pObj->Draw();
					}
				}
				else
				{
					m_pObjNext = pObj->m_pPrev;
				}
			}
		}
	}

#if 0
	//優先順位の必要数分繰り返す
	for (int nCntPriotiry = 0; nCntPriotiry < NEED_PRIORITY; nCntPriotiry++)
	{
		//オブジェクトの最大数分繰り返す
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			//メモリの確保がされていたら
			if (m_apObject[nCntPriotiry][nCntObj] != nullptr)
			{
				//描画処理
				m_apObject[nCntPriotiry][nCntObj]->Draw();
			}

		}
	}
#endif
}
//<==================================================================================
//オブジェクトの解放処理
//<==================================================================================
void CObject::Release(void)
{

	//<*****************************************
	//
	//<*****************************************
	//もし破壊状態がfalseだったら
	if (m_bDestru == false)
	{
		m_bDestru = true;
	}

	//総数を減らす
	m_nNumAll--;

#if 0
	//メモリ確保がされていたら
	if (m_apObject[nIdxPrio][nIdx] != nullptr)
	{
		//メモリ解放
		delete m_apObject[nIdxPrio][nIdx];
		m_apObject[nIdxPrio][nIdx] = nullptr;

		//総数を減らす
		m_nNumAll--;
	}
#endif
}