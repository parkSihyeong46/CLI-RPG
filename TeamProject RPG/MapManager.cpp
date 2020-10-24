﻿#include "MapManager.h"

void MapManager::GoToXY(SHORT x, SHORT y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void MapManager::LoadMap(int num)
{
	string currentDungeon;
	int y = 0;
	char mapPiece;
	int slimeNumber = 0;

	switch (num)
	{
	case 1:
		fcin.open("MapInfo\\dungeon1.txt");
		getline(fcin, currentDungeon);

		for (int y = 0; y < MAP_ROW; y++)
		{
			for (int x = 0; x < MAP_COL; x++)
			{
				fcin.get(mapPiece);
				if (fcin.eof())
					break;
				if (mapPiece == 'p') 
				{
					player = Player::GetInstance();
					player->SetPos(x, y);
					mapPiece = ' ';
				}
				else if (mapPiece == 's')		//슬라임이 있을 때 마다 슬라임객체생성후 벡터에넣고 위치저장
				{
					Slime::AddInstance();
					slime = Slime::GetInstance();
					(*slime)[slimeNumber++]->SetPos(x, y);
					mapPiece = ' ';
				}	
				map[y][x] = mapPiece;
			}
		}
		break;
	case 2:
		fcin.open("MapInfo\\dungeon2.txt");
		getline(fcin, currentDungeon);
		break;
	default:
		cout << "맵 로드 오류!!";
		break;
	}

	//플레이어가 움직일 수 있는 범위 측정
	LoadCanMovePos();
}

void MapManager::PrintMap()
{
	//원본맵을 출력할 맵에 복사 후
	for (int col = 0; col < MAP_ROW; col++)
	{
		for (int row = 0; row < MAP_COL; row++)
			tempMap[col][row] = map[col][row];
	}

	//캐릭터 정보 가져와서 맵에 동기화
	PrintCharacter(player);
	PrintWeapon(player->GetHoldWeapon());
	if(slime != nullptr)
		PrintSlime(slime);

	//출력할 맵 출력
	GoToXY(0, 0);
	for (int y = 0; y < MAP_ROW; y++)
	{
		for (int x = 0; x < MAP_COL; x++)
			cout << tempMap[y][x];
	}
}

void MapManager::PrintCharacter(Character* character)
{
	auto tempPlayerShape = gameInfo->GetShape(MYPLAYER);

	int playerPosX = player->GetPos().GetX();
	int playerPosY = player->GetPos().GetY();

	//기준점 좌표로 부터 왼쪽 상단으로 이동해 이미지[0][0~3] 출력한다.
	//머리 출력
	for (int index = 0; index < SHAPE_COL; index++)
		tempMap[playerPosY - 2][playerPosX - 1+ index] = tempPlayerShape[0][index];


	//기준점 좌표 y-1 지점으로 이동해 이미지[1][0~3] 출력한다.
	//몸 출력
	for (int index = 0; index < SHAPE_COL; index++)
		tempMap[playerPosY - 1][playerPosX - 1 + index] = tempPlayerShape[1][index];

	//기준점 좌표 x-1 지점으로 이동해 이미지[2][0~3] 출력한다.
	//다리 출력
	if (!player->GetIsWalking())
	{
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape[2][index];
	}
	else
	{
		switch (player->GetWalkCount())
		{
		case 0:
			if (LEFT == player->GetDir())
			{	//왼쪽1번다리 출력
				for (int index = 0; index < SHAPE_COL; index++)
					tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape[5][index];
			}
			else if (RIGHT == player->GetDir())
			{	//오른쪽1번다리 출력
				for (int index = 0; index < SHAPE_COL; index++)
					tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape[3][index];
			}
			break;
		case 1:
			if (LEFT == player->GetDir())
			{	//왼쪽2번다리 출력
				for (int index = 0; index < SHAPE_COL; index++)
					tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape[6][index];
			}
			else if(RIGHT == player->GetDir())
			{	//오른쪽2번다리 출력
				for (int index = 0; index < SHAPE_COL; index++)
					tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape[4][index];
			}
			break;
		}
	}
}

void MapManager::PrintWeapon(string weapon)
{
	string tempWeaponShape, tempWeaponSwingShape;
	tempWeaponShape = gameInfo->GetItemShape(weapon,WEAPON);
	tempWeaponSwingShape = gameInfo->GetItemShape(weapon, WEAPON_SWING_SHAPE);

	if (tempWeaponShape.size() == 0)
		return;

	int playerPosX = player->GetPos().GetX();
	int playerPosY = player->GetPos().GetY();

	if (player->GetIsAttacking() && RIGHT == player->GetDir())	//공격모션 출력
	{
		for (int index = 0; index < tempWeaponSwingShape.size(); index++)
			tempMap[playerPosY - 1][playerPosX + 3 + index] = tempWeaponSwingShape[index];
	}
	else if (player->GetIsAttacking() && LEFT == player->GetDir())
	{
		for (int index = 0; index < tempWeaponSwingShape.size(); index++)
			tempMap[playerPosY - 1][playerPosX - 3 + index] = tempWeaponSwingShape[(tempWeaponSwingShape.size()-1)-index];
	}
	else if (!player->GetIsAttacking() && RIGHT == player->GetDir())	//스탠드모션 출력
	{
		for (int index = 0; index < tempWeaponShape.size(); index++)
			tempMap[playerPosY - 2 + index][playerPosX + 2] = tempWeaponShape[index];
	}
	else if (!player->GetIsAttacking() && LEFT == player->GetDir())
	{
		for (int index = 0; index < tempWeaponShape.size(); index++)
			tempMap[playerPosY - 2 + index][playerPosX - 2] = tempWeaponShape[index];
	}
}

void MapManager::PrintSlime(vector<Slime*>* slime)
{
	auto slimeShape = gameInfo->GetShape(SLIME);
	int slimePosX;
	int slimePosY;

	//슬라임객체수만큼 반복
	for (int i = 0; i < slime->size(); i++)
	{
		slimePosX = (*slime)[i]->GetPos().GetX();
		slimePosY = (*slime)[i]->GetPos().GetY();

		//머리 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[slimePosY - 2][slimePosX - 1 + index] = slimeShape[0][index];

		//몸 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[slimePosY - 1][slimePosX - 1 + index] = slimeShape[1][index];

		//다리 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[slimePosY][slimePosX - 1 + index] = slimeShape[2][index];
	}
}

void MapManager::LoadCanMovePos()
{
	//플레이어가 움직일 수 없는 범위 왼쪽 상단 측정
	for (int row = 0; row < MAP_ROW; row++)
	{
		for (int col = 0; col < MAP_COL; col++)
		{
			if (map[row][col] == '*')
			{
				dontMovePos[0].SetX(col);
				dontMovePos[0].SetY(row);
				row = MAP_ROW;
				break;
			}
		}
	}
	//플레이어가 움직일 수 없는 범위 오른쪽 하단 측정
	for (int row = MAP_ROW - 1; row > 0; row--)
	{
		for (int col = MAP_COL - 1; col > 0; col--)
		{
			if (map[row][col] == '*')
			{
				dontMovePos[1].SetX(col);
				dontMovePos[1].SetY(row);
				row = 0;
				break;
			}
		}
	}
}

Pos* MapManager::GetDontMovePos()
{
	return dontMovePos;
}
