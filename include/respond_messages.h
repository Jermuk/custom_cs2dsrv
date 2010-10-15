#ifndef RESPOND_MESSAGES_H_INCLUDED
#define RESPOND_MESSAGES_H_INCLUDED
#include "main.h"

void SendSpawnMessage(int id, unsigned short x, unsigned short y, int writesocket);
void SendFireMessage(int id, int writesocket);
void SendBuyMessage(int id, int wpnid, int writesocket);
void SendHitMessage(int id, int victim, int health, int writesocket);
void SendWeaponChangeMessage(int id, int wpnid, int writesocket);
void SendPosUpdate(int id, unsigned short x, unsigned short y, int status, int writesocket);
void SendPosRotUpdate(int id, unsigned short x, unsigned short y, int status, float rotation, int writesocket);
void SendRotUpdate(int id, float rotation, int writesocket);
void SendMessageToPlayer(int id, unsigned char *message, int status, int writesocket);
void SendMessageToAll(unsigned char *message, int status, int writesocket);
void SendJoinMessage(int id, int writesocket);
void SendLeaveMessage(int id, int writesocket);
void SendChatMessage(int id, unsigned char *message, int team, int writesocket);
void SendTeamChangeMessage(int id, unsigned char team, unsigned char skin, int writesocket);
void PingAllPlayer(int writesocket);
void SendReloadMessage(int id, int status, int writesocket);
void SendPingList(int writesocket);

#endif // RESPOND_MESSAGES_H_INCLUDED
