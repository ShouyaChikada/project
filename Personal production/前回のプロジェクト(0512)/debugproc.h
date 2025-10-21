//=================================================
//
//	debugproc.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"

class CDebugProc
{
public:

	CDebugProc();
	~CDebugProc();
	void Init(void);
	void Uninit(void);

	static void Print(const char* fmt,...);
	static void Draw(int aWidth, int aHeight);
	static void End(void) { m_nowIndx = 0; };
	static bool GetEnable(void) { return m_Enable; };
	static void SetEnable(bool Enable) { m_Enable = Enable; };
private:

	static LPD3DXFONT m_pFont;		//�t�H���g�ւ̃|�C���^
	static char m_aStr[1024];		//��������i�[����o�b�t�@
	static int m_nowIndx;
	static bool m_Enable;
	static int m_nCountFPS;
};

#endif 