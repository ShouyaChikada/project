//=================================================
//
//	debugproc.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "debugproc.h"
#include "manager.h"

//�ÓI�����o�ϐ�
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[1024] = {};
int CDebugProc::m_nCountFPS = 0;
int CDebugProc::m_nowIndx = 0;
bool CDebugProc::m_Enable = true;

// �R���X�g���N�^
CDebugProc::CDebugProc()
{
	
}

// �f�X�g���N�^
CDebugProc::~CDebugProc()
{

}

// ������
void CDebugProc::Init(void)
{
	m_nowIndx = 0;

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		
	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 20, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont);
		
	memset(m_aStr, NULL, sizeof(m_aStr));
}

// �I��
void CDebugProc::Uninit(void)
{
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

// �ǉ�
void CDebugProc::Print(const char* fmt, ...)
{
#if 1
	va_list args;//va_list�}�N�����g�p

	va_start(args, fmt);

	if (m_nowIndx > 1024)
	{
		m_nowIndx = 0;
		return;
	}
	m_nowIndx  += vsprintf(&m_aStr[m_nowIndx], fmt, args);//vsprintf���g�p����ꍇ�́@�@#define _CRT_SECURE_WARNINGS
	
	va_end(args);

#endif
}

// �`��
void CDebugProc::Draw(int aWidth,int aHeight)
{
#if 1
	if (m_Enable == true)
	{
		RECT rect = { aWidth,aHeight, SCREEN_WIDTH,SCREEN_HEIGHT };

		//�e�L�X�g�̕`��
		m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 255, 0, 255));

		// �o�b�t�@���N���A
		memset(&m_aStr[0], NULL, sizeof(m_aStr));
	}

#endif
}