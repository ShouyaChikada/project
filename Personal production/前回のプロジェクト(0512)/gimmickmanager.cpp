//=================================================
//
//	gimmickmanager.cpp
// 
//	Author:�ߓc����
//
//=================================================
#include "gimmickmanager.h"
#include "game.h"
#include "player.h"
#include "debugproc.h"
#include "input.h"
#include "manager.h"
#include "meshcylinder.h"
#include "gauge.h"
#include "time.h"
#include "scene.h"
#include "tutorial.h"

//�ÓI�����o�ϐ�
CParticle* CGimmickManager::m_pParticle = nullptr;
CGimmick* CGimmickManager::m_pGimmick[MAX_GIMMICK] = {};
bool CGimmickManager::m_bRange = false;
bool CGimmickManager::m_bPush = false;
int CGimmickManager::m_nCntGimmick = 0;
bool CGimmickManager::m_bCheck = false;

// �R���X�g���N�^
CGimmickManager::CGimmickManager()
{
	for (int nCnt = 0; nCnt < MAX_COUNT; nCnt++)
	{
		m_nCnt[nCnt] = 0;
	}
	m_bTime = false;
}

// �f�X�g���N�^
CGimmickManager::~CGimmickManager()
{

}

//=========================
//�@�u���b�N����������
//=========================
HRESULT CGimmickManager::Init(void)
{
	CScene::MODE mode = CScene::GetMode();

	if (mode != CScene::MODE_TUTORIAL)
	{
		m_bCheck = false;
		m_bRange = false;
		m_bPush = false;
		m_pGimmick[0] = CGimmick::Create(D3DXVECTOR3(-200.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmick::TYPE_THUNDER);
		//m_pGimmick[1] = CGimmick::Create(D3DXVECTOR3(-200.0f, 700.0f, 0.0f), D3DXVECTOR3(90, 0.0f, 90), CGimmick::TYPE_METEORITE);

		//m_bUse = ;
	}
	if (mode == CScene::MODE_TUTORIAL)
	{
		m_bCheck = false;
		m_bRange = false;
		m_bPush = false;
		m_pGimmick[0] = CGimmick::Create(D3DXVECTOR3(-200.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmick::TYPE_THUNDER);
	}
	return S_OK;
}
//=========================
//�@�u���b�N�I������
//=========================
void CGimmickManager::Uninit(void)
{

}
//=========================
//�@�u���b�N�X�V����
//=========================
void CGimmickManager::Update(void)
{
	CScene::MODE mode = CScene::GetMode();

	if (mode != CScene::MODE_TUTORIAL)
	{
		// �L�[�{�[�h
		CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

		// �v���C���[
		CPlayer* pPlayer = CGame::GetPlayer();

		// ���b�V���V�����_�[
		CMeshCylinder* pMeshcylinder = CGimmick::GetMeshCylinder();

		// �Q�[�W
		CGauge* pGauge = CGimmick::GetGauge();

		// UI
		CBaseUI* pBaseUI = CGimmick::GetBaseUI();

		// ����
		int nTime = CTime::GetTime();

		D3DXVECTOR3 GimmickPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		CGimmick::TYPE type = CGimmick::TYPE_METEORITE;
		bool bUse = false;

		for (int nCnt = 0; nCnt < MAX_GIMMICK; nCnt++)
		{
			if (m_pGimmick[nCnt] != nullptr)
			{
				// �M�~�b�N
				GimmickPos = m_pGimmick[nCnt]->GetPos();
				type = m_pGimmick[nCnt]->GetType();
				bUse = m_pGimmick[nCnt]->GetUse();
			}
		}
		// �g���Ă��� & �u���b�N�̃^�C�v������������
		if (bUse == true && type == CGimmick::TYPE_THUNDER)
		{
			//�p�[�e�B�N���p�x
			float fAngleX = (float)(rand() % 628 - 314) * 0.01f;
			float fAngleY = (float)(rand() % 628 - 314) * 0.01f;
			float fAngleZ = (float)(rand() % 628 - 314) * 0.01f;

			//���a�̎Z�o�ϐ�
			float PRadiusPos = 55.0f;
			float GRadiusPos = 195.0f;

			//�v���C���[�̈ʒu�̎擾
			D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

			//�͈͌v�Z
			float fDisX = PlayerPos.x - GimmickPos.x;
			float fDisY = PlayerPos.y - GimmickPos.y;
			float fDisZ = PlayerPos.z - GimmickPos.z;

			//��̔��a�����߂�
			float fRadX = PRadiusPos + GRadiusPos;

			// �v���C���[�����̃M�~�b�N�͈̔͂ɓ����Ă�����
			if ((fDisX * fDisX) + (fDisZ * fDisZ) <= (fRadX * fRadX))
			{
				m_bRange = true;

				// F�{�^���������Ă�����
				if (pInputKeyboard->GetPress(DIK_F) == true)
				{
					m_bPush = true;

					m_nCnt[0]++;

					if (m_nCnt[0] >= 480)
					{
						m_bCheck = true;

					}
				}
				else if (pInputKeyboard->GetPress(DIK_F) == false && m_bCheck == false)
				{
					m_bPush = false;
				}

			}
			else
			{
				if (m_bCheck == false)
				{
					m_bRange = false;
					m_bPush = false;
				}
			}

			if (m_bCheck == true)
			{
				m_nCnt[1]++;
				//m_bUse = true;
				if (m_nCnt[1] >= 120)
				{
					for (int nCnt = 0; nCnt < MAX_GIMMICK; nCnt++)
					{
						if (m_pGimmick[nCnt] != nullptr)
						{
							m_pGimmick[nCnt]->Uninit();
						}
					}

					if (pMeshcylinder != nullptr)
					{
						pMeshcylinder->Uninit();
					}

					if (pGauge != nullptr)
					{
						pGauge->Uninit();
					}

					if (pBaseUI != nullptr)
					{
						pBaseUI->Uninit();
					}

					m_nCnt[0] = 0;
					m_nCnt[1] = 0;


					// �C�� or �j��̃J�E���g
					m_nCntGimmick++;
				}
			}
		}
		if (nTime == 5400 || nTime == 3600 || nTime == 1800)
		{
			m_bTime = true;
		}
		if (m_bTime == true)
		{
			m_bCheck = false;
			m_pGimmick[1] = CGimmick::Create(D3DXVECTOR3(-200.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmick::TYPE_THUNDER);
			m_bTime = false;
		}
	}

	if (mode == CScene::MODE_TUTORIAL)
	{
		// �L�[�{�[�h
		CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

		// �v���C���[
		CPlayer* pPlayer = CTutorial::GetPlayer();

		// ���b�V���V�����_�[
		CMeshCylinder* pMeshcylinder = CGimmick::GetMeshCylinder();

		// �Q�[�W
		CGauge* pGauge = CGimmick::GetGauge();

		// UI
		CBaseUI* pBaseUI = CGimmick::GetBaseUI();

		D3DXVECTOR3 GimmickPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		CGimmick::TYPE type = CGimmick::TYPE_METEORITE;
		bool bUse = false;

		if (m_pGimmick[0] != nullptr)
		{
			// �M�~�b�N
			GimmickPos = m_pGimmick[0]->GetPos();
			type = m_pGimmick[0]->GetType();
			bUse = m_pGimmick[0]->GetUse();
		}
		// �g���Ă��� & �u���b�N�̃^�C�v������������
		if (bUse == true && type == CGimmick::TYPE_THUNDER)
		{
			//�p�[�e�B�N���p�x
			float fAngleX = (float)(rand() % 628 - 314) * 0.01f;
			float fAngleY = (float)(rand() % 628 - 314) * 0.01f;
			float fAngleZ = (float)(rand() % 628 - 314) * 0.01f;

			//���a�̎Z�o�ϐ�
			float PRadiusPos = 55.0f;
			float GRadiusPos = 195.0f;

			//�v���C���[�̈ʒu�̎擾
			D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

			//�͈͌v�Z
			float fDisX = PlayerPos.x - GimmickPos.x;
			float fDisY = PlayerPos.y - GimmickPos.y;
			float fDisZ = PlayerPos.z - GimmickPos.z;

			//��̔��a�����߂�
			float fRadX = PRadiusPos + GRadiusPos;

			// �v���C���[�����̃M�~�b�N�͈̔͂ɓ����Ă�����
			if ((fDisX * fDisX) + (fDisZ * fDisZ) <= (fRadX * fRadX))
			{
				m_bRange = true;

				// F�{�^���������Ă�����
				if (pInputKeyboard->GetPress(DIK_F) == true)
				{
					m_bPush = true;

					m_nCnt[0]++;

					if (m_nCnt[0] >= 30) // 480
					{
						m_bCheck = true;

					}
				}
				else if (pInputKeyboard->GetPress(DIK_F) == false && m_bCheck == false)
				{
					m_bPush = false;
				}

			}
			else
			{
				if (m_bCheck == false)
				{
					m_bRange = false;
					m_bPush = false;
				}
			}

			if (m_bCheck == true)
			{
				m_nCnt[1]++;
				//m_bUse = true;
				if (m_nCnt[1] >= 120)
				{
					
					if (m_pGimmick[0] != nullptr)
					{
						m_pGimmick[0]->Uninit();
					}
					

					if (pMeshcylinder != nullptr)
					{
						pMeshcylinder->Uninit();
					}

					if (pGauge != nullptr)
					{
						pGauge->Uninit();
					}

					//if (pBaseUI != nullptr)
					//{
					//	pBaseUI->Uninit();
					//}

					m_nCnt[0] = 0;
					m_nCnt[1] = 0;

				}
			}
		}
	}

	
}
//=========================
//�@�u���b�N�`�揈��
//=========================
void CGimmickManager::Draw(void)
{
	// �͈͂ɓ����Ă�����
	if (m_bRange == true)
	{
		CDebugProc::Print("�M�~�b�N�͈� + [ F ] : �I��\n");
	}
	// �͈͊O��������
	else if (m_bRange == false)
	{
		CDebugProc::Print("�M�~�b�N�͈� + [ F ] : �I�t\n");
	}

	// ��Ƃ��I���Ă�����
	if (m_bCheck == true)
	{
		// �`�揈��
		//m_pBaseUI->Draw();
	}
}