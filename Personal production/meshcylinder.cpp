//=================================================
//
//	meshcylinder.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "meshcylinder.h"
#include "manager.h"
#include "texturemanager.h"
//#include "gimmickmanager.h"

// �R���X�g���N�^
CMeshCylinder::CMeshCylinder(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;						//���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = NULL;						//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_fRadius = 0.0f;
	m_nIdx = NULL;
}

// �f�X�g���N�^
CMeshCylinder::~CMeshCylinder()
{

}

// ����
CMeshCylinder* CMeshCylinder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	CMeshCylinder* pMeshCylinder = nullptr;
	pMeshCylinder = new CMeshCylinder;

	if (pMeshCylinder != nullptr)
	{
		pMeshCylinder->m_pos = pos;
		pMeshCylinder->m_rot = rot;
		pMeshCylinder->m_fRadius = fRadius;
		pMeshCylinder->Init();
		return pMeshCylinder;
	}
	else
	{
		return nullptr;
	}
}

//=======================================
// ����������
//=======================================
HRESULT CMeshCylinder::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CTextureManager* pTex = CManager::GetTexManager();

	//m_nIdx = pTex->Register("data\\TEXTURE\\red1.png");

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_MAX_VTX,
		D3DUSAGE_WRITEONLY,
		D3DFVF_VERTEX,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_MAX_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	int index = 0;
	float fAngle;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�
	for (int nCntV = 0; nCntV < MESHFIELD_V_BLOCK + 1; nCntV++)
	{//Z�����̌J��Ԃ�

		for (int nCntH = 0; nCntH < MESHFIELD_H_BLOCK + 1; nCntH++)
		{//X�����̌J��Ԃ�
			fAngle = (D3DX_PI * 2) / MESHFIELD_H_BLOCK /*(D3DX_PI * 2) / (MESHFIELD_H_BLOCK - nCntH)*/;

			//���_���W�̐ݒ�
			pVtx[index].pos = D3DXVECTOR3(sinf((fAngle)*nCntH) * m_fRadius, 20.0f * (nCntV * 2), cosf((fAngle)*nCntH) * m_fRadius);

			//�@���̐ݒ�
			D3DXVec3Normalize(&pVtx[index].nor, &pVtx[index].pos);

			//�J���[�ݒ�
			pVtx[index].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`���ݒ�
			pVtx[index].tex = D3DXVECTOR2((1.0f / MESHFIELD_H_BLOCK) * nCntV, (1.0f / MESHFIELD_V_BLOCK) * nCntH);

			index++;

		}


	}
	//�A�����b�N
	m_pVtxBuff->Unlock();

	//���_���̐ݒ�
	WORD* pIdx;
	int nCnt1 = 0;
	int nCnt2 = 0;
	int nCnt3 = 25;

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntV = 0; nCntV < MESHFIELD_V_BLOCK; nCntV++)
	{//Z�����̌J��Ԃ�
		for (int nCntH = 0; nCntH < MESHFIELD_H_BLOCK + 1; nCntH++)
		{//X�����̌J��Ԃ�

		//�C���f�b�N�X�̐ݒ�
			pIdx[nCnt1] = nCnt2;
			pIdx[nCnt1 + 1] = nCnt3;

			nCnt1 += 2;
			nCnt2++;
			nCnt3++;

		}
	}
	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();


	return S_OK;
}
//=======================================
//�I������
//=======================================
void CMeshCylinder::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	CObject::Release();
}
//=======================================
//�X�V����
//=======================================
void CMeshCylinder::Update(void)
{
	//bool bUse = CGimmickManager::GetPush();

	//VERTEX_3D* pVtx = NULL;
	//int index = 0;

	////���_�o�b�t�@�����b�N
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//if (bUse == true)
	//{
	//	//���_�̐ݒ�
	//	for (int nCntV = 0; nCntV < MESHFIELD_V_BLOCK + 1; nCntV++)
	//	{//Z�����̌J��Ԃ�

	//		for (int nCntH = 0; nCntH < MESHFIELD_H_BLOCK + 1; nCntH++)
	//		{//X�����̌J��Ԃ�
	//			//�J���[�ݒ�
	//			pVtx[index].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.75f);

	//			index++;
	//		}
	//	}
	//}

	//if (bUse == false)
	//{
	//	//���_�̐ݒ�
	//	for (int nCntV = 0; nCntV < MESHFIELD_V_BLOCK + 1; nCntV++)
	//	{//Z�����̌J��Ԃ�

	//		for (int nCntH = 0; nCntH < MESHFIELD_H_BLOCK + 1; nCntH++)
	//		{//X�����̌J��Ԃ�
	//			//�J���[�ݒ�
	//			pVtx[index].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.75f);

	//			index++;
	//		}
	//	}
	//}

	////�C���f�b�N�X�o�b�t�@�̃A�����b�N
	//m_pIdxBuff->Unlock();

}
//=======================================
//�`�揈��
//=======================================
void CMeshCylinder::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CTextureManager* pTex = CManager::GetTexManager();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, pTex->GetAddress(m_nIdx));

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0, 0, MESHFIELD_MAX_VTX, 0, MESHFIELD_MAX_POLYGON); //���_���\���̂̃T�C�Y
}

void CMeshCylinder::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
D3DXVECTOR3 CMeshCylinder::GetPosition(void)
{
	return m_pos;
}