/*
 * sendto_functions.h
 *
 *  Created on: 12.10.2010
 *      Author: Jeremy
 */

#ifndef SENDTO_FUNCTIONS_H_
#define SENDTO_FUNCTIONS_H_

#include "main.h"
void SendToPlayer(unsigned char *message, int length, int id, int reliable, int writesocket);
void SendToAll(unsigned char *message, int length, int reliable, int writesocket);
void SendToTeam(unsigned char *message, int length, int reliable, int team, int writesocket);
void SendToAllOther(int id, unsigned char *message, int length, int reliable, int writesocket);

#endif /* SENDTO_FUNCTIONS_H_ */
