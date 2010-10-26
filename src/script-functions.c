/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#include "../include/script-functions.h"

/*
 int OnJoin(int id, int writesocket)
 id - Who joins
 Return Values:
 0 - OK
 */
int OnJoin(int id, int writesocket)
{
	SendJoinMessage(id, writesocket);
	printf("%s (#%d) has joined the game!\n\tUsing ip %s:%d and usgn-id #%d!\n", player[id].name, id, inet_ntoa(player[id].ip), player[id].port, *player[id].usgn);
	return 0;
}

/*
 int OnLeave(int id, int writesocket)
 id - Who leaves
 Return Values:
 0 - OK
 */
int OnLeave(int id, int writesocket)
{
	SendLeaveMessage(id, writesocket);
	printf("%s has left the game!\n", player[id].name);
	return 0;
}

/*
 int OnSpecmove(int id, int newx, int newy, int writesocket)
 Return Values:
 0 - OK
 1 - Don't save it
 */

int OnSpecmove(int id, int newx, int newy, int writesocket)
{
	return 0;
}

/*
 int OnServerstart()
 Return Values:
 0 - OK
 */
int OnServerStart()
{
	time_t rawtime;
	time(&rawtime);
	printf("********** Server started **********\n");
	printf("%s", ctime(&rawtime));
	return 0;
}

/*
 int OnExit()
 Return Values:
 0 - OK
 */
int OnExit()
{
	printf("********** Server Shutdown! **********\n\n\n\n\n");
	return 0;
}

/*
 int OnRespawnRequest(int id, int writesocket)
 Return Values:
 0 - Respawn
 1 - Don't Respawn
 */
int OnRespawnRequest(int id, int writesocket)
{
	if (player[id].dead == 1)
		return 0;
	else
		return 1;
}

/*
 int OnRespawn(int id, int writesocket)
 Return Values:
 0 - OK
 */
int OnRespawn(int id, int writesocket)
{
	return 0;
}

/*
 int OnRespawn(int id, int writesocket)
 Return Values:
 0 - OK
 */
int OnWeaponChangeAttempt(int id, int wpnid, int writesocket)
{
	int i;
	for (i = 0; i <= 9; i++)
	{
		if (player[id].slot[i].id == wpnid)
		{
			player[id].actualweapon = i;
			if (weapons[wpnid].special == 4 || weapons[wpnid].special == 5)
			{
				player[id].zoommode = 0;
			}
			player[id].reloading = 0;

			printf("%s switched to %s\n", player[id].name, weapons[player[id].slot[player[id].actualweapon].id].name);
			return 0;
		}
	}
	return 1;
}

/*
 int OnAdvancedFire(int id, int status, int writesocket)
 Return Values:
 0 - OK
 1 - Not OK
 */
int OnAdvancedFire(int id, int status, int writesocket)
{
	int wpnid = player[id].slot[player[id].actualweapon].id;

	int temptime = mtime();
	if (temptime < player[id].zoomtimer)
	{
		printf("Zoomtimer error!\n");
		return 1;
	}
	else
	{
		player[id].zoomtimer = mtime() + 500;
	}

	switch (weapons[wpnid].special)
	{
	case 0:
		printf("%s tried to hack!\n", player[id].name);
		return 1;
	case 1:
	case 2:
	{
		if (status <= 1)
		{
			player[id].zoommode = status;
			break;
		}
		return 1;
	}
	case 3:
	{
		player[id].zoommode = 1;
		OnFire(id, writesocket);
		player[id].zoommode = 0;
		break;
	}
	case 4:
	{
		if (status <= 1)
		{
			player[id].zoommode = status;
			break;
		}
		return 1;
	}
	case 5:
	{
		if (status <= 2 && player[id].zoommode + 1 == status)
		{
			player[id].zoommode = status;
			break;
		}
		else if (player[id].zoommode == 2)
		{
			player[id].zoommode = 0;
			break;
		}
		return 1;
	}
	default:
	{
		SendMessageToPlayer(id, "Not implemented yet!", 1, writesocket);
		return 1;
	}

	}

	return 0;
}
/*
 int OnFire(int id, int writesocket)
 Return Values:
 0 - OK
 1 - Not OK
 */
int OnFire(int id, int writesocket)
{
	//printf("%s tried to shoot!\n", player[id].name);
	short *ammo1 = &player[id].slot[player[id].actualweapon].ammo1;
	if (*ammo1 <= 0 && *ammo1 != -1)
	{
		printf("Not enough ammo!\n");
		return 1;
	}
	else
	{
		if (*ammo1 != -1)
		{
			*ammo1 = *ammo1 - 1;
		}
	}
	int temptime = mtime();
	if (temptime < player[id].firetimer)
	{
		printf("Firetimer error!\n");
		return 1;
	}
	else
	{
		player[id].firetimer = mtime()
				+ weapons[player[id].slot[player[id].actualweapon].id].freq;
	}

	int i;
	int range = weapons[player[id].slot[player[id].actualweapon].id].range;

	int startx = player[id].x;
	int starty = player[id].y;
	float rotx;
	float roty;
	float temprot = player[id].rotation;

	short playershit[MAX_CLIENTS] =
	{ 0 };

	if (temprot < 0)
	{
		temprot = 360 - (temprot * -1);
	}
	temprot = 360 - temprot;

	temprot += 90;
	if (temprot > 360)
	{
		temprot = temprot - 360;
	}

	rotx = cos((temprot) * PI / 180);
	roty = sin((temprot) * PI / 180);

	for (i = 1; i <= range; i++)
	{
		startx += i * rotx;
		starty -= i * roty;

		int tilex = (int) (startx) / 32;
		int tiley = (int) (starty) / 32;

		if (tilex <= 0 || tiley <= 0)
			break;
		int tilemode = map[tilex][tiley].mode;
		if (tilemode == 1 || tilemode == 3 || tilemode == 4)
		{
			break;
		}

		int b;
		for (b = 1; b <= sv_maxplayers; b++)
		{
			if (player[b].used == 1 && player[b].joinstatus >= 4 && b != id
					&& player[b].dead == 0 && playershit[b] == 0
					&& player[id].team != player[b].team)
			{
				if (sqrt((player[b].x - startx) * (player[b].x - startx)
						+ (player[b].y - starty) * (player[b].y - starty))
						<= 16)
				{
					OnHit(id, b, writesocket);
					playershit[b] = 1;
				}
			}
		}
	}
	return 0;
}
/*
 int OnHit(int hitter, int victim, int writesocket)
 Return Values:
 0 - OK
 */
int OnHit(int hitter, int victim, int writesocket)
{
	int wpnid = player[hitter].slot[player[hitter].actualweapon].id;
	int damage;
	switch (player[hitter].zoommode)
	{
	case 0:
		damage = weapons[wpnid].weapondamage;
		break;
	case 1:
		damage = weapons[wpnid].weapondamage_z1;
		break;
	case 2:
		damage = weapons[wpnid].weapondamage_z2;
		break;
	default:
		damage = weapons[wpnid].weapondamage;
		break;
	}
	if (player[victim].health - damage > 0)
	{
		player[victim].health -= damage;
		SendHitMessage(victim, hitter, player[victim].health, writesocket);
		printf("%s hitted %s with %s\n", player[hitter].name, player[victim].name, weapons[wpnid].name);
	}
	else
	{
		OnKill(hitter, victim, wpnid, writesocket);
	}

	return 0;
}

int OnBuyAttempt(int id, int wpnid, int writesocket)
{

	int i;
	for (i = 0; i <= 99; i++)
	{
		if (weapons[wpnid].name != NULL) //test if weapon available
		{
			if (player[id].money - weapons[wpnid].price >= 0)
			{
				if (weapons[wpnid].team == 0 || weapons[wpnid].team
						== player[id].team) //Check if he is in the right team to buy this weapon
				{
					if (player[id].team == 1)
					{
						//Check if in buyzone
						int b;
						for (b = 0; b <= tspawncount; b++)
						{
							int playerx = player[id].x;
							int playery = player[id].y;
							int tempx = tspawnx[b] * 32;
							int tempy = tspawny[b] * 32;
							//If player in buyzone (5*5)
							if (playerx >= tempx - 64 && playerx <= tempx + 64
									&& playery >= tempy - 64 && playery
									<= tempy + 64)
							{
								return 0;
							}
						}
						SendBuyFailedMessage(id, 255, writesocket);
						return 1;
					}
					else if (player[id].team == 2)
					{
						int b;
						for (b = 0; b <= ctspawncount; b++)
						{
							int playerx = player[id].x;
							int playery = player[id].y;
							int tempx = ctspawnx[b] * 32;
							int tempy = ctspawny[b] * 32;
							//If player in buyzone (5*5)
							if (playerx >= tempx - 64 && playerx <= tempx + 64
									&& playery >= tempy - 64 && playery
									<= tempy + 64)
							{
								return 0;
							}
						}
						SendBuyFailedMessage(id, 255, writesocket);
						return 1;
					}
				}
				else
				{
					SendBuyFailedMessage(id, 252, writesocket);
					return 1;
				}
			}
			else
			{
				SendBuyFailedMessage(id, 253, writesocket);
				return 1;
			}
		}
	}
	//if nothing found
	SendBuyFailedMessage(id, 244, writesocket);
	/*
	 * 242 nothing
	 * 243 Grenade rebuying is not allowed at this server
	 * 244 it's not allowed to buy that weapon at this server
	 * 245 you can't carry more of this
	 * 246 you can't carry more of this
	 * 247 you can't carry an additional weapon
	 * 248 you can't buy more ammo
	 * 249 you are not allowed to buy anything
	 * 250 buying is not allowed
	 * 251 you have already this or something better
	 * 252 you can't buy this item;
	 * 253 insufficient fund;
	 * 254 buytime passed;
	 * 255 you are not in a buyzone
	 */
	return 1;
}

int OnBuy(int id, int wpnid, int writesocket)
{
	player[id].money -= weapons[wpnid].price;
	player[id].actualweapon = GivePlayerWeapon(id, wpnid); //Return slot
	printf("%s bought %s!\n", player[id].name, weapons[wpnid].name);
	return 0;
}

int OnKill(int hitter, int victim, int wpnid, int writesocket)
{
	player[victim].health = 0;
	player[victim].dead = 1;
	player[hitter].score++;
	player[hitter].kills++;
	player[victim].deaths++;
	RemoveAllPlayerWeapon(victim);
	SendHitMessage(victim, hitter, player[victim].health, writesocket);
	printf("%s killed %s with %s\n", player[hitter].name, player[victim].name, weapons[wpnid].name);
	return 0;
}
/*
 int OnChatMessage(int id, unsigned char *message, int team, int writesocket)
 Return Values:
 0 - OK
 */
int OnChatMessage(int id, unsigned char *message, int team, int writesocket)
{
	if (team == 1)
	{
		printf("%s: %s\n", player[id].name, message);
	}
	else if (team == 2)
	{
		printf("%s (Team): %s\n", player[id].name, message);
	}
	SendChatMessage(id, message, team, writesocket);
	return 0;
}

/*
 int OnTeamChangeAttempt(int id, unsigned char team, unsigned char skin, int writesocket)
 Return Values:
 0 - OK
 1 - Don't join
 */
int OnTeamChangeAttempt(int id, unsigned char team, unsigned char skin,
		int writesocket)
{
	return 0;
}

/*
 int OnTeamChange(int id, unsigned char team, unsigned char skin, int writesocket)
 Return Values:
 0 - OK
 */
int OnTeamChange(int id, unsigned char team, unsigned char skin,
		int writesocket)
{
	if (skin != 5)
	{
		switch (team)
		{
		case 0:
			printf("%s is now spectator\n", player[id].name);
			break;
		case 1:
			printf("%s is now terrorist\n", player[id].name);
			break;
		case 2:
			printf("%s is now counter-terrorist\n", player[id].name);
			break;
		default:
			printf("%s joined a unknown team\n", player[id].name);
			break;
		}
		SendHitMessage(id, id, 0, writesocket);
		player[id].dead = 1;
		RemoveAllPlayerWeapon(id);
	}
	if (team <= 2)
	{
		SendTeamChangeMessage(id, team, skin, writesocket);
	}
	return 0;
}

/*
 int OnMoveAttempt(int id, unsigned short x, unsigned short y, int status, int writesocket)
 Return Values:
 0 - OK
 1 - Don't move
 */
int OnMoveAttempt(int id, unsigned short x, unsigned short y, int status,
		int writesocket)
{
	/*
	 int newx = (int)ceil((x)/32);
	 int newy = (int)ceil((y)/32);
	 printf("(Debug) Tilemode: %d\n", map[newx][newy].mode);
	 */
	return 0;
}
