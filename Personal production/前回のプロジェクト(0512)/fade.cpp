//=================================================
//
//	fade.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "fade.h"
#include "manager.h"
// �R���X�g���N�^
CFade::CFade()
{
	m_pVtxBuff = nullptr;						// ���_�o�b�t�@
	m_Fade = FADE_NONE;							// �t�F�C�h
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);		// �J���[
}

// �f�X�g���N�^
CFade::~CFade()
{

}

// �t�F�[�h�̐���
CFade* CFade::Create(void)
{
	CFade* pFade = nullptr;
	pFade = new CFade;

	if (pFade != nullptr)
	{
		pFade->Init();
		return pFade;
	}
	else
	{
		return nullptr;
	}
}

// ����������
HRESULT CFade::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//�����|���S��(�s����)�ɂ��Ă���

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[2].col = m_col;
	pVtx[1].col = m_col;
	pVtx[3].col = m_col;

	//�A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//�t�F�[�h�̔j������
void CFade::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

//�t�F�[�h�̍X�V����
void CFade::Update(void)
{
	if (m_Fade == FADE_NONE) return;

	VERTEX_2D* pVtx = nullptr;

	if (m_Fade == FADE_IN)
	{//�t�F�[�h�C�����
		m_col.a -= 0.07f;	//�|���S���𓧖��ɂ��Ă���

		if (m_col.a <= 0.0f)
		{
			m_col.a = 0.0f;
			m_Fade = FADE_NONE;	//�������Ă��Ȃ���Ԃ�

		}
	}
	else if (m_Fade == FADE_OUT)
	{//�t�F�[�h�A�E�g���
		m_col.a += 0.07f;	//�|���S����s�����ɂ��Ă���
		
		if (m_col.a >= 1.0f)
		{

			m_col.a = 1.0f;
			m_Fade = FADE_IN;	//�t�F�[�h�C����Ԃ�
			CManager::SetMode(m_pScene);

			return;
		}
	}
	//���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	//�A�����b�N
	m_pVtxBuff->Unlock();

}
//�t�F�[�h�̕`�揈��
void CFade::Draw(void)
{
	// FOG������
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`����ݒ�
	pDevice->SetTexture(0, NULL);//�e�N�X�`�����g�p���Ȃ��Ƃ��͕K��NULL���w�肷��

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		0,
		2); //���_���\���̂̃T�C�Y

	// FOG�̐ݒ�
	CManager::GetRenderer()->SetupVertexFog(D3DCOLOR_XRGB(255, 255, 255), D3DFOG_LINEAR, TRUE, 0.005f);

}
//�t�F�[�h�̐ݒ菈��
void CFade::SetFade(CScene* pScene)
{
	if (m_Fade != FADE_NONE)
	{
		delete pScene;

		pScene = nullptr;

		return;
	}
	
	if (m_pScene != nullptr)
	{
		m_pScene = nullptr;
	}

	if (m_pScene == nullptr)
	{
		m_pScene = pScene;
		m_Fade = FADE_OUT;
	}
}
// �擾����
CFade::FADE CFade::GetFadeState(void)
{
	return m_Fade;
}