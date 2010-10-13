#include "../include/weapons.h"

void AddWeapon(short id, char name[], short wpndmg, short wpndmg_z1, short wpndmg_z2, short freq, short speed, short slot, short price, short range, short accuracy, short ammo1, short ammo2)
{
	if(name != NULL)
	{
		weapons[id].name             = malloc(strlen(name)+1);
		if(weapons[id].name == NULL) error_exit("Memory Error in AddWeapon()\n");
		strncpy(weapons[id].name, name, strlen(name)+1);
	}
	else
	{
		weapons[id].name         = NULL;
	}
    weapons[id].weapondamage     = wpndmg;
    weapons[id].weapondamage_z1  = wpndmg_z1;
    weapons[id].weapondamage_z2  = wpndmg_z2;
    weapons[id].freq             = freq;
    weapons[id].speed            = speed;
    weapons[id].slot             = slot;
    weapons[id].price            = price;
    weapons[id].range            = range;
    weapons[id].accuracy         = accuracy;
    weapons[id].ammo1            = ammo1;
    weapons[id].ammo2            = ammo2;
}
void WeaponInit()
{
	int i;
	for(i = 0; i <= 99; i++)
	{
		AddWeapon(i, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0);
	}
    AddWeapon(1, "USP"   , 24 , 0, 0, 166 , 1, 2, 500, 300, 0 , 12, 100);
    AddWeapon(2, "Glock" , 21 , 0, 0, 166 , 1, 2, 400, 250, 0 , 20, 120);
    AddWeapon(3, "Deagle", 34 , 0, 0, 100 , 1, 2, 550, 300, 0 , 7 , 35 );
    AddWeapon(50, "Knife", 100, 0, 0, 1   , 1, 2, 0  , 8  , 0 , -1, -1 );
}


