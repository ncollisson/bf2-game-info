#pragma once
#include <d3dx9.h>

class Velocity_Object
{
public:
	virtual void vf1() {};
	virtual void vf2() {};
	virtual void vf3() {};
	virtual void vf4() {};
	virtual void vf5() {};
	virtual void vf6() {};
	virtual void vf7() {};
	virtual void vf8() {};
	virtual void vf9() {};
	virtual void vf10() {};
	virtual void vf11() {};
	virtual void vf12() {};
	virtual void vf13() {};
	virtual void vf14() {};
	virtual void vf15() {};
	virtual void vf16() {};
	virtual void vf17() {};
	virtual D3DXVECTOR3* GetPosition();

	char u1[0x20];
	D3DXVECTOR3 velocity;
};

class Object_2
{
public:
	char u1[0x350];
	int vehicleClass;
};

class Physical_Object
{
public:
	int u3[5];
	Object_2* object_2;
	int u1[11];
	Velocity_Object* velocity_object;
	char u2[0xB8 - 0x48];
	D3DXVECTOR3 coords;
};

class Object_1
{
public:
	char u1[0x4];
	Physical_Object* physical_object;
};

class Player
{
public:
	D3DXVECTOR3* GetCoords();
	D3DXVECTOR3* GetVelocity();
	D3DXVECTOR3* GetPosition();
	int GetTeam();
	int GetVehicleClass();
	unsigned char isManDown();
	unsigned char isAlive();

private:

	char u1[0x80];
	Object_1* object_1;
	char u3[0x48];
	Object_1* object_12;
	char u2[0x54 - 0x4C];
	int team;
};