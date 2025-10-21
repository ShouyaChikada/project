//=================================================
//
//	object2D.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "object.h"

//�h���N���X
class CObject2D:public CObject
{
public:
	//���
	typedef enum
	{
		STATE_NONE = 0,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	// ���_�����̎��
	enum ANCHORTYPE
	{
		ANCHORTYPE_CENTER,
		ANCHORTYPE_LEFT,
		ANCHORTYPE_RIGHT,
		ANCHORTYPE_UP,
		ANCHORTYPE_DOWN,
		ANCHORTYPE_MAX
	};

	CObject2D(int nPriolty = 3);
	~CObject2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetTex(float aUV, float zUV);
	void SetAnim(D3DXVECTOR2 UV,float fSizeX,float fSizeY);
	void SetAnim(float aTex, float fAdd);
	void SetSize(float fWidth, float fHeight);
	void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius);
	void SetType(int nType) { m_nType = nType; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	static CObject2D* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,float fWidth,float fHeight,D3DXCOLOR col);
	void Set2Dpolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col);
	D3DXVECTOR3 GetPosition(void);

	void UpdateCenter(void);
	void UpdateLeft(void);
	//void UpdateCenter(void);

	void SetCol(D3DXCOLOR col) { m_col = col; }
	void Setcol(D3DXCOLOR col);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXCOLOR m_col;					// ���_�J���[
	float m_fAngle;						// �p�x
	float m_fLength;					// ����
	float m_aUV;						// ���l
	float m_zUV;						// ���l
	float m_Width;					// ���̃T�C�Y
	float m_Height;					// �c�̃T�C�Y
	int m_nType;						// ���_�����̎�� 
};
#endif
