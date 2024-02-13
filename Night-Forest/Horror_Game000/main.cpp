//<==================================================================================
//C++�p�v���W�F�N�g[main.cpp]
//
//Author kazuki watanabe
//<==================================================================================
#include "main.h"
#include "Manager.h"

//�}�N����`
#define SLOW_SPEED			(0.5f)					//�ݑ��̒l
#define NORMAL_SPEED		(1)						//�����̒l
#define SPEED_UP_VALUE		(2)						//�X�s�[�h�A�b�v�̒l

#define CLASS_NAME			"WindowsClass"			//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME			"Night-Forest"	//�E�C���h�E�̖��O(�L���v�V����)

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//�O���[�o���ϐ��錾
int g_nCountFPS = 0;						//FPS�J�E���^
bool g_bDoubleSpeed = false;				//�{�����邩���Ȃ����ǂ����̐���
bool g_bSlowSpeed = false;					//�x�����邩�̐���
//<==================================================================================t
//���C���֐�
//<==================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmbLine, int nCmbShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASS�̃������T�C�Y
		CS_CLASSDC,							//�E�C���h�E�̃X�^�C��
		WindowProc,							//�E�C���h�E�v���V�[�W��
		0,									//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,									//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,							//�C���X�^���X�n���h��
		LoadIcon(hInstance, IDI_APPLICATION),	//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW),		//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C�A���g�̈�̔w�i�F
		NULL,								//���j���[�o�[
		CLASS_NAME,							//�E�C���h�E�N���X�̖��O
		LoadIcon(hInstance,IDI_APPLICATION)		//�t�@�C���̃A�C�R��

	};

	HWND hWnd;								//�E�C���h�E�n���h��(���ʎq)
	MSG msg;								//���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	//��ʃT�C�Y�̍\����

														//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);


	//�E�C���h�E�̐���
	hWnd = CreateWindowEx(
		NULL,								//�g���E�C���h�E�X�^�C��
		CLASS_NAME,							//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,						//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,				//�E�C���h�E�X�^�C��
		CW_USEDEFAULT,						//�E�C���h�E�̍���X���W
		CW_USEDEFAULT,						//�E�C���h�E�̍���Y���W
		(rect.right - rect.left),			//�E�C���h�E�̕�
		(rect.bottom - rect.top),			//�E�C���h�E�̍���
		NULL,								//�e�E�C���h�E�̃n���h��
		NULL,								//���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,							//�C���X�^���X�n���h��
		NULL								//�E�C���h�E�쐬�f�[�^
	);


	ShowWindow(hWnd, nCmbShow);
	UpdateWindow(hWnd);

	CManager *pManager = nullptr;

	//���������[�N���o��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (pManager == nullptr)
	{
		pManager = new CManager;				//�������m�ۂ��J�n����
	}

	//�����������m�ۂɐ���������
	if (pManager != nullptr)
	{
		//���������������s������
		if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
		{
			return -1;
		}
	}
	


	//����\��ݒ�
	timeBeginPeriod(1);
	DWORD dwCurrentTime = 0;					//���ݎ���������������
	DWORD dwExecLastTime = timeGetTime();		//���ݎ������擾(�ۑ�)[�Ō�ɏ�����������]

	DWORD dwFrameCount = 0;					//�t���[�����̃J�E���g������������
	DWORD dwFPSLastTime = timeGetTime();	//���ݎ������擾(�ۑ�)[�Ō��FPS���v����������]

											//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Window�̏���

		 //����WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);				//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);				//�E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���

			//�ǂ����false��������
			if (g_bDoubleSpeed == false && g_bSlowSpeed == false)
			{
				dwCurrentTime = timeGetTime() * NORMAL_SPEED;		//���ݎ������擾
			}
			//�{�����[�h��true&&�ݑ����[�h��false
			else if(g_bDoubleSpeed == true&&g_bSlowSpeed == false)
			{
				dwCurrentTime = timeGetTime() * SPEED_UP_VALUE;		//���ݎ������擾(2�{������)
			}
			//�ݑ����[�h��true&&�{�����[�h��false
			else if (g_bSlowSpeed == true && g_bDoubleSpeed == false)
			{
				dwCurrentTime = timeGetTime() / SPEED_UP_VALUE;		//���ݎ������擾(2�{������)
			}
			//�ǂ����true�������ꍇ
			else if (g_bSlowSpeed == true && g_bDoubleSpeed == true)
			{
				dwCurrentTime = timeGetTime() * NORMAL_SPEED;		//���ݎ������擾(�ǂ���ɂ��딼������邽��)
			}
			
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��

				//�ǂ����false��������
				if (g_bDoubleSpeed == false && g_bSlowSpeed == false)
				{
					g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime) * NORMAL_SPEED;		//�ʏ��FPS�ɂ���
				}
				//�{�����[�h��true&&�ݑ����[�h��false
				else if (g_bDoubleSpeed == true && g_bSlowSpeed == false)
				{
					g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime) * SPEED_UP_VALUE;		//2�{���̏�Ԃ�FPS�ɂ���
				}
				//�ݑ����[�h��true&&�{�����[�h��false
				else if (g_bSlowSpeed == true && g_bDoubleSpeed == false)
				{
					g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime) / 2;					//�ݑ��̏�Ԃ�FPS�ɂ���
				}
				//�ǂ����true�������ꍇ
				else if (g_bSlowSpeed == true && g_bDoubleSpeed == true)
				{
					g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime) * NORMAL_SPEED;		//�ʏ��FPS�ɂ���(�ǂ���ɂ��딼������邽��)
				}

				dwFPSLastTime = dwCurrentTime;		//FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;					//�t���[���J�E���g���N���A
			}

			//����dwCurrentTime�͑����̌��ƂȂ��Ă���
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��

				dwExecLastTime = dwCurrentTime;		//�����J�n�̎���[���ݎ���]��ۑ�

				//�����������m�ۂɐ���������
				if (pManager != nullptr)
				{
					pManager->Update();				//�X�V����

					pManager->Draw();				//�`�揈��

					//�q�[�v���j�����Ă����玸�s�������Ƃ�`����
					_ASSERTE(_CrtCheckMemory());
				}
				

				dwFrameCount++;						//�t���[���J�E���g�����Z
			}
		}
	}

	//<==========================
	//���������
	//<==========================
	//�����������m�ۂɐ���������
	if (pManager != nullptr)
	{
		//�I������
		pManager->Uninit();
		delete pManager;
		pManager = nullptr;
	}

	//����\��߂�
	timeEndPeriod(1);

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	_CrtDumpMemoryLeaks();

	return (int)msg.wParam;
}
//<==================================================================================
//�E�C���h�E�v���V�[�W��
//<==================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;	//�Ԃ�l���i�[
	int Width = 0, Height = 0;

	switch (uMsg)
	{
	case WM_DESTROY:				//�E�C���h�E�j���̃��b�Z�[�W
									//WM_QUIT���b�Z�[�W�𑗂�

		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:				//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:				//ESC�L�[����

			//�E�C���h�E��j������(VK_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
	
			break;
		}
		break;

	case WM_CLOSE:				//�o�c��
								//���b�Z�[�W�{�b�N�X��\��
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			//�E�C���h�E��j������(VK_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;			//0��Ԃ��ďI����h��
		}
		break;

	case WM_LBUTTONDOWN:		//�}�E�X���N���b�N
								//�ΏۃE�C���h�E�Ƀt�H�[�J�X�����킹��

		SetFocus(hWnd);
		break;

	case WM_TIMER:				//�^�C�}�[���s�̃��b�Z�[�W
		break;

	case WM_MOVE:
		Width = LOWORD(lParam);
		Height = HIWORD(lParam);
		break;

	case WM_SIZE:
		InvalidateRect(hWnd, NULL, true);//��ʍX�V
		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//����̏�����Ԃ�
}
//<==================================================================================
//�t���[�����[�g���擾
//<==================================================================================
int GetFPS(void)
{
	return g_nCountFPS;
}
//<==================================================================================
//�{�����邩���Ȃ����̓���ւ�
//<==================================================================================
void SetD_SPEED(void)
{
	//�O�����Z�q�œ���ւ����s��
	g_bDoubleSpeed == false ? g_bDoubleSpeed = true : g_bDoubleSpeed = false;
}
//<==================================================================================
//�ݑ����邩���Ȃ����̓���ւ�
//<==================================================================================
void SetS_SPEED(void)
{
	//�O�����Z�q�œ���ւ����s��
	g_bSlowSpeed == false ? g_bSlowSpeed = true : g_bSlowSpeed = false;
}