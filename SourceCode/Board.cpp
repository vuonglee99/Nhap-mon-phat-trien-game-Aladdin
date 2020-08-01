#include "Board.h"
#include "Aladin.h"

Board * Board::_instance = NULL;

Board * Board::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new Board();
	}
	return _instance;
}

Board::~Board()
{

}

Board::Board()
{
	mHealthBoard = HealthBoard::GetInstance();
	aladinHealth = Aladin::GetInstance()->GetHealth();
	mRedJewelBoard = RedJewelBoard::GetInstance();
	mAppleBoard = AppleBoard::GetInstance();
	mFont = Font::GetInstance();

}

void Board::Render()
{
	mHealthBoard->Draw(aladinHealth);
	mRedJewelBoard->Draw();
	mAppleBoard->Draw();
	mFont->Draw(220, 190, FillNumber(std::to_string(this->numRedJewel),2));
	mFont->Draw(260, 190, FillNumber(std::to_string(this->numApple), 2));
	mFont->Draw(220, 50, FillNumber(std::to_string(this->point), 6));
	mFont->Draw(16, 180, FillNumber(std::to_string(this->life), 2));
}

void Board::Update()
{
	Aladin *mAladin = Aladin::GetInstance();
	this->aladinHealth= mAladin->GetHealth();
	numRedJewel = mAladin->GetNumRedJewel();
	numApple = mAladin->GetNumApple();
	point = mAladin->GetPoint();
	life = mAladin->GetLife();
}

void Board::LoadAni()
{
}

string Board::FillNumber(string s, UINT MaxNumber)
{
	while (s.size() < MaxNumber)
		s = "0" + s;
	return s;
}