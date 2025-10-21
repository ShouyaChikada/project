//=================================================
//
//	camera.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "camera.h"
#include "input.h"
#include "manager.h"
#include "debugproc.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "pausemanager.h"
#include "tutorial.h"

#define MAX_ANGLE (3.0f)

CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f,0.0f,0.0f);		
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR2(0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fDistance = NULL;
	m_bFlattery = false;
	m_bTPS = NULL;
}
CCamera::~CCamera()
{

}

//================================
//����������
//================================
HRESULT CCamera::Init(void)
{
	m_bFlattery = false;
	m_bTPS = true;
	//���_�E�����_�E�������ݒ肷��
#if 0
	m_posV = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, -300.0f);
#else
	//���_
	m_posV = D3DXVECTOR3(0.0f, 330.0f, -60.0f);
#endif
	//�����_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�����
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_rot = D3DXVECTOR3(D3DX_PI * 0.6f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_���璍���_�܂ł̋���
	m_fDistance = sqrtf((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x) + (m_posV.y - m_posR.y) * (m_posV.y - m_posR.y) + (m_posV.z - m_posR.z) * (m_posV.z - m_posR.z));

	//m_viewport.X = 0.0f;
	//m_viewport.Y = 0.0f;
	//m_viewport.Width = 640.0f;
	//m_viewport.Height = 720.0f;

	return S_OK;
}
//================================
//�I������
//================================
void CCamera::Uninit(void)
{
	
}
//================================
//�X�V����
//================================
void CCamera::Update(void)
{
//#ifndef _DEBUG
//#endif
	//	�L�[�{�[�h
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	// �}�E�X
	CInputMouse* pInputMouse = CManager::GetMouse();
	
	// �Q�[���̏I���̔���
	bool bGame = CGame::GetCheck();

	bool bTutorial = CTutorial::GetCheck();

	bool bCheck = CPauseManager::GetCheck();
	static int nCnt = 0;

	if (bTutorial == false)
	{
		if (bGame == true)
		{
			nCnt++;
			if (nCnt >= 90)
			{
				m_bFlattery = false;
				//���_
				m_posV = D3DXVECTOR3(0.0f, 330.0f, -60.0f);
				//�����_
				m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//�����
				m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				m_rot = D3DXVECTOR3(D3DX_PI * 0.6f, 0.0f, 0.0f);

				nCnt = 0;
			}
		}
	}

	if (bTutorial == false)
	{
		if (bCheck == true)
		{
			nCnt++;
			if (nCnt >= 30)
			{
				m_bFlattery = false;
				//���_
				m_posV = D3DXVECTOR3(0.0f, 330.0f, -110.0f);
				//�����_
				m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//�����
				m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				m_rot = D3DXVECTOR3(D3DX_PI * 0.6f, 0.0f, 0.0f);

				nCnt = 0;
			}
		}
	}

#if 0
	if (m_bFlattery == false)
	{
		if (pInputKeyboard->GetTrigger(DIK_F8) == true)
		{
			m_bFlattery = true;

		}
	}
	else if (m_bFlattery == true)
	{
		if (pInputKeyboard->GetTrigger(DIK_F8) == true)
		{
			m_bFlattery = false;
		}
	}
	
	// �J�����̃}�E�X����
	if (m_bFlattery == false)
	{
		MouseView(pInputMouse);

		// ���K��
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}
		if (m_rot.x > D3DX_PI)
		{
			m_rot.x -= D3DX_PI * 2.0f;
		}
		else if (m_rot.x < -D3DX_PI)
		{
			m_rot.x += D3DX_PI * 2.0f;
		}

	}

	// �v���C���[�̒Ǐ]
	if (m_bFlattery == true)
	{

		//���_�̐���(��)
		if (pInputKeyboard->GetPress(DIK_Q) == true)
		{
			m_rot.y -= 0.05f;
			//�p�x�̐��K��
			// ���K��
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}
			else if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}
		}
		//���_�̐���(�E)
		if (pInputKeyboard->GetPress(DIK_E) == true)
		{
			m_rot.y += 0.05f;
			// ���K��
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}
			else if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}
		}	

		m_posV.x = m_posR.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posV.y = m_posR.y - cosf(m_rot.x) * m_fDistance;
		m_posV.z = m_posR.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;

		m_posR.x += (m_posRDest.x - m_posR.x) * 0.2f;
		m_posR.y += (m_posRDest.y - m_posR.y) * 0.2f;
		m_posR.z += (m_posRDest.z - m_posR.z) * 0.2f;

		m_posV.x += (m_posVDest.x - m_posV.x) * 0.2f;
		m_posV.z += (m_posVDest.z - m_posV.z) * 0.2f;

		
	}
#else
	//���_�̐���(��)
	if (pInputKeyboard->GetPress(DIK_Q) == true)
	{
		m_rot.y -= 0.05f;
		//�p�x�̐��K��
		// ���K��
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}
	}
	//���_�̐���(�E)
	if (pInputKeyboard->GetPress(DIK_E) == true)
	{
		m_rot.y += 0.05f;
		// ���K��
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}
	}

	m_posV.x = m_posR.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posV.y = m_posR.y - cosf(m_rot.x) * m_fDistance;
	m_posV.z = m_posR.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;

	m_posR.x += (m_posRDest.x - m_posR.x) * 0.2f;
	m_posR.y += (m_posRDest.y - m_posR.y) * 0.2f;
	m_posR.z += (m_posRDest.z - m_posR.z) * 0.2f;

	m_posV.x += (m_posVDest.x - m_posV.x) * 0.2f;
	m_posV.z += (m_posVDest.z - m_posV.z) * 0.2f;

#endif

}
//================================
//�ݒ菈��
//================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		5000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	CDebugProc::Print("�J�������_���W : {(�����_) x:%.2f,y:%.2f,z:%.2f }{(���_)  x:%.2f,y:%.2f,z:%.2f }\n", m_posR.x, m_posR.y, m_posR.z, m_posV.x, m_posV.y, m_posV.z);

	if (m_bFlattery == true)
	{
		CDebugProc::Print("�v���C���[�̒Ǐ] [ F8 ] : �I��\n");
	}
	else if (m_bFlattery == false)
	{
		CDebugProc::Print("�v���C���[�̒Ǐ] [ F8 ] : �I�t\n");
	}


}

D3DXVECTOR3 CCamera::GetRotasion(void)
{
	return m_rot;
}

D3DXVECTOR3 CCamera::GetPosV(void)
{
	return m_posV;
}

D3DXVECTOR3 CCamera::GetPosR(void)
{
	return m_posR;
}

D3DXVECTOR3 CCamera::GetVecU(void)
{
	return m_vecU;
}

void CCamera::MouseView(CInputMouse* pMouse)
{
	// �E�N���b�N
	if (pMouse->OnDownR(CInputMouse::MOUSE_R))
	{
		// �}�E�X�̈ړ��ʎ擾
		D3DXVECTOR2 Move = pMouse->GetVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetVelocityOld();

		// ���݂̊p�x���v�Z
		D3DXVECTOR2 fAngle = Move - MoveOld;

		// ��]�ʂ��X�V
		m_rot.y += fAngle.x * 0.005f;
		m_rot.x += fAngle.y * 0.005f;

		// ��]�ʂ𐧌�
		if (m_rot.x > MAX_ANGLE)
		{
			m_rot.x -= fAngle.x * 0.005f;
		}
		else if (m_rot.x < 0.1f)
		{
			m_rot.x += fAngle.x * 0.005f;
		}

		// �J�������W���X�V
		m_posR.x = m_posV.x + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posR.y = m_posV.y + cosf(m_rot.x) * m_fDistance;
		m_posR.z = m_posV.z + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	}
	// ���N���b�N
	else if (pMouse->OnDownL(CInputMouse::MOUSE_L))
	{
		D3DXVECTOR2 Move = pMouse->GetVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetVelocityOld();

		D3DXVECTOR2 fAngle = Move - MoveOld;

		// ��]�ʂ��X�V
		m_rot.y += fAngle.x * 0.005f;
		m_rot.x += fAngle.y * 0.005f;

		// ��]�ʂ𐧌�
		if (m_rot.x > MAX_ANGLE)
		{
			m_rot.x -= fAngle.x * 0.005f;
		}
		else if (m_rot.x < 0.1f)
		{
			m_rot.x += fAngle.x * 0.005f;
		}

		// �J�����̎��_�̏��
		m_posV.x = m_posR.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posV.y = m_posR.y - cosf(m_rot.x) * m_fDistance;
		m_posV.z = m_posR.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	}
	
	// ���K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x -= D3DX_PI * 2.0f;
	}
	else if (m_rot.x < -D3DX_PI)
	{
		m_rot.x += D3DX_PI * 2.0f;
	}
}

// �Ǐ]�̐ݒ�
void CCamera::SetFollowing(D3DXVECTOR3 pos, D3DXVECTOR3 rotDest)
{
	//�����_�̖ړI
	m_posRDest.x = pos.x + sinf(rotDest.y) * MAX_SPEED;
	m_posRDest.y = pos.y + cosf(rotDest.y) * MAX_SPEED;
	m_posRDest.z = pos.z + cosf(rotDest.y) * MAX_SPEED;

	//���_�̖ړI
	m_posVDest.x = pos.x - sinf(m_rot.y) * m_fDistance;
	m_posVDest.y = pos.y - cosf(m_rot.y) * m_fDistance;
	m_posVDest.z = pos.z - cosf(m_rot.y) * m_fDistance;
}