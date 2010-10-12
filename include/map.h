#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "main.h"

void ReadMap();
unsigned char *ReadLine(FILE *file);
unsigned char ReadByte(FILE *file);
int ReadInt(FILE *file);
#define MAX_SPAWNPOINTS 10

unsigned short tspawnx[MAX_SPAWNPOINTS];
unsigned short tspawny[MAX_SPAWNPOINTS];
unsigned short tspawncount;

unsigned short ctspawnx[MAX_SPAWNPOINTS];
unsigned short ctspawny[MAX_SPAWNPOINTS];
unsigned short ctspawncount;


#endif // MAP_H_INCLUDED
