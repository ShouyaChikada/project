//=================================================
//
//	ObjectX.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "objectx.h"
#include "manager.h"
#include "texturemanager.h"

//静的メンバ変数
const char* CObjectX::m_txt = {};

// コンストラクタ
CObjectX::CObjectX(int nPriolty):CObject(nPriolty)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_pTexture[nCnt] = NULL;
		m_nIdx[nCnt] = NULL;
	}
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;	
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_txt = NULL;
	m_pModel = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&m_mtxRot);

	m_fValueRot = 0.0f;
	m_VecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

// デストラクタ
CObjectX::~CObjectX()
{

}

// 生成
CObjectX* CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt)
{
	//int nNumAll = Getobject();

	//if (nNumAll < MAX_OBJECT - 1)
	//{
		CObjectX* pObjectX = NULL;
		pObjectX = new CObjectX;
		pObjectX->m_pos = pos;
		pObjectX->m_rot = D3DXToRadian(rot);
		pObjectX->m_txt = txt;
		pObjectX->Init();
		return pObjectX;
	//}
	//return NULL;
}

//================================
// 初期化処理
//================================
HRESULT CObjectX::Init(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャマネージャーの取得
	CTextureManager* pTex = CManager::GetTexManager();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(m_txt,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	m_fValueRot = 0.01f;

	D3DXMATERIAL *pMat = nullptr;	//マテリアルへのポインタ

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{//テクスチャファイルが存在する
				//テクスチャの読み込み
			//	D3DXCreateTextureFromFile(pDevice,
			//		pMat[nCntMat].pTextureFilename,
			//		&m_pTexture[nCntMat]);
			m_nIdx[nCntMat] = pTex->Register(pMat[nCntMat].pTextureFilename);
		}
	}

	return S_OK;
}
//================================
// 終了処理
//================================
void CObjectX::Uninit(void)
{
	//メッシュの破棄
	if (m_pMesh != NULL)
	{	   
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//マテリアルの破棄
	if (m_pBuffMat != NULL)
	{	   
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	
	//// テクスチャの破棄
	//for (int nCnt = 0; nCnt < (int)m_dwNumMat; nCnt++)
	//{
	//	if (m_pTexture[nCnt] != NULL)
	//	{
	//		m_pTexture[nCnt]->Release();
	//		m_pTexture[nCnt] = NULL;
	//	}
	//}
	
	//自分の破棄
	CObject::Release();
}
//================================
// 更新処理
//================================
void CObjectX::Update(void)
{
	//移動とモーションのセット
	SetInput();

	//float fCirc = 2.0f * D3DX_PI * 5.0f;

	//m_move.y = (fValueRot / (2 * D3DX_PI)) * fCirc;
	//m_move.z = (fValueRot / (2 * D3DX_PI)) * fCirc;

	//角度の正規化
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = m_rot.y + D3DX_PI;
		m_rot.y = D3DX_PI + m_rot.y;
	}
	else if (m_rot.y > D3DX_PI)
	{
		m_rot.y = m_rot.y - D3DX_PI;
		m_rot.y = -D3DX_PI - m_rot.y;

	}

	//角度の調整
	m_Diff = m_rotDest.y - m_rot.y;

	if (m_Diff < -D3DX_PI)
	{
		m_Diff = m_Diff + (D3DX_PI * 2);
	}
	else if (m_Diff > D3DX_PI)
	{
		m_Diff = m_Diff - (D3DX_PI * 2);
	}

	//プレイヤーの向き
	m_rot.y += m_Diff * 0.25f;

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.5f;
	m_move.z += (0.0f - m_move.z) * 0.5f;

	//前回の位置を保存	位置更新の上で書く
	m_posOld = m_pos;


	m_pos += m_move;

	////重力
	//if (m_pos.y < -600.0f)
	//{
	//	m_pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	//	m_move.y = 0.0f;
	//	m_bJump = false;
	//}
}
//================================
// 描画処理
//================================
void CObjectX::Draw(void)
{
	CTextureManager* pTex = CManager::GetTexManager();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//マルチターゲット
	LPDIRECT3DTEXTURE9 pTexMT;

	D3DXMATRIX mtxRot, mtxTrans;						// 計算用マトリックス
	D3DMATERIAL9 matDef;								// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;									// マテリアルデータへのポインタ
	D3DXQUATERNION quat;								// クォータニオン
	D3DXVECTOR3 vecAxis = D3DXVECTOR3(0.0f,1.0f,0.0f);	// 回転軸
	float fValueRot = 0.0f;								// 回転角(回転量)
	fValueRot = D3DX_PI * 0.001f;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転軸のおける指定の回転角からクォータニオンを作成
	D3DXQuaternionRotationAxis(&quat, &vecAxis, fValueRot);

	// クォータニオンから回転マトリックスの作成
	D3DXMatrixRotationQuaternion(&mtxRot, &quat);

	// 現在の回転量に次の回転量を加える
	D3DXMatrixMultiply(&m_mtxRot, &m_mtxRot, &mtxRot);
	
	// 次の回転量をワールドマトリックスの加える
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	// 位置のマトリックスの作成
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	// ワールドマトリックスに位置のマトリックスを加える
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		pTexMT = CManager::GetRenderer()->GetTextureMT();

		//テクスチャの設定
		pDevice->SetTexture(0, pTex->GetAddress(m_nIdx[nCntMat]));

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを隠す
	pDevice->SetMaterial(&matDef);
}

LPD3DXMESH CObjectX::GetMesh(void)
{
	return m_pMesh;
}

//============================
// 移動処理
//============================
void CObjectX::SetInput(void)
{
	//D3DXVec3Cross();
	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	//カメラの情報取得
	CCamera* pCamera = CManager::GetCamera();
	D3DXVECTOR3 rot = pCamera->GetRotasion();

	pCamera->SetFollowing(m_pos, m_rotDest);

	//左移動
	if (pInputKeyboard->GetPress(DIK_A) == true)
	{

		//前移動
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			m_rotDest.y = rot.y + D3DX_PI * 0.75f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;

			//m_rot.z = 0.19625f;

		}
		//後ろ移動
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{

			m_rotDest.y = rot.y + D3DX_PI * 0.25f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;

		}
		else
		{
			m_rotDest.y = rot.y + D3DX_PI * 0.5f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;

		}
	}
	//右移動
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		//前移動
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			m_rotDest.y = rot.y - D3DX_PI * 0.75f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		//後ろ移動
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{
			m_rotDest.y = rot.y - D3DX_PI * 0.25f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		else
		{

			m_rotDest.y = rot.y - D3DX_PI * 0.5f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
	}
	//前移動
	if (pInputKeyboard->GetPress(DIK_W) == true)
	{

		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		//前移動
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		else
		{
			m_rotDest.y = rot.y + D3DX_PI;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
	}
	//後ろ移動
	if (pInputKeyboard->GetPress(DIK_S) == true)
	{

		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		//前移動
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		else
		{
			m_rotDest.y = rot.y;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;

		}
	}
}