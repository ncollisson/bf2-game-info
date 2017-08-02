#include "stdafx.h"
#include <d3dx9.h>
#include "bf2-player.h"

D3DXVECTOR3* Player::GetCoords()
{
	Object_1* a = object_1;
	if (a == NULL) return NULL;

	Physical_Object* b = a->physical_object;
	if (b == NULL) return NULL;

	D3DXVECTOR3* coords;
	coords = (D3DXVECTOR3*)((char *)b + 0xB8);

	return coords;
}

D3DXVECTOR3* Player::GetPosition()
{
	/*Object_1* a = object_1;
	if (a == NULL) return NULL;

	Physical_Object* b = a->physical_object;
	if (b == NULL) return NULL;

	Velocity_Object* c = b->velocity_object;
	if (c == NULL)
	{*/
		Object_1* a = object_12;
		if (a == NULL) return NULL;

		Physical_Object* b = a->physical_object;
		if (b == NULL) return NULL;

		Velocity_Object* c = b->velocity_object;
		if (c == NULL) return NULL;
	//}

	D3DXVECTOR3* position = c->GetPosition();

	return position;
}

D3DXVECTOR3* Player::GetVelocity()
{
	Object_1* a = object_1;
	if (a == NULL) return NULL;

	Physical_Object* b = a->physical_object;
	if (b == NULL) return NULL;

	Velocity_Object* c = b->velocity_object;
	if (c == NULL) return NULL;

	D3DXVECTOR3* velocity;
	velocity = (D3DXVECTOR3*)&(c->velocity);

	return velocity;
}

int Player::GetTeam()
{
	return team;
}

int Player::GetVehicleClass()
{
	Object_1* a = object_1;
	if (a == nullptr) return 10;

	Physical_Object* b = a->physical_object;
	if (b == nullptr) return 10;

	Object_2* c = b->object_2;
	if (c == nullptr) return 10;

	return c->vehicleClass;
}

unsigned char Player::isManDown()
{
	unsigned char isManDown = *(u1 + 0xE8);

	return isManDown;
}

unsigned char Player::isAlive()
{
	unsigned char isAlive = *(u1 + 0xD5);

	return isAlive;
}