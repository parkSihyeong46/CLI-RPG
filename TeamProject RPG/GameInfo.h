﻿#pragma once
#include <Windows.h>
#include <map>
#include "Player.h"
#include "Slime.h"
#include "Tank.h"
#include "Oak.h"

constexpr auto SHAPE_ROW = 10;
constexpr auto SHAPE_COL = 3;

class GameInfo
{
private:
	map<string, string> playerShape;

	map<string, string> slimeShape;
	map<string, string> oakShape;
	map<string, string> tankShape;

	map<string, string> weaponShape;
	map<string, string> weaponSwingShape;
	map<string, string> itemBoxShape;
	Player* player = Player::GetInstance();
	static GameInfo* gameInfoInstance;

	TCHAR loadData[256] = { '\0' };
	GameInfo() {};
public:
	static GameInfo* GetInstance();
	static void ReleaseInstance();

	const map<string, string>& GetShape(const int& character);

	const string& GetItemShape(string itemName, int option);	//0 : 무기, 1 : 아이템
	
	const int ReadFileInt(const char* section, const char* key, const char* path);
	void ReadFileString(const char* section, const char* key, const char* path);

	void LoadWeaponData();
	void LoadItemBoxShape();

	void LoadNewData();
	void LoadPlayerStats(const string& path, const string& name);
	void LoadPlayerShape();
	void LoadInventoryItem(const string& path, const string& name);

	void LoadMonsterShape(vector<Monster*>* monster);
	void LoadMonsterStats(vector<Monster*>* monster);
	void LoadMonsterDefaultSettingValue(vector<Monster*>* monster);

	void WriteData(string tempSection, string tempKey, string tempValue, string tempPath);
};
const enum items{
	WEAPON,
	ITEM,
	WEAPON_SWING_SHAPE

};
const enum characters{
	MYPLAYER,
	SLIME,
	OAK,
	TANK,
	ITEMBOX		//..나중에 옮기기
	//그외에 적들 추가후 GetShape()에 넣기
};

