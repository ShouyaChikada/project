//=================================================
//
//	meshfield.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "meshfield.h"
#include "manager.h"
#include "texturemanager.h"

// �R���X�g���N�^
CMeshField::CMeshField(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;						//���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = NULL;						//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);	//����
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);	//�ʒu
	m_fRadius = 0.0f;
	m_nIdx = NULL;
}

// �f�X�g���N�^
CMeshField::~CMeshField()
{

}

// ����
CMeshField* CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	CMeshField* pMeshField = nullptr;
	pMeshField = new CMeshField;

	if (pMeshField != nullptr)
	{
		pMeshField->m_pos = pos;
		pMeshField->m_rot = rot;
		pMeshField->m_fRadius = fRadius;
		pMeshField->Init();
		return pMeshField;
	}
	else
	{
		return nullptr;
	}
}

//=======================================
// ����������
//=======================================
HRESULT CMeshField::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CTextureManager* pTex = CManager::GetTexManager();
	m_nIdx = pTex->Register("data\\TEXTURE\\sky000.jpg");

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_MAX_VTX,
		D3DUSAGE_WRITEONLY,
		D3DFVF_VERTEX,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);


	return S_OK;
}
//=======================================
//�I������
//=======================================
void CMeshField::Uninit(void)
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
void CMeshField::Update(void)
{


}
//=======================================
//�`�揈��
//=======================================
void CMeshField::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();


	// FOG�̐ݒ�
	CManager::GetRenderer()->SetupVertexFog(D3DCOLOR_XRGB(55, 55, 255), D3DFOG_LINEAR, TRUE, 0.005f);

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	vector<Vertex> vertices;
	vector<Vertex> fan;

	GenerateSphereVertices(4000.0f, 6, 6, vertices);  // ���a1.0�A20����

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �X�t�B�A�̕`��
	RenderSphere(pDevice,vertices, 6, 6);
	
	pDevice->Present(NULL, NULL, NULL, NULL);

	// FOG������
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);


}

void CMeshField::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
D3DXVECTOR3 CMeshField::GetPosition(void)
{
	return m_pos;
}

// �X�t�B�A�p�ܓx�ƌo�x�Ɋ�Â��Ē��_���v�Z
void CMeshField::GenerateSphereVertices(float radius, int slices, int stacks, vector<Vertex>& vertices)
{
	for (int i = 0; i <= stacks; ++i) 
	{
		float phi = D3DX_PI * i / stacks;  // �ܓx
		for (int j = 0; j <= slices; ++j) 
		{
			float theta = 2.0f * D3DX_PI * j / slices;  // �o�x

			Vertex v;
			v.x = radius * sinf(phi) * cosf(theta);
			v.y = radius * cosf(phi);
			v.z = radius * sinf(phi) * sinf(theta);
			v.color = 0xFFFFFFFF;  // ���F
			vertices.push_back(v);
		}
	}
}

// �X�t�B�A�̕`��
void CMeshField::RenderSphere(LPDIRECT3DDEVICE9 pDevice, const vector<Vertex>& vertices, int slices, int stacks)
{
	CTextureManager* pTex = CManager::GetTexManager();

	//vector<Vertex> fan;
	int index = 0;
	VERTEX_3D* pVtx = nullptr;

	for (int i = 0; i < stacks; ++i)
	{
		for (int j = 0; j < slices; ++j)
		{

			vector<Vertex> fan;

			// �O�p�`�t�@���̒��S
			fan.push_back(vertices[i * (slices + 1) + j]);

			// ���͂̒��_
			fan.push_back(vertices[(i + 1) * (slices + 1) + j]);
			fan.push_back(vertices[(i + 1) * (slices + 1) + (j + 1)]);
			fan.push_back(vertices[i * (slices + 1) + (j + 1)]);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

			// �`�惋�[�v
			pDevice->SetFVF(D3DFVF_VERTEX);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTex->GetAddress(m_nIdx));

			// �`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, fan.size() - 2, fan.data(), sizeof(Vertex));

		}
	}
	//�A�����b�N
	m_pVtxBuff->Unlock();
}