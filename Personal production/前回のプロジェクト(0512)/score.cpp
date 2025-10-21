//=================================================
//
//	score.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "score.h"
#include "manager.h"

// �ÓI�����o�ϐ�
CNumber* CScore::m_pNumber[MAX_SCORE] = {};
int CScore::m_Score = 0;

//�R���X�g���N�^
CScore::CScore(int nPriority) : CObject(nPriority)
{	
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
}

//�f�X�g���N�^
CScore::~CScore()
{

}

//�X�R�A�̐���
CScore* CScore::Create(D3DXVECTOR3 pos)
{
	CScore* pScore = nullptr;
	pScore = new CScore;

	if (pScore != nullptr)
	{
		pScore->m_Pos = pos;
		pScore->Init();
		return pScore;
	}
	else
	{
		return nullptr;
	}
}
//*********************
// ����������
//*********************
HRESULT CScore::Init(void)
{

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_pNumber[nCnt] = new CNumber;
		m_pNumber[nCnt]->Init(1000.0f, 1000.0f,nCnt,50.0f,50.0f,1,4, "data\\TEXTURE\\number005.png", 0.1f);
		//�e�N�X�`����ݒ�
		//m_pNumber[nCnt]->BindTexture(m_pTexture);
	}
	CScore::Set(0);

	
	return S_OK;
}

//*********************
// �I������
//*********************
void CScore::Uninit(void)
{
	//�i���o�[�̔j��
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_pNumber[nCnt] != NULL)
		{
			m_pNumber[nCnt]->Uninit();
			delete m_pNumber[nCnt];
			m_pNumber[nCnt] = NULL;
		}
	}
	// �������g�̔j��
	CObject::Release();
}

//*********************
// �X�V����
//*********************
void CScore::Update(void)
{

}

//*********************
// �`�揈��
//*********************
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_pNumber[nCnt]->Draw();
	}
}

//*********************
// �X�R�A�ݒ菈��
//*********************
void CScore::Set(int nScore)
{
	int aPosTexU[MAX_SCORE] = {};

	int nData = 1000;
	int aData = 100;	//�e���̐������i�[

	m_Score = nScore;
	
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		//�����Ƃɕ�������
		if (nCount == 0)
		{
			aPosTexU[0] = m_Score / nData;//8����
		}
		else
		{
			aPosTexU[nCount] = m_Score % nData / aData;//7����
			nData = nData / 10;
			aData = aData / 10;
		}
		m_pNumber[nCount]->SetNumber(aPosTexU[nCount],4);
	}
}

//*********************
// �X�R�A���Z����
//*********************
void CScore::Add(int nValue)
{
	// �e���̐������i�[
	int aPosTexU[MAX_SCORE] = {};

	int nData = 1000;
	int aData = 100;	//�e���̐������i�[

	m_Score += nValue;

	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		//�����Ƃɕ�������
		if (nCount == 0)
		{
			aPosTexU[nCount] = m_Score / nData;//8����
		}
		else
		{
			aPosTexU[nCount] = m_Score % nData / aData;//7����
			nData = nData / 10;
			aData = aData / 10;
		}
		m_pNumber[nCount]->SetNumber(aPosTexU[nCount],4);
	}

}

//=====================
// �X�R�A��0���J�E���g
//=====================
int  CScore::Counter(int nScore)
{
	int nNum = nScore;	// �X�R�A�̂O�̕������J�E���g
	int nKeepNum = 0;	// �X�R�A�̌���

	while (nNum != 0)	// ����؂�Ȃ��Ȃ�܂ŌJ��Ԃ�(�O�܂�)
	{
		nNum /= 10;		// nNum��10�Ŋ����Ă���
		nKeepNum++;		// ���������Z

	}
	if (nScore == 0)
	{
		// 1���ڂ�0�������Ă���Ƃ�
		nKeepNum = 1;
	}
	return nKeepNum;	// �X�R�A�̌�����Ԃ�
}

//=====================
// ���݂̃X�R�A
//=====================
int CScore::GetScore(void)
{
	return m_Score;
}

//�ʒu�̐ݒ�
void CScore::SetPosition(D3DXVECTOR3 pos)
{
	m_SetPosition = pos;
}

// �ʒu���擾
D3DXVECTOR3 CScore::GetPosition(void)
{
	return m_SetPosition;
}