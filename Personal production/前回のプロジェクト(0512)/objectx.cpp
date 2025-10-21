//=================================================
//
//	ObjectX.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "objectx.h"
#include "manager.h"
#include "motion.h"
#include "texturemanager.h"

//�ÓI�����o�ϐ�
const char* CObjectX::m_txt = {};

// �R���X�g���N�^
CObjectX::CObjectX(int nPriolty):CObject(nPriolty)
{
	m_pTexture = { nullptr };

	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_nIdx[nCnt] = NULL;
	}
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = NULL;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_txt = nullptr;
	m_pModel = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

// �f�X�g���N�^
CObjectX::~CObjectX()
{

}

// ����
CObjectX* CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt)
{
	CObjectX* pObjectX = nullptr;
	pObjectX = new CObjectX;

	if (pObjectX != nullptr)
	{
		pObjectX->m_pos = pos;
		pObjectX->m_rot = D3DXToRadian(rot);
		pObjectX->m_txt = txt;
		pObjectX->Init();
		return pObjectX;
	}
	else
	{
		return nullptr;
	}
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

	D3DXMATERIAL *pMat = nullptr;	//�}�e���A���ւ̃|�C���^

	m_pTexture = new int[m_dwNumMat];

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{//�e�N�X�`���t�@�C�������݂���
			// �e�N�X�`���|�C���^�擾
			CTextureManager* pTexture = CManager::GetTexManager();

			m_pTexture[nCntMat] = pTexture->Register(pMat[nCntMat].pTextureFilename);
		}
		else
		{
			m_pTexture[nCntMat] = -1;
		}
	}

	return S_OK;
}
//================================
// �I������
//================================
void CObjectX::Uninit(void)
{

	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		delete[] m_pTexture;

		m_pTexture = nullptr;
	}

	//���b�V���̔j��
	if (m_pMesh != nullptr)
	{	   
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
	//�}�e���A���̔j��
	if (m_pBuffMat != nullptr)
	{	   
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	//�����̔j��
	CObject::Release();
}
//================================
// �X�V����
//================================
void CObjectX::Update(void)
{
	
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

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;	//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.x, m_rot.y, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
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

		if (m_pTexture[nCntMat] != -1)
		{
			pTexMT = CManager::GetRenderer()->GetTextureMT();

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTex->GetAddress(m_pTexture[nCntMat]));
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
		}

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