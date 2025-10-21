//=================================================
//
//	ObjectX.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "objectx.h"
#include "manager.h"
#include "texturemanager.h"

//�ÓI�����o�ϐ�
const char* CObjectX::m_txt = {};

// �R���X�g���N�^
CObjectX::CObjectX(int nPriolty):CObject(nPriolty)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_pTexture[nCnt] = NULL;
		m_nIdx[nCnt] = NULL;
	}
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;	
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_txt = NULL;
	m_pModel = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&m_mtxRot);

	m_fValueRot = 0.0f;
	m_VecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

// �f�X�g���N�^
CObjectX::~CObjectX()
{

}

// ����
CObjectX* CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt)
{
	//int nNumAll = Getobject();

	//if (nNumAll < MAX_OBJECT - 1)
	//{
		CObjectX* pObjectX = NULL;
		pObjectX = new CObjectX;
		pObjectX->m_pos = pos;
		pObjectX->m_rot = D3DXToRadian(rot);
		pObjectX->m_txt = txt;
		pObjectX->Init();
		return pObjectX;
	//}
	//return NULL;
}

//================================
// ����������
//================================
HRESULT CObjectX::Init(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���}�l�[�W���[�̎擾
	CTextureManager* pTex = CManager::GetTexManager();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(m_txt,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	m_fValueRot = 0.01f;

	D3DXMATERIAL *pMat = nullptr;	//�}�e���A���ւ̃|�C���^

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{//�e�N�X�`���t�@�C�������݂���
				//�e�N�X�`���̓ǂݍ���
			//	D3DXCreateTextureFromFile(pDevice,
			//		pMat[nCntMat].pTextureFilename,
			//		&m_pTexture[nCntMat]);
			m_nIdx[nCntMat] = pTex->Register(pMat[nCntMat].pTextureFilename);
		}
	}

	return S_OK;
}
//================================
// �I������
//================================
void CObjectX::Uninit(void)
{
	//���b�V���̔j��
	if (m_pMesh != NULL)
	{	   
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{	   
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	
	//// �e�N�X�`���̔j��
	//for (int nCnt = 0; nCnt < (int)m_dwNumMat; nCnt++)
	//{
	//	if (m_pTexture[nCnt] != NULL)
	//	{
	//		m_pTexture[nCnt]->Release();
	//		m_pTexture[nCnt] = NULL;
	//	}
	//}
	
	//�����̔j��
	CObject::Release();
}
//================================
// �X�V����
//================================
void CObjectX::Update(void)
{
	//�ړ��ƃ��[�V�����̃Z�b�g
	SetInput();

	//float fCirc = 2.0f * D3DX_PI * 5.0f;

	//m_move.y = (fValueRot / (2 * D3DX_PI)) * fCirc;
	//m_move.z = (fValueRot / (2 * D3DX_PI)) * fCirc;

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


	m_pos += m_move;

	////�d��
	//if (m_pos.y < -600.0f)
	//{
	//	m_pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	//	m_move.y = 0.0f;
	//	m_bJump = false;
	//}
}
//================================
// �`�揈��
//================================
void CObjectX::Draw(void)
{
	CTextureManager* pTex = CManager::GetTexManager();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�}���`�^�[�Q�b�g
	LPDIRECT3DTEXTURE9 pTexMT;

	D3DXMATRIX mtxRot, mtxTrans;						// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;								// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;									// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXQUATERNION quat;								// �N�H�[�^�j�I��
	D3DXVECTOR3 vecAxis = D3DXVECTOR3(0.0f,1.0f,0.0f);	// ��]��
	float fValueRot = 0.0f;								// ��]�p(��]��)
	fValueRot = D3DX_PI * 0.001f;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]���̂�����w��̉�]�p����N�H�[�^�j�I�����쐬
	D3DXQuaternionRotationAxis(&quat, &vecAxis, fValueRot);

	// �N�H�[�^�j�I�������]�}�g���b�N�X�̍쐬
	D3DXMatrixRotationQuaternion(&mtxRot, &quat);

	// ���݂̉�]�ʂɎ��̉�]�ʂ�������
	D3DXMatrixMultiply(&m_mtxRot, &m_mtxRot, &mtxRot);
	
	// ���̉�]�ʂ����[���h�}�g���b�N�X�̉�����
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	// �ʒu�̃}�g���b�N�X�̍쐬
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	// ���[���h�}�g���b�N�X�Ɉʒu�̃}�g���b�N�X��������
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		pTexMT = CManager::GetRenderer()->GetTextureMT();

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pTex->GetAddress(m_nIdx[nCntMat]));

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A�����B��
	pDevice->SetMaterial(&matDef);
}

LPD3DXMESH CObjectX::GetMesh(void)
{
	return m_pMesh;
}

//============================
// �ړ�����
//============================
void CObjectX::SetInput(void)
{
	//D3DXVec3Cross();
	// �L�[�{�[�h
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	//�J�����̏��擾
	CCamera* pCamera = CManager::GetCamera();
	D3DXVECTOR3 rot = pCamera->GetRotasion();

	pCamera->SetFollowing(m_pos, m_rotDest);

	//���ړ�
	if (pInputKeyboard->GetPress(DIK_A) == true)
	{

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
}