//=================================================
//
//	block.cpp
// 
// Author:�ߓc ����
//
//=================================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "block.h"
#include "enemy.h"
#include "player.h"
#include "manager.h"
#include "game.h"

// �R���X�g���N�^
CBlock::CBlock(int nPriority):CObjectX(nPriority)
{
	m_type = TYPE_0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Vtxmax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Vtxmin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bLanding = false;
	m_nIdx = NULL;
}

// �f�X�g���N�^
CBlock::~CBlock()
{

}

//=========================
// �u���b�N�̐���
//=========================
CBlock* CBlock::Create(const char * FileName,D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBlock* pBlock = nullptr;
	pBlock = new CBlock;
	if (pBlock != nullptr)
	{
		// �I�u�W�F�N�g�ݒ�
		pBlock->SetType(TYPE_BLOCK);
		pBlock->SetXfile(FileName);
		pBlock->SetPosition(pos);
		pBlock->SetRot(D3DXToRadian(rot));	
		pBlock->Init(pos, rot);
		return pBlock;

	}
	else
	{
		return nullptr;
	}
}

//=========================
//�@�u���b�N����������
//=========================
HRESULT CBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObjectX::Init();

	m_pos = pos;
	m_rot = rot;

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
void CBlock::Uninit(void)
{
	CObjectX::Uninit();

	// CBlock::Release();
}
//=========================
//�@�u���b�N�X�V����
//=========================
void CBlock::Update(void)
{
	// ��U�Ȃ�
	CObjectX::Update();
	
}
//=========================
//�@�u���b�N�`�揈��
//=========================
void CBlock::Draw(void)
{
	// FOG�̐ݒ�
	//CManager::GetRenderer()->SetupVertexFog(D3DCOLOR_XRGB(255, 255, 255), D3DFOG_LINEAR, TRUE, 0.00005f);

	CObjectX::Draw();

	// FOG������
	//CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

}

//=============================
//�@�u���b�N�̓����蔻�菈��
//=============================
bool CBlock::Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3* move, D3DXVECTOR3* size)
{
	bool bLanding = false;	

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
		//// �c�̓����蔻��--------------------------
		//if (pos->x - size->x * HALF < m_pos.x + m_size.x * HALF &&
		//	pos->x + size->x * HALF > m_pos.x - m_size.x * HALF)
		//{
		//	if (posOld->z - size->z * HALF < m_pos.z + m_size.z * HALF &&
		//		pos->z + size->z * HALF > m_pos.z - m_size.z * HALF)
		//	{
		//		// �ォ��߂荞�񂾎�
		//		if (posOld->y >= m_pos.y + m_size.y * HALF &&
		//			pos->y < m_pos.y + m_size.y * HALF)
		//		{
		//			bLanding = true;	// �W�����v
		//			pos->y = posOld->y;
		//			move->y = 0.0f;
		//		}
		//		// ������߂荞�񂾎�
		//		else if (posOld->y + size->y <= m_pos.y - m_size.y * HALF &&
		//			pos->y + size->y > m_pos.y - m_size.y * HALF)
		//		{
		//			pos->y = (m_pos.y - m_size.y) - size->y * HALF;
		//			move->y = 0.0f;
		//		}
		//	}
		//}
	}

	//if ((pos->x - PlayerSize.x * 0.5f) < (m_pos.x + m_size.x * 0.5f)
	//	&& (pos->x + PlayerSize.x * 0.5f) > (m_pos.x - m_size.x * 0.5f)
	//	&& (pos->z - PlayerSize.z * 0.5f) < (m_pos.z + m_size.z * 0.5f)
	//	&& (pos->z + PlayerSize.z * 0.5f) > (m_pos.z - m_size.z * 0.5f))
	//{
	//	if ((posOld->y >= m_pos.y + m_size.y)
	//		&& (pos->y < m_pos.y + m_size.y))
	//	{
	//		bLanding = true;
	//		pos->y = posOld->y;
	//	}
	//}
	//if ((pos->x + PlayerSize.x * 0.5f) < (m_pos.x - m_size.x * 0.5f)
	//	&& (pos->x - PlayerSize.x * 0.5f) > (m_pos.x + m_size.x * 0.5f)
	//	&& (pos->z + PlayerSize.z * 0.5f) < (m_pos.z - m_size.z * 0.5f)
	//	&& (pos->z - PlayerSize.z * 0.5f) > (m_pos.z + m_size.z * 0.5f))
	//{
	//	if ((posOld->y <= m_pos.y - m_size.y)
	//		&& (pos->y > m_pos.y - m_size.y))
	//	{
	//		bLanding = true;
	//		pos->y = posOld->y;
	//	}
	//}

	return bLanding;
}