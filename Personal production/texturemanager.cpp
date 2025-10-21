//=================================================
//
//	TextureManager.cpp
// 
//	Author:�ߓc����
//
//=================================================
#include "texturemanager.h"
#include "manager.h"

// �ÓI�����o�ϐ�
int CTextureManager::m_nNumAll = NULL;

// �R���X�g���N�^
CTextureManager::CTextureManager()
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_apTex[nCnt] = nullptr;
		m_pName[nCnt] = {};
	}
}

// �f�X�g���N�^
CTextureManager::~CTextureManager()
{

}

// �ǂݍ���
HRESULT CTextureManager::Load()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	const char* TexName[MAX_TEXTURE] =
	{
		//------------------------------------
		"data\\TEXTURE\\inseki.jpg",				//	0
		"data\\TEXTURE\\effect000.jpg",				//	1
		"data\\TEXTURE\\sky000.jpg",				//	2
		"data\\TEXTURE\\title.jpg",					//	3
		"data\\TEXTURE\\title5.png",				//	4
		"data\\TEXTURE\\title1.png",				//	5
		"data\\TEXTURE\\sea1.jpg",					//	6
		"data\\TEXTURE\\sea02s.jpg",				//	7
		"data\\TEXTURE\\number005.png",				//	8
		"data\\TEXTURE\\ue.jpg",					//	9
		//------------------------------------			
		"data\\TEXTURE\\ue1.jpg",					//	10
		"data\\TEXTURE\\ue2.jpg",					//	11
		"data\\TEXTURE\\ue3.jpg",					//	12
		"data\\TEXTURE\\kabe.jpg",					//	13
		"data\\TEXTURE\\kabe1.jpg",					//	14
		"data\\TEXTURE\\kabe2.jpg",					//	15
		"data\\TEXTURE\\kabe3.jpg",					//	16
		"data\\TEXTURE\\renga1.jpg",				//	17
		"data\\TEXTURE\\face3.png",					//	18
		"data\\TEXTURE\\kaminari.jpg",				//	19
		//------------------------------------			
		"data\\TEXTURE\\moyou.png",					//	20
		"data\\TEXTURE\\red1.png",					//	21
		"data\\TEXTURE\\koron.png",					//	22
		"data\\TEXTURE\\Tumbase.png",				//	23
		"data\\TEXTURE\\YellowGauge.png",			//	24
		"data\\TEXTURE\\check1.png",				//	25
		"data\\TEXTURE\\continue2.png",				//	26
		"data\\TEXTURE\\retry2.png",				//	27
		"data\\TEXTURE\\quit2.png",					//	28
		"data\\TEXTURE\\brack.png",					//	29
		//------------------------------------			
		"data\\TEXTURE\\MasicCircle.png",			//	30
		"data\\TEXTURE\\humanface.jpg",				//	31
		"data\\TEXTURE\\result.jpg",				//	32
		"data\\TEXTURE\\tutorial.jpg",
		"data\\TEXTURE\\rock000.jpg",
		//------------------------------------			
	};											  

	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (TexName[nCnt] != nullptr)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				TexName[nCnt],
				&m_apTex[nCnt]);

			m_pName[nCnt] = TexName[nCnt];
		}
	}
	return S_OK;
}

// �j��
void CTextureManager::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//�e�N�X�`����NULL����Ȃ�������
		if (m_apTex[nCnt] != NULL)
		{
			//�I��
			m_apTex[nCnt]->Release();
			m_apTex[nCnt] = NULL;
		}

	}
}

int CTextureManager::Register(const char* pFilename)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (pFilename != nullptr)
		{
			if (strcmp(pFilename, m_pName[nCnt]) == 0)
			{
				return nCnt;
			}
		}
	}
	return -1;
}

LPDIRECT3DTEXTURE9 CTextureManager::GetAddress(int nIdx)
{
	return m_apTex[nIdx];
}