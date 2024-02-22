#ifndef _DESTARROW_H_
#define _DESTARROW_H_

#include "Object3D.h"
#include "3DPlayer.h"
#include "Item.h"

class CDestArrow : public CObject3D
{
public:

	CDestArrow(int nPriority = FIX_PRIORITY);
	~CDestArrow();

	static CDestArrow *Create(void);

	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override;
	void Draw(void)		override 
	{ 
		if (m_bFind == true)
		{
			CObject3D::Draw();
		}
	}
	void SetVtx(void)	override {}

	void RotateToDest(void);

	void SetFindfalse(void) { m_bFind = false; }	//�`��̃I���I�t
	void SetFindtrue(void) { m_bFind = true; }	//�`��̃I���I�t

	bool GetFind(void) { return m_bFind; }

private:

	static LPDIRECT3DTEXTURE9	m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	static const char*			m_pFilename;				//�t�@�C����

	D3DXVECTOR3 m_rPos;
	D3DXVECTOR3 m_rRot;
	D3DXVECTOR3 m_rSize;

	D3DXVECTOR3 m_rRotDest;

	float m_fRotDest;
	float m_fRotDiff;
	float m_fSearch;

	D3DXVECTOR3 m_rDis;

	bool m_bFind;
	int m_nNum;

	CItem *m_apItem[INT_VALUE::MAX_SIZE];
	C3DPlayer *m_p3DPlayer;

};

#endif