#ifndef _DESTARROW2D_H_
#define _DESTARROW2D_H_

#include "main.h"
#include "object2D.h"

//<**********************************
//
//<**********************************
class CDestArrow2D :public CObject2D
{
public:

	CDestArrow2D();
	~CDestArrow2D();

	static CDestArrow2D *Create(const D3DXVECTOR2 rPos);

	HRESULT Init(void)	override;
	void Uninit(void)	override	{ CObject2D::Uninit(); }
	void Update(void)	override;
	void Draw(void)		override	{ CObject2D::Draw(); }
	void SetVtx(void)	override {}


private:

	void RotateDest(void);

	static LPDIRECT3DTEXTURE9 m_pTexture;
	static const char*			m_cFilename;				//�t�@�C����
	static int m_nNumAll;

	D3DXVECTOR2 m_rPos;		//�ʒu
	D3DXVECTOR2 m_rSize;	//�T�C�Y
	D3DXVECTOR2 m_rDis;		//����
	D3DXVECTOR3 m_rRot;		//����

};

#endif
