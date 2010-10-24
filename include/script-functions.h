#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED

#include "main.h"

int OnJoin(int id, int writesocket);
int OnLeave(int id, int writesocket);
int OnSpecmove(int id, int newx, int newy, int writesocket);
int OnServerStart();
int OnExit();
int OnRespawnRequest(int id, int writesocket);
int OnRespawn(int id, int writesocket);
int OnWeaponChangeAttempt(int id, int wpnid, int writesocket);
int OnAdvancedFire(int id, int status, int writesocket);
int OnFire(int id, int writesocket);
int OnHit(int hitter, int victim, int writesocket);
int OnBuyAttempt(int id, int wpnid, int writesocket);
int OnBuy(int id, int wpnid, int writesocket);
int OnKill(int hitter, int victim, int wpnid, int writesocket);
int OnChatMessage(int id, unsigned char *message, int team, int writesocket);
int OnTeamChangeAttempt(int id, unsigned char team, unsigned char skin, int writesocket);
int OnTeamChange(int id, unsigned char team, unsigned char skin, int writesocket);
int OnMoveAttempt(int id, unsigned short x, unsigned short y, int status, int writesocket);
#endif
