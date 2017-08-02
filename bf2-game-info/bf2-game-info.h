 #pragma once
#include "bf2-player.h"

int GetBF2GameInfo();

typedef struct player_list_node pl_node;

typedef struct player_list_node
{
	pl_node* next;
	pl_node* prev;
	Player* player;
} pl_node;
