//=============================================
//
// author chikada shouya
//
//=============================================

#include "shadows.h"													
#include "manager.h"
#include "debugproc.h"

//�R���X�g���N�^
CShadowS::CShadowS(int nPriority):CObjectX(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);	//�e�̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�e�̌���
	m_mtxWorld = {};
	m_pVtxBuff = nullptr;
	m_bLook = false;
	m_Obj2D = NULL;
}

// �f�X�g���N�^
CShadowS::~CShadowS()
{

}

// �e�̐���
CShadowS* CShadowS::Create(const char* txt,D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CShadowS* pShadowS = nullptr;
	pShadowS = new CShadowS;

	if (pShadowS != nullptr)
	{
		pShadowS->SetXfile(txt);
		pShadowS->Init(pos, rot);
		return pShadowS;
	}
	else
	{
		return nullptr;
	}
}
//=======================================
//����������
//=======================================
HRESULT CShadowS::Init (D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CObjectX::Init();
	
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	VERTEX_2D* pVtx = nullptr;

	// ���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = SCREEN_WIDTH;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = SCREEN_HEIGHT;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = SCREEN_WIDTH;
	pVtx[3].pos.y = SCREEN_HEIGHT;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=======================================
//�I������
//=======================================
void CShadowS::Uninit(void)
{

	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CObjectX::Uninit();

}
//=======================================
//�X�V����
//=======================================
void CShadowS::Update(void)
{
	CObjectX::Update();
	// �L�[�{�[�h
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();
	pInputKeyboard = CManager::GetKeyboard();

	//�I�[���������Ƃ�
	if (pInputKeyboard->GetTrigger(DIK_O) == true)
	{
		m_bLook = true;
	}

	//�s�[���������Ƃ�
	if (pInputKeyboard->GetTrigger(DIK_P) == true)
	{
		m_bLook = false;
	}

	CObjectX::SetPosition(m_pos);
}
//=======================================
//�`�揈��
//=======================================
void CShadowS::Draw(void)
{
	if (m_bLook == false)
	{

		//�f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// �X�e���V���e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		// Z�o�b�t�@�ւ̏����݂𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		// �J���[�o�b�t�@�ւ̏������݂𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);

		// �X�e���V���o�b�t�@�̔�r�p�����[�^�̐ݒ�
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);		// �ǂ��������i���Ă���Ƃ�
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);		// �X�e���V���o�b�t�@�͍��i�AZ�o�b�t�@�͕s���i�̎�
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);			// �X�e���V���o�b�t�@���s���i�ɂȂ��Ă���Ƃ�

		// �\�ʂ̃J�����O
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		// �e���f���̕`��
		CObjectX::Draw();

		// �X�e���V���o�b�t�@�̎Q�ƒl��ݒ�("1"�ɂȂ�)
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

		// �X�e���V���o�b�t�@�̔�r�p�����[�^�̐ݒ�
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);		// �ǂ��������i���Ă���Ƃ�
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// �X�e���V���o�b�t�@�͍��i�AZ�o�b�t�@�͕s���i�̎�
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// �X�e���V���o�b�t�@���s���i�ɂȂ��Ă���Ƃ�

		// ���ʂ̃J�����O
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		// �e���f���̕`��
		CObjectX::Draw();

		// �J���[�o�b�t�@�ւ̏������݂�L���ɂ���
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);

		// �X�e���V���o�b�t�@�̎Q�ƒl��ݒ�("2"�ɂȂ�)
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

		// �X�e���V���o�b�t�@�̔�r�p�����[�^�̐ݒ�
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);		// �ǂ��������i���Ă���Ƃ�
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// �X�e���V���o�b�t�@�͍��i�AZ�o�b�t�@�͕s���i�̎�
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// �X�e���V���o�b�t�@���s���i�ɂȂ��Ă���Ƃ�

		// ��ʂ̑傫���̍����|���S�����o��

		//m_Obj2D->Draw();

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
			0, 2); //���_���\���̂̃T�C�Y


		// ���ׂČ��ɖ߂� 
		// Z�o�b�t�@�ւ̏����݂�L���ɂ���
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		// �X�e���V���e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
		// �J�����O
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


	}
	if (m_bLook == true)
	{
		CObjectX::Draw();
	}
}
//=========================
//�e�̐ݒ菈��
//=========================
void CShadowS::SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
}
////=========================
////�G�̈ʒu�̍X�V����
////=========================
//void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
//{
//	//�����Ŏw�肳�ꂽ�ԍ��̉e��pos��ݒ�
//	g_aShadow[nIdxShadow].pos = pos;
//}
////=========================
////�e�̎擾
////=========================
//Shadow* GetShadow(void)
//{
//	return &g_aShadow[0];
//}