//=============================================
//
// author chikada shouya
//
//=============================================

#include "billboard.h"
#include "player.h"
#include "input.h"
#include "manager.h"

// �R���X�g���N�^
CBillboard::CBillboard(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�ʒu
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);		//����
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�ړ���
	m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����i�[
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bTest = false;
	m_bUse = false;
	m_fRadius = 0.0f;
}

// �f�X�g���N�^
CBillboard::~CBillboard()
{

}

//============================
// �I�u�W�F�N�g3D����
//============================
CBillboard* CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBillboard* pBillboard = nullptr;
	pBillboard = new CBillboard;

	if (pBillboard != nullptr)
	{
		pBillboard->m_pos = pos;
		pBillboard->m_move = move;
		pBillboard->Init();
		return pBillboard;
	}
	else
	{
		return nullptr;
	}
}

//=======================================
// ����������
//=======================================
HRESULT CBillboard::Init(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	VERTEX_3D* pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(- m_fRadius,+ m_fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ m_fRadius,+ m_fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- m_fRadius,- m_fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ m_fRadius,- m_fRadius, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=======================================
// �I������
//=======================================
void CBillboard::Uninit(void)
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
//=======================================
// �X�V����
//=======================================
void CBillboard::Update(void)
{

}
//=======================================
// �`�揈��
//=======================================
void CBillboard::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// Z
	pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	// Z�̔�r
	pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		// Z�o�b�t�@�ɏ������܂Ȃ�

	//���C�g�𖳌��ɂ���
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	D3DXMATRIX mtxView;
	pD3DDevice->GetTransform(D3DTS_VIEW, &mtxView);	//�r���[�}�g���b�N�X�̎擾

	//�J�����̋t�s���ݒ�
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0, 2); //���_���\���̂̃T�C�Y


	pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//���C�g��L���ɖ߂�
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	// Z�̔�r���@�ύX
	pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		// Z�o�b�t�@�ɏ�������


}

// �ʒu���擾
D3DXVECTOR3 CBillboard::GetPosition(void)
{
	return m_SetPosition;
}

// �ʒu�̐ݒ�
void CBillboard::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
