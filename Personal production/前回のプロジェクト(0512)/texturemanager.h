//=================================================
//
//	TextureManager.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "main.h"

class CTextureManager
{
public:
	CTextureManager();
	~CTextureManager();
	HRESULT Load(void);
	void Unload(void);
	int Register(const char* pFilename);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);
private:
	LPDIRECT3DTEXTURE9 m_apTex[MAX_TEXTURE];	// �e�N�X�`���̃|�C���^
	static int m_nNumAll;						// ����
	const char* m_pName[MAX_TEXTURE];						// ���O
};
#endif