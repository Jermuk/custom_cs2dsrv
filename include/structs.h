/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk, FloooD
 */

#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "main.h"
#define MAX_CLIENTS 64
#define BUFFER_SIZE 100
struct WEAPON
{
	short weapondamage, weapondamage_z1, weapondamage_z2;
	short shoottime, reloadtime;
	short freq; //every freq ms one shoot
	short speed;
	short slot;
	short price;
	short range;
	short accuracy;
	short ammo1, ammo2;
	char *name;
	short special;
	short team;
};
/*
 * team
 * 0 - everyone can buy it
 * 1 - t-only
 * 2 - ct only
 * 3 - unbuyable
 */

struct PLAYER_WEAPON
{
	short id, slot;
	short ammo1, ammo2;
	short special;
};
/*
 * special
 * 0 = Normal
 * 1 = Silencer
 * 2 = Burst
 * 3 = Melee
 * 4 = 1xZoom
 * 5 = 2xZoom
 * 6 = Shotgun
 */

struct PLAYER
{
	int used;
	unsigned short client_nummer;
	unsigned short server_nummer;
	int lastpaket;
	unsigned short joinstatus;

	unsigned char *name;
	unsigned char *spraylogo;
	unsigned char *win;
	unsigned short version;
	unsigned short *usgn;
	unsigned char team;
	unsigned char skin;
	unsigned short deaths;
	short score;
	unsigned short x, y;
	unsigned short buffer_x[BUFFER_SIZE + 1], buffer_y[BUFFER_SIZE +1];
	unsigned char health, armor;
	unsigned char actualweapon;
	struct PLAYER_WEAPON slot[10];
	float rotation; //-180 to +180
	int specposx, specposy;
	unsigned short money;
	unsigned short kills;
	int reloadtimer, reloading;

	short dead;

	int start;
	unsigned short latency;

	int firetimer, zoomtimer;
	int zoommode;

	/* Address*/
	unsigned short port;
	struct in_addr ip;
};
struct PLAYER player[MAX_CLIENTS];

struct TILE
{
	unsigned char mode;
	unsigned char tileid;
};
struct TILE **map;

#endif // STRUCTS_H_INCLUDED
