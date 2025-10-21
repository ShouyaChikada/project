//=================================================
//
//	result.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "result.h"
#include "fade.h"
#include "manager.h"
#include "title.h"
#include "game.h"

// �ÓI�����o�ϐ�
bool CResult::m_bCheck = false;

// �R���X�g���N�^
CResult::CResult() :CScene(CScene::MODE_RESULT)
{
	m_pResultManager = nullptr;
}

// �f�X�g���N�^
CResult::~CResult()
{

}

//�^�C�g����ʂ̏���������
HRESULT CResult::Init(void)
{
	m_bCheck = false;

	m_pResultManager = CResultManager::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f),"data\\TEXTURE\\result.jpg");
	return S_OK;
}
//���U���g�̏I������
void CResult::Uninit(void)
{

}
//�^�C�g����ʂ̍X�V����
void CResult::Update(void)
{
	// �Q�[���̏I���̔���
	bool bUse = CGame::GetCheck();

	if (bUse == true)
	{
		m_bCheck = true;
	}

	// �L�[�{�[�h
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	// �t�F�[�h
	CFade* pFade = CManager::GetFade();
	CFade::FADE mFade;
	mFade = pFade->GetFadeState();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && mFade == CFade::FADE_NONE)
	{//����L�[(ENTER�L�[)�������ꂽ
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		pFade->SetFade(new CTitle());
	}
}
//�^�C�g����ʂ̕`�揈��
void CResult::Draw(void)
{

}