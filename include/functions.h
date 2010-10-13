#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "main.h"
int IsPlayerKnown(struct in_addr ip, u_short port);
void ClearPlayer(int id);
void ClearAllPlayer(void);
void CheckForTimeout(void);
int GivePlayerWeapon(int id, int wpnid);
void RemovePlayerWeapon(int id, int wpnid);
void RemoveAllPlayerWeapon(int id);
int PlayerTimeout(int id);
unsigned short GetServerStatus(void);
unsigned short endian_swap_short(unsigned short *x);
unsigned int endian_swap_int(unsigned int *x);
int ValidatePaket(char *message, int id);
void PaketConfirmation(char *message, int id, int writesocket);
int CheckPlayerData(char *password);
unsigned char *GetEncodedString(unsigned char *string, int length);
void CheckAllPlayerForReload(int writesocket);

extern time_t firsttime;

#endif // FUNCTIONS_H_INCLUDED
