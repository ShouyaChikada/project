//=================================================
//
//	manager.cpp
// 
// Author:�ߓc����
//
//=================================================
#include "manager.h"
#include "object2D.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include <stdlib.h>
#include "effect.h"
#include "number.h"
#include "time.h"

//�ÓI�����o�ϐ�
CMotion* CManager::m_pMotion = nullptr;
CMotion* CManager::m_pMotion1 = nullptr;
CModel* CManager::m_pModel[MAX_PMODEL] = {};
CModel* CManager::m_pModel1[MAX_HMODEL] = {};
CDebugProc* CManager::m_pDebugProc = nullptr;
CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;
CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyboard* CManager::m_pInputKeyboard = nullptr;
CInputJoypad* CManager::m_pInputJoypad = nullptr;
CInputMouse* CManager::m_pInputMouse = nullptr;
CObject* CManager::m_pObject = nullptr;
CScene* CManager::m_pScene = nullptr;
CFade* CManager::m_pFade = nullptr;
CTextureManager* CManager::m_pTexManager = nullptr;

//�R���X�g���N�^
CManager::CManager()
{
	
}
//�f�X�g���N�^
CManager::~CManager()
{

}

//����������
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�������m��
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, TRUE);

	m_pInputKeyboard = new CInputKeyboard;
	//�L�[�{�[�h�̏�����
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	m_pInputJoypad = new CInputJoypad;
	//�W���C�p�b�h�̏���������
	if (FAILED(m_pInputJoypad->Init()))
	{
		return E_FAIL;
	}

	m_pInputMouse = new CInputMouse;
	if (FAILED(m_pInputMouse->Init(hInstance,hWnd)))
	{
		return E_FAIL;
	}

	// �e�N�X�`���}�l�[�W���[�̃��[�h
	m_pTexManager = new CTextureManager;
	if (FAILED(m_pTexManager->Load()))
	{
		return E_FAIL;
	}

	m_pCamera = new CCamera;
	m_pCamera->Init();

	m_pLight = new CLight;
	m_pLight->Init();

	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();

	// �t�F�[�h�̐���
	m_pFade = new CFade;
	m_pFade->Init();

	m_pFade->SetFade(new CTitle());

	//m_pMotion1 = CMotion::Create("data\\human.txt", &m_pModel1[0]);	//whichMotion.txt || motion2.txt

	return S_OK;
}

//�I������
void CManager::Uninit(void)
{	
	//NULL�`�F�b�N
	if (m_pInputKeyboard != nullptr)
	{
		//�L�[�{�[�h�̏I������
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}
	
	//NULL�`�F�b�N
	if (m_pInputJoypad != nullptr)
	{
		//�W���C�p�b�h�̏I������
		m_pInputJoypad->Uninit();
		delete m_pInputJoypad;
		m_pInputJoypad = nullptr;
	}

	//NULL�`�F�b�N
	if (m_pInputMouse != nullptr)
	{
		//�}�E�X�̏I������
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = nullptr;
	}

	// NULL�`�F�b�N
	if (m_pRenderer != nullptr)
	{
		// �����_���[�̏I������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pDebugProc != nullptr)
	{
		// �f�o�b�O�t�H���g�̏I������
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}

	if (m_pCamera != nullptr)
	{
		// �J�����̏I������
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pLight != nullptr)
	{
		// ���C�g�̏I������
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	if (m_pFade != nullptr)
	{	
		// �t�F�[�h�̏I������
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	if (m_pTexManager != nullptr)
	{
		// �I������
		m_pTexManager->Unload();
		delete m_pTexManager;
		m_pTexManager = nullptr;
	}

	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	// ���ׂẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();
}

//�X�V����
void CManager::Update(void)
{
	if (m_pInputKeyboard != nullptr)
	{
		// �L�[�{�[�h�̍X�V
		m_pInputKeyboard->Update();
	}

	// �W���C�p�b�h�̍X�V
	if (m_pInputJoypad != nullptr)
	{
		m_pInputJoypad->Update();
	}

	if (m_pInputMouse != nullptr)
	{
		// �}�E�X�̍X�V
		m_pInputMouse->Update();
	}

	if (m_pCamera != nullptr)
	{
		// �J�����̍X�V����
		m_pCamera->Update();
	}

	if (m_pLight != nullptr)
	{
		// ���C�g�̍X�V����
		m_pLight->Update();
	}

	if (m_pFade != nullptr)
	{
		// �t�F�[�h�̍X�V����
		m_pFade->Update();
	}

	// null �`�F�b�N
	if (m_pScene != nullptr)
	{
		// �V�[���̍X�V����
		m_pScene->Update();
	}

	if (m_pRenderer != nullptr)
	{
		// �����_���[�̍X�V
		m_pRenderer->Update();
	}

}

// �`�揈��
void CManager::Draw()
{
	CScene::MODE pMode;
	pMode = m_pScene->GetMode();

	CFade::FADE pFade;
	pFade = m_pFade->GetFadeState();

	if (m_pRenderer != nullptr)
	{
		//�����_���[�̕`��
		m_pRenderer->Draw();

		if (pMode == m_pScene->MODE_TITLE)
		{
			CDebugProc::Print("���݂̃V�[��:�^�C�g��\n");
		}
		if (pMode == m_pScene->MODE_GAME)
		{
			CDebugProc::Print("���݂̃V�[��:�Q�[��\n");
		}
		if (pMode == m_pScene->MODE_RESULT)
		{
			CDebugProc::Print("���݂̃V�[��:���U���g\n");
		}

		if (pFade == m_pFade->FADE_IN)
		{
			CDebugProc::Print("���݂̃t�F�C�h:�t�F�C�h�C��\n");
		}

		if (pFade == m_pFade->FADE_OUT)
		{
			CDebugProc::Print("���݂̃t�F�C�h:�t�F�C�h�A�E�g\n");
		}
	}
}

// ���[�h�ݒ�
void CManager::SetMode(CScene* pNewScene)
{
	// �T�E���h�̒�~
	
	// �V�[���̔j��
	if (m_pScene != nullptr)
	{
		// ���݂̃��[�h��j��
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;

		// ���ׂẴI�u�W�F�N�g�̔j��
		CObject::ReleaseAll();

	}

	if (m_pScene == nullptr)
	{
		m_pScene = pNewScene;
		m_pScene->Init();
	}

}

//�����_���[�̏�����
CRenderer* CManager::GetRenderer(void) 
{
	return m_pRenderer;
}

//�L�[�{�[�h�̎擾
CInputKeyboard* CManager::GetKeyboard(void)
{
	return m_pInputKeyboard;
}

//�p�b�h�̎擾
CInputJoypad* CManager::GetJoypad(void)
{
	return m_pInputJoypad;
}

//�}�E�X�̎擾
CInputMouse* CManager::GetMouse(void)
{
	return m_pInputMouse;
}

// �I�u�W�F�N�g�̎擾
CObject* CManager::getobject(void)
{
	return m_pObject;
}

CFade* CManager::GetFade()
{
	return m_pFade;
}

// �f�o�b�O�t�H���g�̎擾
CDebugProc* CManager::GetDebugProc(void)
{
	return m_pDebugProc;
}

// �J�����̎擾
CCamera* CManager::GetCamera(void)
{
	return m_pCamera;
}

// ���C�g�̎擾
CLight* CManager::GetLight(void)
{
	return m_pLight;
}

// �e�N�X�`���}�l�[�W���[�̎擾
CTextureManager* CManager::GetTexManager(void)
{
	return m_pTexManager;
}

// ���[�V�����̎擾
CMotion* CManager::GetMotion(void)
{
	return m_pMotion;
}
// ���[�V�����̎擾1
CMotion* CManager::GetMotion1(void)
{
	return m_pMotion1;
}

CModel** CManager::GetModel(void)
{
	return &m_pModel[0];
}

CModel** CManager::GetModel1(void)
{
	return &m_pModel1[0];
}