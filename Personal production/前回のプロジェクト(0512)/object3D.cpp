//=================================================
//
//	object3D.cpp
// 
//	Author:�ߓc����
//
//=================================================
#include "object3D.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"

//============================
//�R���X�g���N�^
//============================
CObject3D::CObject3D()
{
	m_pVtxBuff = NULL;
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//============================
//�f�X�g���N�^
//============================
CObject3D::~CObject3D()
{

}

//============================
// �I�u�W�F�N�g3D����
//============================
CObject3D* CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 ros)
{
	//int nNumAll = Getobject();

	//if (nNumAll < MAX_OBJECT - 1)
	//{
		CObject3D* pObject3D = NULL;
		pObject3D = new CObject3D;
		pObject3D->Init();
		return pObject3D;
	//}
	//return NULL;
}
//============================
//����������
//============================
HRESULT CObject3D::Init(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();
	
	//���_�o�b�t�@�̐���
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);
	
	VERTEX_3D* pVtx = NULL;
	
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-450.0f, 0.0f, 450.0f);
	pVtx[1].pos = D3DXVECTOR3(450.0f, 0.0f, 450.0f);
	pVtx[2].pos = D3DXVECTOR3(-450.0f, 0.0f, -450.0f);
	pVtx[3].pos = D3DXVECTOR3(450.0f, 0.0f, -450.0f);
	
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	//�A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================
//�I������
//============================
void CObject3D::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{			  
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	
	//�����̔j��
	CObject::Release();
}

//============================
//�X�V����
//============================
void CObject3D::Update(void)
{
	
}

//============================
//�`�揈��
//============================
void CObject3D::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

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
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	
	//�e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, NULL);

	//���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,
		2); //���_���\���̂̃T�C�Y
}

//�ʒu�̐ݒ�
void CObject3D::SetPosition(D3DXVECTOR3 pos)
{
	m_SetPosition = pos;
}

//�ʒu���擾
D3DXVECTOR3 CObject3D::GetPosition(void)
{
	return m_SetPosition;
}
