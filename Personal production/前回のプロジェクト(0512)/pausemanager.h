//=================================================
//
//	pausemanager.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef _PAUSEMANAGER_H_
#define _PAUSEMANAGER_H_

#include "main.h"
#include "pause.h"

// �}�N��
#define MAX_PAUSE (4)
class CPauseManager
{
public:

	//�|�[�Y���j���[
	typedef enum
	{
		MENU_CONTINUE = 0,	//�Q�[���ɖ߂�
		MENU_RETRY,			//�Q�[������蒼��
		MENU_QUIT,			//�^�C�g����ʂɖ߂�
		MENU_MAX
	}MENU;

	CPauseManager();
	~CPauseManager();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetEnablePause(bool bPause) { m_bPause = bPause; }
	void SetEnablePause(void);
	
	static bool GetPause(void) { return m_bPause; }
	static bool GetCheck(void) { return m_bCheck; }

private:
	CPause* m_pPause[MAX_PAUSE];
	int m_SelectIdx;

	static bool m_bPause;
	static bool m_bCheck;

};

#endif