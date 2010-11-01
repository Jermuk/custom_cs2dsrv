/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk, FloooD
 */

#include "../include/functions.h"

/**
 * \fn void UpdateBuffer(void)
 * \brief update old player locations
 */
void UpdateBuffer(void)
{
	int id, i;
	for (id = 1; id < (MAX_CLIENTS); id++)
	{
			for (i = sv_lcbuffer; i >= 1; i--)
			{
				player[id].buffer_x[i] = player[id].buffer_x[i - 1];
				player[id].buffer_y[i] = player[id].buffer_y[i - 1];
			}
			player[id].buffer_x[0] = player[id].x;
			player[id].buffer_y[0] = player[id].y;
	}
}

/**
 * \fn int IsPlayerKnown(struct in_addr ip, u_short port)
 * \brief checks if a player is already known
 * \param ip client's ip
 * \param port client's port
 * \return the playerid or 0 if not found
 */
int IsPlayerKnown(struct in_addr ip, u_short port)
{
	int i;
	for (i = 1; i <= sv_maxplayers; i++)
	{
		if (!strcmp(inet_ntoa(ip), inet_ntoa(player[i].ip)) && port
				== player[i].port)
		{
			return i;
		}
	}
	return -1;
}

/**
 * \fn void ClearPlayer(int id)
 * \brief clear all player variables
 */
void ClearPlayer(int id)
{
	player[id].used = 0;
	player[id].client_nummer = 0;
	player[id].server_nummer = 0;
	player[id].lastpaket = 0;
	player[id].joinstatus = 0;

	free(player[id].name);
	player[id].name = NULL;
	free(player[id].spraylogo);
	player[id].spraylogo = NULL;
	free(player[id].win);
	player[id].win = NULL;
	free(player[id].usgn);
	player[id].usgn = NULL;
	player[id].version = 0;

	player[id].team = 0;
	player[id].deaths = 0;
	player[id].score = 0;

	player[id].x = 0;
	player[id].y = 0;

	player[id].health = 0;
	player[id].armor = 0;

	player[id].actualweapon = 0;
	player[id].reloading = 0;
	player[id].reloadtimer = 0;
	player[id].zoomtimer = 0;
	player[id].firetimer = 0;

	int i;
	for (i = 0; i <= 9; i++)
	{
		player[id].slot[i].id = 0;
	}
	for (i = 0; i <= sv_lcbuffer; i++)
	{
		player[id].buffer_x[i] = 0;
		player[id].buffer_y[i] = 0;
	}
	player[id].rotation = 0;

	player[id].dead = 1;

	player[id].start = 0;
	player[id].money = mp_startmoney;
	player[id].zoommode = 0;

	/* Address*/
	player[id].port = 0;
	//player[id].ip = "";
}

/**
 * \fn void ClearAllPlayer(void)
 * \brief clear all player variables
 */
void ClearAllPlayer(void)
{
	int i;
	for (i = 1; i <= sv_maxplayers; i++)
	{
		ClearPlayer(i);
	}
}

/**
 * \fn void CheckForTimeout(int writesocket)
 * \brief check all player for timeout
 */
void CheckForTimeout(int writesocket)
{
	int i;
	for (i = 1; i <= sv_maxplayers; i++)
	{
		if (player[i].used == 1 && PlayerTimeout(i))
		{
			printf("Client %d timed out!\n", i);
			SendLeaveMessage(i, writesocket);
			ClearPlayer(i);
		}
	}
}
/**
 * \fn int GivePlayerWeapon(int id, int wpnid)
 * \brief adds an specific weapon to a player
 * \param id player-id
 * \param wpnid weapon-id
 * \return the slot-id or 0 if not found
 */
int GivePlayerWeapon(int id, int wpnid)
{
	int i;
	for (i = 0; i <= 9; i++)
	{
		if (player[id].slot[i].id == 0)
		{
			player[id].slot[i].id = wpnid;
			player[id].slot[i].slot = weapons[wpnid].slot;
			player[id].slot[i].ammo1 = weapons[wpnid].ammo1;
			player[id].slot[i].ammo2 = weapons[wpnid].ammo2;
			return i;
		}
	}
	return 0;
}
/**
 * \fn void RemovePlayerWeapon(int id, int wpnid)
 * \brief removes an specific weapon to a player
 * \param id player-id
 * \param wpnid weapon-id
 */
void RemovePlayerWeapon(int id, int wpnid)
{
	int i;
	for (i = 0; i <= 9; i++)
	{
		if (player[id].slot[i].id == wpnid)
		{
			player[id].slot[i].id = 0;
			player[id].slot[i].slot = 0;
			player[id].slot[i].ammo1 = 0;
			player[id].slot[i].ammo2 = 0;
			break;
		}
	}
}
/**
 * \fn void RemoveAllPlayerWeapon(int id)
 * \brief remove all weapons from a player
 * \param id player-id
 */
void RemoveAllPlayerWeapon(int id)
{
	int i;
	for (i = 0; i <= 9; i++)
	{
		player[id].slot[i].id = 0;
		player[id].slot[i].slot = 0;
		player[id].slot[i].ammo1 = 0;
		player[id].slot[i].ammo2 = 0;
		player[id].slot[i].special = 0;
		player[id].zoommode = 0;

	}
}

/**
 * \fn int PlayerTimeout(int id)
 * \brief checks if a specific player is timeout
 * \param id player-id
 * \return 1 - timeout; 0 - success
 *
 */
int PlayerTimeout(int id)
{
	//id = 0;

	int actualtime = mtime();

	if (((player[id].lastpaket + TIMEOUT*1000) < actualtime) && player[id].lastpaket
			!= 0)
	{
		return 1;
	}
	return 0;
}

/**
 * \fn unsigned short GetServerStatus(void)
 * \brief needs for serverlist
 * \return serverstatus
 */
unsigned short GetServerStatus(void)
{
	unsigned short serverstatus = 0;
	if (strcmp((char*) sv_password, ""))
	{
		serverstatus += 1;
	}
	if (sv_usgnonly == 1)
	{
		serverstatus += 2;
	}
	if (sv_fow == 1)
	{
		serverstatus += 4;
	}
	if (sv_friendlyfire == 1)
	{
		serverstatus += 8;
	}
	if (1) //Same Version?
	{
		serverstatus += 16;
	}
	if (sv_gamemode != 0)
	{
		serverstatus += 32;
	}
	if (0) //LuaScripts
	{
		serverstatus += 64;
	}
	if (1) //Dedicated
	{
		serverstatus += 128;
	}
	return serverstatus;
}

/**
 * \fn unsigned short endian_swap_short(unsigned short *x)
 * \brief swap the endian for a short
 * \param *x pointer to an unsigned short
 * \return the endian-changed unsigned short
 */
unsigned short endian_swap_short(unsigned short *x)
{
	*x = (*x >> 8) | (*x << 8);
	return *x;
}
/**
 * \fn unsigned int endian_swap_int(unsigned int *x)
 * \brief swap the endian for an int
 * \param *x pointer to an int
 * \return the endian-changed int
 */
unsigned int endian_swap_int(unsigned int *x)
{
	*x = (*x >> 24) | ((*x << 8) & 0x00FF0000) | ((*x >> 8) & 0x0000FF00) | (*x
			<< 24);
	return *x;
}

/**
 * \fn int ValidatePaket(char *message, int id)
 * \brief validate if the first two bytes follow the numbering for a player and rise them if necessary
 * \param *message pointer to the message
 * \param id player-id
 * \return 0 if invalid; 1 if valid
 */
int ValidatePaket(unsigned char *message, int id)
{
	/*
	unsigned short *pTempNummer = malloc(2);
	pTempNummer[0] = message[0];
	pTempNummer[1] = message[1];
	*/
	unsigned short *pTempNummer = (unsigned short *)message;
	if (*pTempNummer % 2 != 0)
	{
		if (((*pTempNummer) + 2) < player[id].client_nummer || (*pTempNummer)
				> (player[id].client_nummer + 2))
		{
			printf("Invalid paket! (Bad index: %d; expected: %d)\n", *pTempNummer, player[id].client_nummer);
			//free(pTempNummer);
			return 0;
		}
	}
	if (*pTempNummer - 1 > player[id].client_nummer)
	{
		player[id].client_nummer = *pTempNummer;
	}
	/*
	 unsigned short *pNummer = &player[id].client_nummer;
	 pNummer[0] = buffer[0];
	 pNummer[1] = buffer[1];
	 */
	//free(pTempNummer);
	return 1;
}
/**
 * \fn void PaketConfirmation(char *message, int id, int writesocket)
 * \brief sends an confirmation to a player if necessary
 * \param *message pointer to the message
 * \param id player-id
 */
void PaketConfirmation(unsigned char *message, int id, int writesocket)
{
	unsigned short *pTempNummer = (unsigned short *)message;
	/*
	unsigned short *pTempNummer = malloc(sizeof(unsigned short));
	pTempNummer[0] = message[0];
	pTempNummer[1] = message[1];
	*/
	if (*pTempNummer % 2 == 0)
	{
		int stringsize = 3;
		unsigned char *buffer = malloc(stringsize);
		buffer[0] = 0x01;
		memcpy(buffer + 1, pTempNummer, 2);

		SendToPlayer(buffer, stringsize, id, 0, writesocket);

		free(buffer);
	}
	//free(pTempNummer);
}
/**
 * \fn int CheckPlayerData(char *password)
 * \brief check all player data and looks if he/she can join
 * \param *password pointer to the password
 * \return the error number or 0
 */
int CheckPlayerData(unsigned char *password)
{
	if (strcmp((char*) sv_password, (char*) password) != 0)
	{
		printf("Password wrong!\n");
		return 1;
	}
	if (sv_maxplayers == onlineplayer)
	{
		printf("Server full!\n");
		return 3;
	}
	/*
	 0 - Normal
	 1 - Password wrong
	 2 - USGN only
	 3 - Server full
	 4 - Banned
	 5 - Another Game Version
	 6 - ??
	 7 - Can't validate user (USGN offline)
	 8 - ??
	 9 - Connection already exists
	 10 - Wrong client (pre_authcode)
	 11 - Different map (temp, etc.)
	 12 - Map unknown (maptransfer disabled)
	 13++ - Failed to join
	 */

	return 0;
}

/**
 * \fn unsigned char *GetEncodedString(unsigned char *string, int length)
 * \brief convert the playername into cs2d format
 * \param *string playername
 * \param length length from playername
 * \return the converted name
 */
unsigned char *GetEncodedString(unsigned char *string, int length)
{
	unsigned char *buffer = malloc(length + 1); //+1 need for \0
	if (buffer == NULL)
		error_exit("Memory error ( GetEncodedString() )\n");

	int i;
	for (i = 0; i <= length; i++) //length and not length-1 because malloc(length+1)
	{
		if ((i % 3) == 0)
		{
			buffer[i] = string[i] + 110;
		}
		else if ((i % 3) == 1)
		{
			buffer[i] = string[i] + 97;
		}
		else if ((i % 3) == 2)
		{
			buffer[i] = string[i] + 109;
		}
	}
	buffer[length] = '\0';

	return buffer;
}

/**
 * \fn void CheckAllPlayerForReload(int writesocket)
 * \brief check all player if their reload is ended,
 * send message if necessary, and rise their magazine
 */
void CheckAllPlayerForReload(int writesocket)
{
	int i;
	for (i = 1; i <= sv_maxplayers; i++)
	{
		if (player[i].reloading != 0)
		{
			if (player[i].reloadtimer <= mtime())
			{
				SendReloadMessage(i, 2, writesocket);
				if (player[i].slot[player[i].reloading].ammo2
						-= player[i].slot[player[i].reloading].ammo1 > 0)
				{
					player[i].slot[player[i].reloading].ammo2
							-= player[i].slot[player[i].reloading].ammo1;
					player[i].slot[player[i].reloading].ammo1
							= weapons[player[i].slot[player[i].reloading].id].ammo1;
				}
				else
				{
					player[i].slot[player[i].reloading].ammo1
							= player[i].slot[player[i].reloading].ammo2;
				}
				player[i].reloading = 0;
			}
		}
	}
}

struct in_addr GetIp(char *name)
{
	struct in_addr ip;
	struct hostent *dnsresolve;
	if ((dnsresolve = gethostbyname(name)) == NULL)
	{
		printf("Error: Failed to resolve %s!\n", name);
		ip.s_addr = inet_addr("85.214.102.60");
		return ip; //return usgn ip
	}
	memcpy(&ip, dnsresolve->h_addr_list[0], dnsresolve->h_length);

	return ip;
}

int UsgnRegister(int writesocket)
{
	struct sockaddr_in tempclient;

	tempclient.sin_family = AF_INET;
	tempclient.sin_port = htons(36963);
	tempclient.sin_addr = GetIp("usgn.de");

	unsigned char *buffer = malloc(4);
	if (buffer == NULL)
		error_exit("Memory error ( UsgnRegister() )");
	int position = 0;

	buffer[position] = 1;
	position++;
	buffer[position] = 0;
	position++;
	buffer[position] = 27;
	position++;
	buffer[position] = 1;
	position++;

	udp_send(writesocket, buffer, 4, &tempclient);
	free(buffer);

	printf("[USGN] Sent ADD request to %s...\n", inet_ntoa(tempclient.sin_addr));
	return 0;
}

int UsgnUpdate(int writesocket)
{
	struct sockaddr_in tempclient;

	tempclient.sin_family = AF_INET;
	tempclient.sin_port = htons(36963);
	tempclient.sin_addr = GetIp("usgn.de");

	unsigned char *buffer = malloc(4);
	if (buffer == NULL)
		error_exit("Memory error ( UsgnRegister() )");
	int position = 0;

	buffer[position] = 1;
	position++;
	buffer[position] = 0;
	position++;
	buffer[position] = 28;
	position++;
	buffer[position] = 2;
	position++;

	udp_send(writesocket, buffer, 4, &tempclient);
	free(buffer);

	printf("[USGN] Sent UPDATE request to %s...\n", inet_ntoa(tempclient.sin_addr));
	return 0;
}

void ExecuteFunctionsWithTime(time_t *checktime, int writesocket)
{
	time_t actualtime;
	time(&actualtime);
	if (*checktime != actualtime) //prevents executing more times than one in a second
	{
		if (actualtime % 5 == 0) //execute every 5 seconds
		{
			SendPingList(writesocket);
			SendMessageToAll("This is an alpha version! Don't play at it!", 1,
					writesocket); //Do not remove or change this until server reaches beta status
			PingAllPlayer(writesocket);
		}
		else if (actualtime % 50 == 0)
		{
			UsgnUpdate(writesocket);
		}
		*checktime = actualtime;
	}
}

size_t u_strlen(unsigned char* buffer)
{
	return strlen((char*) buffer);
}
