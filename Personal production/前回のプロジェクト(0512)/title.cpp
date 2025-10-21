//=================================================
//
//	title.cpp
// 
// Author:�ߓc ����
//
//=================================================

#include "title.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "texturemanager.h"
#include "game.h"
#include "tutorial.h"

// �R���X�g���N�^
CTitle::CTitle():CScene(CScene::MODE_TITLE)
{
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		m_pTitleManager[nCnt] = nullptr;
		m_aPosTexU[nCnt] = NULL;
	}

}

// �f�X�g���N�^
CTitle::~CTitle()
{

}

// ������
HRESULT CTitle::Init(void)
{

	m_pTitleManager[0] = CTitleManager::Create(D3DXVECTOR3(640.0f,360.0f,0.0f), "data\\TEXTURE\\title.jpg");
	m_pTitleManager[1] = CTitleManager::Create(D3DXVECTOR3(640.0f,360.0f,0.0f), "data\\TEXTURE\\title5.png");
	m_pTitleManager[2] = CTitleManager::Create(D3DXVECTOR3(640.0f,360.0f,0.0f), "data\\TEXTURE\\title1.png");

	return S_OK;
}

//�I��
void CTitle::Uninit(void)
{
	
}

// �X�V
void CTitle::Update(void)
{
	// �L�[�{�[�h
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetJoypad();

	m_aPosTexU[0] += 0.0001f;
	m_aPosTexU[2] += 0.001f;

	for (int nCntBG = 0; nCntBG < MAX_TITLE; nCntBG++)
	{
		m_pTitleManager[nCntBG]->SetAnim(m_aPosTexU[nCntBG], 1.0f);
		//m_pTitleManager[nCntBG]->SetAnim(m_aPosTexU[nCntBG], 1.0f);
	}

	// �t�F�[�h
	CFade* pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::KEY_START) == true)
	{//����L�[(ENTER�L�[)�������ꂽ
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		pFade->SetFade(new CTutorial());
	}
}

// �`��
void CTitle::Draw(void)
{

}