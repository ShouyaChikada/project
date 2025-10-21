//=================================================
//
//	input.cpp
// 
// Author:�ߓc����
//
//=================================================
#include"input.h"

//�ÓI�����o�ϐ�
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}
//�R���X�g���N�^
CInput::CInput()
{
	m_pDevice = NULL;
}

//�f�X�g���N�^
CInput::~CInput()
{

}

//�L�[�{�[�h�̏���������
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInput
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}
//�L�[�{�[�h�̏I������
void CInput::Uninit(void)
{
	//���̓f�o�C�X
	if (m_pDevice != NULL)
	{
		//�A�N�Z�X���̔j��
		m_pDevice->Unacquire();

		//�f�o�C�X�̔j��
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	//Direct
	if (m_pInput != NULL)
	{
		//�I�u�W�F�N�g�̔j��
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//�X�V����
void CInput::Update(void)
{

}
//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�R���X�g���N�^
CInputKeyboard::CInputKeyboard()
{
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = NULL;
		m_aOldState[nCnt] = NULL;
	}
}

//�f�X�g���N�^
CInputKeyboard::~CInputKeyboard()
{

}

HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//�f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}
//�L�[�{�[�h�̍X�V����
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;
	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aOldState[nCntKey] = m_aKeyState[nCntKey];
	}
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}

}
//�L�[�{�[�h�̃v���X���
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//�L�[�{�[�h�g���K�[
bool CInputKeyboard::GetTrigger(int nKey)
{
	bool Trigger = false;
	if ((m_aKeyState[nKey] & 0x80) && !(m_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===================================================================================
//�R���X�g���N�^
CInputJoypad::CInputJoypad()
{
	m_joykeyState;
	m_joykeyStateTrigger;
}

//�f�X�g���N�^
CInputJoypad::~CInputJoypad()
{

}

//�W���C�p�b�h�̏�����
HRESULT CInputJoypad::Init(void)
{
	//�������̃N���A
	memset(&m_joykeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_joykeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//Xinput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}

//�W���C�p�b�h�̏I������
void CInputJoypad::Uninit(void)
{
	//XInput�̃X�e�[�g�ݒ�(�����ɂ���)
	XInputEnable(false);
}

//�W���C�p�b�h�̍X�V����
void CInputJoypad::Update(void)
{
	XINPUT_STATE joykeyState;	//�W���C�p�b�h�̓��͏��

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = m_joykeyState.Gamepad.wButtons;

		m_joykeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;
		m_joykeyState = joykeyState;	//�W���C�p�b�h�̃v���X���̕ۑ�
	}
}

//�W���C�p�b�h�̃v���X����ۑ�
bool CInputJoypad::GetPress(KEY key)
{
	return (m_joykeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//�W���C�p�b�h�̃g���K�[
bool CInputJoypad::GetTrigger(KEY key)
{
	return (m_joykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//==========================================================================================

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//�R���X�g���N�^
CInputMouse::CInputMouse()
{
	m_CurrentMouseState = {};
	m_PrevMouseState = {};
	m_aOldMouseState = {};
}

//�f�X�g���N�^
CInputMouse::~CInputMouse()
{

}

//=====================================
// �}�E�X�̏���������
//=====================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// �������[�h
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}
//=====================================
// �}�E�X�̏I������
//=====================================
void CInputMouse::Uninit(void)
{
	CInput::Uninit();
}
//=====================================
// �}�E�X�̍X�V����
//=====================================
void CInputMouse::Update(void)
{
	m_aOldMouseState.lX = m_CurrentMouseState.lX;
	m_aOldMouseState.lY = m_CurrentMouseState.lY;

	// �X�V�O�ɍŐV�}�E�X����ۑ�����
	m_PrevMouseState = m_CurrentMouseState;

	// �ŐV�̃}�E�X�̏�Ԃ��X�V
	HRESULT	hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState);

	if (FAILED(hr))
	{
		m_pDevice->Acquire();
	}

	// �}�E�X���W���擾����
	POINT p;
	GetCursorPos(&p);

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
	ScreenToClient(FindWindowA(CLASS_NAME, WINDOW_NAME), &p);

	m_CurrentMouseState.lX = p.x;
	m_CurrentMouseState.lY = p.y;

#if 0
	m_aOldMouseState.lX = m_CurrentMouseState.lX;
	m_aOldMouseState.lY = m_CurrentMouseState.lY;

	// �X�V�O�ɍŐV�}�E�X����ۑ�����
	m_PrevMouseState = m_CurrentMouseState;

	// �ŐV�̃}�E�X�̏�Ԃ��X�V
	HRESULT	hr1 = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState);

	if (FAILED(hr1))
	{
		m_pDevice->Acquire();
	}

	POINT p;
	GetCursorPos(&p);

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &p);

	m_CurrentMouseState.lX = p.x;
	m_CurrentMouseState.lY = p.y;
#endif
}
//=====================================
// �}�E�X�������ꂽ����
//=====================================
bool CInputMouse::OnDown(MouseButton button_type)
{
	if (!(m_PrevMouseState.rgbButtons[button_type] & 0x80) &&
		m_CurrentMouseState.rgbButtons[button_type] & 0x80)
	{
		return true;
	}

	return false;
}
bool CInputMouse::OnDownL(MouseButton button_type)
{
	if (m_CurrentMouseState.rgbButtons[button_type] & (0x80))
	{
		// ���N���b�N��
		return true;
	}
	return false;
}
bool CInputMouse::OnDownR(MouseButton button_type)
{
	if (m_CurrentMouseState.rgbButtons[button_type] & (0x80))
	{
		// �E�N���b�N��
		return true;
	}
	return false;
}
bool CInputMouse::OnDownWheel(MouseButton button_type)
{
	if (m_CurrentMouseState.rgbButtons[button_type] & (0x80))
	{
		// �E�N���b�N��
		return true;
	}
	return false;
}
//=====================================
// �}�E�X�������ꂽ����
//=====================================
bool CInputMouse::OnUp(MouseButton button_type)
{
	if (m_PrevMouseState.rgbButtons[button_type] & 0x80 &&
		!(m_CurrentMouseState.rgbButtons[button_type] & 0x80))
	{
		return true;
	}

	return false;
}
bool CInputMouse::OnUpL(MouseButton button_type)
{
	//if (!m_CurrentMouseState.rgbButtons[0] & (0x80))
	//{
	//	return true;
	//}

	return false;
}
bool CInputMouse::OnUpR(MouseButton button_type)
{
	//if (!m_CurrentMouseState.rgbButtons[1] & (0x80))
	//{
	//	return true;
	//}

	return false;
}

D3DXVECTOR2 CInputMouse::GetVelocity()
{
	return D3DXVECTOR2((float)m_CurrentMouseState.lX, (float)m_CurrentMouseState.lY);
}

D3DXVECTOR2 CInputMouse::GetVelocityOld()
{
	return D3DXVECTOR2((float)m_aOldMouseState.lX, (float)m_aOldMouseState.lY);
}
