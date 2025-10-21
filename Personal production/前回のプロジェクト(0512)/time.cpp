//=================================================
//
//	time.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "time.h"
#include "manager.h"

// �ÓI�����o�ϐ�
CNumber* CTime::m_pNumber1[MAX_TIME] = {};
CNumber* CTime::m_pNumber2[MAX_TIME] = {};
CNumber* CTime::m_pNumber3 = {};
int CTime::m_nTime = NULL;

// �R���X�g���N�^
CTime::CTime(int nPriolity):CObject(nPriolity)
{
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);						
	m_ntime = 0;							
	m_ns = 0;
	m_min = 0;
	m_bTime = false;
}

// �f�X�g���N�^
CTime::~CTime()
{

}

// ����
CTime* CTime::Create(D3DXVECTOR3 pos)
{
	CTime* pTime = nullptr;
	pTime = new CTime;

	if (pTime != nullptr)
	{
		pTime->m_pos = pos;
		pTime->Init();
		return pTime;
	}
	else
	{
		return nullptr;
	}
}

//=====================
// ����������
//=====================
HRESULT CTime::Init(void)
{
	// �ʒu������������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ��
	m_min = MAX_MIN;

	m_nTime = 7200;

	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber1[nCnt] = new CNumber;
		m_pNumber1[nCnt]->Init(200.0f, 200.0f, nCnt,50.0f,50.0f, MAX_TIME,4, "data\\TEXTURE\\number005.png", 0.1f);

		m_pNumber2[nCnt] = new CNumber;
		m_pNumber2[nCnt]->Init(50.0f,50.0f, nCnt, 50.0f, 50.0f, MAX_TIME,4, "data\\TEXTURE\\number005.png",0.1f);
	}

	m_pNumber3 = new CNumber;
	m_pNumber3->Init(150.0f, 200.0f,0, 1.0f, 0.0f, 1,0, "data\\TEXTURE\\koron.png",1.0f);

	//CTime::SetTime(MAX_COUNTTIME);

	return S_OK;
}

//=============================================================================
// �^�C�}�[�̏I������
//=============================================================================
void CTime::Uninit(void)
{
	//�i���o�[�̔j��(�b)
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (m_pNumber1[nCnt] != NULL)
		{
			m_pNumber1[nCnt]->Uninit();
			delete m_pNumber1[nCnt];
			m_pNumber1[nCnt] = NULL;
		}
	}

	//�i���o�[�̔j��(��)
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (m_pNumber2[nCnt] != NULL)
		{
			m_pNumber2[nCnt]->Uninit();
			delete m_pNumber2[nCnt];
			m_pNumber2[nCnt] = NULL;
		}
	}

	//�i���o�[�̔j��(�F)
	if (m_pNumber3 != NULL)
	{
		m_pNumber3->Uninit();
		delete m_pNumber3;
		m_pNumber3 = NULL;
	}
	
	// �������g�̔j��
	CObject::Release();
}

//=============================================================================
// �^�C�}�[�̍X�V����
//=============================================================================
void CTime::Update(void)
{
	m_ns++;

	// 1�b�o��
	if (m_ns > 60)
	{
		SubNs(1);

		m_ns = 0;
	}

	// 1���o��
	if (m_ntime < 0)
	{
		if (m_min <= 0)
		{// 0��0�b�ɂȂ�����Q�[������

			m_bTime = true;
		}
		else
		{// ����ȊO
			SubNs(-60);

			SubMin(1);
		}
	}
	
	m_nTime--;
}

//=============================================================================
// �^�C�}�[�̕`�揈��
//=============================================================================
void CTime::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber1[nCnt]->Draw();
		m_pNumber2[nCnt]->Draw();
	}
	m_pNumber3->Draw();
}

//=============================================================================
// �^�C�}�[�̐ݒ菈��
//=============================================================================
void CTime::SetTime(int ntime)
{
	// �b��
	int aPosTexU[MAX_TIME] = {};	// �e���̐������i�[
	int nData = 100;				// 3��
	int nData1 = 10;				// 2��

	m_ntime += ntime;

	for (int nCnt1 = 0; nCnt1 < MAX_TIME; nCnt1++)
	{
		if (nCnt1 == 0)
		{
			// 0�Ԗڂ�������
			aPosTexU[0] = m_ntime / nData;
		}
		else
		{
			// 0�ԖڈȊO
			aPosTexU[nCnt1] = (m_ntime % nData) / nData1;
			nData = nData / 10;
			nData1 = nData1 / 10;
		}
		m_pNumber2[nCnt1]->SetNumber(aPosTexU[nCnt1],4);
	}

	int nData2 = 100;
	int nData3 =  10;

	for (int nCnt2 = 0; nCnt2 < MAX_TIME; nCnt2++)
	{
		if (nCnt2 == 0)
		{
			// 0�Ԗڂ�������
			aPosTexU[0] = m_min / nData2;
		}
		else
		{
			// 0�ԖڈȊO
			aPosTexU[nCnt2] = (m_min % nData2) / nData3;
			nData2 = nData2 / 10;
			nData3 = nData3 / 10;
		}
		m_pNumber1[nCnt2]->SetNumber(aPosTexU[nCnt2],4);
	}

}

//=============================================================================
// �^�C�}�[�̕b�Z����
//=============================================================================
void CTime::SubNs(int nValue)
{
	int aPosTexU[MAX_TIME] = {};	// �e���̐������i�[
	int nData = 100;				// 3��
	int nData1 = 10;				// 2��

	m_ntime -= nValue;

	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		// 0�ԖڈȊO
		aPosTexU[nCnt] = (m_ntime % nData) / nData1;
		nData = nData / 10;
		nData1 = nData1 / 10;

		m_pNumber1[nCnt]->SetNumber(aPosTexU[nCnt],4);

	}
}

//=============================================================================
// �^�C�}�[�̕����Z����
//=============================================================================
void CTime::SubMin(int nValue)
{
	int aPosTexU[MAX_TIME] = {};	// �e���̐������i�[
	int nData = 100;				// 3��
	int nData1 = 10;				// 2��

	m_min -= nValue;

	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		// 0�ԖڈȊO
		aPosTexU[nCnt] = (m_min % nData) / nData1;
		nData = nData / 10;
		nData1 = nData1 / 10;

		m_pNumber2[nCnt]->SetNumber(aPosTexU[nCnt],4);
	}
}

//=============================================================================
//�^�C�}�[�̕b�擾
//=============================================================================
int CTime::GetNs(void)
{
	return m_ntime;
}

//=============================================================================
//�^�C�}�[�̕��擾
//=============================================================================
int CTime::GetMin(void)
{
	return m_min;
}

//�ʒu�̐ݒ�
void CTime::SetPosition(D3DXVECTOR3 pos)
{
	m_SetPosition = pos;
}

// �ʒu���擾
D3DXVECTOR3 CTime::GetPosition(void)
{
	return m_SetPosition;
}
