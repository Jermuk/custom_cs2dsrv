#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "main.h"

struct WEAPON
{
    short weapondamage, weapondamage_z1, weapondamage_z2;
    short shoottime, reloadtime;
    float freq;
    short speed;
    short slot;
    short price;
    short range;
    short accuracy;
    short ammo1, ammo2;
    char *name;
};

struct PLAYER_WEAPON
{
    short id, slot;
    short ammo1, ammo2;
};

struct PLAYER
{
    int used;
    unsigned short client_nummer;
    unsigned short server_nummer;
    time_t lastpaket;
    unsigned short joinstatus;

    unsigned char *name;
    unsigned char *spraylogo;
    unsigned char *win;
    unsigned short version;
    unsigned short *usgn;
    unsigned char team;
    unsigned char skin;
    short deaths, score;
    unsigned short x,y;
    unsigned char health, armor;
    unsigned char actualweapon;
    struct PLAYER_WEAPON slot[10];
    float rotation; //-180 to +180
    int specposx, specposy;
    unsigned short money;
    unsigned short kills;
    int reloadtimer, reloading;

    short dead;

    int start;
    int latency;

    int firetimer;
    int zoommode;


    /* Address*/
    unsigned short port;
    struct in_addr ip;
};
struct PLAYER player[MAX_CLIENTS];


struct TILE
{
    unsigned char mode;
    unsigned char tileid;
};
struct TILE **map;

#endif // STRUCTS_H_INCLUDED
