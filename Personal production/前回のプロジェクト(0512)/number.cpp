//=================================================
//
//	number.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "number.h"
#include "manager.h"

// �R���X�g���N�^
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdx = 0;
}

// �f�X�g���N�^
CNumber::~CNumber()
{

}

// ����
CNumber* CNumber::Create(D3DXVECTOR3 pos)
{
	return NULL;
}

// ������
HRESULT CNumber::Init(float fX1, float fX2, int nCnt, float fNum1, float fNum2, int nNum, int nAdd, const char* FileName, float fx)
{
	CTextureManager* pTex = CManager::GetTexManager();
	m_nIdx = pTex->Register(FileName);

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * nNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	VERTEX_2D* pVtx;

	// ���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(fX1 + nCnt * fNum1, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fX2 + nCnt * fNum1 + fNum2, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(fX1 + nCnt * fNum1, 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fX2 + nCnt * fNum1 + fNum2, 50.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fx, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fx, 1.0f);

	pVtx += nAdd;

	// �A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

// �I��
void CNumber::Uninit(void)
{
	// �o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

// �X�V
void CNumber::Update(void)
{

}

// �`��
void CNumber::Draw(void)
{
	CTextureManager* pTex = CManager::GetTexManager();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_2D);
		
	//�e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, pTex->GetAddress(m_nIdx));
	//�|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0, 2); //���_���\���̂̃T�C�Y

}

//�����ɂ���ăe�N�X�`�����W�ɂ��ݒ�
void CNumber::SetNumber(int nNumber, int nAdd)
{
	VERTEX_2D* pVtx = nullptr;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�����Ōv�Z����
	float fTex = 0.1f * nNumber;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + fTex, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + fTex, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + fTex, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + fTex, 1.0f);

	pVtx += nAdd;

	m_pVtxBuff->Unlock();
}