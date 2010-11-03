/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#ifndef RESPOND_MESSAGES_H_INCLUDED
#define RESPOND_MESSAGES_H_INCLUDED
#include "main.h"

void SendSpawnMessage(int id, unsigned short x, unsigned short y,
		int writesocket);
void SendAdvancedFireMessage(int id, int status, int writesocket);
void SendFireMessage(int id, int writesocket);
void SendBuyMessage(int id, int wpnid, int writesocket);
void SendHitMessage(int id, int victim, int health, int writesocket);
void SendWeaponChangeMessage(int id, int wpnid, int writesocket);
void SendPosUpdate(int id, unsigned short x, unsigned short y, int status,
		int writesocket);
void SendPosRotUpdate(int id, unsigned short x, unsigned short y, int status,
		float rotation, int writesocket);
void SendRotUpdate(int id, float rotation, int writesocket);
void SendMessageToPlayer(int id, char *message, int status, int writesocket);
void SendMessageToAll(char *message, int status, int writesocket);
void SendJoinMessage(int id, int writesocket);
void SendLeaveMessage(int id, int writesocket);
void SendChatMessage(int id, unsigned char *message, int team, int writesocket);
void SendTeamChangeMessage(int id, unsigned char team, unsigned char skin,
		int writesocket);
void PingAllPlayer(int writesocket);
void SendReloadMessage(int id, int status, int writesocket);
void SendSprayMessage(char id, unsigned short xx, unsigned short yy, char c,
		int writesocket);
void SendKillMessage(int id, int victim, int writesocket);
void SendPingList(int writesocket);
void SendBuyFailedMessage(int id, int status, int writesocket);
void SendDropMessage(int id, int wpnid, int ammo1, int ammo2, int unknown1,
		int unknown2, int unknown3, int writesocket);
#endif // RESPOND_MESSAGES_H_INCLUDED
