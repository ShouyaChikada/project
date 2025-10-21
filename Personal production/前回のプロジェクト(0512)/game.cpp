//=================================================
//
//	game.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "game.h"
#include "manager.h"
#include "result.h"

// �ÓI�����o�ϐ�
CPlayer* CGame::m_pPlayer = nullptr;
CScore* CGame::m_pScore = nullptr;
CObject3D* CGame::m_pObject3D = nullptr;
CBillboard* CGame::m_pBillboard = nullptr;
CObjectX* CGame::m_pObjectX = nullptr;
CMeshField* CGame::m_pMeshField = nullptr;
CBlockManager* CGame::m_pBlockManager = nullptr;
CShadowS* CGame::m_pShadowS = nullptr;
CGrand* CGame::m_pGrand = nullptr;
CGimmickManager* CGame::m_pGimmickManager = nullptr;
CHumManager* CGame::m_pHumManager = nullptr;
CTime* CGame::m_pTime = nullptr;
CPauseManager* CGame::m_pPauseManager = nullptr;
CModel* CGame::m_pModel1[MAX_HMODEL] = {};
CMotion* CGame::m_pMotion1 = nullptr;
bool CGame::m_bCheck = false;

// �R���X�g���N�^
CGame::CGame() : CScene(CScene::MODE_GAME)
{

}

// �f�X�g���N�^
CGame::~CGame()
{

}

// ������
HRESULT CGame::Init(void)
{
	m_pMotion1 = CMotion::Create("data\\human.txt", &m_pModel1[0]);	//whichMotion.txt || motion2.txt

	m_bCheck = false;

	m_pBlockManager = new CBlockManager;
	if (FAILED(m_pBlockManager->Init()))
	{
		return E_FAIL;
	}

	m_pGimmickManager = new CGimmickManager;
	if (FAILED(m_pGimmickManager->Init()))
	{
		return E_FAIL;
	}

	m_pHumManager = new CHumManager;
	if (FAILED(m_pHumManager->Init()))
	{
		return E_FAIL;
	}

	m_pPauseManager = new CPauseManager;
	if (FAILED(m_pPauseManager->Init()))
	{
		return E_FAIL;
	}

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(300.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pScore = CScore::Create(D3DXVECTOR3(1000.0f, 50.0f, 0.0f));

	m_pMeshField = CMeshField::Create(D3DXVECTOR3(200.0f, -1100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f);

	m_pGrand = CGrand::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pTime = CTime::Create(D3DXVECTOR3(100.0f, 50.0f, 0.0f));

	return S_OK;
}

// �I������
void CGame::Uninit(void)
{
	if (m_pBlockManager != nullptr)
	{
		// �u���b�N�}�l�[�W���[�̏I������
		m_pBlockManager->Uninit();
		delete m_pBlockManager;
		m_pBlockManager = nullptr;
	}

	if (m_pGimmickManager != nullptr)
	{
		// �M�~�b�N�}�l�[�W���[�̏I������
		m_pGimmickManager->Uninit();
		delete m_pGimmickManager;
		m_pGimmickManager = nullptr;
	}

	if (m_pHumManager != nullptr)
	{
		// �q���[�}���}�l�[�W���[�̏I������
		m_pHumManager->Uninit();
		delete m_pHumManager;
		m_pHumManager = nullptr;
	}

	if (m_pPauseManager != nullptr)
	{
		// �|�[�Y�}�l�[�W���[�̏I������
		m_pPauseManager->Uninit();
		delete m_pPauseManager;
		m_pPauseManager = nullptr;
	}

}

// �X�V����
void CGame::Update(void)
{
	// �L�[�{�[�h
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	// �|�[�Y�̉����m�F�֐�
	m_pPauseManager->SetEnablePause();

	// �|�[�Y�̍X�V����
	m_pPauseManager->Update();
	

	//// �p�b�h
	//CInputJoypad* pInputJoypad = nullptr;
	//pInputJoypad = CManager::GetJoypad();

	// �t�F�[�h
	CFade* pFade = CManager::GetFade();


	if (m_pPauseManager->GetPause() == false)
	{
		// �u���b�N�}�l�[�W���[�̍X�V����
		m_pBlockManager->Update();

		// �M�~�b�N�}�l�[�W���[�̍X�V����
		m_pGimmickManager->Update();

		// �q���[�}���}�l�[�W���[�̍X�V����
		m_pHumManager->Update();

		bool bFinish = m_pTime->GetbTime();

		if (bFinish == true || pInputKeyboard->GetTrigger(DIK_M) == true)
		{//����L�[(ENTER�L�[)�������ꂽ
			//���[�h�ݒ�(�Q�[����ʂɈڍs)
			pFade->SetFade(new CResult());
			m_bCheck = true;
		}
	}
}

// �`�揈��
void CGame::Draw(void)
{
	// �M�~�b�N�}�l�[�W���[�̕`�揈��
	m_pGimmickManager->Draw();
}

// �v���C���[�̎擾
CPlayer* CGame::GetPlayer(void)
{
	return m_pPlayer;
}

// �X�R�A�̎擾
CScore* CGame::GetScore(void)
{
	return m_pScore;
}

// ���C�g�̎擾
CObject3D* CGame::GetObject3D(void)
{
	return m_pObject3D;
}

// ���C�g�̎擾
CBillboard* CGame::GetBillboard(void)
{
	return m_pBillboard;
}

// �I�u�W�F�N�gX�̎擾
CObjectX* CGame::GetObjectX(void)
{
	return m_pObjectX;
}

// ���b�V���t�B�[���h�̎擾
CMeshField* CGame::GetMeshField(void)
{
	return m_pMeshField;
}

// �I�u�W�F�N�g�̎擾
CBlockManager* CGame::GetBlockManager(void)
{
	return m_pBlockManager;
}

// �e�̎擾
CShadowS* CGame::GetShadowS(void)
{
	return m_pShadowS;
}

// �n�ʂ̎擾
CGrand* CGame::GetGrand(void)
{
	return m_pGrand;
}

// �M�~�b�N�}�l�[�W���[�̎擾
CGimmickManager* CGame::GetGimmickManager(void)
{
	return m_pGimmickManager;
}

// �q���[�}���}�l�[�W���[�̎擾
CHumManager* CGame::GetHumManamger(void)
{
	return m_pHumManager;
}

// �^�C���̎擾
CTime* CGame::GetTime(void)
{
	return m_pTime;
}

// ���[�V�����̎擾1
CMotion* CGame::GetMotion1(void)
{
	return m_pMotion1;
}

CModel** CGame::GetModel1(void)
{
	return &m_pModel1[0];
}
