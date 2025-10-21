//=================================================
//
//	model.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "model.h"
#include "manager.h"
#include "object.h"
#include "texturemanager.h"

D3DXVECTOR3 CModel::m_Size = {};
// �R���X�g���N�^
CModel::CModel()
{
	m_pTexture = { nullptr };

	m_pParent = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

// �f�X�g���N�^
CModel::~CModel()
{

}

// ����
CModel* CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt)
{
	//int nNumAll = CObject::Getobject();

	//if (nNumAll < MAX_OBJECT - 1)
	//{
	CModel* pModel = nullptr;
	pModel = new CModel;
	if (pModel != nullptr)
	{
		pModel->Init(pos, rot, txt);
		return pModel;
	}
	else
	{
		return nullptr;
	}
		//}
	//return NULL;
}

//================================
// ����������
//================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt)
{
	
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	CObject* pObject = CManager::getobject();

	//X�t�@�C���̓ǂݍ���(�S�p�[�c)2
	D3DXLoadMeshFromX(txt,
		D3DXMESH_SYSTEMMEM,
		pD3DDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	m_pos = pos;
	m_rot = rot;

	// ���[�J���ϐ��錾-----------------------------
	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	//----------------------------------------------

	// ���_���̎擾
	nNumVtx = m_pMesh->GetNumVertices();

	// ���_�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// ���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	m_Size = pObject->SetSize(m_VtxMax, m_VtxMin, nNumVtx, sizeFVF, pVtxBuff);

	// �A�����b�N
	m_pMesh->UnlockVertexBuffer();

	D3DXMATERIAL* pMat;	//�}�e���A���ւ̃|�C���^

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
void CModel::Uninit(void)
{
	// ����nullptr��������
	if (this == nullptr) return;

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
}
//================================
// �X�V����
//================================
void CModel::Update(void)
{
	//�O��̈ʒu��ۑ�	�ʒu�X�V�̏�ŏ���
	m_posOld = m_pos;

}
//================================
// �`�揈��
//================================
void CModel::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;			//�e�̃}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���݂̃}�e���A�����擾
	pD3DDevice->GetMaterial(&matDef);

	//�p�[�c�́u�e�̃}�g���b�N�X�v��ݒ�
	if (m_pParent != NULL)
	{//�e�̃��f��������ꍇ
		mtxParent = m_pParent->GetMtxWorld();//�e���f���̃C���f�b�N�X���w��
	}
	else
	{//�e���f�����Ȃ��ꍇ
		//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pD3DDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//�Z�o�����u�p�[�c�̃}�g���b�N�X�v�Ɓu�e�̃}�g���b�N�X�v���������킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld ,&mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pD3DDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���C���f�b�N�X������Ƃ�
		if (m_pTexture[nCntMat] != -1)
		{
			// �e�N�X�`���|�C���^�擾
			CTextureManager* pTexture = CManager::GetTexManager();
				
			//�e�N�X�`�����蓖��
			pD3DDevice->SetTexture(0, pTexture->GetAddress(m_pTexture[nCntMat]));
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pD3DDevice->SetTexture(0, NULL);
		}

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A�����B��
	pD3DDevice->SetMaterial(&matDef);

}

// ���[���h�}�g���b�N�X�̎擾
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}

// �p�[�c�̃y�A�����g�ݒ�
void CModel::SetParent(CModel* pModel)
{
	m_pParent = pModel;
}
// �ʒu�̐ݒ�
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
	
}

// �����̐ݒ�
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

// �O�̈ʒu�̐ݒ�
void CModel::SetPosOld(D3DXVECTOR3 PosOld)
{
	m_posOld = PosOld;
}

// �T�C�Y�̐ݒ�
void CModel::SetSize(D3DXVECTOR3 Size)
{
	m_Size = Size;
}

// �ړ��ʂ̐ݒ�
void CModel::SetMove(D3DXVECTOR3 Move)
{
	m_move = Move;
}

D3DXVECTOR3 CModel::GetSize(void)
{
	return m_Size;
}