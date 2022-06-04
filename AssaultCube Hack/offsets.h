#pragma once
#include "pch.h"

struct Vector3 {float x, y, z; };

// Created with ReClass.NET 1.2 by KN4CK3R

class LocalPlayer
{
public:
	Vector3 head; //0x0004
	float xForce; //0x0010
	float yForce; //0x0014
	float zForce; //0x0018
	char pad_001C[12]; //0x001C
	Vector3 curVelocity; //0x0028
	float xCoord; //0x0034
	float yCoord; //0x0038
	float zCoord; //0x003C
	float yaw; //0x0040
	float pitch; //0x0044
	float roll; //0x0048
	float pitchForce; //0x004C
	char pad_0050[24]; //0x0050
	bool inWater; //0x0068
	bool onGround; //0x0069
	bool onLadder; //0x006A
	bool jump; //0x006B
	char pad_006C[4]; //0x006C
	int32_t isStill; //0x0070
	char pad_0074[12]; //0x0074
	int32_t movement; //0x0080
	char pad_0084[116]; //0x0084
	int32_t health; //0x00F8
	int32_t armor; //0x00FC
	char pad_0100[20]; //0x0100
	int32_t pistolAmmo; //0x0114
	int32_t carbineAmmo; //0x0118
	int32_t shotgunAmmo; //0x011C
	int32_t smgAmmo; //0x0120
	int32_t sniperAmmo; //0x0124
	int32_t arAmmo; //0x0128
	char pad_012C[16]; //0x012C
	int32_t pistolMagazine; //0x013C
	int32_t carbineMagazine; //0x0140
	int32_t shotgunMagazine; //0x0144
	int32_t smgMagazine; //0x0148
	int32_t sniperMagazine; //0x014C
	int32_t arMagazine; //0x0150
	char pad_0154[4]; //0x0154
	int32_t grenadeAmmo; //0x0158
	char pad_015C[4]; //0x015C
	int32_t knifeCd; //0x0160
	int32_t pistolCd; //0x0164
	int32_t carbineCd; //0x0168
	int32_t shotgunCd; //0x016C
	int32_t smgCd; //0x0170
	int32_t sniperCd; //0x0174
	int32_t arCd; //0x0178
	char pad_017C[4]; //0x017C
	int32_t grenadeCd; //0x0180
	char pad_0184[96]; //0x0184
	int32_t clientNumber; //0x01E4
	char pad_01E8[61]; //0x01E8
	char name[16]; //0x0225
	char pad_0235[247]; //0x0235
	int32_t team; //0x032C
	char pad_0330[68]; //0x0330
	class weapon* curWeapon; //0x0374
	char pad_0378[264]; //0x0378

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0480
static_assert(sizeof(LocalPlayer) == 0x480);

class currentWeapon
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044
static_assert(sizeof(currentWeapon) == 0x44);

class weapon
{
public:
	char pad_0000[8]; //0x0000
	class N00000618* N000001A4; //0x0008
	class wpnBaseStats* weapBase; //0x000C
	class wpnStats* wpnstatPtr; //0x0010
	char pad_0014[4]; //0x0014
	class N00000604* N000001A8; //0x0018
	char pad_001C[40]; //0x001C
}; //Size: 0x0044
static_assert(sizeof(weapon) == 0x44);

class wpnStats
{
public:
	int32_t ammo; //0x0000
	char pad_0004[36]; //0x0004
	int32_t magazine; //0x0028
	char pad_002C[36]; //0x002C
	int32_t cooldown; //0x0050
}; //Size: 0x0054
static_assert(sizeof(wpnStats) == 0x54);

class wpnBaseStats
{
public:
	char pad_0000[260]; //0x0000
	int16_t N00000209; //0x0104
	int16_t N000002DA; //0x0106
	int16_t N0000020A; //0x0108
	int16_t cooldown; //0x010A
	int16_t N0000020B; //0x010C
	int16_t N000002DE; //0x010E
	int16_t N0000020C; //0x0110
	int16_t N000002E0; //0x0112
	int16_t baseSpread; //0x0114
	int16_t knockback; //0x0116
	int16_t N0000020E; //0x0118
	int16_t animUpForce; //0x011A
	int16_t animKickback; //0x011C
	int16_t N000002E6; //0x011E
	int16_t minRecoilVel; //0x0120
	int16_t maxRecoilVel; //0x0122
	int16_t N00000211; //0x0124
	int16_t N000002EA; //0x0126
}; //Size: 0x0128
static_assert(sizeof(wpnBaseStats) == 0x128);

class N00000604
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044
static_assert(sizeof(N00000604) == 0x44);

class N00000618
{
public:
	char pad_0000[1092]; //0x0000
}; //Size: 0x0444
static_assert(sizeof(N00000618) == 0x444);