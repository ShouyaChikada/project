//=================================================
//
//	object.cpp
// 
//	Author:�ߓc����
//
//=================================================
#include "object.h"
#include "renderer.h"
#include "camera.h"
#include "manager.h"
#include "game.h"

//�ÓI�����o�ϐ�
CObject* CObject::m_apTop[NUM_PRIORITY] = {};
CObject* CObject::m_apCur[NUM_PRIORITY] = {};
int CObject::m_nNumAll = 0;

//============================
//�R���X�g���N�^
//============================
CObject::CObject(int nPriority)
{
	m_type = TYPE_NONE;			//�^�C�v�̏�����
	m_nPriority = nPriority;	// �`��D�揇�ʂ̑��
 	m_bDeath = false;			// ���S�t���O��false�ɂ��Ă���

	// �Ȃ��̏�����
	m_pNext = nullptr;
	m_pPrev = nullptr;

	m_pPrev = m_apCur[nPriority];	// �O�̔��ӃW�F�N�g�Ƃ̂Ȃ�

	// �Ō���������Ă���
	if (m_apCur[nPriority])
	{
		m_apCur[nPriority]->m_pNext = this;		// �Ō���̎��ɐݒ�
	}
	else
	{
		m_apTop[nPriority] = this;	// �擪�̐ݒ�
	}

	m_apCur[nPriority] = this;		// �Ō���̐ݒ�
	m_nNumAll++;		//�����̉��Z
}

//============================
// �f�X�g���N�^
//============================
CObject::~CObject()
{

}

// ���ׂĂ�j������
void CObject::ReleaseAll(void)
{
	// �`��D�揇�ʕ��܂킷
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		// �擪�̃I�u�W�F�N�g����
		CObject* pObject = m_apTop[nCnt];	

		// ��񂪓����Ă�����
		while (pObject != nullptr)
		{ 
			// ���̃I�u�W�F�N�g��ۑ�
			CObject* pObjectNext = pObject->m_pNext;	

			// �I�u�W�F�N�g�̏I������
			pObject->Uninit();

			// �I�u�W�F�N�g�̃��X�g����폜
			pObject->m_pNext = nullptr;
			pObject->m_pPrev = nullptr;

			// �I�u�W�F�N�g�̔j��
			delete pObject;
			pObject = nullptr;

			// ���̃I�u�W�F�N�g����
			pObject = pObjectNext;	
		}

		// �擪�̏�����
		m_apTop[nCnt] = nullptr;

		// �Ō���̏�����
		m_apCur[nCnt] = nullptr;
	}

	// �����̌��Z
	m_nNumAll = NULL;
	
}

// �������g�̔j��
void CObject::Release(void)
{
	// ���S�t���O�𗧂Ă�
	m_bDeath = true;
}

// ���ׂĂ̍X�V����
void CObject::UpdateAll(void)
{
	// �`��D�揇�ʕ��܂킷
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		// �擪�̃I�u�W�F�N�g����
		CObject* pObject = m_apTop[nCnt];

		// ��񂪓����Ă�����
		while (pObject != nullptr)
		{
			// ���̃I�u�W�F�N�g��ۑ�
			CObject* pObjectNext = pObject->m_pNext;

			if (CPauseManager::GetPause())
			{
				if (pObject->GetType() == TYPE_PAUSE)
				{
					// �X�V����
					pObject->Update();
				}
			}
			else
			{
				// ���S�t���O�������Ă�����
				if (pObject->m_bDeath == false)
				{

					// �X�V����
					pObject->Update();
				}
			}

			//���̃I�u�W�F�N�g����
			pObject = pObjectNext;
		}

	}

	// �`��D�揇�ʕ��܂킷
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		CObject* pObject = m_apTop[nCnt];	//�擪�̃I�u�W�F�N�g����

		// ��񂪓����Ă�����
		while (pObject != nullptr)
		{
			// ���̃I�u�W�F�N�g��ۑ�
			CObject* pObjectNext = pObject->m_pNext;

			// ���S�t���O�������Ă�����
			if (pObject->m_bDeath == true)
			{
				// �O�ɃI�u�W�F�N�g����������
				if (pObject->m_pPrev != nullptr)
				{
					// �O�̎��̃I�u�W�F�N�g�ƂȂ���
					pObject->m_pPrev->m_pNext = pObject->m_pNext;
				}
				else
				{
					// ���̃I�u�W�F�N�g�Ɉ����p����
					m_apTop[nCnt] = pObject->m_pNext;
				}

				// ��낪��������
				if (pObject->m_pNext != nullptr)
				{
					// ���̑O�̃I�u�W�F�N�g�ƂȂ���
					pObject->m_pNext->m_pPrev = pObject->m_pPrev;
				}
				else
				{
					// �O�̃I�u�W�F�N�g�Ɉ����p����
					m_apCur[nCnt] = pObject->m_pPrev;
				}

				pObject->m_pNext = nullptr;
				pObject->m_pPrev = nullptr;

				m_nNumAll--;

				delete pObject;
			}
			pObject = pObjectNext;
		}

	}
	
}

//���ׂĂ̕`�揈��
void CObject::DrawAll(void)
{
	CCamera* pCamera = CManager::GetCamera();
	pCamera->SetCamera();
	
	// �`��D�揇�ʕ��܂킷
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		// �擪�̃I�u�W�F�N�g����
		CObject* pObject = m_apTop[nCnt];	

		// ��񂪓����Ă�����
		while (pObject != nullptr)
		{
			// ���̃I�u�W�F�N�g��ۑ�
			CObject* pObjectNext = pObject->m_pNext;

			// �`�揈��
			pObject->Draw();

			// ���̃I�u�W�F�N�g����
			pObject = pObjectNext;

		}
		

	}
}

// �ő吔�̎擾
int CObject::Getobject(void)
{
	return m_nNumAll;
}

// �^�C�v�̑��
void CObject::SetType(TYPE type)
{
	m_type = type;
}

// �^�C�v�̎擾
CObject::TYPE CObject::GetType(void)
{
	return m_type;
}
// �T�C�Y�̎擾
D3DXVECTOR3 CObject::SetSize(D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin, int nNumVtx, DWORD sizeFVF, BYTE* pVtxBuff)
{
	D3DXVECTOR3 Size;

	// ���_������
	for (int nCntBlock = 0; nCntBlock < nNumVtx; nCntBlock++)
	{
		// ���_���W�̑��
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

		// ���_���W�̔�r
		if (Vtx.x > VtxMax.x)
		{// x���ő�l���傫��������
			// ���
			VtxMax.x = Vtx.x;
		}
		if (Vtx.y > VtxMax.y)
		{// y���ő�l���傫��������
			// ���
			VtxMax.y = Vtx.y;
		}
		if (Vtx.z > VtxMax.z)
		{// z���ő�l���傫��������
			// ���
			VtxMax.z = Vtx.z;
		}

		if (Vtx.x < VtxMin.x)
		{// x���ŏ��l��菬����������
			// ���
			VtxMin.x = Vtx.x;
		}
		if (Vtx.y < VtxMin.y)
		{// y���ŏ��l��菬����������
			// ���
			VtxMin.y = Vtx.y;
		}
		if (Vtx.z < VtxMin.z)
		{// z���ŏ��l��菬����������
			// ���
			VtxMin.z = Vtx.z;
		}

		// ���_�t�H�[�}�b�g�̃T�C�Y���i�߂�
		pVtxBuff += sizeFVF;
	}

	// �T�C�Y��������
	Size.x = VtxMax.x - VtxMin.x;	// size��x
	Size.y = VtxMax.y - VtxMin.y;	// size��y
	Size.z = VtxMax.z - VtxMin.z;	// size��z

	return Size;
}

//�擪�A�h���X�̎擾
CObject* CObject::GetTop(int nPriority)
{
	return m_apTop[nPriority];
}