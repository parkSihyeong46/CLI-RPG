﻿#include "GameInfo.h"

GameInfo* GameInfo::gameInfoInstance = nullptr;

GameInfo* GameInfo::GetInstance()
{
	if (gameInfoInstance == nullptr)
		gameInfoInstance = new GameInfo();
	
	return gameInfoInstance;
}

void GameInfo::ReleaseInstance()
{
	if (gameInfoInstance)
	{
		delete gameInfoInstance;
		gameInfoInstance = nullptr;
	}
}

const char(*GameInfo::GetShape(const int character))[SHAPE_COL]
{
	switch (character)
	{
	case MYPLAYER:
		return playerShape;
	case SLIME:
		return slimeShape;

		//적추가하면넣기


	default:
		return playerShape;
	}
		
}

//테스트용
map<string, string> GameInfo::GetShape1(const int character)
{
	switch (character)
	{
	//case MYPLAYER:
	//	return playerShape;
	case SLIME:
		return slimeShape2;
	case ITEMBOX:
		return itemBoxShape;
	case OAK:
		return oakShape;

	//default:
	//	return playerShape;
	}
}

string GameInfo::GetItemShape(string itemName, int option)
{
	try
	{
		switch (option)
		{
		case WEAPON:
			return weapon[itemName];
		case ITEM:
			break;
		case WEAPON_SWING_SHAPE:
			return weaponShape[itemName];
		default:
			break;
		}
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
}

const int GameInfo::ReadFileInt(const char* section, const char* key, const char* path)
{
	return GetPrivateProfileIntA(section, key, 0, path);
 }

void GameInfo::ReadFileString(const char* section, const char* key, const char* path)
{
	GetPrivateProfileString(section, key,"", loadData, sizeof(loadData), path);
}

void GameInfo::LoadWeaponData()
{
	ReadFileString("weapon", "sword", "GameInfo\\weapon.ini");	//칼
	for (int index = 0; index < 2; index++)
		tempChar[index] = loadData[index];

	weapon.insert(pair<string, char*>("sword", tempChar));

	ReadFileString("weapon", "axe", "GameInfo\\weapon.ini");	//도끼
	for (int index = 0; index < 2; index++)
		tempChar[index] = loadData[index];

	weapon.insert(pair<string, char*>("axe", tempChar));

	//=================================================================

	ReadFileString("weaponSwing", "sword", "GameInfo\\weaponSwing.ini");	//칼 공격 모션
	for (int index = 0; index < 2; index++)
		tempChar[index] = loadData[index];

	weaponShape.insert(pair<string, char*>("sword", tempChar));

	ReadFileString("weaponSwing", "axe", "GameInfo\\weaponSwing.ini");	//도끼 공격 모션
	for (int index = 0; index < 2; index++)
		tempChar[index] = loadData[index];

	weaponShape.insert(pair<string, char*>("axe", tempChar));
}

void GameInfo::LoadItemBoxShape()
{
	ReadFileString("itembox", "head", "GameInfo\\itemBox.ini");
	itemBoxShape["head"] = loadData;

	ReadFileString("itembox", "body", "GameInfo\\itemBox.ini");
	itemBoxShape["body"] = loadData;

	ReadFileString("itembox", "legs", "GameInfo\\itemBox.ini");
	itemBoxShape["legs"] = loadData;
}

void GameInfo::LoadSaveData(int dataNumber)
{
	switch (dataNumber)
	{
	case 1:
		LoadPlayerStats(dataNumber);
		break;
	case 2:
		LoadPlayerStats(dataNumber);
		break;
	default:
		LoadPlayerStats(dataNumber);
		break;	//새게임
	}
}

void GameInfo::LoadPlayerStats(int dataNumber)
{
	int hp = 0;
	int power = 0;

	switch (dataNumber)
	{
	case 1:
		hp = ReadFileInt("player", "hp", "GameInfo\\player.ini");//섹션수정
		power = ReadFileInt("player", "power", "GameInfo\\player.ini");//섹션수정
		break;
	case 2:
		hp = ReadFileInt("player", "hp", "GameInfo\\player.ini");	//섹션수정
		power = ReadFileInt("player", "power", "GameInfo\\player.ini");//섹션수정
		break;
	default:
		hp = ReadFileInt("player", "hp", "GameInfo\\player.ini");
		power = ReadFileInt("player", "power", "GameInfo\\player.ini");
		break;
	}
	player->SetStats(hp, power);
}

void GameInfo::LoadPlayerShape(int dataNumber)
{
	for (int row = 0; row < SHAPE_ROW; row++)	//플레이어 기본 모습 로드
	{
		switch (row)
		{
		case 0:ReadFileString("player", "head", "GameInfo\\player.ini");	//머리
			for (int col = 0; col < SHAPE_COL; col++)
				playerShape[row][col] = loadData[col];
			break;
		case 1:ReadFileString("player", "body", "GameInfo\\player.ini");	//몸
			for (int col = 0; col < SHAPE_COL; col++)
				playerShape[row][col] = loadData[col];
			break;
		case 2:ReadFileString("player", "legs", "GameInfo\\player.ini");	//기본다리
			for (int col = 0; col < SHAPE_COL; col++)
				playerShape[row][col] = loadData[col];
			break;
		case 3:ReadFileString("player", "walkingRight1", "GameInfo\\player.ini");	//우측이동모션1
			for (int col = 0; col < SHAPE_COL; col++)
				playerShape[row][col] = loadData[col];
			break;
		case 4:ReadFileString("player", "walkingRight2", "GameInfo\\player.ini");	//우측이동모션2
			for (int col = 0; col < SHAPE_COL; col++)
				playerShape[row][col] = loadData[col];
			break;
		case 5:ReadFileString("player", "walkingLeft1", "GameInfo\\player.ini");	//좌측이동모션1
			for (int col = 0; col < SHAPE_COL; col++)
				playerShape[row][col] = loadData[col];
			break;
		case 6:ReadFileString("player", "walkingLeft2", "GameInfo\\player.ini");	//좌측이동모션2
			for (int col = 0; col < SHAPE_COL; col++)
				playerShape[row][col] = loadData[col];
			break;
		case 7:ReadFileString("playerState", "head", "GameInfo\\player.ini");	//줍기모션(머리)
			for (int col = 0; col < SHAPE_COL; col++)
				playerShape[row][col] = loadData[col];
			break;
		case 8:ReadFileString("playerState", "body", "GameInfo\\player.ini");	//줍기모션(몸통)
			for (int col = 0; col < SHAPE_COL; col++)
				playerShape[row][col] = loadData[col];
			break;
		case 9:ReadFileString("playerState", "legs", "GameInfo\\player.ini");	//줍기모션(다리)
			for (int col = 0; col < SHAPE_COL; col++)
				playerShape[row][col] = loadData[col];
			break;
		}
	}
}

void GameInfo::LoadSlimeStats()
{
	slime = Slime::GetInstance();

	if (slime != nullptr)
	{
		for (int i = 0; i < slime->size(); i++)		//슬라임객체에 체력과 공격력과 속도넣기
			(*slime)[i]->SetStats(ReadFileInt("slime", "hp", "gameinfo\\slime.ini"), ReadFileInt("slime", "power", "gameinfo\\slime.ini"), ReadFileInt("slime", "speed", "gameinfo\\slime.ini") - i*200);
	}
}

void GameInfo::LoadSlimeShape()
{
	for (int col = 0; col < SHAPE_ROW; col++)
	{
		switch (col)
		{
		case 0:
			ReadFileString("slime", "head", "GameInfo\\slime.ini");	//머리
			slimeShape2["head"] = loadData;
			//for (int row = 0; row < SHAPE_COL; row++)
			//	slimeShape[col][row] = loadData[row];
			break;
		case 1:
			ReadFileString("slime", "body", "GameInfo\\slime.ini");	//몸
			slimeShape2["body"] = loadData;
			//for (int row = 0; row < SHAPE_COL; row++)
			//	slimeShape[col][row] = loadData[row];
			break;
		case 2:
			ReadFileString("slime", "legs", "GameInfo\\slime.ini");	//다리
			slimeShape2["legs"] = loadData;
			//for (int row = 0; row < SHAPE_COL; row++)
			//	slimeShape[col][row] = loadData[row];
			break;
		}
	}
}

void GameInfo::LoadOakStats()
{
	oak = Oak::GetInstance();

	if (oak != nullptr)
	{
		for (int i = 0; i < oak->size(); i++)		//오크객체에 체력과 공격력과 속도넣기
			(*oak)[i]->SetStats(ReadFileInt("oak", "hp", "gameinfo\\oak.ini"), ReadFileInt("oak", "power", "gameinfo\\oak.ini"), ReadFileInt("oak", "speed", "gameinfo\\oak.ini") - i * 200);
	}
}

void GameInfo::LoadOakShape()
{
	ReadFileString("oak", "head", "GameInfo\\oak.ini");	//머리
	oakShape["head"] = loadData;

	ReadFileString("oak", "body", "GameInfo\\oak.ini");	//몸
	oakShape["body"] = loadData;

	ReadFileString("oak", "legs", "GameInfo\\oak.ini");	//다리
	oakShape["legs"] = loadData;
}
