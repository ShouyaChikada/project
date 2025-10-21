//=================================================
//
//	jimen.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "manager.h"
#include "jimen.h"
#include "texturemanager.h"

// �R���X�g���N�^
CGrand::CGrand(int nPriolity) : CObject(nPriolity)
{
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_aPosTexU = 0.0f;
	m_mtxWorld = {};
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_nIdx = NULL;
}

// �f�X�g���N�^
CGrand::~CGrand()
{

}

// ����
CGrand* CGrand::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CGrand* pGrand = nullptr;
	pGrand = new CGrand;

	if (pGrand != nullptr)
	{
		pGrand->m_pos = pos;
		pGrand->m_rot = rot;
		pGrand->Init();
		return pGrand;
	}
	else
	{
		return nullptr;
	}
}

//=======================================
// ����������
//=======================================
HRESULT CGrand::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CTextureManager* pTex = CManager::GetTexManager();
	m_nIdx = pTex->Register("data\\TEXTURE\\sea02s.jpg");

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * GRAND_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * GRAND_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = nullptr;

	int radius = 500;	//���a
	int index = 0;
	float fAngle = 0.0f;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	float fxz = 100.0f;

	//���_�̐ݒ�
	for (int nCntZ = 0; nCntZ < GRAND_Z_BLOCK; nCntZ++)
	{//Z�����̌J��Ԃ�

		for (int nCntX = 0; nCntX < GRAND_X_BLOCK; nCntX++)
		{//X�����̌J��Ԃ�

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-fxz, -50.0f, fxz);
			pVtx[1].pos = D3DXVECTOR3(0.0f, -50.0f, fxz);
			pVtx[2].pos = D3DXVECTOR3(fxz, -50.0f, fxz);
			pVtx[3].pos = D3DXVECTOR3(-fxz, -50.0f, 0.0f);
			pVtx[4].pos = D3DXVECTOR3(0.0f, -50.0f, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(fxz, -50.0f, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(-fxz, -50.0f, -fxz);
			pVtx[7].pos = D3DXVECTOR3(0.0f, -50.0f, -fxz);
			pVtx[8].pos = D3DXVECTOR3(fxz, -50.0f, -fxz);

			//�@���̐ݒ�
			pVtx[nCntX].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//�J���[�ݒ�
			pVtx[nCntX].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`���ݒ�
			//pVtx[nCntZ].tex = D3DXVECTOR2(nCntX * (0.25f / nCntX), nCntZ * (0.25f / nCntZ));
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
			pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
			pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
			pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}
	//�A�����b�N
	m_pVtxBuff->Unlock();

	//���_���̐ݒ�
	WORD* pIdx;
	int nCnt1 = 0;
	int nCnt2 = 3;
	int nCnt3 = 0;
	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);


	//�C���f�b�N�X�̐ݒ�

	pIdx[0] = 3;
	pIdx[1] = 0;

	pIdx[2] = 4;
	pIdx[3] = 1;

	pIdx[4] = 5;
	pIdx[5] = 2;

	pIdx[6] = 2;
	pIdx[7] = 6;

	pIdx[8] = 6;
	pIdx[9] = 3;

	pIdx[10] = 7;
	pIdx[11] = 4;

	pIdx[12] = 8;
	pIdx[13] = 5;


	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}
//=======================================
//�I������
//=======================================
void CGrand::Uninit(void)
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
void CGrand::Update(void)
{

	VERTEX_3D* pVtx = nullptr;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_aPosTexU += 0.0001f;

	pVtx[0].tex = D3DXVECTOR2(m_aPosTexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_aPosTexU + 0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(m_aPosTexU, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(m_aPosTexU + 0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(m_aPosTexU, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(m_aPosTexU + 0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 1.0f);
	
	m_pVtxBuff->Unlock();
}
//=======================================
//�`�揈��
//=======================================
void CGrand::Draw(void)
{

	CTextureManager* pTex = CManager::GetTexManager();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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
	pDevice->SetTexture(0, pTex->GetAddress(m_nIdx));

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0, 0, GRAND_VERTEX_NUM, 0, GRAND_PRIMITVE_NUM)); //���_���\���̂̃T�C�Y
}

void CGrand::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
D3DXVECTOR3 CGrand::GetPosition(void)
{
	return m_pos;
}
