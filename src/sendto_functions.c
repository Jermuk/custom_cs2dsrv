/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#include "../include/sendto_functions.h"

void SendToPlayer(unsigned char *message, int length, int id, int reliable,
		int writesocket)
{
	struct sockaddr_in tempclient;
	tempclient.sin_family = AF_INET;
	tempclient.sin_port = player[id].port;
	tempclient.sin_addr = player[id].ip;
	unsigned char *buffer = malloc(length + 2);
	if (buffer == NULL)
		error_exit("Memory error ( SendToPlayer() )");

	if (reliable == 1)
	{
		unsigned short *pNummer = &player[id].server_nummer;
		memcpy(buffer, pNummer, sizeof(unsigned short));
		player[id].server_nummer += 2;
	}
	else if (reliable == 0)
	{
		player[id].server_nummer--;
		unsigned short *pNummer = &player[id].server_nummer;
		memcpy(buffer, pNummer, sizeof(unsigned short));
		player[id].server_nummer++;
	}
	memcpy(buffer + 2, message, length);
	udp_send(writesocket, buffer, length + 2, &tempclient);
}

void SendToAll(unsigned char *message, int length, int reliable,
		int writesocket)
{
	int i;
	for (i = 1; i <= sv_maxplayers; i++)
	{
		if (player[i].used == 1 && player[i].joinstatus >= 4)
		{
			SendToPlayer(message, length, i, reliable, writesocket);
		}
	}
}

void SendToTeam(unsigned char *message, int length, int reliable, int team,
		int writesocket)
{
	int i;
	for (i = 1; i <= sv_maxplayers; i++)
	{
		if (player[i].used == 1 && player[i].joinstatus >= 4 && player[i].team
				== team)
		{
			SendToPlayer(message, length, i, reliable, writesocket);
		}
	}
}

void SendToAllOther(int id, unsigned char *message, int length, int reliable,
		int writesocket)
{
	int i;
	for (i = 1; i <= sv_maxplayers; i++)
	{
		if (player[i].used == 1 && player[i].joinstatus >= 4 && i != id)
		{
			SendToPlayer(message, length, i, reliable, writesocket);
		}
	}
}
