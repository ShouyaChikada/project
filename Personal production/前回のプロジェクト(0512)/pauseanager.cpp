//=================================================
//
//	pausemanager.h
// 
//	Author:�ߓc����
//
//=================================================
#include "pausemanager.h"
#include "input.h"
#include "game.h"
#include "manager.h"
#include "scene.h"

// �ÓI�����o�ϐ�
bool CPauseManager::m_bPause = false;
bool CPauseManager::m_bCheck = false;

// �R���X�g���N�^
CPauseManager::CPauseManager()
{
	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		m_pPause[nCnt] = nullptr;
	}

	m_SelectIdx = 1;
}

// �f�X�g���N�^
CPauseManager::~CPauseManager()
{

}

// ������
HRESULT CPauseManager::Init(void)
{
	m_bCheck = false;

	m_pPause[0] = CPause::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), 640.0f, 360.0f, "data\\TEXTURE\\brack.png");
	m_pPause[1] = CPause::Create(D3DXVECTOR3(640.0f, 180.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 125.0f, 60.0f, "data\\TEXTURE\\continue2.png");
	m_pPause[2] = CPause::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 275.0f, 60.0f, "data\\TEXTURE\\retry2.png");
	m_pPause[3] = CPause::Create(D3DXVECTOR3(640.0f, 540.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),300.0f, 60.0f,"data\\TEXTURE\\quit2.png");

	return S_OK;
}

// �I������
void CPauseManager::Uninit(void)
{

}

// �X�V����
void CPauseManager::Update(void)
{
	if (!m_bPause) return;

	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();
	
	CInputJoypad* pInputJoypad = CManager::GetJoypad();

	// �t�F�[�h
	CFade* pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_UP) == true)
	{
		if (m_SelectIdx == 1)
		{
			m_SelectIdx = 3;
		}
		else if (m_SelectIdx == 2)
		{
			m_SelectIdx = 1;
		}
		else if (m_SelectIdx == 3)
		{
			m_SelectIdx = 2;
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_DOWN) == true)
	{
		if (m_SelectIdx == 1)
		{
			m_SelectIdx = 2;
		}
		else if (m_SelectIdx == 2)
		{
			m_SelectIdx = 3;
		}
		else if (m_SelectIdx == 3)
		{
			m_SelectIdx = 1;
		}
	}

	// �J���[
	switch (m_SelectIdx - 1)
	{
	case MENU_CONTINUE:
		m_pPause[1]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pPause[2]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pPause[3]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		break;
	case MENU_RETRY:
		m_pPause[1]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pPause[2]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pPause[3]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		break;
	case MENU_QUIT:
		m_pPause[1]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pPause[2]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pPause[3]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{//����L�[(ENTER�L�[)�������ꂽ
		//���j���[�ɍ��킹�ă��[�h�̐؂�ւ�
		switch (m_SelectIdx - 1)
		{
		case MENU_CONTINUE:
			SetEnablePause(false);
			break;
		case MENU_RETRY:
			pFade->SetFade(new CGame());
			SetEnablePause(false);
			m_bCheck = true;
			break;
		case MENU_QUIT:
			pFade->SetFade(new CTitle());
			SetEnablePause(false);
			m_bCheck = true;
			break;
		}
	}

}

void CPauseManager::Draw(void)
{

}

void CPauseManager::SetEnablePause(void)
{
	// �L�[�{�[�h
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_TAB) == true)
	{//�|�[�Y�L�[(TAB�L�[)�������ꂽ
		m_bPause = m_bPause ? false:true;
	}
}
