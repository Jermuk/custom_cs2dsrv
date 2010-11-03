/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk, GuccaGucca, FloooD
 */

#include "../include/settings.h"

unsigned char pre_authcode[] = "5TWs3Obv7";
char startweapons[] =
{ 50 };
int fpsnow = 0;
int dropped_weapons_count = 0;

unsigned char *sv_name = NULL;
unsigned char *sv_map = NULL;
unsigned char *sv_rcon = NULL;
unsigned int sv_hostport = 0;
unsigned short sv_maxplayers = 0;
unsigned short sv_fps = 0;
unsigned short sv_lcbuffer = 0;
unsigned short sv_fow = 0;
unsigned short sv_gamemode = 0;
unsigned short sv_friendlyfire = 0;
unsigned short sv_usgnonly = 0;
unsigned char *sv_password = 0;
unsigned short bot_count = 0;

unsigned short mp_roundtime = 0;
unsigned short mp_freezetime = 0;
unsigned short mp_c4timer = 0;
unsigned short mp_infammo = 0;
unsigned short mp_respawndelay = 0;
unsigned short mp_specmode = 0;
unsigned short onlineplayer = 0;
unsigned short mp_startmoney = 0;
unsigned short mp_dmspawnmoney = 0;

struct setting
{
	char *name;
	char *value;
};

int tointeger(char * c);
double todouble(char *c);
struct setting * settings[256];
int entries;

int readConfig()
{
	FILE * pFile;
	char s[256];
	int setting_num = 0;
	pFile = fopen("server.cfg", "r");

	if (pFile == NULL)
		perror("Error opening file: server.cfg");
	else
	{
		while ((fgets(s, sizeof(s), pFile)) != NULL)
		{
			if (s[0] == '\n' || (s[0] == '/' && s[1] == '/'))
				continue;
			//char *s1,*s2,*type;

			int i;
			for (i = 0; i < strlen(s); i++)
			{
				if (s[i] == ' ')
				{
					i++; //skip ' ' char
					struct setting * var;
					var = (struct setting*) malloc(sizeof(struct setting));

					var->name = malloc(i + 1);
					if (var->name == NULL)
						error_exit("Memory error in readConfig()\n");
					strncpy(var->name, s, i);
					var->name[i] = '\0';
					if (s[strlen(s) - i - 1] == '\n') //if  \n found then remove it
					{
						var->value = malloc(strlen(s) - i - 1 + 1);
						if (var->value == NULL)
							error_exit("Memory error in readConfig()\n");
						strncpy(var->value, &s[i], strlen(s) - i - 1); //also ommit the \n
						var->value[strlen(s) - i - 1] = '\0';
					}
					else
					{
						var->value = malloc(strlen(s) - i + 1);
						if (var->value == NULL)
							error_exit("Memory error in readConfig()\n");
						strncpy(var->value, &s[i], strlen(s) - i); //also ommit the \n
						var->value[strlen(s) - i] = '\0';
					}

					settings[setting_num] = var;
					break;
				}
			}
			setting_num++;
		}
		fclose(pFile);
	}
	return setting_num;
}

char *GetValue(char *sname, char *alternate)////struct setting ** arr , int length)
{
	int i;
	for (i = 0; i < entries; i++)
	{
		if (settings[i] != NULL)
		{
			struct setting *var = settings[i];
			if (strcmp(var->name, sname) == 0)
			{
				char *string = malloc(strlen(var->value) + 1);
				if (string == NULL)
					error_exit("Memory error in GetValue()\n");
				strncpy(string, var->value, strlen(var->value));
				string[strlen(var->value)] = '\0';

				free(var->name);
				free(var->value);
				free(var); //also frees settings[i]
				settings[i] = NULL;
				return string;
			}
		}

	}
	//If not found
	char *string = malloc(strlen(alternate) + 1);
	if (string == NULL)
		error_exit("Memory error in GetValue()\n");
	strncpy(string, alternate, strlen(alternate));
	string[strlen(alternate)] = '\0';

	return string; // doesn't exist
}

void ReadCfg()
{
	entries = readConfig();

	sv_name = (unsigned char *) GetValue("sv_name", "Alpha Custom CS2D Server");
	sv_map = (unsigned char *) GetValue("sv_map", "de_cs2d");
	sv_hostport = tointeger(GetValue("sv_hostport", "36963"));
	sv_maxplayers = tointeger(GetValue("sv_maxplayers", "32")) + 1;
	sv_fps = tointeger(GetValue("sv_fps", "250"));
	sv_lcbuffer = tointeger(GetValue("sv_lcbuffer", "100"));
	sv_fow = tointeger(GetValue("sv_fow", "0"));
	sv_gamemode = tointeger(GetValue("sv_gamemode", "2"));
	sv_friendlyfire = tointeger(GetValue("sv_friendlyfire", "0"));
	sv_usgnonly = tointeger(GetValue("sv_usgnonly", "0"));
	sv_password = (unsigned char *) GetValue("sv_password", "");
	sv_rcon = (unsigned char *) GetValue("sv_rcon", "testing");
	bot_count = tointeger(GetValue("bot_count", "0"));

	mp_roundtime = tointeger(GetValue("mp_roundtime", "5"));
	mp_freezetime = tointeger(GetValue("mp_freezetime", "0"));
	mp_c4timer = tointeger(GetValue("mp_c4timer", "35"));
	mp_infammo = tointeger(GetValue("mp_infammo", "0"));
	mp_respawndelay = tointeger(GetValue("mp_respawndelay", "0"));
	mp_specmode = tointeger(GetValue("mp_specmode", "0"));
	mp_startmoney = tointeger(GetValue("mp_startmoney", "1000"));
	mp_dmspawnmoney = tointeger(GetValue("mp_dmspawnmoney", "32000"));
}

int tointeger(char *c)
{
	int buff = atoi(c);
	free(c);
	return buff;
}

double todouble(char *c)
{
	double buff = atof(c);
	free(c);
	return buff;
}
