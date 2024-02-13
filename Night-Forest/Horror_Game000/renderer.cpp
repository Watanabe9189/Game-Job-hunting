//<==============================================
//�����_���[����(renderer.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "DebugProc.h"
#include "Useful.h"
//<==================================================================================
//�����_���[�̃R���X�g���N�^
//<==================================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;			//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	m_pD3DDevice = NULL;	//Direct3D�f�o�C�X�ւ̃|�C���^
	m_pPixShade = nullptr;
	m_bUsePix = false;
	m_nStencil = INITIAL_INT;
}
//<==================================================================================
//�����_���[�̃f�X�g���N�^
//<==================================================================================
CRenderer::~CRenderer()
{

}

//<==================================================================================
//�����_���[�̏���������
//<==================================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm = {};			//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp = {};	//�v���[���e�[�V�������[�h
	HRESULT hStencil = E_FAIL;


									//Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//���g��NULL��������
	if (m_pD3D == NULL)
	{
		return E_FAIL;//�G���[���b�Z�[�W��\��
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{//���s�����Ƃ�
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;		//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;					//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;		//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	//�f�o�C�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;					//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//�C���^�[�o��
																//Direct3D�f�o�C�X�̐���

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
	//�X�e���V���o�b�t�@���g���邩�`�F�b�N
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

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3DDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);		//�f�B�U�����O�L����
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//�T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//�e�N�X�`���X�e�[�W�X�e�[�g
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�����̎��ݒ�
	srand((unsigned int)time(0));

	//<**************************
	//�s�N�Z���V�F�[�_�[�֘A
	//<**************************
	CheckPixShade();
	/*m_pPixShade = LoadPixShade();*/
	//<**************************

	return S_OK;
}
//<==================================================================================
//�����_���[�̏I������
//<==================================================================================
void CRenderer::Uninit(void)
{
CObject::ReleaseAll();

//Direct3D�f�o�C�X�̔j��
if (m_pD3DDevice != NULL)
{
	m_pD3DDevice->Release();
	m_pD3DDevice = NULL;
}

//Direct3D�I�u�W�F�N�g�̔j��
if (m_pD3D != NULL)
{
	m_pD3D->Release();
	m_pD3D = NULL;
}

}
//<==================================================================================
//�����_���[�̍X�V����
//<==================================================================================
void CRenderer::Update(void)
{
	//I�{�^����������Ă�����
	if (CManager::GetKeyboard()->bGetTrigger(DIK_I))
	{
		//�t���X�N���[���Ɉړ�����
		SetWindowLong(m_hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);

		//��ʂɃE�B���h�E�����킹��
		MoveWindow(m_hWnd, GetSystemMetrics(SM_XVIRTUALSCREEN),
			GetSystemMetrics(SM_YVIRTUALSCREEN),
			GetSystemMetrics(SM_CXVIRTUALSCREEN),
			GetSystemMetrics(SM_CYVIRTUALSCREEN), TRUE);
	}
	//I�{�^����������Ă�����
	else if (CManager::GetKeyboard()->bGetTrigger(DIK_O))
	{
		//�t���X�N���[���Ɉړ�����
		SetWindowLong(m_hWnd, GWL_STYLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW);

		//��ʂɃE�B���h�E�����킹��
		MoveWindow(m_hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TRUE);
	}

	CObject::UpdateAll();
}
//<==================================================================================
//�����_���[�̕`�揈��
//<==================================================================================
void CRenderer::Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�ƃX�e���V���o�b�t�A�̃N���A)
	m_pD3DDevice->Clear
	(	0,														//��`�̐����w��
		NULL,													//�`��̈�S�̂��N���A
		(D3DCLEAR_STENCIL|D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),	//�N���A�Ώۂ��w��
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f),						//��ʕ`��F���w��
		1.0f,													//�[�x�o�b�t�@�ɕۑ�����Z�l���w��
		0														//�X�e���V���o�b�t�@�ɕۑ�����l���w��
	);

	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CObject::DrawAll();

		CManager::GetDebugProc()->Draw();

		//�s�N�Z���V�F�[�_�[���g���Ȃ�`�悷��
		//if (m_bUsePix) { m_pD3DDevice->SetPixelShader(m_pPixShade); }

		CDebug::SetManual();

		//�`��I��
		m_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//<==================================================================================
//�����_���[�̃s�N�Z���V�F�[�_�[�`�F�b�N
//<==================================================================================
void CRenderer::CheckPixShade(void)
{
	D3DCAPS9 caps;						//
	m_pD3DDevice->GetDeviceCaps(&caps);	//

	//�s�N�Z���V�F�[�_�[�o�[�W�������g���邩�ǂ���
	if (caps.PixelShaderVersion < D3DPS_VERSION(2, 0)&& caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
	{
		//�x������\��
		MessageBox(NULL, "�Ή����Ă��܂���", "ERROR", MB_ICONWARNING);
	}
}
//<===================================================
//
//<===================================================
LPDIRECT3DPIXELSHADER9 CRenderer::LoadPixShade(void)
{

	LPDIRECT3DPIXELSHADER9 shader = NULL;
	HRESULT hr = E_FAIL;

	//�V�F�[�_�v���O�����̓ǂݍ���
	LPD3DXBUFFER pShaderSource = nullptr;
	LPD3DXBUFFER pErrMessage = NULL;

	hr = D3DXAssembleShaderFromFile("data\\TEXT\\Monochrome.txt", NULL, NULL, 0, &pShaderSource, &pErrMessage);

	if (FAILED(hr)) 
	{
		//�G���[���b�Z�[�W�\�� �����R�[�h��ANSI�ł���
		::MessageBoxA(NULL, (LPCSTR)(pErrMessage->GetBufferPointer()), "�G���[", MB_OK);
		pErrMessage->Release();
		return NULL;
	}

	//�s�N�Z���V�F�[�_�쐬
	hr = m_pD3DDevice->CreatePixelShader((DWORD*)pShaderSource->GetBufferPointer(), &shader);

	if (FAILED(hr)) 
	{
		return NULL;
	}

	//�s�N�Z���V�F�[�_���������\�[�X�͉�����ėǂ�
	pShaderSource->Release();

	return shader;
}
//<==================================================================================
//�����_���[�̃X�N���[���V���b�g�쐬�֐�
//<==================================================================================
void CRenderer::ScreenShot(const char *cName)
{
	//�����ł����g��Ȃ����[�J���ϐ��錾
	D3DXIMAGE_FILEFORMAT FileFormat = D3DXIFF_FORCE_DWORD;	//�t�@�C���t�H�[�}�b�g
	LPDIRECT3D9 pdirect3d9 = nullptr;						//IDirect3D9�C���^�[�t�F�C�X���擾���邽�߂̕ϐ�
	LPDIRECT3DSURFACE9 pSurface = nullptr;					//�T�[�t�F�C�X�ϐ�
	D3DDISPLAYMODE dmode = {};								//�f�B�X�v���C���[�h
	TCHAR fileName[INT_VALUE::MAX_CHAR] = {};							//�R�s�[�p�̃t�@�C�����ϐ�
	FILE* pFile = nullptr;									//�t�@�C���ϐ�

	//����".png"�Ƃ����g���q�ɂȂ��Ă�����
	if (strstr(cName, ".png"))
	{
		////���̕�����̒���".png"�Ƃ��������񂪂��邩�̃`�F�b�N������
		//assert(strstr(cName, ".png") != nullptr);

		//PNG�`���ɂ���
		FileFormat = D3DXIFF_PNG;

		//������(�t�@�C����)���R�s�[����
		sprintf(fileName, cName);
	}
	//����".jpg"�Ƃ����g���q�ɂȂ��Ă�����
	else if (strstr(cName, ".jpg"))
	{
		////���̕�����̒���".jpg"�Ƃ��������񂪂��邩�̃`�F�b�N������
		//assert(strstr(cName, ".jpg") != nullptr);

		//JPG�����ɂ���
		FileFormat = D3DXIFF_JPG;

		//������(�t�@�C����)���R�s�[����
		sprintf(fileName, cName);

	}
	
	//�����t�@�C�����J���Ă�����
	if (pFile != nullptr)
	{
		//�t�@�C�������
		fclose(pFile);
	}

	//IDirect3D9�C���^�[�t�F�C�X���擾����
	m_pD3DDevice->GetDirect3D(&pdirect3d9);

	//���݂̃f�B�X�v���C�t�H�[�}�b�g���擾
	if (FAILED(pdirect3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dmode)))
	{
		//IDirect3D9�C���^�[�t�F�C�X�̔j��
		if (pdirect3d9 != nullptr)
		{
			pdirect3d9->Release();
			pdirect3d9 = nullptr;
		}
	}

	//IDirect3D9�C���^�[�t�F�C�X�̔j��
	if (pdirect3d9 != nullptr)
	{
		//���ꂵ�Ȃ��ƃ��������[�N����
		pdirect3d9->Release();
		pdirect3d9 = nullptr;
	}

	//�L���v�`���p�̃T�[�t�F�C�X���쐬
	assert(SUCCEEDED(m_pD3DDevice->CreateOffscreenPlainSurface(dmode.Width,
		dmode.Height,
		D3DFMT_A8R8G8B8,
		D3DPOOL_SCRATCH,
		&pSurface,
		NULL)));

	//�T�[�t�F�C�X�Ƀt�����g�o�b�t�@�̃C���[�W��ۑ�����
	if (FAILED(m_pD3DDevice->GetFrontBufferData(0, pSurface)))
	{
		//�T�[�t�F�C�X�̔j��
		if (pSurface != nullptr)
		{
			pSurface->Release();
			pSurface = nullptr;
		}
	}

	//�t�@�C���o��
	if ((D3DXSaveSurfaceToFile(fileName, FileFormat, pSurface, NULL, NULL))!=D3D_OK)
	{
		//�T�[�t�F�C�X�̔j��
		if (pSurface != nullptr)
		{
			pSurface->Release();
			pSurface = nullptr;
		}
	}

	//�T�[�t�F�C�X�̔j��
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
