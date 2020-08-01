#include "SceneBoss.h"
#include "define.h"
#include "Sound.h"


SceneBoss::SceneBoss()
{
}

SceneBoss::SceneBoss(int state)
{
	mAladin = Aladin::GetInstance();
	this->State = state;
	this->mEvent = ALADIN_NORMAL;
	mCamera = Camera::GetInstance();
	mBoard = Board::GetInstance();
	mBoss = Boss::GetInstance();
	mSnake = Snake::GetInstance();
	mSFire = new StaticFire();
	LoadResources();
}

SceneBoss::~SceneBoss()
{
	

}

void SceneBoss::LoadResources()
{
	mMapBoss = new GameMap(MapBoss, "Resources/Map/mapboss_matrix.txt");
	mMapBoss2 = new GameMap(MapBoss2, "Resources/Map/mapboss2_matrix.txt");
	int id, type, direction, width, height, n, state;
	float x, y;

	ifstream file("Resources/Object/BossObject.txt", ios::in);
	file >> n;

	for (int i = 0; i < n; i++)
	{
		file >> id >> type >> direction >> width >> height >> x >> y >> state;
		AddObject(id, type, direction, width, height, x, y, state);
	}
	listObj.push_back(mBoss);
	listObj.push_back(mSnake);
	mCamera->SetTypeMap(MapBoss);
	mAladin->SetPosition(47, 300);
	mAladin->SetRestartPoint(D3DXVECTOR2(47, 300));
	Sound::GetInstance()->Play(eSound::sound_BossTune);
}

void SceneBoss::SetEvent(int mEvent)
{
	this->mEvent = mEvent;
	
}

void SceneBoss::Render()
{
	switch (mEvent)
	{
	case ALADIN_NORMAL:
		CSprites::GetInstance()->Add(BossBackGround, 0, 0, 830, 450, CTexture::GetInstance()->Get(BossBackGround));
		CSprites::GetInstance()->Get(BossBackGround)->Draw(0,0,0,D3DXVECTOR2(0,0),0);
		mMapBoss->Draw(MapBoss);
		mMapBoss2->Draw(MapBoss2);
		for (auto x : listObj)
			x->Render();
		mBoss->Render();
		mAladin->Render();
		mBoard->Render();
		mSFire->Render();
		break;
	case ALADIN_DIE:
		mAladin->Render();
		break;
	}
}

void SceneBoss::Update(DWORD dt)
{
	switch (mEvent)
	{
	case ALADIN_NORMAL:
		Sound::GetInstance()->Play(eSound::sound_BossTune);
		mBoard->Update();
		for (auto x : listObj)
			x->Update(dt, &listObj);
		if (mAladin->GetIsRestart())
		{
			float x, y;
			mAladin->getRestartPoint(x, y);
			mAladin->SetPosition(x, y);
			mAladin->SetState(ALADIN_IDLE_STATE);
		}
		mAladin->Update(dt, &listObj);
		mSFire->Update(dt, &listObj);
		if (mBoss->GetHealth() <= 0)
		{
			Sound::GetInstance()->StopAll();
			SceneManager::GetInstance()->SetScene(new SceneWin());
		}
		break;
	case ALADIN_DIE:
		Sound::GetInstance()->StopAll();
		DebugOut(L"G", NULL);
		if (mAladin->GetLife() < 0)
			SceneManager::GetInstance()->SetScene(new SceneGameOver());
		mAladin->Update(dt, &listObj);
		break;
	}
}

void SceneBoss::KeyState(BYTE * state)
{
	if (mEvent==ALADIN_NORMAL)
	{
		if (CKeyHandler::GetInstance()->isKeyDown(DIK_RIGHT))
		{
			if (mAladin->GetDx() != 0)
			{
				isRunning = true;
				if (mAladin->GetTimeRun() == 0)
					mAladin->SetTimeRun(GetTickCount());
			}
			else
				isRunning = false;
			mAladin->SetState(ALADIN_WALKING_RIGHT_STATE);
		}

		else if (CKeyHandler::GetInstance()->isKeyDown(DIK_LEFT))
		{
			if (mAladin->GetDx() != 0)
			{
				isRunning = true;
				if (mAladin->GetTimeRun() == 0)
					mAladin->SetTimeRun(GetTickCount());
			}
			else
				isRunning = false;

			mAladin->SetState(ALADIN_WALKING_LEFT_STATE);

		}
		else if (CKeyHandler::GetInstance()->isKeyDown(DIK_UP))
		{
			if (mAladin->GetClimbing() != -1)
			{
				if (mAladin->GetPosY() <= mAladin->yRopeStart)
					mAladin->SetClimbing(0);
				else
					mAladin->SetClimbing(1);//1 là leo lên
			}
			else
				mAladin->SetState(ALADIN_FACEUP_STATE);

		}
		else if (CKeyHandler::GetInstance()->isKeyDown(DIK_DOWN))
		{
			if (mAladin->GetClimbing() != -1)
			{
				if (mAladin->GetPosY() + 30 >= mAladin->yRopeEnd)
					mAladin->SetClimbing(-1);
				else
					mAladin->SetClimbing(2);//2 là leo xuống
			}
			else
				mAladin->SetState(ALADIN_SIT_STATE);

		}
		else//k nhan
		{
			if (isRunning && !mAladin->getisPushing())
			{
				if (GetTickCount() - mAladin->GetTimeRun() >= ALADIN_MIN_RUNNING_TIME)
				{
					if (time == 0)
						time = GetTickCount();
					if (GetTickCount() - time < 500)
						mAladin->SetState(ALADIN_STOP_STATE);
					else
					{
						isRunning = false;
						mAladin->SetTimeRun(0);
						mAladin->SetState(ALADIN_IDLE_STATE);
						time = 0;
					}
				}
				else
				{
					isRunning = false;
					mAladin->SetTimeRun(0);
					time = 0;
					mAladin->SetState(ALADIN_IDLE_STATE);
				}

			}
			else
			{
				mAladin->SetState(ALADIN_IDLE_STATE);
				mAladin->SetTimeRun(0);
				if (mAladin->GetClimbing() == 1 || mAladin->GetClimbing() == 2)
					mAladin->SetClimbing(0);
			}
		}
	}
}

void SceneBoss::OnKeyDown(int KeyCode)
{
	if (mEvent==ALADIN_NORMAL)
	{
		switch (KeyCode)
		{
		case DIK_SPACE:
			mAladin->SetState(ALADIN_JUMPPING_STATE);
			mAladin->SetTimeRun(0);
			break;
		case DIK_A:
			mAladin->SetState(ALADIN_ATTACKING_STATE);
			break;
		case DIK_X:
			mAladin->SetState(ALADIN_ATTACKAPPLE_STATE);
			break;
		case DIK_F:
			mAladin->SetHealth(8);
			break;
		case DIK_S:
			mBoss->SetHealth(-1);
			break;
		case DIK_D:
			mAladin->SetNumApple();
			break;
		}
	}
}

void SceneBoss::OnKeyUp(int KeyCode)
{
}

GameObject* SceneBoss::NewObject(int id, int type, int direction, int width, int height, float x, float y, int state)
{
	switch (type)
	{
	case BRICK:
		return new Brick(x, y, width, height);
		break;
	case WALL:
		return new Wall(x, y, width, height);
		break;
	}
}

void SceneBoss::AddObject(int id, int type, int direction, int width, int height, float x, float y, int state)
{
	GameObject *obj = NewObject(id, type, direction, width, height, x, y, state);
	obj->SetID(id);
	listObj.push_back(obj);
}
