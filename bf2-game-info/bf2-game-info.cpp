#include "stdafx.h"
#include "bf2-game-info.h"
#include "GameInfo.h"
#include "bf2-player.h"
#include "Psapi.h"

Player* GetPlayerByIndex(unsigned int index)
{
	unsigned int anchor_1 = 0xA08F06;

	unsigned int object_1 = *(unsigned int *)anchor_1;
	if (object_1 == NULL) return NULL;

	unsigned int dbl_linked_player_list = *(unsigned int *)(object_1 + 0x10);
	if (dbl_linked_player_list == NULL) return NULL;

	Player* player = NULL;
	pl_node* current_node = (pl_node *)dbl_linked_player_list;
	// do i need to deref here?

	for (unsigned int i = 0; i != index; i++)
	{
		if (i != 0 && current_node->player == NULL) return NULL;
		current_node = current_node->next;
	}

	return current_node->player;
}

unsigned int GetRendDX9Base()
{
	HANDLE h_process = GetCurrentProcess();
	HMODULE h_renddx9 = GetModuleHandle(L"RendDX9.dll");
	MODULEINFO modinfo;

	GetModuleInformation(h_process, h_renddx9, &modinfo, sizeof(modinfo));

	CloseHandle(h_process);

	unsigned int renddx9_base = (unsigned int)modinfo.lpBaseOfDll;

	return renddx9_base;
}

int GetBF2GameInfo()
{
	HANDLE hGameInfoMem = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, TEXT("bf2-game-info"));

	GameInfo* gameInfo = (GameInfo*) MapViewOfFile(hGameInfoMem, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	unsigned int renddx9_base = GetRendDX9Base();

	while (true)
	{
		gameInfo->myCamera = *(D3DXMATRIX*) (renddx9_base + 0x25e64c);
		gameInfo->myZoom = *(float*)(renddx9_base + 0x25e64c + 0x58);

		Player* currentPlayer = nullptr;
		unsigned int numberOfPlayers = 0;
		D3DXVECTOR3* position = nullptr, * position2 = nullptr;
		unsigned int team, isManDown, isAlive;
		int vehicleClass;

		for (unsigned int i = 1; i <= 128; i++)
		{
			currentPlayer = GetPlayerByIndex(i);

			if (currentPlayer == nullptr) break;

			position = currentPlayer->GetCoords();

			position2 = currentPlayer->GetPosition();
			if (position2 != nullptr) position = position2;
			if (position == nullptr) continue;

			vehicleClass = currentPlayer->GetVehicleClass();
			team = currentPlayer->GetTeam();
			isAlive = currentPlayer->isAlive();
			isManDown = currentPlayer->isManDown();

			gameInfo->playerInfo[numberOfPlayers].position = *position;
			gameInfo->playerInfo[numberOfPlayers].team = team;
			gameInfo->playerInfo[numberOfPlayers].vehicleClass = vehicleClass;
			gameInfo->playerInfo[numberOfPlayers].isAlive = isAlive;
			gameInfo->playerInfo[numberOfPlayers].isManDown = isManDown;

			numberOfPlayers++;
		}

		gameInfo->numberOfPlayers = numberOfPlayers;

		Sleep(10);
	}
}
