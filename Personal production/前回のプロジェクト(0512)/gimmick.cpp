//=================================================
//
//	gimmick.cpp
// 
//	Author:�ߓc����
//
//=================================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "gimmick.h"
#include "enemy.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "gimmickmanager.h"
#include "scene.h"

// �ÓI�����o�ϐ�
bool CGimmick::m_bUse = false;
CMeshCylinder* CGimmick::m_pMeshCylinder = nullptr;
CGauge* CGimmick::m_pGauge = nullptr;
CBaseUI* CGimmick::m_pBaseUI = nullptr;

// �R���X�g���N�^
CGimmick::CGimmick(int nPriority) :CObjectX(nPriority)
{
	m_type = TYPE_METEORITE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Vtxmax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Vtxmin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bLanding = false;
	m_fAddCharge = 0.0f;
	m_bUse = false;

}

// �f�X�g���N�^
CGimmick::~CGimmick()
{

}

//=========================
// �u���b�N�̐���
//=========================
CGimmick* CGimmick::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	CGimmick* pGimmick = nullptr;
	pGimmick = new CGimmick;

	if (pGimmick != nullptr)
	{
		// �I�u�W�F�N�g�ݒ�
		pGimmick->SetXfile(pGimmick->GIMMICK_FILE[type]);
		pGimmick->SetPosition(pos);
		pGimmick->SetRot(D3DXToRadian(rot));
		pGimmick->Init(pos, rot, type);
		pGimmick->m_bUse = true;
		return pGimmick;

	}
	else
	{
		return nullptr;
	}
}

//=========================
//�@�u���b�N����������
//=========================
HRESULT CGimmick::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	CScene::MODE mode = CScene::GetMode();

	CObjectX::Init();

	m_pMeshCylinder = CMeshCylinder::Create(D3DXVECTOR3(pos.x,-20.0f,pos.z), D3DXVECTOR3(0.0f,0.0f,0.0f), 250.0f);
	m_pGauge = CGauge::Create(D3DXVECTOR3(315.0f,335.0f,0.0f),nullptr,D3DXCOLOR(1.0f,1.0f,0.0f,1.0f));

	if (mode == CScene::MODE_TUTORIAL)
	{
		m_pBaseUI = CBaseUI::Create(D3DXVECTOR3(250.0f, 360.0f, 0.0f), "data\\TEXTURE\\Tumbase.png");
	}

	if (mode != CScene::MODE_TUTORIAL)
	{
		m_pBaseUI = CBaseUI::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), "data\\TEXTURE\\Tumbase.png");
	}

	m_pos = pos;
	m_rot = rot;
	m_type = type;
	LPD3DXMESH pMesh = CObjectX::GetMesh();

	// ���[�J���ϐ��錾-----------------------------
	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	//----------------------------------------------

	// ���_���̎擾
	nNumVtx = pMesh->GetNumVertices();

	// ���_�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(pMesh->GetFVF());

	// ���_�o�b�t�@�����b�N
	pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	m_size = CObject::SetSize(m_Vtxmax, m_Vtxmin, nNumVtx, sizeFVF, pVtxBuff);

	// �A�����b�N
	pMesh->UnlockVertexBuffer();

	return S_OK;
}
//=========================
//�@�u���b�N�I������
//=========================
void CGimmick::Uninit(void)
{
	m_bUse = false;

	CObjectX::Uninit();

}
//=========================
//�@�u���b�N�X�V����
//=========================
void CGimmick::Update(void)
{
	bool bUse = CGimmickManager::GetPush();

	if (bUse == true)
	{
		m_fAddCharge += 0.5f;

		if (m_fAddCharge < 260.0f)
		{
			m_pGauge->FSetGageLength(200.0f, m_fAddCharge, 500.0f, 50.0f);
		}


	}

	m_pos += m_move;

	if (m_type == TYPE_METEORITE)
	{
		m_move.y = -0.05f;
		m_rot.y += 0.5f;
		if (m_pos.y <= 0.0f)
		{
			Uninit();
		}
	}	

	SetPosition(m_pos);
}
//=========================
//�@�u���b�N�`�揈��
//=========================
void CGimmick::Draw(void)
{

	CObjectX::Draw();
}

//=============================
//�@�����蔻�菈��
//=============================
bool CGimmick::Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3* move, D3DXVECTOR3* size)
{
	bool bLanding = false;

	CPlayer* pPlayer = CGame::GetPlayer();

	if (m_bUse == true)
	{
		if (pos->y - (size->y * HALF) < m_pos.y + (m_size.y * HALF) &&
			pos->y + (size->y * HALF) > m_pos.y - (m_size.y * HALF))
		{
			// ���E�̓����蔻��----------------------
			if (posOld->z - (size->z * HALF) < m_pos.z + (m_size.z * HALF) &&
				pos->z + (size->z * HALF) > m_pos.z - (m_size.z * HALF))
			{
				// ������߂荞��
				if (posOld->x + (size->x * HALF) < m_pos.x - (m_size.x * HALF) &&
					pos->x + (size->x * HALF) > m_pos.x - (m_size.x * HALF))
				{
					pos->x = m_pos.x - m_size.x * HALF - size->x * HALF - 0.1f;

				}
				// �E����߂荞��
				else if (posOld->x - (size->x * HALF) > m_pos.x + (m_size.x * HALF) &&
					pos->x - (size->x * HALF) < m_pos.x + (m_size.x * HALF))
				{
					pos->x = m_pos.x + (m_size.x * HALF) + (size->x * HALF) + 0.1f;
				}
			}

			// �O��̓����蔻��------------------------------
			if (posOld->x - (size->z * HALF) < m_pos.x + (m_size.z * HALF) &&
				pos->x + (size->z * HALF) > m_pos.x - (m_size.z * HALF))
			{
				// ��O����߂荞��
				if (posOld->z + (size->z * HALF) < m_pos.z - (m_size.z * HALF) &&
					pos->z + (size->z * HALF) > m_pos.z - (m_size.z * HALF))
				{
					pos->z = m_pos.z - (m_size.z * HALF) - (size->z * HALF) - 0.3f;

				}
				// ������߂荞��
				else if (posOld->z - (size->z * HALF) > m_pos.z + (m_size.z * HALF) &&
					pos->z - (size->z * HALF) < m_pos.z + (m_size.z * HALF))
				{
					pos->z = m_pos.z + (m_size.z * HALF) + (size->z * HALF) + 0.3f;

				}
			}

			// �c�̓����蔻��--------------------------
			if (pos->x - (size->x * HALF) < m_pos.x + (m_size.x * HALF) &&
				pos->x + (size->x * HALF) > m_pos.x - (m_size.x * HALF))
			{
				if (posOld->z - (size->z * HALF) < m_pos.z + (m_size.z * HALF) &&
					pos->z + (size->z * HALF) > m_pos.z - (m_size.z * HALF))
				{
					// �ォ��߂荞�񂾎�
					if (posOld->y - (size->y * HALF) >= m_pos.y + (m_size.y * HALF) &&
						pos->y - (size->y * HALF) < m_pos.y + (m_size.y * HALF))
					{
						bLanding = true;	// �W�����v
						pos->y = posOld->y;
						move->y = 0.0f;

					}
					// ������߂荞�񂾎�
					else if (posOld->y + size->y <= m_pos.y - (m_size.y * HALF) &&
						pos->y + size->y > m_pos.y - (m_size.y * HALF))
					{
						pos->y = m_pos.y - (m_size.y * HALF);
						move->y = 0.0f;
					}
				}
			}
		}
	}
	return bLanding;
}