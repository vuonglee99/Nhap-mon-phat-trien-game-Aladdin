#include"Aladin.h"
#include"Sound.h"


Aladin *Aladin::_instance = NULL;

void Aladin::ResetAll()
{
	this->health = 8;
	this->life = 3;
	this->isBeingHurt = false;
	this->point = 0;
	this->numApple = 30;
	restartPoint = D3DXVECTOR2(113, 991);

}

Aladin *Aladin::GetInstance()
{
	if (_instance == NULL)
		_instance = new Aladin();
	return _instance;
}

Aladin::Aladin()
{
	GameObject::GameObject();
	this->type = ALADDIN;
	this->health = 8;
	numApple = 30;
	life = 3;
	mApple = new Apple();
	LoadResources();
	
}

void Aladin::LoadResources()
{
	ifstream file;
	int id,left, top, right, bottom, n;
	CTexture *texture = CTexture::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texAladin = texture->Get(Type::ALADIN);
	LPDIRECT3DTEXTURE9 texAladin2 = texture->Get(Type::ALADIN2);
	LPDIRECT3DTEXTURE9 texAladin3 = texture->Get(Type::ALADIN3);

	LPANIMATION ani;
	//standing state
	//sprites->Add(20000, 20,61,66, 147, texAladin);
	sprites->Add(20000, 3,9,40,59, texAladin);

	ani = new CAnimation(100);
	ani->Add(20000);
	animations->Add(100, ani);
	AddAnimation(100);//0//ds cac animation

	////IDLE2(quay ngang trai phai)
	file.open("Resources/Aladin/Idle2.txt");
	file >> n;//18
	ani = new CAnimation(115);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000+id, left, top, right, bottom, texAladin2);
		ani->Add(20000+id);
		
	}
	animations->Add(200, ani);
	AddAnimation(200);//1
	file.close();

	//dung yen tung tao
	file.open("Resources/Aladin/Idle3.txt");
	file >> n;//7
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(300, ani);
	AddAnimation(300);//2
	file.close();

	//chi tung tao
	file.open("Resources/Aladin/Idle4.txt");
	file >> n;//7
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(400, ani);
	AddAnimation(400);//3
	file.close();

	//Idle5
	file.open("Resources/Aladin/Idle5.txt");
	file >> n;
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(500, ani);
	AddAnimation(500);//4
	file.close();

	//Running1
	file.open("Resources/Aladin/Running.txt");
	file >> n;
	ani = new CAnimation(45);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(600, ani);
	AddAnimation(600);//5
	file.close();

	//ngua mat
	ani = new CAnimation(100);
	sprites->Add(20071, 111, 491, 160, 549, texAladin);
	ani->Add(20071);
	animations->Add(700, ani);
	AddAnimation(700);//6

	//jumpping
	file.open("Resources/Aladin/Jumpping1.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(800, ani);
	AddAnimation(800);//7
	file.close();

	//jumpping2
	file.open("Resources/Aladin/Jumpping2.txt");
	file >> n;
	ani = new CAnimation(125);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(900, ani);
	AddAnimation(900);//8
	file.close();

	//Parking
	file.open("Resources/Aladin/Parking.txt");
	file >> n;
	ani = new CAnimation(75);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(1000, ani);
	AddAnimation(1000);//9
	file.close();

	//attacking1: dung chem
	file.open("Resources/Aladin/Attacking1.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(1100, ani);
	AddAnimation(1100);//10
	file.close();

	//cui dau
	ani = new CAnimation(50);
	sprites->Add(20116, 378, 516, 431, 551, texAladin);
	ani->Add(20116);
	animations->Add(1200, ani);
	AddAnimation(1200);//11

	//attacking2: ngoi chem
	file.open("Resources/Aladin/Attacking2.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(1300, ani);
	AddAnimation(1300);//12
	file.close();

	//attacking3: vua di vua chem
	file.open("Resources/Aladin/Attacking3.txt");
	file >> n;
	ani = new CAnimation(25);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin2);
		ani->Add(20000 + id);

	}
	animations->Add(1400, ani);
	AddAnimation(1400);//13
	file.close();

	//attacking4: vua nhay vua chem
	file.open("Resources/Aladin/Attacking4.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(1500, ani);
	AddAnimation(1500);//14
	file.close();


	file.open("Resources/Aladin/AttackApple.txt");
	file >> n;
	ani = new CAnimation(25);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(1600, ani);
	AddAnimation(1600);//15
	file.close();

	//ngoi nem tao
	file.open("Resources/Aladin/AttackApple2.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(1700, ani);
	AddAnimation(1700);//16
	file.close();

	//chay va nhay nem tao
	file.open("Resources/Aladin/AttackApple3.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(1800, ani);
	AddAnimation(1800);//17
	file.close();
	

	//ngua mat tan cong
	file.open("Resources/Aladin/Attacking5.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(1900, ani);
	AddAnimation(1900);//18
	file.close();

	//Pushing
	file.open("Resources/Aladin/Pushing.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(2000, ani);
	AddAnimation(2000);//19
	file.close();

	//climbing
	file.open("Resources/Aladin/Climbing.txt");
	file >> n;
	ani = new CAnimation(25);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(2100, ani);
	AddAnimation(2100);//20
	file.close();

	//climbing_Idle
	ani = new CAnimation(50);
	sprites->Add(20188, 11, 1362, 40, 1448, texAladin);
	ani->Add(20188);
	animations->Add(2200, ani);
	AddAnimation(2200);//21

	//Jump on climbing
	file.open("Resources/Aladin/JumpOnClimbing.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin);
		ani->Add(20000 + id);

	}
	animations->Add(2300, ani);
	AddAnimation(2300);//22
	file.close();

	//Attack on climbing
	file.open("Resources/Aladin/AttackOnClimbing.txt");
	file >> n;
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin2);
		ani->Add(20000 + id);

	}
	animations->Add(2400, ani);
	AddAnimation(2400);//23
	file.close();

	//Attack apple on climbing
	file.open("Resources/Aladin/AppleOnClimbing.txt");
	file >> n;
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin2);
		ani->Add(20000 + id);

	}
	animations->Add(2500, ani);
	AddAnimation(2500);//24
	file.close();

	//2600,2700

	//vua chay vua nem tao
	file.open("Resources/Aladin/AttackApple4.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin3);
		ani->Add(20000 + id);

	}
	animations->Add(2800, ani);
	AddAnimation(2800);//25
	file.close();

	//2900,3000
	//bi thuong
	file.open("Resources/Aladin/BeingHurt.txt");
	file >> n;
	ani = new CAnimation(50);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin3);
		ani->Add(20000 + id);

	}
	animations->Add(3100, ani);
	AddAnimation(3100);//26
	file.close();

	//Death
	file.open("Resources/Aladin/Death.txt");
	file >> n;
	ani = new CAnimation(100);
	for (int i = 0; i < n; i++)
	{
		file >> id >> left >> top >> right >> bottom;
		sprites->Add(20000 + id, left, top, right, bottom, texAladin3);
		ani->Add(20000 + id);

	}
	animations->Add(3200, ani);
	AddAnimation(3200);//27
	file.close();

}

void Aladin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{	
	if (health >= 0)
	{
		isSubLife = false;
		isRestart = false;
		isReSetAni = true;
		if (climbing < 0 || isJumpOnRope)
		{
			GameObject::Update(dt, coObject);

		}
		CollisionWithRope(coObject);
		vy += ALADIN_GRAVITY * dt;
		if (climbing >= 0)
		{
			switch (climbing)
			{
			case 0:
				vy = 0;
				dy = 0;
				break;
			case 1:
				dy = -3;
				break;
			case 2:
				dy = 3;
				break;
			case 3:
				currentState = 21;
				climbing = 0;
				vy = dy = 0;
				dx = vx = 0;
				break;
			}
		}
		CollisionWithWall(coObject);
		CollisionWithItems(coObject);
		if (GetTickCount() - untouchableTime >= ALADIN_BEINGHURT_TIME)
		{
			CollisionWithDefensiveWork(coObject);
			CollisionWithEnemy(coObject);
			if (isBeingHurt)
				animations[ALADIN_ANI_BEINGHURT]->SetCurrentFrame();
		}

		CollisionWithBrick(coObject);

		//Kich hoat, update va render vu khi
		if (isAttachApple&&!isBeingHurt)
		{
			if (numApple > 0)
			{
				if (!isFinish)
				{
					mApple->SetSpeed(this->nx);
					mApple->SetPosition(this->x, this->y, this->nx);
					isFinish = true;
					mApple->SetIsFinish();
					SubNumApple();
				}
				mApple->Update(dt, coObject);
			}
		}
		if (vx < 0 && x < 8) x = 8;
		if (vy <= 0 && y <= 5) y = 5;
		if (x >= 2225) x = 2225;
		int deltaY = 0;
		if (isFaceUp&&isCollisWithBrick) deltaY = -70;
		else if (isSit || isSitAttach) deltaY = 70;
		Camera::GetInstance()->SetPosition(x + 46, y + 50 + deltaY);
	}
	else
	{
		if (!isSubLife) {
			life--;
			isSubLife = true;
		}
		SceneManager::GetInstance()->SetEvent(0);
		if (isReSetAni)
		{
			animations[ALADIN_ANI_DEATH]->SetCurrentFrame();
			isReSetAni = false;
		}
		if (animations[ALADIN_ANI_DEATH]->GetCurrentFrame() == 33)
		{
			health = 8;
			SceneManager::GetInstance()->SetEvent(1);
			isBeingHurt = false;
			untouchableTime = 0;
		}
		isRestart = true;
	}
}

void Aladin::Render()
{
	int formSize = 1, alpha = 255;
	int toX = 0, toY = 0;
	int ani_ID = 0;
	int loop = 1;//0 là k lap
	float y2 = this->vy;
	if (health >= 0)
	{
		if (vx == 0)
		{
			switch (currentState)
			{
			case 1://trang thai idle1
				isBusy = true;
				dem++;
				ani_ID = ALADIN_ANI_IDLE1;
				loop = 0;
				if (dem >= ALADIN_IDLE1_TIME)
				{
					currentState = 2;
					dem = 0;
					animations[1]->SetCurrentFrame();
				}
				break;
			case 2:
				isBusy = true;
				dem++;
				ani_ID = ALADIN_ANI_IDLE2;
				loop = 1;
				if (dem >= ALADIN_IDLE2_TIME)
				{
					currentState = 3;
					dem = 0;
					animations[2]->SetCurrentFrame();
				}
				break;
			case 3:
				isBusy = true;
				ani_ID = ALADIN_ANI_IDLE3;
				loop = 1;
				if (animations[ALADIN_ANI_IDLE3]->GetCurrentFrame() == 4)
					currentState = 4;
				break;
			case 4:
				isBusy = true;
				ani_ID = ALADIN_ANI_IDLE4;
				loop = 1;
				if (animations[ani_ID]->GetCurrentFrame() == 9)
					currentState = 4 + rand() % (2);
				break;
			case 5:
				isBusy = true;
				ani_ID = ALADIN_ANI_IDLE5;
				loop = 1;
				if (animations[ani_ID]->GetCurrentFrame() == 16)
					currentState = 4 + rand() % (2);
				break;

			case 6://ngửa mặt
				isBusy = false;
				ani_ID = ALADIN_ANI_FACEUP;
				break;

			case 7://ngồi xuống
				isBusy = false;
				ani_ID = ALADIN_ANI_SIT;
				break;

			case 9://đứng tấn công
				ani_ID = ALADIN_ANI_ATTACKING1;
				isBusy = true;
				if (GetFrame(ani_ID) == 4)
				{
					isBusy = false;
					isResetFrame = true;
					isAttacking = false;
				}
				break;

			case 10://ngồi tấn công
				ani_ID = ALADIN_ANI_ATTACKING2;
				if (GetFrame(ani_ID) == 6)
				{
					isSitAttach = false;
					index = 0;
					isResetFrame = true;
					isBusy = false;
					isAttacking = false;
				}
				break;

			case 11://đứng ném táo
				ani_ID = ALADIN_ANI_ATTACKAPPLE;
				if (GetFrame(ani_ID) == 5)
				{
					isBusy = false;//khong ban lam gi ca co the dung yen 
					isResetFrame = true;
				}
				break;

			case 12://ngồi ném táo
				if (GetFrame(ALADIN_ANI_ATTACKAPPLE2) == 3)
				{
					index = 0;
					isResetFrame = true;
				}
				ani_ID = ALADIN_ANI_ATTACKAPPLE2;
				loop = 0;
				break;

			case 15://ngửa mặt và tấn công
				ani_ID = ALADIN_ANI_ATTACKING5;
				if (GetFrame(ani_ID) == 19)//lấy frame hiện tại của nó đem đi so sánh để xem nó đã kết thúc 1 vòng lặp animation hay chưa
				{
					index = 0;
					isResetFrame = true;
				}
				break;
			}

		}
		else//aladin đang di chuyển theo phương x
		{
			switch (currentState)
			{
			case 16:
				isBusy = false;
				ani_ID = ALADIN_ANI_RUNNING;
				formSize = 2;
				break;

			case 17://chạy và tấn công
				ani_ID = ALADIN_ANI_ATTACKING3;
				if (GetFrame(ani_ID) == 5)
				{
					isResetFrame = true;
					index = 0;
					isBusy = true;
				}
				break;

			case 26://chạy và ném táo
				ani_ID = ALADIN_ANI_ATTACKAPPLE4;
				if (GetFrame(ani_ID) == 5)
				{
					isResetFrame = true;
					index = 0;
				}
				break;

			case 20://dung lai
				ani_ID = ALADIN_ANI_STOP;
				if (GetFrame(ani_ID) == 5)
					isResetFrame = true;
				break;
			case 25:
				DebugOut(L"A", NULL);
				ani_ID = ALADIN_ANI_PUSHING;
				Sound::GetInstance()->Play(eSound::sound_AladinPush);
				formSize = 2;
				break;
			default:
				isBusy = false;
				ani_ID = ALADIN_ANI_RUNNING;
				if (isCollisWithWall)
				{
					Sound::GetInstance()->Play(eSound::sound_AladinPush);
					ani_ID = ALADIN_ANI_PUSHING;
					formSize = 2;
					isPushing = true;
				}
				formSize = 2;
				break;
			}
		}

		if (!isCollisWithBrick)
		{
			switch (currentState)
			{
			case 8://nhay len binh thuong
				ani_ID = ALADIN_ANI_JUMPPING;
				if (GetFrame(ani_ID) == 8)
					isBusy = false;
				break;

			case 13://nhay tai cho va tan cong
				ani_ID = ALADIN_ANI_ATTACKING3;
				if (GetFrame(ani_ID) == 5)
				{
					isBusy = false;
					isResetFrame = true;
				}
				break;

			case 14://nhảy tại chỗ và ném táo
				ani_ID = ALADIN_ANI_ATTACKAPPLE3;
				if (GetFrame(ani_ID) == 4)
				{
					isResetFrame = true;
					index = 0;
				}
				break;

			case 19://vừa chạy vừa nhảy
				ani_ID = ALADIN_ANI_JUMPPING2;
				loop = 1;

				if (GetFrame(ani_ID) == 5)
					index = 0;
				break;

			case 17:
				ani_ID = ALADIN_ANI_ATTACKING3;
				if (GetFrame(ani_ID) == 5)
				{
					isResetFrame = true;
					index = 0;
				}
				break;

			case 21:
				ani_ID = ALADIN_ANI_CLIMBING_IDLE;
				if (climbing == 1 || climbing == 2)
					ani_ID = ALADIN_ANI_CLIMBING;
				break;

			case 22://nhảy khi đang leo dây
				ani_ID = ALADIN_ANI_JUMP_ON_CLIMBING;
				break;

			case 23://tấn công khi đang leo dây
				ani_ID = ALADIN_ANI_ATTACK_ON_CLIMBING;
				formSize = 0;
				if (GetFrame(ani_ID) == 7)
				{
					isClimbing = true;
					isResetFrame = true;
				}
				toY = -45;
				break;

			case 24://ném táo khi đang leo
				ani_ID = ALADIN_ANI_APPLE_ON_CLIMBING;
				formSize = 3;
				if (nx == 1)
				{
					toX = 30;
					toY = -87;
				}
				else
				{
					toX = 7;
					toY = -87;
				}
				if (GetFrame(ani_ID) == 4)
				{
					isAttachApple = true;
					isClimbing = true;
					isResetFrame = true;
				}
				break;

			case 26://chạy và ném táo
				ani_ID = ALADIN_ANI_ATTACKAPPLE4;
				if (GetFrame(ani_ID) == 5)
				{
					isResetFrame = true;
					index = 0;
				}
				break;
			default:
				ani_ID = ALADIN_ANI_JUMPPING;
				index = 0;
				if (isJumpOnRope)
					ani_ID = ALADIN_ANI_JUMP_ON_CLIMBING;
				break;

			}
		}

		if (isBeingHurt)
		{
			Sound::GetInstance()->Play(eSound::sound_AladinHurt);
			if (climbing != -1)
				climbing = -1;
			if (isSit || isSitAttach)
			{
				if (animations[ani_ID]->GetCurrentFrame() % 2 == 0)
					alpha = 180;
				if (GetTickCount() - untouchableTime >= ALADIN_BEINGHURT_TIME)
					isBeingHurt = false;
			}
			else
			{
				ani_ID = ALADIN_ANI_BEINGHURT;
				if (animations[ani_ID]->GetCurrentFrame() == 5)
					isBeingHurt = false;
			}
			dem = 0;
			loop = 0;
		}
		if (this->nx == -1 && formSize != 3)
			toX = 40;
		if (formSize == 2)
		{
			if (nx == 1)
				toX = 40;
			else
				toX = 0;
		}

		float finalX = x + toX, finalY = y + 52 + toY;
		if (!isClimbing)
			if (climbing != -1)	finalX += X;
		else finalX += X;
		animations[ani_ID]->Render(finalX, finalY, loop, this->nx, Camera::GetInstance()->GetTranform(), formSize, alpha);
		if (isAttachApple&&!isBeingHurt)
		{
			if (numApple > 0)
				mApple->Render();
			else
				isAttachApple = false;
		}
		if (DISPLAY_BOX == 1)
		{
			if (currentState == 21)
				RenderBoundingBox(22 + (int)X, 26);
			else
				if (isAttacking)
				{

					if (this->nx == 1)
						RenderBoundingBox(34, 26);
					else
						RenderBoundingBox(0, 26);
				}
				else
					if (isSit || isSitAttach)
						RenderBoundingBox(20, 32);
					else
						RenderBoundingBox(20, 26);
		}
	}
	else
	{
		ani_ID = ALADIN_ANI_IDLE1;
		animations[ALADIN_ANI_DEATH]->Render(180, 120, 1, 1, D3DXVECTOR2(0,0),2);
	}
	
}


void Aladin::SetState(int state)
{

	switch (state)
	{
	case ALADIN_IDLE_STATE:
		isSit = isFaceUp=isPushing=false;
		if(isResetVx)
			vx = 0;
		if (index == 14)
			currentState = 14;
		if (!isBusy)
		{
			currentState = 1;
			isAttacking = false;
			isSitAttach = false;
			dem = 0;
			climbing = -1;
			if(isCollisWithBrick)
				isJumpOnRope = false;
			isResetFrame = true;
		}
		if (isClimbing)
		{
			currentState = 21;
			climbing = 0;
			if (ropeX > this->x)
			{
				X = ropeX - (this->x + 18);
			}
			else//ropeX<this->x
			{
				X = (this->x + 18) -ropeX ;
			}
			if (this->y < yRopeStart)
				this->y = yRopeStart;
			isBusy = true;
		}
		if (vx != 0 && vy != 0)
		{
			if (isClimbing)
			{
				currentState = 21;
				climbing = 0;
				dx = 0;
				if (ropeX > this->x)
				{
					X = ropeX - (this->x + 18);
				}
				else//ropeX<this->x
				{
					X = (this->x + 18) - ropeX;
				}
				if (this->y < yRopeStart)
					this->y = yRopeStart;
				isBusy = true;
			}
		}
		break;
	
	case ALADIN_FACEUP_STATE:
		isBusy = isFaceUp=true;
		climbing = -1;
		switch (index)
		{
		case 15://đang có trạng thái tấn công xảy ra, để nó hoàn thành trk
			currentState = 15;
			break;
		default:
			currentState = 6;
			break;
		}
		break;

	case ALADIN_SIT_STATE:
		if (vy == 0)
		{
			isSit = true;
			vx = 0;
		}
		switch (index)
		{
		case 10://đang có trạng thái tấn công xảy ra khi đang ngồi, ưu tiên hoàn thành tấn công trk
			currentState = 10;
			break;
		case 12://(tương tự)
			currentState = 12;
			break;
		default:
			isSitAttach = false;
			currentState = 7;
			break;
		}
		break;

	case ALADIN_JUMPPING_STATE:
		if (isCollisWithBrick)//nếu đang va chạm với nền thì ms cho nhảy tiếp, tránh trường hợp đang nhảy thì nhấn nhảy lần 2.
		{
			vy = -ALADIN_JUMPPING_SPEED;
			if (vx == 0)
			{
				currentState = 8;
				ResetFrame(ALADIN_ANI_JUMPPING);
			}
			else
			{
				currentState = 19;//vừa chạy vừa nhảy
				index = 19;
			}
			ResetFrame(ALADIN_ANI_JUMPPING2);
			isCollisWithBrick = false;
		}
		else
			if (climbing == 0)
			{
				currentState = 22;
				vy = -0.33f;
				isJumpOnRope = true;
				climbing = -1;
				isBusy = false;
			}	
		break;
		
	case ALADIN_ATTACKING_STATE:
		if (climbing == -1)
		{
			if (isSit)
			{
				isSit = false;
				isSitAttach = true;
				currentState = 10;//ngồi tấn công
				index = 10;//chỉ số cho biết nó đang ở trạng thái tấn công nào.
			}
			else if (isFaceUp)//trường hợp đang ngửa mặt và tấn công
			{
				isFaceUp = false;
				currentState = 15;
				index = 15;
			}
			else if (vx != 0)
			{
				currentState = 17;//chạy và tấn công
				index = 17;
			}
			else
			{
				DebugOut(L"y", NULL);
				currentState = 9;//đứng yên tấn công
			}
		
			if (!isCollisWithBrick)
			{
				currentState = 13;//nhảy tại chỗ và tấn công
				vy = 0;
			}
			
		}
		else
			currentState = 23;//tấn công khi đang leo dây
		isBusy = true;
		isAttacking = true;
		Sound::GetInstance()->Play(eSound::sound_HighSword);
		if (isResetFrame)//set về frame bắt đầu=0 để tăng độ chính xác
		{
			isResetFrame = false;
			ResetFrame(ALADIN_ANI_ATTACKING1);
			ResetFrame(ALADIN_ANI_ATTACKING2);
			ResetFrame(ALADIN_ANI_ATTACKING3);
			ResetFrame(ALADIN_ANI_ATTACKING4);
			ResetFrame(ALADIN_ANI_ATTACKING5);
			ResetFrame(ALADIN_ANI_ATTACK_ON_CLIMBING);
		}
		break;

	case ALADIN_ATTACKAPPLE_STATE:
		if (climbing == -1)
		{
			if (isSit)
			{
				isSit = false;
				currentState = 12;//ngồi và ném táo(tương tự ngồi và tấn công)
				index = 12;//chỉ số biểu thị(dùng để phân biệt ngồi và ngồi tấn công khi cả 2 trạng thái đồng thời xảy ra,
				//theo đó hành động có index khác 0 thì nó đc ưu tiên hoàn thành và set tới trạng thái của nó trước)
			}
			else if (vx != 0)
			{
				DebugOut(L"A", NULL);
				currentState = 26;//chạy và ném táo
				index = 26;
			}
			else
				currentState = 11;
			
			if (!isCollisWithBrick)
			{
				currentState = 14;//nhảy tại chỗ và ném táo(tương tự currentState 13)
				vy = 0;
				if (vx != 0)
					index = 14;
			} 
			if (!isBeingHurt && !isFaceUp)
			{
				isAttachApple = true;
				mApple->Revival();
			}
		}
		else
			currentState = 24;//tấn công khi đang leo
		isBusy = true;
		isFinish = false;
		
		Sound::GetInstance()->Play(eSound::sound_ThrowApple);
		if (isResetFrame)
		{
			isResetFrame = false;
			ResetFrame(ALADIN_ANI_ATTACKAPPLE);
			ResetFrame(ALADIN_ANI_ATTACKAPPLE2);
			ResetFrame(ALADIN_ANI_ATTACKAPPLE3);
			ResetFrame(ALADIN_ANI_ATTACKAPPLE4);
			ResetFrame(ALADIN_ANI_APPLE_ON_CLIMBING);
		}
		break;

	case ALADIN_WALKING_RIGHT_STATE:
		if (climbing == -1)
		{
			if (isCollisWithBrick)
				isJumpOnRope = false;
			vx = ALADIN_WALKING_SPEED * changeVx;
			if (isCollisWithWall)
			{
				currentState = 25;
				isPushing = true;
			}
			else
			{
				switch (index)
				{
				case 14:
					currentState = 14;
					break;
				case 17:
					currentState = 17;
					break;
				case 18:
					currentState = 18;
					break;
				case 19:
					currentState = 19;//vừa chạy vừa nhảy
					break;
				case 26:
					currentState = 26;
					break;
				default:
					isAttacking = false;
					isResetFrame = true;
					currentState = 16;
					isSit = false;
					break;
				}
			}
		}
		else
		{
			if (isClimbing)
			{
				climbing = 0;
				currentState = 21;
				vx = dx = 0;
			}
		}
		this->nx = 1;
		break;

	case ALADIN_WALKING_LEFT_STATE:
		if (climbing == -1)
		{
			vx = -ALADIN_WALKING_SPEED * changeVx;
			if(isCollisWithBrick)
				isJumpOnRope = false;
			if (isClimbing)
			{
				climbing = 0;
				currentState = 21;
				isJumpOnRope = true;
			}
			if (isCollisWithWall)
			{
				currentState = 25;
				isPushing = true;
			}
			else
			{
				switch (index)
				{
				case 14:
					currentState = 14;
					break;
				case 17:
					currentState = 17;
					break;
				case 18:
					currentState = 18;
					break;
				case 19:
					currentState = 19;
					break;
				case 26:
					currentState = 26;
					break;
				default:
					isAttacking = false;
					currentState = 16;
					isSit = false;
					break;
				}
			}
		}
		else
		{
			if (isClimbing)
			{
				climbing = 0;
				currentState = 21;
				vx = dx = 0;
			}
		}
			
		this->nx = -1;
		break;

	case ALADIN_STOP_STATE:
		vx = this->nx*ALADIN_STOP_SPEED;
		currentState = 20;
		if (isResetFrame)
		{
			ResetFrame(ALADIN_ANI_STOP);
			isResetFrame = false;
		}
		break;
	}
}


Aladin::~Aladin()
{

}

void Aladin::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (currentState == 22 || currentState == 21)
	{
		left = x + X;
		right = left + 40;
	}
	else
	{
		if (isAttacking)
		{
			if (this->nx == -1)
			{
				left = x - 32;
				if(isSitAttach)
					right = left + 88;
				else
					right = left + 66;
			}
			else
			{
				left = x;
				if (isSitAttach)
					right = left + 88;
				else
					right = left + 66;
			}
		}
		else
		{
			left = x;
			right = left + 40;
		}
	}
	
	if (isSit || isSitAttach)
	{
		top = y + 26;
		bottom = top + 26;
	}
	else
	{
		top = y;
		bottom = top + 52;
	}
}

void Aladin::CollisionWithBrick(vector<LPGAMEOBJECT>* coObject)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	coEventsResult.clear();

	//lay ds cac brick trong list object hien co

	vector<LPGAMEOBJECT> list_Brick;
	list_Brick.clear();
	for (UINT i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i)->GetType() == Type::BRICK|| coObject->at(i)->GetType() == Type::MOVINGBRICK)
		{
			list_Brick.push_back(coObject->at(i));
		}
	}

	CalcPotentialCollisions(&list_Brick, coEvents);//dua ra dc cac obj co the xay ra va cham(coEvents)

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);//dem loc ra xem laoi doi tuong, tg, huong
		if (nx != 0) vx = 0;
		//xet logic va cham voi brick
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Brick *>(e->obj))//e->obj is Brick
			{
				//DebugOut(L"Collision", NULL);
				if (e->nx != 0)//co xay ra va cham theo phuong Ox
				{
					if (isCollisWithWall) dx = 0;
					x += dx;
				}
				else//k xay ra va cham theo phuong Ox
				{
					x += min_tx * dx + nx * 0.4f;
				}
				if (e->ny == -1)//dang di xuong
				{
 					//y += min_ty * dy + ny * 0.4f;
					if (ny != 0)
					{
						vy = 0;
					}
					isCollisWithBrick = true;
					if (isCollisWithWall) dy = 0;
				}
				else// Nhay duoi len(ny==1)
				{
					/*if(e->ny==0)*/
						y += dy;
				}
				
			}
			else
			{
				dynamic_cast<MovingBrick *>(e->obj);
				if (e->nx != 0)
				{
					x += dx;
					dy = 0;
					//isCollisWithBrick = true;
				}
				else
				{
					x += min_tx * dx + nx * 0.4f;
				}
				if (e->ny == -1)
				{
					//y += min_ty * dy + ny * 0.4f;
					if (ny != 0)
					{
						vy = 0;
					}
					isCollisWithBrick = true;
				}
				else// Nhay duoi len
				{
					y += dy;
				}
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Aladin::CollisionWithWall(vector<LPGAMEOBJECT>* coObject)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	coEventsResult.clear();

	//lay ds cac brick trong list object hien co

	vector<LPGAMEOBJECT> list_Wall;
	list_Wall.clear();
	for (UINT i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i)->GetType() == Type::WALL)
		{
			list_Wall.push_back(coObject->at(i));
		}
	}

	CalcPotentialCollisions(&list_Wall , coEvents);

	if (coEvents.size() != 0)//co xay ra va cham
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			DebugOut(L"W", NULL);
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->nx == -1||e->nx==1)
			{
				dx = 0;
				isCollisWithWall = true;
				if(e->ny!=0)
					x += min_tx * dx + nx * 0.4f;
			}
			else x += min_tx * dx + nx * 0.4f;
			if (e->ny == 1)
				dx = 0;

		}
	}
	else
	{
		int demCollis = 0;
		for (int i = 0; i <list_Wall.size(); i++) {
			if (AABBcollision(list_Wall.at(i)))
			{
				/*if (coEvents.at(i)->nx == 0)
				{*/
				if (list_Wall.at(i)->GetPosX() < this->x) {
					if (this->nx == -1) {
						isCollisWithWall = true;
						demCollis++;
						dx = 0;
					}
				}
				else if (list_Wall.at(i)->GetPosX() > (this->x-4)) {
					if (this->nx == 1) {
						isCollisWithWall = true;
						demCollis++;
						dx = 0;
					}
				}
			}
		}
		if(demCollis==0)
			isCollisWithWall = false;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Aladin::CollisionWithRope(vector<LPGAMEOBJECT>* coObject)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	coEventsResult.clear();

	//lay ds cac brick trong list object hien co

	vector<LPGAMEOBJECT> list_Rope;
	list_Rope.clear();
	for (UINT i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i)->GetType() == Type::ROPE)
		{
			list_Rope.push_back(coObject->at(i));
		}
	}

	CalcPotentialCollisions(&list_Rope, coEvents);

	if (coEvents.size() == 0)//co xay ra va cham
	{
		isClimbing = false;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			
			LPCOLLISIONEVENT e = coEventsResult[i];
			Rope *currentRope = dynamic_cast<Rope *>(e->obj);
			e->obj->GetPosition(ropeX, ropeY);
			currentRope->getStartEnd(yRopeStart, yRopeEnd);
			/*dx = 0;*/
		
			if (e->nx == 0)
			{
				if (e->ny == 1)
				{
					y += min_ty * dy + ny * 0.4f;
					DebugOut(L"Collision", this->y);
					isClimbing = true;
					dy = 0;
					dx = 0;
				}
			}
			
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Aladin::CollisionWithItems(vector<LPGAMEOBJECT>* coObject)
{
	float rX, rY;
	vector<LPGAMEOBJECT> listItems;
	listItems.clear();
	for (int i = 0; i < coObject->size(); i++)
		if (coObject->at(i)->GetType() == Type::APPLEITEM|| coObject->at(i)->GetType() == Type::REDJEWEL|| coObject->at(i)->GetType()==Type::GENIE||
			coObject->at(i)->GetType() == Type::HEART|| coObject->at(i)->GetType() == Type::RESTARTPOINT)
			if(coObject->at(i)->GetHealth()!=0)
				listItems.push_back(coObject->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	coEventsResult.clear();

	CalcPotentialCollisions(&listItems, coEvents);//dung aabb de tien doan

	if (coEvents.size() == 0)//co xay ra va cham
	{
		for (int i = 0; i < listItems.size(); i++)
		{
			LPGAMEOBJECT e = listItems.at(i);
			if (AABBcollision(e) && e->GetHealth() != 0)
			{
				e->SubHealth();
				if (e->GetType() == Type::RESTARTPOINT)
				{
					e->GetPosition(rX, rY);
					restartPoint.x = rX;
					restartPoint.y = rY - 25;
					idRestartPoint = e->GetID();
					Sound::GetInstance()->Play(eSound::sound_ContinuePoint);
				}

			}
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			LPGAMEOBJECT item = e->obj;
			if (item->GetType() == Type::HEART)
			{
				Healing(3);
				if (health >= 8)
					health = 8;
			}
			else if (item->GetType() == Type::REDJEWEL)
			{
				AddRedJewel();
				Sound::GetInstance()->Play(eSound::sound_GemCollect);
			}
			else if (item->GetType() == Type::APPLEITEM)
			{
				AddApple();
				Sound::GetInstance()->Play(eSound::sound_AppleCollect);
			}
				
			else if (item->GetType() == Type::RESTARTPOINT)
			{
				Sound::GetInstance()->Play(eSound::sound_ContinuePoint);
				item->GetPosition(rX, rY);
				restartPoint.x = rX;
				restartPoint.y = rY - 25;
				idRestartPoint = item->GetID();
			}
			else if (item->GetType() == Type::GENIE) {
				Sound::GetInstance()->Play(eSound::sound_Wow);
			}

			item->SubHealth();
			item->Update(dt, coObject);

		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void Aladin::CollisionWithDefensiveWork(vector<LPGAMEOBJECT>* coObject)
{
	float left, top, right, bottom;
	RECT RAladin;
	GetBoundingBox(left, top, right, bottom);
	RAladin.left = left;
	RAladin.top = top;
	RAladin.right = right;
	RAladin.bottom = bottom;
	vector<LPGAMEOBJECT> listDefensiveWork;
	listDefensiveWork.clear();
	for (int i = 0; i < coObject->size(); i++)
		if (coObject->at(i)->GetType() == Type::ARROW|| coObject->at(i)->GetType() == Type::BOB)
			listDefensiveWork.push_back(coObject->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	coEventsResult.clear();

	CalcPotentialCollisions(&listDefensiveWork, coEvents);

	if (coEvents.size() == 0)
	{
		
		for (int i = 0; i < listDefensiveWork.size(); i++)
		{
			RECT obj;
			listDefensiveWork.at(i)->GetBoundingBox(left, top, right, bottom);
			obj.left = left;
			obj.top = top;
			obj.right = right;
			obj.bottom = bottom;

			if (Camera::GetInstance()->isContain(RAladin, obj))
			{
					SubHealth();
					StartUntouchableTime();
					isBeingHurt = true;
					DebugOut(L"A", NULL);
			}

		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			StartUntouchableTime();
			isBeingHurt = true;
			SubHealth();
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Aladin::CollisionWithEnemy(vector<LPGAMEOBJECT>* coObject)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> listEnemy;
	listEnemy.clear();
	for (UINT i = 0; i < coObject->size(); i++)
	{
		LPGAMEOBJECT cO = coObject->at(i);
		if ((cO->GetType() == Type::BAT || cO->GetType() == GUARD || cO->GetType() == MONKEY || cO->GetType() == SKELETON || cO->GetType()==Type::BONE)
			&& cO->GetHealth() != 0)
			listEnemy.push_back(coObject->at(i));
	}

	for (UINT i = 0; i < listEnemy.size(); i++)
	{
		LPGAMEOBJECT e = listEnemy.at(i);
		if (AABBcollision(e) &&e->GetHealth() != 0)
		{				
			if (isAttacking)
			{
				if (e->GetType() == Type::GUARD|| e->GetType() == Type::MONKEY)
				{
					if (collisGuard == 0)
					{
						e->SubHealth();
						e->SetIsBeingHurt(2);
						DebugOut(L"G", NULL);
						collisGuard++;
					}
					else if (collisGuard > 20)
					{
						e->SubHealth();
						collisGuard = 0;
						e->SetIsBeingHurt(2);
						DebugOut(L"G", NULL);
					}
					else
						collisGuard++;
				}
				else
				{
						collisGuard = 0;
						e->SubHealth();
				}
			}
			else
			{
				if (e->GetType() == Type::BAT|| e->GetType() == Type::SKELETON)
				{
					SubHealth();
					StartUntouchableTime();
					isBeingHurt = true;
				}
			}
		}
	}
}


