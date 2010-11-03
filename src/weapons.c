/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#include "../include/weapons.h"

void AddWeapon(short id, char name[], short wpndmg, short wpndmg_z1,
		short wpndmg_z2, short freq, short speed, short slot, short price,
		short range, short accuracy, short ammo1, short ammo2, int reloadtime,
		short special, short team)
{
	if (name != NULL)
	{
		weapons[id].name = malloc(strlen(name) + 1);
		if (weapons[id].name == NULL)
			error_exit("Memory Error in AddWeapon()\n");
		strncpy(weapons[id].name, name, strlen(name) + 1);
	}
	else
	{
		weapons[id].name = NULL;
	}
	weapons[id].weapondamage = wpndmg;
	weapons[id].weapondamage_z1 = wpndmg_z1;
	weapons[id].weapondamage_z2 = wpndmg_z2;
	if (freq != 0)
		weapons[id].freq = (short) (1 / freq) * 60 * 1000;
	else
		weapons[id].freq = 1000;
	weapons[id].speed = speed;
	weapons[id].slot = slot;
	weapons[id].price = price;
	weapons[id].range = range;
	weapons[id].accuracy = accuracy;
	weapons[id].ammo1 = ammo1;
	weapons[id].ammo2 = ammo2;
	weapons[id].reloadtime = reloadtime;
	weapons[id].special = special;
	weapons[id].team = team;
}
void WeaponInit()
{
	int i;
	for (i = 0; i <= 99; i++)
	{
		AddWeapon(i, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	AddWeapon(1, "USP", 24, 0, 0, 166, 1, 2, 500, 300, 0, 12, 100, 1000, 1, 0);
	AddWeapon(2, "Glock", 21, 0, 0, 166, 1, 2, 400, 250, 0, 20, 120, 1000, 2, 0);
	AddWeapon(3, "Deagle", 34, 0, 0, 100, 1, 2, 550, 300, 0, 7, 35, 1000, 0, 0);
	AddWeapon(4, "P228", 22, 0, 0, 166, 1, 2, 600, 300, 0, 13, 35, 1000, 0, 0);
	AddWeapon(5, "Elite", 22, 0, 0, 187, 1, 2, 1000, 300, 0, 13, 120, 1000, 0,
			0);
	AddWeapon(6, "Five-Seven", 21, 0, 0, 187, 1, 2, 750, 300, 0, 20, 100, 2000,
			0, 0);
	AddWeapon(20, "MP5", 13, 0, 0, 500, 1, 1, 1500, 300, 2, 30, 120, 1000, 0, 0);
	AddWeapon(21, "TMP", 9, 0, 0, 750, 1, 1, 1250, 100, 4, 30, 120, 1000, 0, 2);
	AddWeapon(22, "P90", 11, 0, 0, 750, 1, 1, 2350, 300, 3, 50, 100, 1000, 0, 2);
	AddWeapon(35, "AWP", 50, 65, 150, 23, 3, 1, 4750, 400, 0, 10, 30, 2000, 5,
			0);
	AddWeapon(50, "Knife", 50, 100, 0, 1, 1, 2, 0, 8, 0, -1, -1, 0, 3, 0);
}

