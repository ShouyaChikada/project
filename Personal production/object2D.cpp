//=================================================
//
//	object2D.cpp
// 
//	Author:�ߓc����
//
//=================================================
#include "object2D.h"
#include "renderer.h"
#include "manager.h"

//============================
//�R���X�g���N�^
//============================
CObject2D::CObject2D(int nPriolity): CObject(nPriolity)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_aUV = 0.0f;
	m_zUV = 0.0f;
	m_Width = 0.0f;
	m_Height = 0.0f;
	m_nType = 0;
}

//============================
//�f�X�g���N�^
//============================
CObject2D::~CObject2D()
{

}

//============================
// �I�u�W�F�N�g2D����
//============================
CObject2D* CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col)
{
	CObject2D* pObject2D = nullptr;
	pObject2D = new CObject2D;

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		return pObject2D;
	}
	else
	{
		return NULL;
	}
	
}
//============================
//����������
//============================
HRESULT CObject2D::Init(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	VERTEX_2D* pVtx = nullptr;

	// ���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}

//============================
//�I������
//============================
void CObject2D::Uninit(void)
{
	//�o�b�t�@�̔j��==========================
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//========================================

	//�������g�̔j��
	CObject::Release();
}

//============================
//�X�V����
//============================
void CObject2D::Update(void)
{
	switch (m_nType)
	{
	case ANCHORTYPE_CENTER:
		UpdateCenter();
		break;
	case ANCHORTYPE_LEFT:
		UpdateLeft();
		break;
	default:
		UpdateCenter();
		break;
	}
}

//============================
//�`�揈��
//============================
void CObject2D::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0, 2); //���_���\���̂̃T�C�Y

	//�e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, NULL);
}

//�ʒu�̐ݒ�
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�e�N�X�`���̃T�C�Y
void CObject2D::SetTex(float aUV, float zUV)
{
	m_aUV = aUV;
	m_zUV = zUV;
}

//�A�j���[�V�����̐ݒ�
void CObject2D::SetAnim(D3DXVECTOR2 UV, float fSizeX, float fSizeY)
{
	VERTEX_2D* pVtx;

	//���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(UV.x * fSizeX, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((UV.x * fSizeX) + fSizeX, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(UV.x * fSizeX, fSizeY);
	pVtx[3].tex = D3DXVECTOR2((UV.x * fSizeX) + fSizeX, fSizeY);

	//�A�����b�N
	m_pVtxBuff->Unlock();
}

//	�A�j���[�V����
void CObject2D::SetAnim(float aTex, float fAdd)
{
	VERTEX_2D* pVtx;

	//���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(aTex, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(aTex +fAdd, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(aTex, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(aTex + fAdd, 1.0f);

	//�A�����b�N
	m_pVtxBuff->Unlock();

}

void CObject2D::SetSize(float fWidth, float fHeight)
{
	m_Width = fWidth;
	m_Height = fHeight;
}

//�ʒu���擾
D3DXVECTOR3 CObject2D::GetPosition(void)
{
	return m_pos;
}

void CObject2D::UpdateLeft(void)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;
	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Width, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_Height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Width, m_pos.y + m_Height, 0.0f);

	// rhw�̐ݒ�( 1.0f�ŌŒ� )
	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = D3DXCOLOR(m_col);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	m_pVtxBuff->Unlock();

}

void CObject2D::UpdateCenter(void)
{
	VERTEX_2D* pVtx = nullptr;

	//���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//========================================
	//���_���W�̐ݒ�

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Width, m_pos.y - m_Height, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Width, m_pos.y - m_Height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Width, m_pos.y + m_Height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Width, m_pos.y + m_Height, 0.0f);
	//========================================

	//�A�����b�N
	m_pVtxBuff->Unlock();

}


//�G�t�F�N�g
void CObject2D::SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius)
{
	VERTEX_2D* pVtx;

	//���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x - fRadius, pos.y - fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fRadius, pos.y - fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fRadius, pos.y + fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fRadius, pos.y + fRadius, 0.0f);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//�A�����b�N
	m_pVtxBuff->Unlock();
}


void CObject2D::Set2Dpolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col)
{
	VERTEX_2D* pVtx;

	//���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//========================================
	//���_���W�̐ݒ�
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = fWidth;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = fWidth;
	pVtx[3].pos.y = fHeight;
	pVtx[3].pos.z = 0.0f;
	//========================================


	//========================================
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//========================================

	//========================================
	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	//========================================

	//========================================
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//========================================

	//�A�����b�N
	m_pVtxBuff->Unlock();


}

void CObject2D::Setcol(D3DXCOLOR col)
{
	VERTEX_2D* pVtx;

	//���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//�A�����b�N
	m_pVtxBuff->Unlock();


}