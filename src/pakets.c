/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#include "../include/pakets.h"

/**
 * \fn int unknown(unsigned char *message, int length, unsigned char *buffer, int size, int position)
 * \brief every unknown packet lands here
 * \param *message pointer to the unknown message
 * \param length sizeof message
 * \param *buffer pointer to the udp-packet
 * \param size sizeof buffer
 * \param position where the unknown message in buffer begins
 * \return read bytes (specific: parameter length)
 */
int unknown(unsigned char *message, int length, unsigned char *buffer,
		int size, int position)
{
	int paketlength = length;
	int i;
	printf("Unknown packet: ");
	for (i = 2; i <= position - 1; i++)
	{
		eprintf("%d-", buffer[i]);
	}
	eprintf("\n\t");
	for (i = 0; i <= length - 1; i++)
	{
		eprintf("%d-", message[i]);
	}
	eprintf("\n");
	return paketlength;
}

/**
 * \fn int connection_setup_unknown(unsigned char *message, int length, struct in_addr ip, unsigned short port)
 * \brief handles a connection setup for unknown player
 * \param *message pointer to the unknown message
 * \param length sizeof message
 * \param ip clients ip
 * \param port clients port
 * \return read bytes (specific: 3)
 */
int connection_setup_unknown(unsigned char *message, int length,
		struct in_addr ip, unsigned short port)
{
	int paketlength = 3;
	if (length < paketlength)
	{
		printf("Invalid packet (connection_setup_unknown)!\n");
		return length;
	}
	return paketlength;
}

/**
 * \fn int connection_setup_known(unsigned char *message, int length, struct in_addr ip, unsigned short port)
 * \brief handles a connection setup for known player
 * \param *message pointer to the unknown message
 * \param length sizeof message
 * \param ip clients ip
 * \param port clients port
 * \return read bytes (specific: 3)
 */
int connection_setup_known(unsigned char *message, int length,
		struct in_addr ip, unsigned short port, int id)
{
	int paketlength = 3;
	if (length < paketlength)
	{
		printf("Invalid packet (connection_setup_known)!\n");
		return length;
	}

	return paketlength;
}

/**
 * \fn int ping_ingame(unsigned char *message, int length, int id, int writesocket)
 * \brief handles a answer from the server ingame ping. this function calculates the latency
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 5)
 */
int ping_ingame(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 5;
	if (length < paketlength)
	{
		printf("Invalid packet (ping_ingame)!\n");
		return length;
	}
	player[id].latency = mtime() - player[id].start;
	//printf("%s: %d\n", player[id].name, player[id].latency);
	return paketlength;
}

/**
 * \fn int confirmation_unknown(unsigned char *message, int length, struct in_addr ip, unsigned short port)
 * \brief handles a confirmation for unknown player
 * \param *message pointer to the unknown message
 * \param length sizeof message
 * \param ip clients ip
 * \param port clients port
 * \return read bytes (specific: 3)
 */
int confirmation_unknown(unsigned char *message, int length, struct in_addr ip,
		unsigned short port)
{
	int paketlength = 3;
	if (length < paketlength)
	{
		printf("Invalid packet (confirmation_unknown)!\n");
		return length;
	}

	return paketlength;
}

/**
 * \fn int confirmation_known(unsigned char *message, int length, int id, int writesocket)
 * \brief handles a confirmation for known player
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 3)
 */
int confirmation_known(unsigned char *message, int length, int id,
		int writesocket)
{
	int paketlength = 3;
	if (length < paketlength)
	{
		printf("Invalid packet (confirmation_known)!\n");
		return length;
	}
	return paketlength;
}

/**
 * \fn int fire(unsigned char *message, int length, int id, int writesocket)
 * \brief handles a fire
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 1)
 */
int fire(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 1;
	if (length < paketlength)
	{
		printf("Invalid packet (fire)!\n");
		return length;
	}
	switch (OnFire(id, writesocket))
	{
	case 0:
		SendFireMessage(id, writesocket);
		break;
	case 1:
		break;
	}
	return paketlength;
}

/**
 * \fn int advanced_fire(unsigned char *message, int length, int id, int writesocket)
 * \brief handles a advanced_fire (right click)
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 1)
 */
int advanced_fire(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 2;
	if (length < paketlength)
	{
		printf("Invalid packet (advanced_fire)!\n");
		return length;
	}
	unsigned int status = message[1];

	switch (OnAdvancedFire(id, status, writesocket))
	{
	case 0:
		SendAdvancedFireMessage(id, status, writesocket);
		break;
	case 1:
		break;
	}
	return paketlength;
}

/**
 * \fn int buy(unsigned char *message, int length, int id, int writesocket)
 * \brief handles a buy request
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 3)
 */
int buy(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 3;
	if (length < paketlength)
	{
		printf("Invalid packet (buy)!\n");
		return length;
	}

	int position = 1;
	int wpnid;

	wpnid = message[position];
	position++;

	switch (OnBuyAttempt(id, wpnid, writesocket))
	{
	case 0:
		OnBuy(id, wpnid, writesocket);
		SendBuyMessage(id, wpnid, writesocket);
		break;
	case 1:
		break;
	}
	return paketlength;
}

/**
 * \fn int rotupdate(unsigned char *message, int length, int id, int writesocket)
 * \brief handles a rotation update
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 5)
 */
int rotupdate(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 5;
	float temprotation;
	if (length < paketlength)
	{
		printf("Invalid packet (rot_update)!\n");
		return length;
	}
	memcpy(&temprotation, message + 1, sizeof(float));
	if (temprotation >= -180 && temprotation <= 180)
	{
		//if(temprotation < 0) temprotation += 360;
		memcpy(&player[id].rotation, &temprotation, sizeof(float));
		SendRotUpdate(id, player[id].rotation, writesocket);
	}
	return paketlength;
}

/**
 * \fn int posupdatewalk(unsigned char *message, int length, int id, int writesocket)
 * \brief handles a position walk update
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 5)
 */
int posupdatewalk(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 5;
	unsigned short tempx;
	unsigned short tempy;
	if (length < paketlength)
	{
		printf("Invalid packet (posupdatewalk)!\n");
		return length;
	}
	memcpy(&tempx, message + 1, 2);
	memcpy(&tempy, message + 3, 2);
	switch (OnMoveAttempt(id, tempx, tempy, 0, writesocket))
	{
	case 0:
		SendPosUpdate(id, tempx, tempy, 0, writesocket);
		player[id].x = tempx;
		player[id].y = tempy;
		break;
	case 1:
		SendPosUpdate(id, player[id].x, player[id].y, 0, writesocket);
		break;
	default:
		break;
	}
	return paketlength;
}
/**
 * \fn int posupdaterun(unsigned char *message, int length, int id, int writesocket)
 * \brief handles a position run update
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 5)
 */
int posupdaterun(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 5;
	unsigned short tempx;
	unsigned short tempy;
	if (length < paketlength)
	{
		printf("Invalid packet (posupdaterun)!\n");
		return length;
	}
	memcpy(&tempx, message + 1, 2);
	memcpy(&tempy, message + 3, 2);
	switch (OnMoveAttempt(id, tempx, tempy, 0, writesocket))
	{
	case 0:
		SendPosUpdate(id, tempx, tempy, 1, writesocket);
		player[id].x = tempx;
		player[id].y = tempy;
		break;
	case 1:
		SendPosUpdate(id, player[id].x, player[id].y, 1, writesocket);
		break;
	default:
		break;
	}
	return paketlength;
}
/**
 * \fn int posrotupdatewalk(unsigned char *message, int length, int id, int writesocket))
 * \brief handles a position walk and rotation update
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 9)
 */
int posrotupdatewalk(unsigned char *message, int length, int id,
		int writesocket)
{
	int paketlength = 9;
	unsigned short tempx;
	unsigned short tempy;
	float rotation;
	if (length < paketlength)
	{
		printf("Invalid packet (posrotupdatewalk)!\n");
		return length;
	}
	memcpy(&tempx, message + 1, 2);
	memcpy(&tempy, message + 3, 2);
	memcpy(&rotation, message + 5, sizeof(float));

	if (rotation >= -180 && rotation <= 180)
	{
		switch (OnMoveAttempt(id, tempx, tempy, 0, writesocket))
		{
		case 0:
			//if(rotation < 0) rotation += 360;
			SendPosRotUpdate(id, tempx, tempy, 0, rotation, writesocket);
			memcpy(&player[id].rotation, &rotation, sizeof(float));
			player[id].x = tempx;
			player[id].y = tempy;
			break;
		case 1:
			SendPosRotUpdate(id, player[id].x, player[id].y, 0,
					player[id].rotation, writesocket);
			break;
		default:
			break;
		}
	}
	return paketlength;
}

/**
 * \fn int posrotupdaterun(unsigned char *message, int length, int id, int writesocket))
 * \brief handles a position run and rotation update
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 9)
 */
int posrotupdaterun(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 9;
	unsigned short tempx;
	unsigned short tempy;
	float rotation;
	if (length < paketlength)
	{
		printf("Invalid packet (posrotupdatewalk)!\n");
		return length;
	}
	memcpy(&tempx, message + 1, 2);
	memcpy(&tempy, message + 3, 2);
	memcpy(&rotation, message + 5, sizeof(float));

	if (rotation >= -180 && rotation <= 180)
	{
		switch (OnMoveAttempt(id, tempx, tempy, 1, writesocket))
		{
		case 0:
			//if(rotation < 0) rotation += 360;
			SendPosRotUpdate(id, tempx, tempy, 1, rotation, writesocket);
			memcpy(&player[id].rotation, &rotation, sizeof(float));
			player[id].x = tempx;
			player[id].y = tempy;
			break;
		case 1:
			SendPosRotUpdate(id, player[id].x, player[id].y, 1,
					player[id].rotation, writesocket);
			break;
		default:
			break;
		}
	}
	return paketlength;
}

/**
 * \fn int respawnrequest(unsigned char *message, int length, int id, int writesocket)
 * \brief handles a respawn request
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 1)
 */
int respawnrequest(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 1;
	if (length < paketlength)
	{
		printf("Invalid packet (respawnrequest)! (WTF?)\n");
		return length;
	}
	switch (OnRespawnRequest(id, writesocket))
	{
	case 0:
		srand(time(NULL));
		switch (player[id].team)
		{
		case 0:
			printf("%s tried to spawn as spectator!\n", player[id].name);
			break;
		case 1:
		{
			int tmp = rand() % tspawncount;
			printf("%s spawned!\n", player[id].name);
			player[id].health = 100;
			player[id].dead = 0;
			player[id].x = (tspawnx[tmp] + 0.5) * 32;
			player[id].y = (tspawny[tmp] + 0.5) * 32;
			SendSpawnMessage(id, player[id].x, player[id].y, writesocket);
			break;
		}
		case 2:
		{
			int tmp = rand() % ctspawncount;
			printf("%s spawned!\n", player[id].name);
			player[id].health = 100;
			player[id].dead = 0;
			player[id].x = (ctspawnx[tmp] + 0.5) * 32;
			player[id].y = (ctspawny[tmp] + 0.5) * 32;
			SendSpawnMessage(id, player[id].x, player[id].y, writesocket);
			break;
		}

		}
		break;
	case 1:
		break;
	default:
		break;
	}
	return paketlength;
}
/**
 * \fn int weaponchange(unsigned char *message, int length, int id, int writesocket)
 * \brief handles a weapon change
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 3)
 */
int weaponchange(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 3;
	if (length < paketlength)
	{
		printf("Invalid packet (weaponchange)!\n");
		return length;
	}
	int position = 1;
	int wpnid;

	wpnid = message[position];
	position++;

	switch (OnWeaponChangeAttempt(id, wpnid, writesocket))
	{
	case 0:
		SendWeaponChangeMessage(id, wpnid, writesocket);
		break;
	case 1:
		break;
	default:
		break;
	}
	return paketlength;
}

/**
 * \fn int teamchange(unsigned char *message, int length, int id, int writesocket)
 * \brief handles a team change
 * \param *message pointer to the message
 * \param length sizeof message
 * \param id clients player id
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 3)
 */
int teamchange(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 3;
	if (length < paketlength)
	{
		printf("Invalid packet (teamchange)!\n");
		return length;
	}
	unsigned char team = message[1];
	unsigned char skin = message[2];

	switch (OnTeamChangeAttempt(id, team, skin, writesocket))
	{
	case 0:
		player[id].team = team;
		if (skin != 5)
			player[id].skin = skin;
		OnTeamChange(id, team, skin, writesocket);
		break;
	case 1:
		break;
	default:
		break;
	}
	return paketlength;
}
/**
 * \fn int ping_serverlist(unsigned char *message, int length, struct sockaddr_in *client, int writesocket)
 * \brief handles a team change
 * \param *message pointer to the message
 * \param length sizeof message
 * \param *client pointer to the client information structure
 * \param writesocket the socket where it was read
 * \return read bytes (specific: 5)
 */
int ping_serverlist(unsigned char *message, int length,
		struct sockaddr_in *client, int writesocket)
{
	int paketlength = 5;
	if (length < paketlength)
	{
		printf("Invalid packet (ping_serverlist)!\n");
		return length;
	}

	unsigned char *tempbuffer = malloc(paketlength);
	if (tempbuffer == NULL)
		error_exit("Memory error ( ping_serverlist() )");

	tempbuffer[0] = 0x01;
	tempbuffer[1] = 0x00;
	memcpy(tempbuffer + 2, message, paketlength);

	udp_send(writesocket, tempbuffer, 5, client);
	free(tempbuffer);
	return paketlength;
}

int serverinfo_request(unsigned char *message, int length,
		struct sockaddr_in *client, int writesocket)
{
	int paketlength = length;
	if (length < 2)
	{
		printf("Invalid packet (serverinfo_request)!\n");
		return length;
	}

	/*
	 int i;
	 printf("serverinfo_request (%d): ", message[0]);
	 for (i = 1; i <= paketlength; i++)
	 {
	 printf("%d-", message[i]);
	 }
	 printf("(%d)\n", paketlength);
	 int joinroutine_known(unsigned char *message, int length, int id, int writesocket)
	 */

	int stringsize = 10 + u_strlen(sv_name) + u_strlen(sv_map);
	if (sv_gamemode != 0)
	{
		stringsize++;
	}

	unsigned char *buffer = malloc(stringsize);
	if (buffer == NULL)
		error_exit("Memory error ( serverinfo_request() )");

	int position = 0;
	buffer[position] = 1;
	position++;
	buffer[position] = 0;
	position++;
	buffer[position] = 0xFB;
	position++;
	buffer[position] = message[1];
	position++;

	switch (message[1])
	{
	case 1:
	case 2:
		/*
		 if(message[2] == 0)
		 {
		 paketlength = 2;
		 }
		 else
		 {
		 paketlength = 6;
		 }
		 */
		paketlength = 4;

		buffer[position] = GetServerStatus();
		position++;
		buffer[position] = u_strlen(sv_name);
		position++;
		memcpy(buffer + position, sv_name, u_strlen(sv_name));
		position += u_strlen(sv_name);
		buffer[position] = u_strlen(sv_map);
		position++;
		memcpy(buffer + position, sv_map, u_strlen(sv_map));
		position += u_strlen(sv_map);
		buffer[position] = onlineplayer;
		position++;
		buffer[position] = sv_maxplayers;
		position++;
		if (sv_gamemode != 0)
		{
			buffer[position] = sv_gamemode;
			position++;
		}
		buffer[position] = bot_count;
		position++;
		udp_send(writesocket, buffer, stringsize, client);
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}

	free(buffer);

	return paketlength;
}

int joinroutine_unknown(unsigned char *message, int length,
		struct sockaddr_in *client, int writesocket)
{
	int paketlength = length; //Just 2 char read (message[1])
	if (length < 2)
	{
		printf("Invalid packet (joinroutine_unknown)!\n");
		return length;
	}
	switch (message[1])
	{
	case 0x00:
	{
		paketlength = 2;

		int i;
		for (i = 1; i <= MAX_CLIENTS - 1; i++)
		{
			if (player[i].used != 1)
			{
				player[i].used = 1;
				player[i].ip = client->sin_addr;
				player[i].port = client->sin_port;
				player[i].joinstatus = 1;
				player[i].client_nummer = 4;
				player[i].server_nummer = 2;
				break;
			}
		}
		int stringsize = 5 + u_strlen(pre_authcode);
		unsigned char *buffer = malloc(stringsize);
		if (buffer == NULL)
			error_exit("Memory error ( joinroutine_unknown() )");

		int position = 0;
		buffer[position] = 0x01;
		position++;
		buffer[position] = 0x00;
		position++;
		buffer[position] = 0xFC;
		position++;
		buffer[position] = 0x00;
		position++;
		buffer[position] = u_strlen(pre_authcode);
		position++;
		memcpy(buffer + position, pre_authcode, u_strlen(pre_authcode));

		udp_send(writesocket, buffer, stringsize, client);

		free(buffer);
		break;
	}
	default:
		printf("Unexpected join data (%d)\n", message[0]);
		break;
	}

	return paketlength;
}

int specpos(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 9;
	if (paketlength > length)
	{
		printf("Invalid packet (specpos)!\n");
		return length;
	}
	int x, y;

	x = (message[4] << 24) | (message[3] << 16) | (message[2] << 8)
			| message[1];
	y = (message[8] << 24) | (message[7] << 16) | (message[6] << 8)
			| message[5];

	switch (OnSpecmove(id, x, y, writesocket))
	{
	case 0:
	{
		player[id].specposx = x;
		player[id].specposy = y;
		break;
	}
	case 1:
	{
		break;
	}
	}
	return paketlength;
}

int chatmessage(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 4;
	unsigned char team, unknown;
	int paketsize;

	if (paketlength > length)
	{
		printf("Invalid packet (chatmessage)!\n");
		return length;
	}

	int position = 0;
	position++;
	team = message[position];
	position++;

	paketsize = message[position];
	if (paketsize > 255 || paketsize >= (length - position + 1))
	{
		printf("Message too big\n");
		return length;
	}
	position++;
	paketlength += paketsize;

	unknown = message[position];
	position++;

	unsigned char *string = malloc(paketsize);
	if (string == NULL)
		error_exit("Memory error ( chatmessage() )\n");
	memcpy(string, message + position, paketsize);

	string[paketsize] = '\0';
	position += paketsize;

	if (paketsize >= 6){
		if (strncmp((char *)string, "!log", 4) == 0){
			char* log = malloc(sizeof(char)*(paketsize-4));
			if (log == NULL) error_exit("Memory error ( chatmessage() -> log )\n");
			strcpy(log,(char *)string+5);
			//printf("[LOG]: %s\n",log);
			eprintf("[LOG]: %s\n",log);
			free(log); free(string);
			return paketlength;
		}
	}
	switch (OnChatMessage(id, string, team, writesocket))
	{
	case 0:
		break;
	default:
		printf("Unknown Return value for OnChatMessage()!\n");
		break;
	}

	free(string);

	return paketlength;
}

int joinroutine_known(unsigned char *message, int length, int id,
		int writesocket)
{
	int paketlength = 2;
	if (paketlength > length)
	{
		printf("Invalid packet (joinroutine_known)!\n");
		return length;
	}
	switch (message[1])
	{
	case 0:
	{
		paketlength = 2;
		if (paketlength > length)
		{
			printf("Invalid packet (joinroutine_known)!\n");
			return length;
		}
		break;
	}
	case 1:
	{
		if (player[id].joinstatus == 1)
		{
			paketlength = 16; // ???
			if (paketlength > length)
			{
				printf("Invalid packet (joinroutine_known)!\n");
				return length;
			}

			int position = 2;
			//Playername
			int stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Playername too big\n");
				return length;
			}
			paketlength += stringsize;
			position++;

			player[id].name = malloc(stringsize);
			if (player[id].name == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(player[id].name, message + position, stringsize);
			player[id].name[stringsize] = '\0';
			position += stringsize; //+1 because after it there is a null byte, so ignore it

			//printf("Player %s connected..\n", player[id].name);

			stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Password too big\n");
				return length;
			}
			paketlength += stringsize;
			position++;

			unsigned char *password = malloc(stringsize);
			if (password == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(password, message + position, stringsize);
			password[stringsize] = '\0';
			position += stringsize;

			//printf("\tPassword: ");
			/*
			 int i;
			 for (i = 0; i <= u_strlen(password); i++)
			 {
			 printf("%d-", password[i]);
			 }
			 printf("\n");
			 */

			//Encryption String
			stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Encryption too big\n");
				return length;
			}
			paketlength += stringsize;
			position++;

			unsigned char *encryption1 = malloc(stringsize);
			if (encryption1 == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(encryption1, message + position, stringsize);
			encryption1[stringsize] = '\0';
			position += stringsize;

			//printf("\tEncryptionstring: %s\n", encryption1);

			//Player Version
			player[id].version = message[position];
			position++;
			//printf("\tVersion: %d\n", player[id].version);
			position++; //Null-byte


			//USGN ID
			player[id].usgn = malloc(sizeof(unsigned short));
			if (player[id].usgn == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(player[id].usgn, message + position, 2); //sizeof(unsigned short) == 2
			position += 4; //2 bytes + 2 null bytes
			/*
			 #else
			 *player[id].usgn = endian_swap_short(player[id].usgn);
			 #endif
			 */
			//printf("\tUSGN-ID: %u\n", *player[id].usgn);


			//Spraylogo
			stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Spraylogoname too big\n");
				return length;
			};
			paketlength += stringsize;
			position++;

			player[id].spraylogo = malloc(stringsize);
			if (player[id].spraylogo == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(player[id].spraylogo, message + position, stringsize);
			player[id].spraylogo[stringsize] = '\0';
			position += stringsize;

			//printf("\tSpraylogo: %s\n", player[id].spraylogo);


			//Map-Hash
			stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Map-Hash too big\n");
				return length;
			}
			paketlength += stringsize;
			position++;

			unsigned char *maphash = malloc(stringsize);
			if (maphash == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(maphash, message + position, stringsize);
			maphash[stringsize] = '\0';
			position += stringsize;

			//printf("\tMap-Hash: %s\n", maphash);

			position++; //Nullbyte

			//WIN
			stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("WIN too big\n");
				return length;
			}
			paketlength += stringsize;
			position++;

			player[id].win = malloc(stringsize);
			if (player[id].win == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(player[id].win, message + position, stringsize);
			player[id].win[stringsize] = '\0';
			position += stringsize;

			//printf("\tWIN: %s (%d)\n", player[id].win, u_strlen(player[id].win));

			unsigned char *buffer = NULL;
			stringsize = 0;
			int tempstatus = CheckPlayerData(password);
			switch (tempstatus)
			{
			case 0x00:
				stringsize = 6 + u_strlen(sv_map) + u_strlen(pre_authcode);
				buffer = malloc(stringsize);
				if (buffer == NULL)
					error_exit("Memory error ( joinroutine_known() )\n");

				position = 0;

				buffer[position] = 252;
				position++;
				buffer[position] = 2;
				position++;
				buffer[position] = 0; //Normal
				position++;
				buffer[position] = id;
				position++;
				buffer[position] = u_strlen(sv_map);
				position++;
				memcpy(buffer + position, sv_map, u_strlen(sv_map));
				position += u_strlen(sv_map);
				buffer[position] = u_strlen(pre_authcode);
				position++;
				memcpy(buffer + position, pre_authcode, u_strlen(pre_authcode));
				position += u_strlen(pre_authcode);
				player[id].joinstatus = 2;
				break;

			default:
			{
				stringsize = 3;
				buffer = malloc(stringsize);
				if (buffer == NULL)
					error_exit("Memory error ( joinroutine_known() )\n");

				position = 0;

				buffer[position] = 252;
				position++;
				buffer[position] = 2;
				position++;
				buffer[position] = tempstatus; //Everyone is banned (just for testing)
				position++;
				player[id].joinstatus = 0;
				break;
			}

			}
			//stringsize = 16 + u_strlen(sv_map);

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
			 11 - Diffrent map (temp, etc.)
			 12 - Map unknown (maptransfer disabled)
			 13++ - Failed to join
			 */

			if (stringsize != 0)
				SendToPlayer(buffer, stringsize, id, 1, writesocket);

			free(encryption1);
			free(maphash);
			free(buffer);

			onlineplayer++;
		}
		else
		{
			printf("Unexpected join data (%d) from %s; expected %d\n", message[1], player[id].name, player[id].joinstatus+1);
		}
		break;
	}
	case 3:
	{
		if (player[id].joinstatus == 2)
		{
			int position = 2;

			paketlength = 5;
			if (paketlength > length)
			{
				printf("Invalid packet (joinroutine_known)!\n");
				return length;
			}

			//Map-Hash
			int stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Map-Hash too big\n");
				return length;
			}
			position++;

			unsigned char *maphash = malloc(stringsize);
			if (maphash == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(maphash, message + position, stringsize);
			maphash[stringsize] = '\0';
			position += stringsize;
			paketlength += stringsize;

			//printf("\tMaphash: %s\n", maphash);

			//pre_authcode_respond
			stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("pre_authcon_respond too big\n");
				return length;
			}
			position++;

			unsigned char *pre_authcode_respond = malloc(stringsize);
			if (pre_authcode_respond == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(pre_authcode_respond, message + position, stringsize);
			pre_authcode_respond[stringsize] = '\0';
			position += stringsize;
			paketlength += stringsize;

			//printf("\tpre_authcode_respond: %s\n", pre_authcode_respond);

			//Player Version
			//unsigned char mapstatus = message[position]; //avoid warning
			position++;
			//printf("\tMapstatus: %d\n", mapstatus);

			free(pre_authcode_respond);
			free(maphash);

			//Respond
			stringsize = 3;
			unsigned char *buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 4;
			position++;
			buffer[position] = 0; //CheckPlayerData()
			position++;

			SendToPlayer(buffer, stringsize, id, 1, writesocket);
			player[id].joinstatus = 3;
		}
		else
		{
			printf("Unexpected join data (%d) from %s; expected %d\n", message[1], player[id].name, player[id].joinstatus+1);
		}
		break;
	}
	case 5:
	{
		if (player[id].joinstatus == 3)
		{
			int position = 2;

			paketlength = 3;
			if (paketlength > length)
			{
				printf("Invalid packet (joinroutine_known)!\n");
				return length;
			}
			//Map-Hash
			int stringsize = message[position];
			if (stringsize > 255 || stringsize >= (length - position + 1))
			{
				printf("Mapname too big\n");
				return length;
			}
			position++;

			unsigned char *mapname = malloc(stringsize);
			if (mapname == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");
			memcpy(mapname, message + position, stringsize);
			mapname[stringsize] = '\0';
			position += stringsize;
			paketlength += stringsize;

			//printf("\tMapname: %s\n", mapname);


			//----------- ServerData -----------

			stringsize = 28 + u_strlen(sv_map) + u_strlen(sv_name);
			unsigned char *buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 6;
			position++;
			buffer[position] = 0; //CheckPlayerData()
			position++;

			buffer[position] = u_strlen(sv_map);
			position++;
			memcpy(buffer + position, sv_map, u_strlen(sv_map));
			position += u_strlen(sv_map);

			buffer[position] = u_strlen(sv_name);
			position++;
			memcpy(buffer + position, sv_name, u_strlen(sv_name));
			position += u_strlen(sv_name);

			buffer[position] = 0; //Unknown
			position++;
			buffer[position] = 0; //Unknown
			position++;
			buffer[position] = sv_friendlyfire;
			position++;
			buffer[position] = 0; //Unknown
			position++;
			buffer[position] = mp_roundtime;
			position++;
			buffer[position] = mp_freezetime;
			position++;
			buffer[position] = mp_c4timer;
			position++;
			buffer[position] = 32; //Unknown
			position++;
			buffer[position] = 124; //Unknown
			position++;
			buffer[position] = 0; //Unknown
			position++;
			buffer[position] = 0; //Unknown
			position++;
			buffer[position] = 1; //Unknown
			position++;
			buffer[position] = 0; //Unknown
			position++;
			buffer[position] = sv_maxplayers;
			position++;
			buffer[position] = sv_fow;
			position++;
			buffer[position] = mp_specmode;
			position++;
			buffer[position] = sv_gamemode;
			position++;
			buffer[position] = mp_respawndelay;
			position++;
			buffer[position] = mp_infammo;
			position++;
			buffer[position] = 3; //u_strlen ACK
			position++;
			buffer[position] = 65; //A
			position++;
			buffer[position] = 67; //C
			position++;
			buffer[position] = 75; //K
			position++;

			SendToPlayer(buffer, stringsize, id, 1, writesocket);
			free(buffer);

			//----------- PlayerData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 1;
			position++;
			buffer[position] = onlineplayer;
			position++;

			int i;
			for (i = 1; i <= sv_maxplayers; i++)
			{
				if (player[i].used == 1 && player[i].joinstatus >= 1 && i != id)
				{
					unsigned char *encodedname;
					encodedname = GetEncodedString(player[i].name, u_strlen(
							player[i].name));
					unsigned short *deaths = &player[i].deaths;
					unsigned short tempscore = (unsigned) (player[i].deaths
							+ 1000);
					unsigned short *score = &tempscore;

					unsigned short tempx = (player[i].x);
					unsigned short tempy = (player[i].y);
					unsigned short *x = &tempx;
					unsigned short *y = &tempy;

					float *ptemprotation = &player[i].rotation;

					int playersize = 25 + u_strlen(encodedname);
					buffer = realloc(buffer, position + 1 + playersize); //+1 because e.g. buffer[10] are 11 chars
					if (buffer == NULL)
						error_exit("Memory error ( joinroutine_known() )\n");

					buffer[position] = i;
					position++;

					buffer[position] = u_strlen(encodedname);
					position++;
					memcpy(buffer + position, encodedname,
							u_strlen(encodedname));
					position += u_strlen(encodedname);
					free(encodedname);

					buffer[position] = 0; //Unknown
					position++;
					buffer[position] = player[i].team;
					position++;
					buffer[position] = 0; //Unknown
					position++;
					buffer[position] = 0; //Unknown
					position++;
					/*
					 buffer[position] = score[0]; //Deaths
					 position++;
					 buffer[position] = score[1]; //Deaths
					 position++;
					 */
					memcpy(buffer + position, score, 2);
					position += 2;
					/*
					 buffer[position] = deaths[0]; //Deaths
					 position++;
					 buffer[position] = deaths[1]; //Deaths
					 position++;
					 */
					memcpy(buffer + position, deaths, 2);
					position += 2;
					memcpy(buffer + position, x, 2);
					position += 2;
					buffer[position] = 0; //Unknown
					position++;
					buffer[position] = 0; //Unknown
					position++;
					memcpy(buffer + position, y, 2);
					position += 2;
					buffer[position] = 0; //Unknown
					position++;
					buffer[position] = 0; //Unknown
					position++;
					buffer[position] = ptemprotation[0]; //Rotation
					position++;
					buffer[position] = ptemprotation[1]; //Rotation
					position++;
					buffer[position] = player[i].health; //Health
					position++;
					buffer[position] = player[i].armor; //Armor
					position++;
					buffer[position] = 0; //Unknown
					position++;
					buffer[position]
							= player[i].slot[player[i].actualweapon].id; //Aktuelle Waffe
					position++;
					buffer[position] = 0; //Unknown
					position++;
					/*
					 01 00 01 00 00 e8 03 00 00 70 00 00 00 70 01 00 00 7d ff 64 00 00 32 00
					 04 00 01 00 00 e8 03 00 00 0c 18 00 00 0c 18 00 00 66 ff 64 00 00 32 00
					 01 00 01 00 00 e8 03 00 00 00 01 00 00 00 01 00 00 12 00 64 00 00 32 00
					 01 00 02 00 00 e8 03 00 00 01 10 00 00 01 10
					 e8 03 00 00 12 01 00 00 01 03
					 e8 03 00 00 0c 18 00 00 0d 18 00 00 ab 00 64 00 00 1e 00
					 e8 03 00 00 10 18 00 00 10 18 00 00 b6 ff 64 c9 00 49 00
					 01 00 01 00 00 4c 04 96 00 10 18 00 00 10 18 00 00 5e ff 64 00 00 02 00
					 */
				}
			}
			if (1)
			{
				unsigned char *encodedname;
				encodedname = GetEncodedString(player[id].name, u_strlen(
						player[id].name));

				int playersize = 25 + u_strlen(encodedname);
				buffer = realloc(buffer, position + 1 + playersize); //+1 because e.g. buffer[10] are 11 chars
				if (buffer == NULL)
					error_exit("Memory error ( joinroutine_known() )\n");

				buffer[position] = id;
				position++;

				buffer[position] = u_strlen(encodedname);
				position++;
				memcpy(buffer + position, encodedname, u_strlen(encodedname));
				position += u_strlen(encodedname);
				free(encodedname);

				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = player[id].team;
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 232; //Unknown
				position++;
				buffer[position] = 3; //Unknown
				position++;
				buffer[position] = 0; //Deaths
				position++;
				buffer[position] = 0; //Deaths
				position++;
				buffer[position] = 0; //X
				position++;
				buffer[position] = 0; //X
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Y
				position++;
				buffer[position] = 0; //Y
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Health
				position++;
				buffer[position] = 0; //Armor
				position++;
				buffer[position] = 0; //Unknown
				position++;
				buffer[position] = 0; //Aktuelle Waffe 50 = Knife
				position++;
				buffer[position] = 0; //Unknown
				position++;
			}

			SendToPlayer(buffer, position, id, 1, writesocket);
			free(buffer);

			//----------- PlayerData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 1; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1, writesocket);
			free(buffer);

			//----------- HostageData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 2; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1, writesocket);
			free(buffer);

			//----------- ItemData -----------

			/*
			 fc 07 03 01(1 anzahl) 01(id) 00 4b(waffenid) 0f 00 12 00 (position) 01 (munition ?) 00 00 00
			 */
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 3; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1, writesocket);
			free(buffer);

			//----------- EnityData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 4; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1, writesocket);
			free(buffer);

			//----------- DynamicObjectData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 5; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1, writesocket);
			free(buffer);

			//----------- ProjectileData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 6; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1, writesocket);
			free(buffer);

			//----------- DynamicObjectImageData -----------
			stringsize = 4;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 7; //third payload
			position++;
			buffer[position] = 0;
			position++;

			SendToPlayer(buffer, stringsize, id, 1, writesocket);
			free(buffer);

			//----------- Final ACK -----------
			stringsize = 7;
			buffer = malloc(stringsize);
			if (buffer == NULL)
				error_exit("Memory error ( joinroutine_known() )\n");

			position = 0;

			buffer[position] = 252;
			position++;
			buffer[position] = 7;
			position++;
			buffer[position] = 200; //third payload
			position++;
			buffer[position] = 3; //u_strlen ACK
			position++;
			buffer[position] = 65; //A
			position++;
			buffer[position] = 67; //C
			position++;
			buffer[position] = 75; //K
			position++;

			SendToPlayer(buffer, stringsize, id, 1, writesocket);
			free(buffer);

			player[id].joinstatus = 4;
			free(mapname);

			OnJoin(id, writesocket);
		}
		else
		{
			printf("Unexpected join data (%d) from %s; expected %d\n", message[1], player[id].name, player[id].joinstatus+1);
		}
		break;
	}
	default:
	{
		printf("Unexpected join data (%d) from %s; expected %d\n", message[1], player[id].name, player[id].joinstatus+1);
	}
		break;
	}

	return paketlength;
}

int leave(int id, int writesocket)
{
	OnLeave(id, writesocket);

	free(player[id].name);
	free(player[id].usgn);
	free(player[id].spraylogo);
	free(player[id].win);

	player[id].name = NULL;
	player[id].usgn = NULL;
	player[id].spraylogo = NULL;
	player[id].win = NULL;

	onlineplayer--;

	ClearPlayer(id);

	return 2;
}

int reload(unsigned char *message, int length, int id, int writesocket)
{
	int paketlength = 2;
	if (length < paketlength)
	{
		printf("Invalid packet (buy)!\n");
		return length;
	}

	int position = 1;
	int status;

	status = message[position];
	position++;

	if (status == 1)
	{
		SendReloadMessage(id, 1, writesocket);
		player[id].reloading = player[id].actualweapon;
		player[id].reloadtimer
				= mtime()
						+ weapons[player[id].slot[player[id].actualweapon].id].reloadtime;
	}
	return paketlength;
}

int spray(unsigned char *message, int length, int id, int writesocket)
{
	// 28 0 xx yy c
	//  0 1 23 45 6
	struct{
		unsigned char hi; unsigned char lo;
	} x, y;

	if (length < 7)
	{
		printf("Invalid packet (spray)!\n");
		return length;
	}

	x.lo = message[2];
	x.hi = message[3];

	y.lo = message[4];
	y.hi = message[5];

	unsigned short xx = x.hi*256+x.lo, yy = y.hi*256+y.lo;
	unsigned char c = message[6];
	unsigned char i = (char)id;

	// Postprocessing if needed, then send back exact same data
	// xx and yy are positions, not tiles.

	SendSprayMessage(i, xx, yy, c, writesocket);
	return 7;
}
