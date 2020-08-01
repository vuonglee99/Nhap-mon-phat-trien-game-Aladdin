#pragma once
#include <algorithm>


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif
enum Type
{
	ALADDIN=-1,
	ALADIN = 01,
	ALADIN2 = 2,
	ALADIN3=3,
	APPLE=4,
	EXPLOSION=5,
	ITEM=6,
	ENEMY_BAT=7,
	GUARDS=8,
	BOX = 10,
	BRICK = 20,
	ARROW = 21,
	BOB=22,
	MOVINGBRICK=23,
	WALL=24,
	MOVINGBRICK2=25,
	ROPE=26,
	APPLEITEM=27,
	REDJEWEL=28,
	GENIE=29,
	HEART=30,
	RESTARTPOINT=31,
	BAT=32,
	GUARD=33,
	SWORDGUARD=34,
	DIE=35,
	SKELETON=36,
	SKELETON_IMAGE=37,
	MONKEY=38,
	BONE=39,
	GAME_INTRO=40,
	SCENEINTRO=41,
	SCENEGAME=42,
	SCENEDIE=43,
	SCENEOVER=44,
	BOSS=45,
	BOSS_TEX=46,
	SNAKE=47,
	SCENEWIN=48,
	BACKGROUNDINTRO=49,
	BIRDINTRO=50,
	FONT=51,
	SELECTOR=52,


	//Map tu 100
	Map1 = 100,
	Map1_Rows = 7,
	Map1_Columns = 35,
	Map1_Tile = 209,
	Map1_X = 0,//ghep cac map voi nhau(chieu X)
	Map1_Y = 0,
	Map1_End = 1920,

	Map2 = 200,
	Map2_Rows = 7,
	Map2_Columns = 35,
	Map2_Tile = 244,
	Map2_X = 0,
	Map2_Y = 224,

	Map3 = 300,
	Map3_Rows = 7,
	Map3_Columns = 35,
	Map3_Tile = 235,
	Map3_X = 0,
	Map3_Y = 448,

	Map4 = 400,
	Map4_Rows = 7,
	Map4_Columns = 35,
	Map4_Tile = 244,
	Map4_X = 0,
	Map4_Y = 672,

	Map5 = 500,
	Map5_Rows = 7,
	Map5_Columns = 35,
	Map5_Tile = 245,
	Map5_X = 0,
	Map5_Y = 896,

	Map6 = 600,
	Map6_Rows = 7,
	Map6_Columns = 36,
	Map6_Tile = 217,
	Map6_X = 1120,
	Map6_Y = 0,

	Map7 = 700,
	Map7_Rows = 7,
	Map7_Columns = 36,
	Map7_Tile = 249,
	Map7_X = 1120,
	Map7_Y = 224,

	Map8 = 800,
	Map8_Rows = 7,
	Map8_Columns = 36,
	Map8_Tile = 247,
	Map8_X = 1120,
	Map8_Y = 448,

	Map9 = 900,
	Map9_Rows = 7,
	Map9_Columns = 36,
	Map9_Tile = 245,
	Map9_X = 1120,
	Map9_Y = 672,

	Map10 = 1000,
	Map10_Rows = 7,
	Map10_Columns = 36,
	Map10_Tile = 243,
	Map10_X = 1120,
	Map10_Y = 896,

	MapBoss=1100,
	MapBoss_Rows=7,
	MapBoss_Columns=26,
	MapBoss_Tile=147,
	MapBoss_X=0,
	MapBoss_Y=0,


	MapBoss2 = 1200,
	MapBoss2_Rows = 7,
	MapBoss2_Columns = 26,
	MapBoss2_Tile = 141,
	MapBoss2_X = 0,
	MapBoss2_Y = 224,

	BossBackGround=1300,
	//MapObject
	Map_Object = 10000
};
