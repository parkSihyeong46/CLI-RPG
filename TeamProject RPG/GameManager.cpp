﻿#include "GameManager.h"

void GameManager::Play(int saveFileNumber)
{
	gameInfo->LoadSaveData(saveFileNumber); // 세이브파일 번호
	gameInfo->LoadPlayerShape(saveFileNumber);
}

void GameManager::StartDungeon(int dungeonNumber)
{
	bool loop = true;

	map = new MapManager();
	map->LoadMap(dungeonNumber);

	slime = Slime::GetInstance();
	if (slime != nullptr)		//슬라임객체가 존재하면 슬라임형태 불러오기 + 슬라임에 스텟설정하기
	{
		gameInfo->LoadSlimeShape();
		gameInfo->LoadSlimeStats();
	}
	//다른몬스터도 추가되면 넣기

	while (loop)
	{
		if (delayManager.CheckEndDelay())
		{
			map->PrintMap();
			player->Move();

			//if문안에 넣은이유 : 슬라임말고 다른몬스터도 있기때문에 뒤쪽까지 검사해야해서 return;하면안됨
			if (slime != nullptr)
			{
				for (int i = 0; i < slime->size(); i++)
					(*slime)[i]->Move(i);
			}

		}
	}


}

void GameManager::CheckContact()
{

}

