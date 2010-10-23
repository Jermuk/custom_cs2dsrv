#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#define MAX_BUF 1024

/* --- Server Settings --- */
#define LOCAL_PORT 1994
#define MAX_CLIENTS 64
#define TIMEOUT 10

extern unsigned char pre_authcode[];

extern unsigned char sv_name[];
extern unsigned char sv_map[];
extern unsigned int sv_hostport;
extern unsigned short sv_maxplayers;
extern unsigned short sv_fow;
extern unsigned short sv_gamemode;
extern unsigned short sv_friendlyfire;
extern unsigned short sv_usgnonly;
extern unsigned char sv_password[];
extern unsigned short bot_count;

extern unsigned short mp_roundtime;
extern unsigned short mp_freezetime;
extern unsigned short mp_c4timer;
extern unsigned short mp_infammo;
extern unsigned short mp_respawndelay;
extern unsigned short mp_specmode;
extern unsigned short onlineplayer;
extern unsigned short mp_startmoney;

#define STARTWEAPONS_COUNT 2
extern char startweapons[];

#endif // SETTINGS_H_INCLUDED
