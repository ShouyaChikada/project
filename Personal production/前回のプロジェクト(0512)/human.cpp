//=================================================
//
//	human.cpp
// 
//	Author:�ߓc����
//
//=================================================
#include "human.h"
#include "input.h"
#include "manager.h"
#include "camera.h"
#include "debugproc.h"
#include "blockmanager.h"
#include "game.h"
#include "gimmickmanager.h"
#include "time.h"
#include "tutorial.h"

//============================
// �R���X�g���N�^
//============================
CHuman::CHuman(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_HMODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Diff = 0.0f;
	m_bJump = false;
	m_pMotion = nullptr;;
	m_bLeave = true;
	m_nCnt = 0;
	m_bCnt = false;
}

//============================
// �f�X�g���N�^
//============================
CHuman::~CHuman()
{

}

//============================
//  ��������
//============================
CHuman* CHuman::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CHuman* pHuman = nullptr;
	pHuman = new CHuman;

	if (pHuman != nullptr)
	{
		pHuman->m_pos = pos;
		pHuman->m_rot = rot;
		pHuman->Init();
		return pHuman;
	}
	else
	{
		return nullptr;
	}
}

//============================
// ����������
//============================
HRESULT CHuman::Init(void)
{
	CScene::MODE mode = CScene::GetMode();

	static CModel** pModel = nullptr;

	if (mode != CScene::MODE_TUTORIAL)
	{
		m_pMotion = CGame::GetMotion1();
		pModel = CGame::GetModel1();
	}
	else if (mode == CScene::MODE_TUTORIAL)
	{
		m_pMotion = CTutorial::GetMotion1();
		pModel = CTutorial::GetModel1();
	}

	if (pModel != nullptr)
	{
		for (int nCnt = 0; nCnt < MAX_HMODEL; nCnt++)
		{
			m_apModel[nCnt] = pModel[nCnt];
		}
	}

	m_size = CModel::GetSize();

	srand((unsigned int)time(NULL));

	return S_OK;
}

//============================
// �I������
//============================
void CHuman::Uninit(void)
{
	if (this == nullptr) return;

	m_bLeave = false;

	// ���f���̔j��
	for (int nCnt = 0; nCnt < MAX_HMODEL; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = nullptr;
		}
	}

	// ���[�V�����̔j��
	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	CObject::Release();
}

//============================
// �X�V����
//============================
void CHuman::Update(void)
{
	m_pMotion->Update(&m_apModel[0]);

	//AutoWand(m_pos);

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

	m_move.y -= 0.4f;	//�d�͉��Z

	//�d��
	if (m_pos.y < -600.0f)
	{
		m_pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
		m_move.y = 0.0f;
		m_bJump = false;
	}

	// �ړ��̐���
	if (m_pos.y > 800.0f || m_pos.x > 2500.0f || m_pos.z > 2500.0f)
	{
		m_pos = m_posOld;
	}
	else if (m_pos.y < -180.0f || m_pos.x < -2500.0f || m_pos.z < -2500.0f)
	{
		m_pos = m_posOld;
	}

	SetPosition(m_pos);
}

//============================
// �`�揈��
//============================
void CHuman::Draw(void)
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
	for (int nCnt = 0; nCnt < MAX_HMODEL; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

	//�ۑ����Ă����}�e���A�����B��
	pD3DDevice->SetMaterial(&matDef);

}

// �ʒu�̐ݒ�
void CHuman::SetPosition(D3DXVECTOR3 pos)
{
	m_SetPosition = pos;
}

// �ʒu���擾
D3DXVECTOR3 CHuman::GetPosition(void)
{
	return m_SetPosition;
}

D3DXVECTOR3 CHuman::GetPos(void)
{
	return m_pos;
}

// �ړ��ʂ��擾
D3DXVECTOR3 CHuman::GetMove(void)
{
	return m_move;
}

// �O��̈ʒu���擾
D3DXVECTOR3 CHuman::GetPosOld(void)
{
	return m_posOld;
}

// �T�C�Y���擾
D3DXVECTOR3 CHuman::GetSize(void)
{
	return m_size;
}
// �ړI�̌����̎擾
D3DXVECTOR3 CHuman::GetRotDest(void)
{
	return m_rotDest;
}

void CHuman::AutoWand(D3DXVECTOR3 pos)
{
	m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

	D3DXVECTOR3 Turn[MAX_RANDPOINT];

	float fAnglemove = 0.0f;

	static float fX = 0.0f;
	static float fZ = 0.0f;
	static float fMove = 0.0f;

	//�p�j�|�C���g�p�ϐ�
	int nMax = 2000.0f;
	int nMin = -2000.0f;

	//�l�Ԃ̃X�s�[�h�p�ϐ�
	int nMaxS = 20.0f;
	int nMinS = 5.0f;

	if (m_bCnt == false)
	{
		fX = (float)(rand() % (nMax - nMin + 1) + nMin);
		fZ = (float)(rand() % (nMax - nMin + 1) + nMin);
		fMove = (float)(rand() % (nMaxS - nMinS + 1) + nMinS);

		m_bCnt = true;
	}

	Turn[0] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[1] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[2] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[3] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[4] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[5] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[6] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[7] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[8] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[9] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[10] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[11] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[12] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[13] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[14] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[15] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[16] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[17] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[18] = D3DXVECTOR3(fX, 0.0f, fZ);

	// �����p�̕ϐ�
	float fDistance = (pos.x - Turn[m_nCnt].x) * (pos.x - Turn[m_nCnt].x) + (pos.y - Turn[m_nCnt].y) * (pos.y - Turn[m_nCnt].y) + (pos.z - Turn[m_nCnt].z) * (pos.z - Turn[m_nCnt].z);
	
	// �͈͗p�ϐ�
	D3DXVECTOR3 fRadP(100.0f, 0.0f, 100.0f);
	D3DXVECTOR3 fRadE(100.0f, 0.0f, 100.0f);

	// ���a�̎�
	float fRadius = (fRadP.x + fRadE.x) * (fRadP.x + fRadE.x) + (fRadP.y + fRadE.y) * (fRadP.y + fRadE.y) + (fRadP.z + fRadE.z) * (fRadP.z + fRadE.z);


	if (fDistance <= fRadius)
	{//�^�[���n�_�܂ŗ�����

		//���̃^�[���n�_��ݒ�
		m_nCnt += 1;
		m_nCnt = m_nCnt % MAX_RANDPOINT;
		m_bCnt = false;

	}

	// �ړI�̊p�x
	m_rotDest.y = atan2f((Turn[m_nCnt].x - pos.x), (Turn[m_nCnt].z - pos.z)) + D3DX_PI;
	fAnglemove = atan2f((Turn[m_nCnt].x - pos.x), (Turn[m_nCnt].z - pos.z));

	m_move.x = sinf(fAnglemove) * fMove;
	m_move.z = cosf(fAnglemove) * fMove;

}