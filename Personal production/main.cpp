//=================================================
//
//	main.cpp
// 
// Author:�ߓc����
//
//=================================================

#include "main.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "manager.h"
#include <crtdbg.h>

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//�O���[�o���ϐ��錾
bool g_isFullscreen = false;				//	�E�B���h�E��؂�ւ��邽�߂̃t���O
RECT g_windowRect;
int g_nCountFPS = 0;

//===========================
//���C���֐�
//===========================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//�ǉ�����(SAL:�\�[�X�R�[�h���ߌ���)
{
	// ���������[�N���m
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);//���������[�N���m

#if 0
	// ���������[�N�̏ꏊ���m
	_CrtSetBreakAlloc(187);
#endif

	DWORD dwCurrentTime;
	DWORD dwExeclastTime;
	DWORD dwFrameCount;	//�t���[���J�E���g
	DWORD dwFPSLastTime;	//�Ō��FPS���v����������
	CManager* pManager = NULL;
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;//�E�B���h�E�n���h��(���ʎq)
	MSG msg;//���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);
	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	//�E�B���h�E����
	hWnd = CreateWindowEx(0,//�g���E�B���h�E�X�^�C��
		CLASS_NAME,//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,//�E�B���h�E�̍���Y���W
		(rect.right - rect.left),//�E�B���h�E�̕�
		(rect.bottom - rect.top),//�E�B���h�E�̍���
		NULL,//�e�E�B���h�E�̃n���h��
		NULL,//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,//�C���X�^���X�n���h��
		NULL);//�E�B���h�E�쐬�f�[�^

	pManager = new CManager;

	//====================
	//����������
	//====================
	if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExeclastTime = timeGetTime();

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	//FPS���v������������\�ۑ�
				dwFrameCount = 0;	//�t���[���J�E���g���N���A
			}
			if ((dwCurrentTime - dwExeclastTime) >= (1000 / 60))
			{
				dwExeclastTime = dwCurrentTime;

				//====================
				//�����_���[�X�V����
				//====================
				pManager->Update();

				//====================
				//�����_���[�`�揈��
				//====================
				pManager->Draw();

				dwFrameCount++;		//�t���[���J�E���g�����Z
			}
		}
	}

	//�j���̏���


	//�j���̏���
	if (pManager != NULL)
	{
		//====================
		//�����_���[�I������
		//====================
		pManager->Uninit();

		delete pManager;
		pManager = NULL;
	}

	timeEndPeriod(1);
	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}
//************************************************
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//************************************************
void ToggleFullscreen(HWND hWnd)
{
	//==================================
	//	���݂̃E�B���h�E�X�^�C�����擾
	//==================================
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
	if (g_isFullscreen)
	{
		//=============================
		//	�E�B���h�E���[�h�ɐ؂�ւ�
		//=============================
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		//==================================
		//	�t���X�N���[�����[�h�ɐ؂�ւ�
		//==================================
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}
	g_isFullscreen = !g_isFullscreen;
}

//=================================
//�E�B���h�E�v���V�[�W��
//=================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
			//�E�B���h�E��j������
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
			//�E�B���h�E���g��
		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;
	case WM_CREATE:
		//�^�C�}�[�̐ݒ�
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//����̏�����Ԃ�
}

// FPS�̃J�E���g���擾
int GetFPS(void)
{
	return g_nCountFPS;
}