/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#ifndef PAKETS_H_INCLUDED
#define PAKETS_H_INCLUDED

#include "main.h"
//#include ""

int unknown(unsigned char *message, int length, unsigned char *buffer,
		int size, int position);
int connection_setup_unknown(unsigned char *message, int length,
		struct in_addr ip, unsigned short port);
int connection_setup_known(unsigned char *message, int length,
		struct in_addr ip, unsigned short port, int id);
int ping_ingame(unsigned char *message, int length, int id, int writesocket);
int confirmation_unknown(unsigned char *message, int length, struct in_addr ip,
		unsigned short port);
int confirmation_known(unsigned char *message, int length, int id,
		int writesocket);
int fire(unsigned char *message, int length, int id, int writesocket);
int advanced_fire(unsigned char *message, int length, int id, int writesocket);
int buy(unsigned char *message, int length, int id, int writesocket);
int rotupdate(unsigned char *message, int length, int id, int writesocket);
int posupdatewalk(unsigned char *message, int length, int id, int writesocket);
int posupdaterun(unsigned char *message, int length, int id, int writesocket);
int posrotupdatewalk(unsigned char *message, int length, int id,
		int writesocket);
int posrotupdaterun(unsigned char *message, int length, int id,
				int writesocket);
int respawnrequest(unsigned char *message, int length, int id, int writesocket);
int weaponchange(unsigned char *message, int length, int id, int writesocket);
int teamchange(unsigned char *message, int length, int id, int writesocket);
int ping_serverlist(unsigned char *message, int length,
		struct sockaddr_in *client, int writesocket);
int serverinfo_request(unsigned char *message, int length,
		struct sockaddr_in *client, int writesocket);
int joinroutine_unknown(unsigned char *message, int length,
		struct sockaddr_in *client, int writesocket);
int specpos(unsigned char *message, int length, int id, int writesocket);
int chatmessage(unsigned char *message, int length, int id, int writesocket);
int joinroutine_known(unsigned char *message, int length, int id,
		int writesocket);
int leave(int id, int writesocket);
int reload(unsigned char *message, int length, int id, int writesocket);
int spray(unsigned char *message, int length, int id, int writesocket);
#endif // PAKETS_H_INCLUDED
