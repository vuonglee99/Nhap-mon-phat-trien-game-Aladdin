#include "Font.h"

Font * Font::_instance = NULL;

Font::Font()
{
}


Font::~Font()
{
}

Font * Font::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new Font();
	}
	return _instance;
}

void Font::Draw(float x, float y, const string & s, int alpha)
{
	CTexture * texture = CTexture::GetInstance();
	LPDIRECT3DTEXTURE9 tex = texture->Get(Type::ALADIN2);
	LPDIRECT3DTEXTURE9 tex2 = texture->Get(Type::FONT);
	CGame *mGame = CGame::GetInstance();
	int l, t, r, b;
	for (UINT i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
			continue;
		int number = s[i] - '0';
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			int lo = s[i] - 'A';
			if (lo < 18)
			{
				l= 2 + lo * 8;
				t = 1;
				r = l + 9;
				b = t + 9;
			}
			else
			{
				lo -= 18;
				l = 2 + lo * 8;
				t = 10;
				r = l + 9;
				b = t + 9;
			}
			mGame->Draw(x + 4.0f + i * 8, y + 4.0f, tex2, l, t, r, b, 0, D3DXVECTOR2(0, 0),0,alpha);
		}
		else
		{
			switch (number)
			{
			case 0:
				Set(359, 3594, 366, 3601);
				break;
			case 1:
				Set(371, 3594, 374, 3601);
				break;
			case 2:
				Set(379, 3594, 384, 3601);
				break;
			case 3:
				Set(389, 3594, 393, 3601);
				break;
			case 4:
				Set(398, 3594, 404, 3601);
				break;
			case 5:
				Set(409, 3594, 414, 3601);
				break;
			case 6:
				Set(419, 3594, 425, 3601);
				break;
			case 7:
				Set(430, 3594, 435, 3601);
				break;
			case 8:
				Set(439, 3594, 444, 3601);
				break;
			case 9:
				Set(449, 3594, 455, 3601);
				break;

			}
			mGame->Draw(x + 20.0f + i * 8, y, tex, left, top, right, bottom, 0, D3DXVECTOR2(0, 0));
		}
	}
}

void Font::Set(int left, int top, int right, int bottom)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}
