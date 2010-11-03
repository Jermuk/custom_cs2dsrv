/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

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
int OnTeamChangeAttempt(int id, unsigned char team, unsigned char skin,
		int writesocket);
int OnTeamChange(int id, unsigned char team, unsigned char skin,
		int writesocket);
int OnMoveAttempt(int id, unsigned short x, unsigned short y, int status,
		int writesocket);
int OnDrop(int id, unsigned char wpnid, unsigned short ammo1,
		unsigned short ammo2, unsigned char unknown1, unsigned char unknown2,
		unsigned char unknown3, int writesocket);
#endif
