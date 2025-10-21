//=================================================
//
//	input.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//�}�N����`
#define NUM_KEY_MAX (256)

class CInput
{
public:
	//======================
	// �}�E�X�̎��
	//======================
	typedef enum
	{
		MOUSE_L = 0, // �}�E�X��
		MOUSE_R,     // �}�E�X�E
		MOUSE_WHEEL,     // �}�E�X�z�C�[��
		MOUSE_MAX
	}MouseButton;

	
	
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void);

protected:

	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};


class CInputKeyboard :public CInput
{
public:

	CInputKeyboard();
	~CInputKeyboard();
	//�L�[�{�[�h�̃v���g�^�C�v�錾
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aOldState[NUM_KEY_MAX];
};

class CInputJoypad :public CInput
{
public:
	//===================
//�p�b�h�̎��
//===================
	typedef enum
	{
		KEY_UP = 0,	//�\���L�[(��)
		KEY_DOWN,	//�\���L�[(��)
		KEY_LEFT,	//�\���L�[(��)
		KEY_RIGHT,	//�\���L�[(�E)
		KEY_START,	//START�L�[
		KEY_BACK,
		KEY_L3,
		KEY_R3,
		KEY_L1,
		KEY_R1,
		KEY_L2,
		KEY_R2,
		KEY_A,
		KEY_B,
		KEY_X,
		KEY_Y,
		KEY_MAX

	}KEY;

	//�W���C�p�b�h�̃v���g�^�C�v�錾

	CInputJoypad();
	~CInputJoypad();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	bool GetPress(KEY key);
	bool GetTrigger(KEY key);

private:
	XINPUT_STATE m_joykeyState; //�W���C�p�b�h�̃v���X���
	XINPUT_STATE m_joykeyStateTrigger; //�W���C�p�b�h�̃v���X���
};


class CInputMouse :public CInput
{
public:

	// �}�E�X
	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool OnDown(MouseButton button_type);
	bool OnDownL(MouseButton button_type);
	bool OnDownR(MouseButton button_type);
	bool OnDownWheel(MouseButton button_type);
	bool OnUp(MouseButton button_type);
	bool OnUpL(MouseButton button_type);
	bool OnUpR(MouseButton button_type);
	D3DXVECTOR2 GetVelocity();
	D3DXVECTOR2 GetVelocityOld();
private:
	BYTE m_aMauseState;
	//BYTE m_aOldMauseState;
	DIMOUSESTATE m_CurrentMouseState;		                //!< �}�E�X�̌��݂̓��͏��
	DIMOUSESTATE m_PrevMouseState;			                //!< �}�E�X�̈�t���[���O�̓��͏��
	DIMOUSESTATE m_aOldMouseState;		                        //!< �}�E�X�̌��݂̓��͏��

};



#endif


