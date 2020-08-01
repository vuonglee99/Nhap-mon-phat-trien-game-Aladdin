#include "CGame.h"

CGame * CGame::_instance = NULL;


CGame * CGame::GetInstance()
{

	if (_instance == NULL)
	{
		_instance = new CGame();
	}
	return _instance;
}

CGame::~CGame()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backbuffer != NULL) backbuffer->Release();
	if (d3ddev != NULL) d3ddev->Release();
	if (d3d != NULL) d3d->Release();
}


void CGame::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
	this->hWnd = hWnd;
	D3DPRESENT_PARAMETERS d3dpp;


	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (d3ddev == NULL)
	{
		MessageBox(hWnd, "Init d3ddev errors", "Error", MB_OK);
		return;
	}
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	D3DXCreateSprite(d3ddev, &spriteHandler);
}

void CGame::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int flipX, D3DXVECTOR2 transform, int formSize, int alpha)
{
	D3DXMATRIX oldMatrix;
	D3DXMATRIX mMatrix;
	D3DXVECTOR2 Scale = D3DXVECTOR2(1.0, 1.0);
	D3DXVECTOR2 scalingScenter = D3DXVECTOR2(x, y);
	if (flipX == -1)// Co Flip Sang X
	{
		Scale = D3DXVECTOR2(-1.0, 1.0);
		x = -x;
	}

	D3DXMatrixTransformation2D(&mMatrix, NULL, 0, &Scale, NULL,
		NULL, &transform);

	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&mMatrix);

	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	D3DXVECTOR3 center;
	switch (formSize)
	{
	case 0:
		center = D3DXVECTOR3((right - left) / 2, (bottom - top) / 2, 0);
		break;
	case 1:
		center = D3DXVECTOR3(0, (bottom - top), 0);
		break;
	case 2:
		center = D3DXVECTOR3((right-left), (bottom - top), 0);
		break;
	case 3:
		center = D3DXVECTOR3((right - left), 0, 0);
		break;
	}
	D3DXVECTOR3 p(x, y, 0);

	spriteHandler->Draw(texture, &r, &center, &p, D3DCOLOR_ARGB(alpha, 255,255,255));

	spriteHandler->SetTransform(&oldMatrix);
}

void CGame::SweptAABB(float ml, float mt, float mr, float mb, float dx, float dy, float sl, float st, float sr, float sb,float &t, float &nx, float &ny)
{ 

	float dx_entry, dx_exit; //quang duong can di de xay ra va cham,quang duwong can di tu luc xet den khi het va cham
	float tx_entry, tx_exit;//tg de bat dau xay ra va cham, thoi gian tu luc xet den luc het xay ra va cham
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;//tg de bat dau xay ra va cham
	float t_exit;//tg tu luc bat dau xet den khi den thuc va cham

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	//dx,dy:van toc cua doi tuong
	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;//quang duong can di de bat dau xuat hien va cham(ox)
		dx_exit = sr - ml;// qd can di tu luc bat dau xet cho den luc bat dau het va cham
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)//(oy)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)//k xet vat k co van toc
	{
		tx_entry = -99999999999;
		tx_exit = 99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;//tg se xay ra va cham theo phuong x
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else
	{
		ty_entry = dy_entry / dy;//tg se xay ra va cham theo phuong y
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);//tg bat dau xay ra va cham tu luc xet
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;//tg khi nao se xay ra va cham

	if (tx_entry > ty_entry)//tg bat dau va cham theo Ox>tg bat dau va cham theo Oy->k va cham theo phuong y
	{
		ny = 0.0f;//huong(=0 tuc la k co va cham)
		dx > 0 ? nx = -1.0f : nx = 1.0f;//dx: quang duong de bat dau va cham theo phuong x>0->dang di sang phai->nx=-1;(sang phai)
	}
	else//va cham xay ra theo phuong x trk
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;//dy: quang duong can di de bat dau xay ra va cham>0->ny=-1;(di len)
	}

}
