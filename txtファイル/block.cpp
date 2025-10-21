//=============================
//
// ブロック処理 [block.cpp]
// Author: Asuma Nishio
// 
//=============================

//****************************
// インクルードファイル宣言
//****************************
#include "input.h"
#include "block.h"
#include <stdio.h>

//*****************************
// マクロ定義
//*****************************
#define HALF (0.5f)					// 半分の値

//*****************************
// グローバル変数宣言
//*****************************
LPDIRECT3DTEXTURE9 g_apTextureBlock[128] = {};	// テクスチャのポインタ
Block g_Block[BLOCKTYPE_MAX][MAX_BLOCK];		// 構造体変数
int g_nCntBlockSet = 0;

//=========================
//　ブロック初期化処理
//=========================
void InitBlock(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 構造体変数の初期化
	for (int nCnt1 = 0; nCnt1 < BLOCKTYPE_MAX; nCnt1++)
	{
		for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
		{
			g_Block[nCnt1][nCnt].bUse = false;
			g_Block[nCnt1][nCnt].nType = BLOCKTYPE_GROUND;
			g_Block[nCnt1][nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Block[nCnt1][nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
	// 変数の初期化
	g_nCntBlockSet = 0;

	for (int nCnt1 = 0; nCnt1 < BLOCKTYPE_MAX; nCnt1++)
	{
		for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
		{
			// Xファイルの描画
			D3DXLoadMeshFromX(BLOCK_FILE[nCnt1],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Block[nCnt1][nCnt].pBuffMat,
				NULL,		   
				&g_Block[nCnt1][nCnt].dwNumMat,
				&g_Block[nCnt1][nCnt].pMesh);

		}

	}

	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{
		for (int nCnt3 = 0; nCnt3 < MAX_BLOCK; nCnt3++)
		{// 頂点数

			// ローカル変数宣言-----------------------------
			int nNumVtx;		// 頂点数
			DWORD sizeFVF;		// 頂点フォーマットのサイズ
			BYTE* pVtxBuff;		// 頂点バッファのポインタ
			//----------------------------------------------

			// 頂点数の取得
			nNumVtx = g_Block[nCnt][nCnt3].pMesh->GetNumVertices();

			// 頂点のサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_Block[nCnt][nCnt3].pMesh->GetFVF());

			// 頂点バッファをロック
			g_Block[nCnt][nCnt3].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			// 頂点数分回す
			for (int nCntBlock = 0; nCntBlock < nNumVtx; nCntBlock++)
			{
				// 頂点座標の代入
				D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

				// 頂点座標の比較
				if (Vtx.x > g_Block[nCnt][nCnt3].Vtxmax.x)
				{// xが最大値より大きかったら
					// 代入
					g_Block[nCnt][nCnt3].Vtxmax.x = Vtx.x;
				}
				if (Vtx.y > g_Block[nCnt][nCnt3].Vtxmax.y)
				{// yが最大値より大きかったら
					// 代入
					g_Block[nCnt][nCnt3].Vtxmax.y = Vtx.y;
				}
				if (Vtx.z > g_Block[nCnt][nCnt3].Vtxmax.z)
				{// zが最大値より大きかったら
					// 代入
					g_Block[nCnt][nCnt3].Vtxmax.z = Vtx.z;
				}

				if (Vtx.x < g_Block[nCnt][nCnt3].Vtxmin.x)
				{// xが最小値より小さかったら
					// 代入
					g_Block[nCnt][nCnt3].Vtxmin.x = Vtx.x;
				}
				if (Vtx.y < g_Block[nCnt][nCnt3].Vtxmin.y)
				{// yが最小値より小さかったら
					// 代入
					g_Block[nCnt][nCnt3].Vtxmin.y = Vtx.y;
				}
				if (Vtx.z < g_Block[nCnt][nCnt3].Vtxmin.z)
				{// zが最小値より小さかったら
					// 代入
					g_Block[nCnt][nCnt3].Vtxmin.z = Vtx.z;
				}

				// 頂点フォーマットのサイズ分進める
				pVtxBuff += sizeFVF;
			}

			// サイズを代入する
			g_Block[nCnt][nCnt3].size.x = g_Block[nCnt][nCnt3].Vtxmax.x - g_Block[nCnt][nCnt3].Vtxmin.x;	// sizeのx
			g_Block[nCnt][nCnt3].size.y = g_Block[nCnt][nCnt3].Vtxmax.y - g_Block[nCnt][nCnt3].Vtxmin.y;	// sizeのy
			g_Block[nCnt][nCnt3].size.z = g_Block[nCnt][nCnt3].Vtxmax.z - g_Block[nCnt][nCnt3].Vtxmin.z;	// sizeのz

			// アンロック
			g_Block[nCnt][nCnt3].pMesh->UnlockVertexBuffer();

			// マテリアルデータへのポインタ
			D3DXMATERIAL* pMat;

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Block[nCnt][nCnt3].pBuffMat->GetBufferPointer();

			// マテリアル数だけ回す
			for (int nCntMat = 0; nCntMat < (int)g_Block[nCnt][nCnt3].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_apTextureBlock[nCntMat]);
				}
			}
		}
	}
}
//=========================
//　ブロック終了処理
//=========================
void UninitBlock(void)
{
	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{
		for (int nCnt1 = 0; nCnt1 < MAX_BLOCK; nCnt1++)
		{
			// メッシュの破棄
			if (g_Block[nCnt][nCnt1].pMesh != NULL)
			{				 
				g_Block[nCnt][nCnt1].pMesh->Release();
				g_Block[nCnt][nCnt1].pMesh = NULL;
			}

			// マテリアルの破棄
			if (g_Block[nCnt][nCnt1].pBuffMat != NULL)
			{				
				g_Block[nCnt][nCnt1].pBuffMat->Release();
				g_Block[nCnt][nCnt1].pBuffMat = NULL;
			}
		}
	}

	// テクスチャの破棄
	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{
		if (g_apTextureBlock[nCnt] != NULL)
		{
			g_apTextureBlock[nCnt]->Release();
			g_apTextureBlock[nCnt] = NULL;
		}
	}
}
//=========================
//　ブロック更新処理
//=========================
void UpdateBlock(void)
{
	// 一旦なし
}
//=========================
//　ブロック描画処理
//=========================
void DrawBlock(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを取得
	pDevice = GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans,mtxScall;

	// 現在のマテリアルを保存
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{
		for (int nCnt1 = 0; nCnt1 < MAX_BLOCK; nCnt1++)
		{
			if (!g_Block[nCnt][nCnt1].bUse)
			{// 未使用
				continue;
			}

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Block[nCnt][nCnt1].mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block[nCnt][nCnt1].rot.y, g_Block[nCnt][nCnt1].rot.x, g_Block[nCnt][nCnt1].rot.z);
			D3DXMatrixMultiply(&g_Block[nCnt][nCnt1].mtxWorld, &g_Block[nCnt][nCnt1].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Block[nCnt][nCnt1].pos.x, g_Block[nCnt][nCnt1].pos.y, g_Block[nCnt][nCnt1].pos.z);
			D3DXMatrixMultiply(&g_Block[nCnt][nCnt1].mtxWorld, &g_Block[nCnt][nCnt1].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Block[nCnt][nCnt1].mtxWorld);

			// 現在のマトリックスの取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Block[nCnt][nCnt1].pBuffMat->GetBufferPointer();

			// マテリアル数だけ回す
			for (int nCntMat = 0; nCntMat < (int)g_Block[nCnt][nCnt1].dwNumMat; nCntMat++)
			{
				// マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャ設定
				pDevice->SetTexture(0, g_apTextureBlock[nCntMat]);

				// モデル(パーツ)の描画
				g_Block[nCnt][nCnt1].pMesh->DrawSubset(nCntMat);

			}
			// マテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}

	}
}
//=============================
//　ブロックの当たり判定処理
//=============================
void CollisionBlock(void)
{
	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{
		for (int nCnt1 = 0; nCnt1 < MAX_BLOCK; nCnt1++)
		{// 最大数分回す
			// プレイヤーの取得
			PLAYER* pPlayer = GetPlayer();

			if (g_Block[nCnt][nCnt1].bUse)
			{// 使用判定の時

				if (pPlayer->pos.y < g_Block[nCnt][nCnt1].pos.y + g_Block[nCnt][nCnt1].size.y &&
					pPlayer->pos.y + pPlayer->size.y > g_Block[nCnt][nCnt1].pos.y - g_Block[nCnt][nCnt1].size.y)
				{
					// 左右の当たり判定----------------------
					if (pPlayer->posOld.z - pPlayer->size.z * HALF < g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF &&
						pPlayer->pos.z + pPlayer->size.z * HALF > g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * HALF)
					{
						// 左からめり込む
						if (pPlayer->posOld.x + pPlayer->size.x * HALF < g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF &&
							pPlayer->pos.x + pPlayer->size.x * HALF > g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF)
						{
							pPlayer->pos.x = g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF - pPlayer->size.x * HALF - 0.1f;

						}
						// 右からめり込む
						else if (pPlayer->posOld.x - pPlayer->size.x * HALF > g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * HALF &&
							pPlayer->pos.x - pPlayer->size.x * HALF < g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * HALF)
						{
							pPlayer->pos.x = g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * 0.5f + pPlayer->size.x * HALF + 0.1f;
						}
					}

					// 前後の当たり判定------------------------------
					if (pPlayer->posOld.x - pPlayer->size.z * HALF < g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * HALF &&
						pPlayer->pos.x + pPlayer->size.x * HALF > g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF)
					{
						// 手前からめり込む
						if (pPlayer->posOld.z + pPlayer->size.z * HALF < g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * HALF &&
							pPlayer->pos.z + pPlayer->size.z * HALF > g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * HALF)
						{
							pPlayer->pos.z = g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * 0.5f - pPlayer->size.z * HALF - 0.3f;

						}
						// 奥からめり込む
						else if (pPlayer->posOld.z - pPlayer->size.z * HALF > g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF &&
							pPlayer->pos.z - pPlayer->size.z * HALF < g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF)
						{
							pPlayer->pos.z = g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF + pPlayer->size.z * HALF + 0.3f;

						}
					}
					// 縦の当たり判定--------------------------
					if (pPlayer->pos.x - pPlayer->size.x * HALF < g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * HALF &&
						pPlayer->pos.x + pPlayer->size.x * HALF > g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF)
					{
						if (pPlayer->posOld.z - pPlayer->size.z * HALF < g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF &&
							pPlayer->pos.z + pPlayer->size.z * HALF > g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * HALF)
						{
							// 上からめり込んだ時
							if (pPlayer->posOld.y >= g_Block[nCnt][nCnt1].pos.y + g_Block[nCnt][nCnt1].size.y * HALF &&
								pPlayer->pos.y < g_Block[nCnt][nCnt1].pos.y + g_Block[nCnt][nCnt1].size.y * HALF)
							{
								pPlayer->bLanding = true;	// ジャンプ
								pPlayer->pos.y = (g_Block[nCnt][nCnt1].pos.y + g_Block[nCnt][nCnt1].size.y * HALF);
								pPlayer->move.y = 0.0f;

							}
							// 下からめり込んだ時
							else if (pPlayer->posOld.y + pPlayer->size.y <= g_Block[nCnt][nCnt1].pos.y - g_Block[nCnt][nCnt1].size.y * HALF &&
								pPlayer->pos.y + pPlayer->size.y > g_Block[nCnt][nCnt1].pos.y - g_Block[nCnt][nCnt1].size.y * HALF)
							{
								pPlayer->pos.y = (g_Block[nCnt][nCnt1].pos.y - g_Block[nCnt][nCnt1].size.y) - pPlayer->size.y * HALF;
								pPlayer->move.y = 0.0f;
							}
						}
					}
				}
			}
		}

	}
}
//=============================
//　ブロックの設定処理
//=============================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot,BLOCKTYPE nType)
{
	for (int nCnt1 = 0; nCnt1 < MAX_BLOCK; nCnt1++)
	{
		if (!g_Block[nType][nCnt1].bUse)
		{
			// 未使用なら
			g_Block[nType][nCnt1].pos = pos;	// 座標
			g_Block[nType][nCnt1].rot = rot;	// 角度
			g_Block[nType][nCnt1].nType = nType;	// 種類
			g_Block[nType][nCnt1].bUse = true;	// 使用判定

			break;
		}

	}

	
}
//=========================
// ファイルの読み込み処理(一旦保留)
//=========================
#if 0
void LoadBlock(void)
{

	// ファイルポインタを宣言
	FILE* pFile;

	// ファイルを開く
	pFile = fopen("Block/SetBlock.txt", "r");

	if (pFile != NULL)
	{/// ファイルが開けたら
		char aStr[MAX_WORD] = {};		// 文字型の変数

		while (1)
		{
			//読み取り
			fscanf(pFile, "%s", aStr);

			if (strcmp("BLOCKSET", aStr) == 0)
			{// BLOCKSETを読み取ったら

				while (1)
				{
					// 読み取り
					fscanf(pFile, "%s", aStr);

					if (strcmp("BLOCKTYPE", aStr) == 0)
					{// BLOCKTYPEを読み取ったら
						// 値を代入
						fscanf(pFile, "%d", &g_Block[g_nCntBlockSet].nType);
					}

					else if (strcmp("POS", aStr) == 0)
					{// POSを読み取ったら
						// 値を代入
						fscanf(pFile, "%f", &g_Block[g_nCntBlockSet].pos.x);
						fscanf(pFile, "%f", &g_Block[g_nCntBlockSet].pos.y);
						fscanf(pFile, "%f", &g_Block[g_nCntBlockSet].pos.z);
					}

					else if (strcmp("ROT", aStr) == 0)
					{// ROTを読み取ったら
						// 値を代入
						fscanf(pFile, "%f", &g_Block[g_nCntBlockSet].rot.x);
						fscanf(pFile, "%f", &g_Block[g_nCntBlockSet].rot.y);
						fscanf(pFile, "%f", &g_Block[g_nCntBlockSet].rot.z);
					}

					else if (strcmp("END_BLOCKSET", aStr) == 0)
					{// END_BLOCKSETを読み取ったら
						SetBlock(g_Block[g_nCntBlockSet].pos, g_Block[g_nCntBlockSet].rot, g_Block[g_nCntBlockSet].nType);
						g_nCntBlockSet++;	// 加算
						break;
					}
				}

			}
			if (strcmp("END_SET", aStr) == 0)
			{// END_SETを読み取ったら
				// ファイルを閉じる
				fclose(pFile);
				break;
			}

		}

	}
}
#endif
//void CollisionBlock(void)
//{
//	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
//	{// 最大数分回す
//		// プレイヤーの取得
//		PLAYER* pPlayer = GetPlayer();
//
//		if (g_Block[nCnt].bUse)
//		{// 使用判定の時
//
//			if (pPlayer->pos.y < g_Block[nCnt].pos.y + g_Block[nCnt].size.y &&
//				pPlayer->pos.y + pPlayer->size.y > g_Block[nCnt].pos.y - g_Block[nCnt].size.y)
//			{
//				// 左右の当たり判定
//				if (pPlayer->posOld.z - pPlayer->size.z * HALF < g_Block[nCnt].pos.z + g_Block[nCnt].size.z * HALF &&
//					pPlayer->pos.z + pPlayer->size.z * HALF > g_Block[nCnt].pos.z - g_Block[nCnt].size.z * HALF)
//				{
//					// 左からめり込む
//					if (pPlayer->posOld.x + pPlayer->size.x * HALF < g_Block[nCnt].pos.x - g_Block[nCnt].size.x * HALF &&
//						pPlayer->pos.x + pPlayer->size.x * HALF > g_Block[nCnt].pos.x - g_Block[nCnt].size.x * HALF)
//					{
//						pPlayer->pos.x = g_Block[nCnt].pos.x - g_Block[nCnt].size.x * HALF - pPlayer->size.x * HALF - 0.1f;
//
//					}
//					// 右からめり込む
//					else if (pPlayer->posOld.x - pPlayer->size.x * HALF > g_Block[nCnt].pos.x + g_Block[nCnt].size.x * HALF &&
//						pPlayer->pos.x - pPlayer->size.x * HALF < g_Block[nCnt].pos.x + g_Block[nCnt].size.x * HALF)
//					{
//						pPlayer->pos.x = g_Block[nCnt].pos.x + g_Block[nCnt].size.x * 0.5f + pPlayer->size.x * HALF + 0.1f;
//					}
//				}
//
//				// 前後の当たり判定
//				if (pPlayer->posOld.x - pPlayer->size.z * HALF < g_Block[nCnt].pos.x + g_Block[nCnt].size.x * HALF &&
//					pPlayer->pos.x + pPlayer->size.x * HALF > g_Block[nCnt].pos.x - g_Block[nCnt].size.x * HALF)
//				{
//					// 手前からめり込む
//					if (pPlayer->posOld.z + pPlayer->size.z * HALF < g_Block[nCnt].pos.z - g_Block[nCnt].size.z * HALF &&
//						pPlayer->pos.z + pPlayer->size.z * HALF > g_Block[nCnt].pos.z - g_Block[nCnt].size.z * HALF)
//					{
//						pPlayer->pos.z = g_Block[nCnt].pos.z - g_Block[nCnt].size.z * 0.5f - pPlayer->size.z * HALF - 0.3f;
//
//					}
//					// 奥からめり込む
//					else if (pPlayer->posOld.z - pPlayer->size.z * HALF > g_Block[nCnt].pos.z + g_Block[nCnt].size.z * HALF &&
//						pPlayer->pos.z - pPlayer->size.z * HALF < g_Block[nCnt].pos.z + g_Block[nCnt].size.z * HALF)
//					{
//						pPlayer->pos.z = g_Block[nCnt].pos.z + g_Block[nCnt].size.z * HALF + pPlayer->size.z * HALF + 0.3f;
//
//					}
//				}
//				// 縦の当たり判定
//				if (pPlayer->pos.x - pPlayer->size.x * HALF < g_Block[nCnt].pos.x + g_Block[nCnt].size.x * HALF &&
//					pPlayer->pos.x + pPlayer->size.x * HALF > g_Block[nCnt].pos.x - g_Block[nCnt].size.x * HALF)
//				{
//					if (pPlayer->posOld.z - pPlayer->size.z * HALF < g_Block[nCnt].pos.z + g_Block[nCnt].size.z * HALF &&
//						pPlayer->pos.z + pPlayer->size.z * HALF > g_Block[nCnt].pos.z - g_Block[nCnt].size.z * HALF)
//					{
//						// 上からめり込んだ時
//						if (pPlayer->posOld.y >= g_Block[nCnt].pos.y + g_Block[nCnt].size.y * HALF &&
//							pPlayer->pos.y < g_Block[nCnt].pos.y + g_Block[nCnt].size.y * HALF)
//						{
//							pPlayer->bLanding = true;	// ジャンプ
//							pPlayer->pos.y = (g_Block[nCnt].pos.y + g_Block[nCnt].size.y * HALF);
//							pPlayer->move.y = 0.0f;
//
//						}
//						// 下からめり込んだ時
//						else if (pPlayer->posOld.y + pPlayer->size.y <= g_Block[nCnt].pos.y - g_Block[nCnt].size.y * HALF &&
//							pPlayer->pos.y + pPlayer->size.y > g_Block[nCnt].pos.y - g_Block[nCnt].size.y * HALF)
//						{
//							pPlayer->pos.y = (g_Block[nCnt].pos.y - g_Block[nCnt].size.y) - pPlayer->size.y * HALF;
//							pPlayer->move.y = 0.0f;
//						}
//					}
//				}
//			}
//		}
//	}
