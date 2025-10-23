//=================================================
//
//	renderer.cpp
// 
//	Author:�ߓc����
//
//=================================================
#include "renderer.h"
#include "object.h"
#include "debugproc.h"
#include "input.h"
#include "manager.h"
//#include "game.h"
//#include "fade.h"

int CRenderer::m_nCountFPS = 0;
//============================================
// �R���X�g���N�^����
//============================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		m_apTextureMT[nCnt] = NULL;
		m_apRenderMT[nCnt] = NULL;
	}
	m_pZBuffMT = NULL;	
	m_pVtxBuffMT = NULL;

}

//============================================
// �f�X�g���N�^����
//============================================
CRenderer::~CRenderer()
{

}

//============================================
// ����������
//============================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;
	
	//Direct3D
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̐���
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//Direct3D
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//�����^�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	////�����_�����O�^�[�Q�b�g�p�e�N�X�`���̍쐬
	//m_pD3DDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1,
	//	D3DUSAGE_RENDERTARGET,
	//	D3DFMT_A8B8G8R8,
	//	D3DPOOL_DEFAULT,
	//	&m_apTextureMT[0], NULL);

	////�e�N�X�`�������_�����O�p�C���^�[�t�F�[�X�̍쐬
	//m_apTextureMT[0]->GetSurfaceLevel(0, &m_apRenderMT[0]);

	////�e�N�X�`�������_�����O�p�Ƀo�b�t�@�̐���
	//m_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH, SCREEN_HEIGHT,
	//										D3DFMT_D16, 
	//										D3DMULTISAMPLE_NONE, 
	//										0, TRUE, 
	//										&m_pZBuffMT, NULL);

	////���݂̃����_�����O�^�[�Q�b�g���擾(�ۑ�)
	//m_pD3DDevice->GetRenderTarget(0, &pRenderDef);

	////���݂�Z�o�b�t�@�̎擾(�ۑ�)
	//m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);
	//
	////�����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
	//m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);

	////Z�o�b�t�@�𐶐�����Z�o�b�t�@�ɐݒ�
	//m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	////�����_�����O�^�[�Q�b�g�p�e�N�X�`���̃N���A
	//m_pD3DDevice->Clear(0, NULL,
	//	D3DCLEAR_TARGET,
	//	D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	////�����_�����O�^�[�Q�b�g�����ɖ߂�
	//m_pD3DDevice->SetRenderTarget(0, pRenderDef);
	//
	////Z�o�b�t�@�����ɖ߂�
	//m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);

	//�e�N�X�`�������_�����O�p�r���[�|�[�g�̐ݒ�
	m_pViewportMT.X = 0;
	m_pViewportMT.Y = 0;
	m_pViewportMT.Width = SCREEN_WIDTH;
	m_pViewportMT.Height = SCREEN_HEIGHT;
	m_pViewportMT.MinZ = 0.0f;
	m_pViewportMT.MaxZ = 1.0f;

	//���_�o�b�t�@�̐���
	m_pD3DDevice->CreateVertexBuffer(sizeof(CObject::VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffMT, NULL);

	CObject::VERTEX_2D* pVtx = NULL;

	// ���b�N
	m_pVtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	m_pVtxBuffMT->Unlock();

	return S_OK;

}

//============================================
// �I������
//============================================
void CRenderer::Uninit(void)
{

	//�f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffMT != NULL)
	{
		m_pVtxBuffMT->Release();
		m_pVtxBuffMT = NULL;
	}

	//Z�o�b�t�@�̔j��
	if (m_pZBuffMT != NULL)
	{
		m_pZBuffMT->Release();
		m_pZBuffMT = NULL;
	}

	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		//�C���^�[�t�F�[�X�̔j��
		if (m_apRenderMT[nCnt] != NULL)
		{
			m_apRenderMT[nCnt]->Release();
			m_apRenderMT[nCnt] = NULL;
		}
		
		//�e�N�X�`���̔j��
		if (m_apTextureMT[nCnt] != NULL)
		{
			m_apTextureMT[nCnt]->Release();
			m_apTextureMT[nCnt] = NULL;
		}
	}

	//���ׂĔj��
	CObject::ReleaseAll();
}

//============================================
//�X�V����
//============================================
void CRenderer::Update(void)
{
	// �L�[�{�[�h
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();
	pInputKeyboard = CManager::GetKeyboard();

	//���ׂĂ̍X�V����
	CObject::UpdateAll();
	

	if (pInputKeyboard->GetTrigger(DIK_F3))
	{
		onWireFrame();
	}
	else if (pInputKeyboard->GetTrigger(DIK_F4))
	{
		offWireFrame();

	}
}

//============================================
//�`�揈��
//============================================
void CRenderer::Draw(void)
{
	LPDIRECT3DSURFACE9 pRenderWk = NULL;
	LPDIRECT3DTEXTURE9 pTextureWk = NULL;

	//CFade* pFade = CManager::GetFade();
	//CScene* pScene = CManager::GetScene();
	m_nCountFPS = GetFPS();

	//�o�b�N�o�b�t�@
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
		D3DCOLOR_RGBA(128, 154, 255, 255), 1.0f, 0);

	//D3DXVECTOR3 posV = pCamera->GetPosV();
	//D3DXVECTOR3 posR = pCamera->GetPosR();
	//D3DXVECTOR3 vecU = pCamera->GetVecU();

	//D3DXVECTOR3 posV = D3DXVECTOR3(0.0f, 150.0f, -550.0f);
	//D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	////�o�b�N�o�b�t�@			  
	//m_pD3DDevice->Clear(0, NULL,
	//	D3DCLEAR_ZBUFFER,
	//	D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	////�����_�����O�^�[�Q�b�g���e�N�X�`��[0]�ɐݒ�ss
	//ChangeTarget(posV, posR, vecU);

	//m_apTextureMT[0] = NULL;

	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//�`��J�n���������ꂽ�Ƃ�

		// FOG�̐ݒ�
		//SetupVertexFog(D3DCOLOR_XRGB(255, 255, 255), D3DFOG_LINEAR, TRUE, 0.08f);

		//�I�u�W�F�N�g���ׂĂ̕`��
		CObject::DrawAll();

		//pFade->Draw();

		//if (pScene != nullptr)
		//{
		//	pScene->Draw();
		//}

		// FOG������
		//m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);		
#if 1

		CDebugProc::Print("FPS:%d\n",m_nCountFPS);

		//�f�o�b�O�t�H���g�̕`��
		CDebugProc::Draw(15,15);

		CDebugProc::End();

#endif
		////���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		//m_pD3DDevice->SetStreamSource(0, m_pVtxBuffMT, 0, sizeof(CObject::VERTEX_2D));

		////�e�N�X�`���̐ݒ�
		//m_pD3DDevice->SetTexture(0, m_apTextureMT[1]);

		////���_�t�H�[�}�b�g�̐ݒ�
		//m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		////�|���S���̕`��
		//m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		//	0, 2); //���_���\���̂̃T�C�Y

		////�����_�����O�^�[�Q�b�g�����ɖ߂�
		//m_pD3DDevice->SetRenderTarget(0, pRenderWk);
		//
		//////���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		////m_pD3DDevice->SetStreamSource(0, m_pVtxBuffMT, 0, sizeof(CObject::VERTEX_2D));

		////�e�N�X�`���̐ݒ�
		//m_pD3DDevice->SetTexture(0, m_apTextureMT[0]);

		//////���_�t�H�[�}�b�g�̐ݒ�
		////m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		////�|���S���̕`��
		//m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
		//	0, 2); //���_���\���̂̃T�C�Y

		//	//�e�N�X�`��[0]�ƃe�N�X�`��[1]�����ւ���
		//pTextureWk = m_apTextureMT[0];
		//m_apTextureMT[0] = m_apTextureMT[1];
		//m_apTextureMT[1] = pTextureWk;

		////�����_�[[0]�ƃ����_�[[1]�����ւ���
		//pRenderWk = m_apRenderMT[0];
		//m_apRenderMT[0] = m_apRenderMT[1];
		//m_apRenderMT[1] = pRenderWk;

		//�`��I��
		m_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}
//============================================
// �f�o�C�X�̎擾
//============================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

//============================================
// ���C���[�t���[��(�I��)
//============================================
void CRenderer::onWireFrame(void) 
{
	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

//============================================
// ���C���[�t���[��(�I�t)
//============================================
void CRenderer::offWireFrame(void) 
{
	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//============================================
// �����_�����O�^�[�Q�b�g�̐ݒ�
//============================================
void CRenderer::ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU)
{
	D3DXMATRIX mtxView, mtxProjection;
	float fAspect = 0.0f;

	//�����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
	m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);

	//Z�o�b�t�@�𐶐�����Z�o�b�t�@�ɐݒ�
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	//�e�N�X�`�������_�����O�p�̃r���[�|�[�g�̐ݒ�
	m_pD3DDevice->SetViewport(&m_pViewportMT);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);
		
	//�r���[�}�g���b�N�X�̐���;
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	fAspect = (float)m_pViewportMT.Width / (float)m_pViewportMT.Height;

	D3DXMatrixPerspectiveFovLH(&mtxProjection,
								D3DXToRadian(45.0f),
								fAspect,
								10.0f,5000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);


}

//============================================
// �e�N�X�`���̎擾
//============================================
LPDIRECT3DTEXTURE9 CRenderer::GetTextureMT(void)
{
	return m_apTextureMT[0];
}

//============================================
// �t�H�O�̐ݒ�
//============================================
void CRenderer::SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density)
{
	//�f�o�C�X�̎擾
	m_pD3DDevice = GetDevice();

	float Start = 10.0f,    // Linear fog distances
		End = 5000.0f;

	// Enable fog blending.
	m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// Set the fog color.
	m_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, Color);

	// Set fog parameters.
	if (D3DFOG_LINEAR == Mode)
	{
		m_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);
		m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&Start));
		m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&End));
	}
	else
	{
		m_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);
		m_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&Density));
	}

	// Enable range-based fog if desired (only supported for
	//   vertex fog). For this example, it is assumed that UseRange
	//   is set to a nonzero value only if the driver exposes the 
	//   D3DPRASTERCAPS_FOGRANGE capability.
	// Note: This is slightly more performance intensive
	//   than non-range-based fog.
	if (UseRange)
		m_pD3DDevice->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);
}
