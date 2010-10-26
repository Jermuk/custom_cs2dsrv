/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#ifndef SENDTO_FUNCTIONS_H_
#define SENDTO_FUNCTIONS_H_

#include "main.h"
void SendToPlayer(unsigned char *message, int length, int id, int reliable,
		int writesocket);
void SendToAll(unsigned char *message, int length, int reliable,
		int writesocket);
void SendToTeam(unsigned char *message, int length, int reliable, int team,
		int writesocket);
void SendToAllOther(int id, unsigned char *message, int length, int reliable,
		int writesocket);

#endif /* SENDTO_FUNCTIONS_H_ */
