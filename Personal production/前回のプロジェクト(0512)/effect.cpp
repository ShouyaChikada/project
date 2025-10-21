//=================================================
//
//	effect.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include"effect.h"
#include "texturemanager.h"
#include "manager.h"

// �R���X�g���N�^
CEffect::CEffect()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�ړ���
	m_nLife = 0;			//����
	m_nIdx = 0;
	m_mtxWorld = {};

}

// �f�X�g���N�^
CEffect::~CEffect()
{
}

// �G�t�F�N�g�̐���
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife)
{
	CEffect* pEffect = nullptr;
	pEffect = new CEffect;

	if (pEffect != nullptr)
	{
		pEffect->m_pos = pos;
		pEffect->m_move = move;
		pEffect->m_nLife = nLife;
		pEffect->SetRadius(15.0f);
		pEffect->SetColor(col);
		pEffect->Init();
		return pEffect;
		
	}
	else
	{
		return nullptr;
	}
}
// ������
HRESULT CEffect::Init(void)
{

	CTextureManager* pTex = CManager::GetTexManager();
	m_nIdx = pTex->Register("data\\TEXTURE\\effect000.jpg");

	CBillboard::Init();
	return S_OK;
}

//=============================================================================
//�G�t�F�N�g�̏I������
//=============================================================================
void CEffect::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
//�G�t�F�N�g�̍X�V����
//=============================================================================
void CEffect::Update(void)
{
	m_pos += m_move;

	m_nLife--;

	if (m_nLife <= 0)
	{
		Uninit();
	}

	SetPosition(m_pos);
}

//=============================================================================
//�G�t�F�N�g�̕`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	// FOG������
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);



	// �e�N�X�`���̐ݒ�
	CTextureManager* pTex = CManager::GetTexManager();
	pDevice->SetTexture(0, pTex->GetAddress(m_nIdx));
	// �`��
	CBillboard::Draw();

	// �ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// FOG�̐ݒ�
	CManager::GetRenderer()->SetupVertexFog(D3DCOLOR_XRGB(255, 255, 255), D3DFOG_LINEAR, TRUE, 0.005f);
}