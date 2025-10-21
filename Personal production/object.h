//=================================================
//
//	object.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

// �}�N��
#define MAX_OBJECT (256)
#define NUM_PRIORITY (20)

// �N���X
class CObject
{
public:

	// �^�C�v
	typedef enum
	{
		TYPE_NONE = 0,	// �����Ȃ�
		TYPE_PLAYER,	// �v���C���[
		TYPE_ENEMY,		// �G
		TYPE_BULLET,	// �e
		TYPE_BLOCK,		//�u���b�N
		TYPE_PAUSE,		// �|�[�Y
		TYPE_MAX		// �ő吔

	}TYPE;


	typedef struct
	{
		D3DXVECTOR3 pos;//���_���W
		float rhw;		//���p�ϊ��p�W��(1.0f�ŌŒ�)
		D3DCOLOR col;	//���_�J���[
		D3DXVECTOR2 tex;//�e�N�X�`�����W

	}VERTEX_2D;

	typedef struct
	{
		D3DXVECTOR3 pos;	//���_���W
		D3DXVECTOR3 nor;	//�@���x�N�g��
		D3DCOLOR col;		//���_�J���[
		D3DXVECTOR2 tex;	//�e�N�X�`�����W
	}VERTEX_3D;

	CObject(int nPriority = 0);
	//CObject(int nPriority);

	virtual ~CObject();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;
	virtual D3DXVECTOR3 GetPosition(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static int Getobject(void);
	void SetType(TYPE type);
	TYPE GetType(void);
	static CObject* Getobject(int nIdx);
	D3DXVECTOR3 SetSize(D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin, int nNumVtx, DWORD sizeFVF, BYTE* pVtxBuff);
	static CObject* GetTop(int nPriority);
	CObject* GetNext(void);
protected:

	void Release(void);

private:
	static CObject* m_apTop[NUM_PRIORITY];		//�擪�I�u�W�F�N�g�ւ̃|�C���^
	static CObject* m_apCur[NUM_PRIORITY];		//�Ō���I�u�W�F�N�g�ւ̃|�C���^
	CObject* m_pPrev;							//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject* m_pNext;							//���̃I�u�W�F�N�g�ւ̃|�C���^
	static int m_nNumAll;						//�ő吔
	//int m_nID;									//�����̔z���ۑ�
	TYPE m_type;								//�ύX�_�̒��������₷������
	int m_nPriority;							//�X�����ʂ̑���
	bool m_bDeath;								//���S�t���O
};
#endif
