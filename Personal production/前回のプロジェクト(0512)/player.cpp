//=================================================
//
//	player.cpp
// 
//	Author:�ߓc����
//
//=================================================
#include "player.h"
#include "input.h"
#include "manager.h"
#include "camera.h"
#include "debugproc.h"
#include "blockmanager.h"
#include "game.h"
#include "gimmickmanager.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//============================
// �R���X�g���N�^
//============================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{	
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < MAX_PMODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;

	}
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Diff = 0.0f;
	m_bJump = false;
	m_pMotion = NULL;
	m_bLeave = true;
	m_pShadowS = nullptr;
	m_pParticle = nullptr;
}

//CPlayer::CPlayer(int nPriority):CObject2D((int)nPriority)
//{
//	nPriority = 5;
//}

//============================
// �f�X�g���N�^
//============================
CPlayer::~CPlayer()
{

}

//============================
//  ��������
//============================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer* pPlayer = nullptr;
	pPlayer = new CPlayer;

	if(pPlayer != nullptr)
	{
		pPlayer->m_pos = pos;
		pPlayer->m_rot = rot;
		pPlayer->Init();
		return pPlayer;
	}
	else
	{
		return nullptr;
	}
}

//============================
// ����������
//============================
HRESULT CPlayer::Init(void)
{

	m_pShadowS = CShadowS::Create("data\\MODEL\\bou3.x",m_pos, m_rot);
	m_pMotion = CMotion::Create("data\\whichMotion.txt",&m_apModel[0]);	//whichMotion.txt || motion2.txt
	m_size = CModel::GetSize();

	return S_OK;
}

//============================
// �I������
//============================
void CPlayer::Uninit(void)
{
	m_bLeave = false;

	// ���f���̔j��
	for (int nCnt = 0; nCnt < MAX_PMODEL; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = NULL;
		}
	}
	
	// ���[�V�����̔j��
	if (m_pMotion != NULL)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}

	CObject::Release();
}

//============================
// �X�V����
//============================
void CPlayer::Update(void)
{
	m_pMotion->Update(&m_apModel[0]);

	//�ړ��ƃ��[�V�����̃Z�b�g
	SetInput();


	//fCirc = 2.0f * D3DX_PI * 5.0f;

	//m_move.y = (fValueRot / (2 * D3DX_PI)) * fCirc;
	//m_move.z = (fValueRot / (2 * D3DX_PI)) * fCirc;

	//m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�p�x�̐��K��
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = m_rot.y + D3DX_PI;
		m_rot.y = D3DX_PI + m_rot.y;
	}
	else if (m_rot.y > D3DX_PI)
	{
		m_rot.y = m_rot.y - D3DX_PI;
		m_rot.y = -D3DX_PI - m_rot.y;

	}

	//�p�x�̒���
	m_Diff = m_rotDest.y - m_rot.y;

	if (m_Diff < -D3DX_PI)
	{
		m_Diff = m_Diff + (D3DX_PI * 2);
	}
	else if (m_Diff > D3DX_PI)
	{
		m_Diff = m_Diff - (D3DX_PI * 2);
	}

	//�v���C���[�̌���
	m_rot.y += m_Diff * 0.25f;

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.5f;
	m_move.z += (0.0f - m_move.z) * 0.5f;

	//�O��̈ʒu��ۑ�	�ʒu�X�V�̏�ŏ���
	m_posOld = m_pos;

	CBlock** pBlock = CBlockManager::GetBlock();
	CGimmick** pGimmick = CGimmickManager::GetGimmick();

	m_pos += m_move;

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (pBlock[nCnt] != nullptr)
		{
			//�u���b�N�Ƃ̓����蔻��
			if (pBlock[nCnt]->Collision(&m_pos, &m_posOld, &m_move, &m_size) == true)
			{
				m_move.y = 0.0f;
			}

		}
	}

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (pGimmick[nCnt] != nullptr)
		{
			if (pGimmick[nCnt]->Collision(&m_pos, &m_posOld, &m_move, &m_size) == true)
			{
				m_move.y = 0.0f;
			}
		}
	}

	//m_move.y -= 0.4f;	//�d�͉��Z

	////�d��
	//if (m_pos.y < -600.0f)
	//{
	//	m_pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	//	m_move.y = 0.0f;
	//	m_bJump = false;
	//}

	// �ړ��̐���
	if (m_pos.y > 800.0f || m_pos.x > 2500.0f || m_pos.z > 2500.0f)
	{
		m_pos = m_posOld;
	}
	else if (m_pos.y < -180.0f || m_pos.x < -2500.0f || m_pos.z < -2500.0f)
	{
		m_pos = m_posOld;
	}

	m_pShadowS->SetShadow(m_pos, m_rot);

	SetPosition(m_pos);
}

//============================
// �`�揈��
//============================
void CPlayer::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p

	//D3DXMATRIX mtxRot;		// ��]�}�g���b�N�X(�ۑ��p)
	D3DXQUATERNION quat;	// �N�H�[�^�j�I��
	D3DXVECTOR3 vecAxis = m_rot;	// ��]��
	float fValueRot = 0.0f;	// ��]�p(��]��)
	float fCirc = 0.0f;		//�~��(�v�Z�p)

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]���̂�����w��̉�]�p����N�H�[�^�j�I�����쐬
	D3DXQuaternionRotationAxis(&quat, &vecAxis, fValueRot);
	// �N�H�[�^�j�I�������]�}�g���b�N�X�̍쐬
	D3DXMatrixRotationQuaternion(&mtxRot, &quat);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pD3DDevice->GetMaterial(&matDef);

	//���f���p�[�c��`��
	for (int nCnt = 0; nCnt < MAX_PMODEL; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

	//�ۑ����Ă����}�e���A�����B��
	pD3DDevice->SetMaterial(&matDef);

	CDebugProc::Print("�v���C���[���W : { %.2f,%.2f,%.2f }\n", m_pos.x, m_pos.y, m_pos.z);

}


//============================
// �ړ�����
//============================
void CPlayer::SetInput(void)
{
	bool bUse = CGimmickManager::GetPush();
	bool bCheck = CGimmickManager::GetbCheck();

	// �L�[�{�[�h
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	//�J�����̏��擾
	CCamera* pCamera = CManager::GetCamera();
	D3DXVECTOR3 rot = pCamera->GetRotasion();

	pCamera->SetFollowing(m_pos, m_rotDest);

	//if (pInputKeyboard->GetPress(DIK_F) == true)
	//{
	//	m_pParticle = CParticle::Create(D3DXVECTOR3(m_pos), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 30);
	//}


	if (bUse == false || bCheck == true)
	{
		//���ړ�
		if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			// �ړ��̃��[�V����
			m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

			//�O�ړ�
			if (pInputKeyboard->GetPress(DIK_W) == true)
			{
				m_rotDest.y = rot.y + D3DX_PI * 0.75f;
				m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
				m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;

				//m_rot.z = 0.19625f;

			}
			//���ړ�
			else if (pInputKeyboard->GetPress(DIK_S) == true)
			{

				m_rotDest.y = rot.y + D3DX_PI * 0.25f;
				m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
				m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;

			}
			else
			{

				m_rotDest.y = rot.y + D3DX_PI * 0.5f;
				m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
				m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;

			}
		}
		//�E�ړ�
		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			// �ړ��̃��[�V����
			m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);
			//�O�ړ�
			if (pInputKeyboard->GetPress(DIK_W) == true)
			{
				m_rotDest.y = rot.y - D3DX_PI * 0.75f;
				m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
				m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			}
			//���ړ�
			else if (pInputKeyboard->GetPress(DIK_S) == true)
			{
				m_rotDest.y = rot.y - D3DX_PI * 0.25f;
				m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
				m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			}
			else
			{

				m_rotDest.y = rot.y - D3DX_PI * 0.5f;
				m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
				m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			}
		}
		//�O�ړ�
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			// �ړ��̃��[�V����
			m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

			if (pInputKeyboard->GetPress(DIK_D) == true)
			{
				m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
				m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			}
			//�O�ړ�
			else if (pInputKeyboard->GetPress(DIK_A) == true)
			{
				m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
				m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			}
			else
			{
				m_rotDest.y = rot.y + D3DX_PI;
				m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
				m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			}
		}
		//���ړ�
		if (pInputKeyboard->GetPress(DIK_S) == true)
		{
			// �ړ��̃��[�V����
			m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

			if (pInputKeyboard->GetPress(DIK_D) == true)
			{
				m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
				m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			}
			//�O�ړ�
			else if (pInputKeyboard->GetPress(DIK_A) == true)
			{
				m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
				m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			}
			else
			{
				m_rotDest.y = rot.y;
				m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
				m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;

			}
		}

		// �㏸
		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{
			m_move.y = 2.5f;
		}

		// �~��
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{
			m_move.y = -2.5f;
		}
		else
		{
			m_move.y = 0.0f;
		}

		// �����ĂȂ��Ƃ��̓j���[�g������
		if (pInputKeyboard->GetPress(DIK_W) == false &&
			pInputKeyboard->GetPress(DIK_S) == false &&
			pInputKeyboard->GetPress(DIK_A) == false &&
			pInputKeyboard->GetPress(DIK_D) == false &&
			m_bJump == false)
		{
			m_pMotion->Set(CMotion::MOTIONTYPE_NEUTRAL);
		}
	}
}

// �ʒu�̐ݒ�
void CPlayer::SetPosition(D3DXVECTOR3 pos)
{
	m_SetPosition = pos;
}

// �ʒu���擾
D3DXVECTOR3 CPlayer::GetPosition(void)
{
	return m_SetPosition;
}

D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

// �ړ��ʂ��擾
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

// �O��̈ʒu���擾
D3DXVECTOR3 CPlayer::GetPosOld(void)
{	
	return m_posOld;
}

// �T�C�Y���擾
D3DXVECTOR3 CPlayer::GetSize(void)
{
	return m_size;
}
// �ړI�̌����̎擾
D3DXVECTOR3 CPlayer::GetRotDest(void)
{
	return m_rotDest;
}