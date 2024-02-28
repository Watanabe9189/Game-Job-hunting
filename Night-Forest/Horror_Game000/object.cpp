//<==============================================
//�I�u�W�F�N�g����(object.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "object.h"
#include "Camera.h"
#include "Manager.h"
#include "Stencil.h"

//<*****************************************
//�ÓI�����o�ϐ��錾
//<*****************************************
int CObject::m_nNumAll = 0;						//����
CObject *CObject::m_apTop[NEED_PRIORITY] = { nullptr };
CObject *CObject::m_apCur[NEED_PRIORITY] = { nullptr };
CObject *CObject::m_pObject = nullptr;
CObject *CObject::m_pObjNext = nullptr;
//CObject *CObject::m_apObject[NEED_PRIORITY][MAX_OBJECT] = {};	//�I�u�W�F�N�g�̏��

//<==================================================================================
//�I�u�W�F�N�g�̃R���X�g���N�^
//<==================================================================================
CObject::CObject(int nPriority)
{
	//�����D�揇�ʂ��Ȃ��A�܂��͕K�v���𒴂��Ă����ꍇ
	if (nPriority < NO_PRIORITY || nPriority >= NEED_PRIORITY)
	{
		return;
	}

	//<*******************************************
	//�������g�ւ̃|�C���^����
	//<*******************************************
	m_pNext = nullptr;
	m_pPrev = nullptr;
	m_bDestru = false;

#if 1

	//<******************************************
	//���X�g�ɒǉ�����(�擪���Ȃ����)
	//<******************************************
	if (m_apTop[nPriority] == nullptr)
	{
		//�������m�ۂ�����
		m_apTop[nPriority] = this;

		//�ł��Ă��Ȃ�������
		if (m_apTop[nPriority] == nullptr)
		{
			//�����������̊֐��𔲂���
			return;
		}
		//�ł��Ă�����
		else
		{
			//�Ō����擪�ɂ���
			m_apCur[nPriority] = m_apTop[nPriority];

			//���̃I�u�W�F�N�g�̑O�̐擪
			this->m_pPrev = this;

			//�擪�̑O�̃I�u�W�F�N�g
			m_apTop[nPriority]->m_pPrev = this;

			//���̃I�u�W�F�N�g��擪�ɂ���
			this->m_pNext = m_apTop[nPriority];

			//�擪�����̃I�u�W�F�N�g�ɂ���
			m_apTop[nPriority] = this;
		}
	}
	//<******************************************
	//���X�g�ɒǉ�����(�擪�������)
	//<******************************************
	else
	{
		//�Ō���̎��̃I�u�W�F�N�g�̃������m�ۂ�����
		m_apCur[nPriority]->m_pNext = this;

		//�ł��Ȃ�������
		if (m_apCur[nPriority] == nullptr)
		{
			//�����������̊֐��𔲂���
			return;
		}
		//�ł�����
		else
		{
			//�Ō���̎��̃I�u�W�F�N�g���Ō���ɂ���
			m_apCur[nPriority] = m_apCur[nPriority]->m_pNext;

			//
			m_apCur[nPriority] = this;

			//�Ō���̎��͂Ȃ����Ƃ��ؖ�����
			m_apCur[nPriority]->m_pNext = nullptr;


		}

	}
	//�D�揇�ʂ���
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
	//�I�u�W�F�N�g�̍ő吔���J��Ԃ�
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		//�������g���Ȃ����
		if (m_apObject[nPriority][nCntObj] == nullptr)
		{
			//�l�̐ݒ�
			m_apObject[nPriority][nCntObj] = this;				//�������g�̃|�C���^���󂯎��
			m_nID = nCntObj;									//�������g��ID�ݒ�
			m_nPriority = nPriority;							//�D�揇�ʂ�ݒ�
			m_nNumAll += m_nValue;
			break;
		}
	}
#endif
}
//<==================================================================================
//�I�u�W�F�N�g�̃f�X�g���N�^(�I�[�o�[���[�h)
//<==================================================================================
CObject::~CObject()
{

}
//<==================================================================================
//�I�u�W�F�N�g�̑S�J������
//<==================================================================================
void CObject::ReleaseAll(void)
{
	//<******************************************************
	//
	//<******************************************************5
	for (int nCntPri = 0; nCntPri < NEED_PRIORITY; nCntPri++)
	{
		//while�ł��\
		for (CObject *pObj = m_apTop[nCntPri]; pObj != nullptr; pObj = m_pObjNext)
		{
			m_pObjNext = pObj->m_pNext;

			//�X�e���V���̒��g�������
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
		//while�ł��\
		for (CObject *pObj = m_apTop[nCntPri]; pObj != nullptr; pObj = m_pObjNext)
		{
			m_pObjNext = pObj->m_pNext;

			//�I�u�W�F�N�g�̔j�����s��
			delete pObj;
			pObj = nullptr;

			if (m_apTop[nCntPri] != nullptr)
			{
				m_apTop[nCntPri] = nullptr;
				delete m_apTop[nCntPri];
			}
			//�Ō���̍폜
			if (m_apCur[nCntPri] != nullptr)
			{
				m_apCur[nCntPri] = nullptr;
				delete m_apCur[nCntPri];

			}

		}

	}

#if 0
	//�D�揇�ʂ̕K�v�����J��Ԃ�
	for (int nCntPriotiry = 0; nCntPriotiry < NEED_PRIORITY; nCntPriotiry++)
	{
		//�I�u�W�F�N�g�̍ő吔���J��Ԃ�
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			//�������m�ۂ�����Ă�����
			if (m_apObject[nCntPriotiry][nCntObj] != nullptr)
			{
				//�I������
				m_apObject[nCntPriotiry][nCntObj]->Uninit();

			}

		}
	}
#endif
}
//<==================================================================================
//�I�u�W�F�N�g�̑S�X�V����
//<==================================================================================
void CObject::UpdateAll(void)
{

	//<******************************************************
	//
	//<******************************************************
	for (int nCntPri = 0; nCntPri < NEED_PRIORITY; nCntPri++)
	{
		//while�ł��\
		for (CObject *pObj = m_apTop[nCntPri]; pObj != nullptr; pObj = m_pObjNext)
		{
			//���̃I�u�W�F�N�g
			if ((unsigned int)(m_pObjNext = pObj->m_pNext) == 0xDDDDDDDD)
			{
				return;
			}

			//�|�C���^�̗L�������`�F�b�N
			_ASSERTE(_CrtIsValidPointer(pObj, sizeof(CObject), TRUE));

			//��������������Ă��Ȃ��������ɃA�N�Z�X���悤�Ƃ�����
			if (pObj->m_bDestru > true)
			{
				//���̃I�u�W�F�N�g�ɐi�߂�
				pObj = m_pObjNext;
			}
			if (pObj != nullptr)
			{
				//������Ԃ�false��������
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
	//�j������(Uninit�ł͂Ȃ���(�擪�ȊO))
	//<******************************************************
	for (int nCntPri = 0; nCntPri < NEED_PRIORITY; nCntPri++)
	{
		//�O�̃I�u�W�F�N�g�ۑ��p
		CObject *pPrev = nullptr;

		if (m_apTop[nCntPri] != nullptr)
		{
			pPrev = m_apTop[nCntPri];

			//<*********************************
			//while�ł��\
			for (CObject *pObj = m_apTop[nCntPri]; pObj != nullptr; pObj = m_pObjNext)
			{
				m_pObjNext = pObj->m_pNext;

				//������Ԃ�false��������
				if (pObj->m_bDestru == true
					&& !(pObj->m_bDestru > true))
				{
					//
					if (pObj == nullptr)
					{
						m_pObjNext = pPrev;
					}
					//���̃I�u�W�F�N�g�����݂��Ă�����
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
					//���̃I�u�W�F�N�g�����݂��Ă�����
					if (m_apTop[nCntPri] == pObj)
					{
						m_apTop[nCntPri] = pPrev;
					}
					//���̃I�u�W�F�N�g�����݂��Ă�����
					if (m_apCur[nCntPri] == pObj)
					{
						m_apCur[nCntPri] = pPrev;
					}
					//���̃I�u�W�F�N�g�����݂��Ă�����
					if (m_pObjNext == pObj)
					{
						m_pObjNext = pPrev;
					}
					//���̃I�u�W�F�N�g�����݂��Ă�����
					if (pObj != nullptr)
					{
						//�X�e���V���̒��g�������
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

				//��U�ۑ����Ă���
				pPrev = pObj;

			}
		}
	}
#if 0
	//�D�揇�ʂ̕K�v�����J��Ԃ�
	for (int nCntPriotiry = 0; nCntPriotiry < NEED_PRIORITY; nCntPriotiry++)
	{
		//�I�u�W�F�N�g�̍ő吔���J��Ԃ�
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			//�������̊m�ۂ�����Ă�����
			if (m_apObject[nCntPriotiry][nCntObj] != nullptr)
			{
				//�X�V����
				m_apObject[nCntPriotiry][nCntObj]->Update();
			}
		}
	}
#endif
}
//<==================================================================================
//�I�u�W�F�N�g�̑S�`�揈��
//<==================================================================================
void CObject::DrawAll(void)
{
	//<******************************************************
	//while�����g���A
	//<******************************************************
	for (int nCntPri = 0; nCntPri < NEED_PRIORITY; nCntPri++)
	{
		//while�ł��\
		for (CObject *pObj = m_apTop[nCntPri]; pObj != nullptr; pObj = m_pObjNext)
		{
			//���̃I�u�W�F�N�g
			if ((unsigned int)(m_pObjNext = pObj->m_pNext) == 0xDDDDDDDD)
			{
				return;
			}



			//�����j���Ԃ�false��������
			if (pObj->m_bDestru == false)
			{
				//�`�悷��悤�ɂȂ��Ă�����
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
	//�D�揇�ʂ̕K�v�����J��Ԃ�
	for (int nCntPriotiry = 0; nCntPriotiry < NEED_PRIORITY; nCntPriotiry++)
	{
		//�I�u�W�F�N�g�̍ő吔���J��Ԃ�
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			//�������̊m�ۂ�����Ă�����
			if (m_apObject[nCntPriotiry][nCntObj] != nullptr)
			{
				//�`�揈��
				m_apObject[nCntPriotiry][nCntObj]->Draw();
			}

		}
	}
#endif
}
//<==================================================================================
//�I�u�W�F�N�g�̉������
//<==================================================================================
void CObject::Release(void)
{

	//<*****************************************
	//
	//<*****************************************
	//�����j���Ԃ�false��������
	if (m_bDestru == false)
	{
		m_bDestru = true;
	}

	//���������炷
	m_nNumAll--;

#if 0
	//�������m�ۂ�����Ă�����
	if (m_apObject[nIdxPrio][nIdx] != nullptr)
	{
		//���������
		delete m_apObject[nIdxPrio][nIdx];
		m_apObject[nIdxPrio][nIdx] = nullptr;

		//���������炷
		m_nNumAll--;
	}
#endif
}