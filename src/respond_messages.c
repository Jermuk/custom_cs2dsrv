#include "../include/respond_messages.h"


void SendSpawnMessage(int id, unsigned short x, unsigned short y, int writesocket)
{
    int stringsize = 11;
    unsigned char *buffer = malloc(stringsize);
    if (buffer == NULL) error_exit("Memory error ( SendSpawnMessage() )\n");

    int position = 0;

    unsigned short *spawnx = &x;
    unsigned short *spawny = &y;
    unsigned short *pmoney = &player[id].money;

    buffer[position] = 21;
    position++;
    buffer[position] = id;
    position++;
    memcpy(buffer+position, spawnx, 2);
    position += 2;
    memcpy(buffer+position, spawny, 2);
    position += 2;
    buffer[position] = 50; //Team
    position++;
    buffer[position] = 0;
    position++;
    /*
    buffer[position] = pmoney[1]; //Money
    position++;
    buffer[position] = pmoney[0]; // Money
    position++;
    */
    memcpy(buffer+position, pmoney, 2);
    position += 2;

    int i, count;
    count = STARTWEAPONS_COUNT;//sizeof(startweapons)/sizeof(startweapons[0]);
    buffer[position] = count;
    position++;

    buffer = realloc(buffer, stringsize + count);
    if (buffer == NULL) error_exit("Memory error ( SendSpawnMessage() )\n");

    for(i = 0; i <= count-1; i++)
    {
        buffer[position] = startweapons[i];
        position++;

        GivePlayerWeapon(id, startweapons[i]);
        if(startweapons[i] == 50) player[id].actualweapon = i; //else 0
    }

    /*
    int count, i;
    count = 0;
    for(i = 0; i <= 10; i++)
    {
        if(player[id].slot[i].id != 0)
        {
            count++;
        }
    }
    buffer[position] = count; //Count
    position++;

    buffer = realloc(buffer, stringsize + count);
    if (buffer == NULL) error_exit("Memory error ( SendSpawnMessage() )\n");

    for(i = 0; i <= 10; i++)
    {
        if(player[id].slot[i].id != 0)
        {
            buffer[position] = player[id].slot[i].id;
            position++;
        }
    }
    */

    SendToAll(buffer, stringsize + count, 1, writesocket);

    free(buffer);
}

void SendFireMessage(int id, int writesocket)
{
    int stringsize = 2;
    unsigned char *buffer = malloc(stringsize);
    if (buffer == NULL) error_exit("Memory error ( SendFireMessage() )\n");

    int position = 0;

    buffer[position] = 7;
    position++;
    buffer[position] = id;
    position++;

    SendToAll(buffer, stringsize, 1, writesocket);

    free(buffer);
}

void SendBuyMessage(int id, int wpnid, int writesocket)
{
    int stringsize = 6;
    unsigned char *buffer = malloc(stringsize);
    if (buffer == NULL) error_exit("Memory error ( SendBuyMessage() )\n");

    int position = 0;

    buffer[position] = 23;
    position++;
    buffer[position] = id;
    position++;
    buffer[position] = wpnid;
    position++;
    memcpy(buffer+position, &player[id].money, 2);
    position += 2;
    buffer[position] = 0;
    position++;

    SendToPlayer(buffer, stringsize, id, 1, writesocket);

    free(buffer);

    SendWeaponChangeMessage(id, wpnid, writesocket);
}

void SendHitMessage(int id, int victim, int health, int writesocket)
{
    int stringsize = 5;
    unsigned char *buffer = malloc(stringsize);
    if (buffer == NULL) error_exit("Memory error ( SendHitMessage() )\n");

    int position = 0;

    buffer[position] = 17;
    position++;
    buffer[position] = id;
    position++;
    buffer[position] = victim;
    position++;
    buffer[position] = health;
    position++;
    buffer[position] = 0;
    position++;


    SendToAll(buffer, stringsize, 1, writesocket);

    free(buffer);
}

void SendWeaponChangeMessage(int id, int wpnid, int writesocket)
{
    int stringsize = 4;
    unsigned char *buffer = malloc(stringsize);
    if (buffer == NULL) error_exit("Memory error ( SendWeaponChangeMessage() )\n");

    int position = 0;

    buffer[position] = 9;
    position++;
    buffer[position] = id;
    position++;
    buffer[position] = wpnid;
    position++;
    buffer[position] = 0;
    position++;

    SendToAll(buffer, stringsize, 1, writesocket);

    free(buffer);
}

void SendPosUpdate(int id, unsigned short x, unsigned short y, int status, int writesocket)
{
    int stringsize = 6;
    unsigned char *buffer = malloc(stringsize);
    if (buffer == NULL) error_exit("Memory error ( SendSpawnMessage() )\n");

    int position = 0;

    unsigned short *px = &x;
    unsigned short *py = &y;

    if(status == 0) buffer[position] = 11;
    else if(status == 1) buffer[position] = 10;

    position++;
    buffer[position] = id;
    position++;
    memcpy(buffer+position, px, 2);
    position += 2;
    memcpy(buffer+position, py, 2);
    position += 2;

    SendToAllOther(id, buffer, stringsize, 1, writesocket);

    free(buffer);
}

void SendPosRotUpdate(int id, unsigned short x, unsigned short y, int status, float rotation, int writesocket)
{
    int stringsize = 10;
    unsigned char *buffer = malloc(stringsize);
    if (buffer == NULL) error_exit("Memory error ( SendPosRotUpdate() )\n");

    int position = 0;

    unsigned short *px = &x;
    unsigned short *py = &y;
    //if(rotation > 180) rotation = (rotation - 360);
    //unsigned short *protation = &rotation; //2 Bytes cut off

    if(status == 0) buffer[position] = 14;
    else if(status == 1) buffer[position] = 13;

    position++;
    buffer[position] = id;
    position++;
    memcpy(buffer+position, px, 2);
    position += 2;
    memcpy(buffer+position, py, 2);
    position += 2;
    memcpy(buffer+position, &rotation, 4);
    position += 4;

    SendToAllOther(id, buffer, stringsize, 1, writesocket);

    free(buffer);
}

void SendRotUpdate(int id, float rotation, int writesocket)
{
    int stringsize = 6;
    unsigned char *buffer = malloc(stringsize);
    if (buffer == NULL) error_exit("Memory error ( SendRotUpdate() )\n");

    int position = 0;
    //if(rotation > 180) rotation = (rotation - 360);


    buffer[position] = 12;
    position++;
    buffer[position] = id;
    position++;
    memcpy(buffer+position, &rotation, sizeof(float));

    SendToAllOther(id, buffer, stringsize, 1, writesocket);

    free(buffer);
}


void SendMessageToPlayer(int id, unsigned char *message, int status, int writesocket)
{
    /*
    1 - Chat
    2 - Screen
    3 - Console
    4 - Crash
    */
    int stringsize = 5 + strlen(message);
    unsigned char *buffer = malloc(stringsize);
    if (buffer == NULL) error_exit("Memory error ( SendChatMessage() )\n");

    int position = 0;

    buffer[position] = 240;
    position++;
    buffer[position] = 0;
    position++;
    buffer[position] = status;
    position++;
    buffer[position] = strlen(message);
    position++;
    buffer[position] = 0;
    position++;
    memcpy(buffer+position, message, strlen(message));
    position += strlen(message);

    SendToPlayer(buffer, stringsize, id, 1, writesocket);

    switch(status)
    {
    case 1:
        printf("To %s (Chat): %s\n", player[id].name ,message);
        break;
    case 2:
        printf("To %s (Screen): %s\n", player[id].name ,message);
        break;
    case 3:
        printf("To %s (Console): %s\n", player[id].name ,message);
        break;
    default:
        printf("Unknown status (SendMessageToPlayer())!\n");
        break;
    }

    free(buffer);
}

void SendMessageToAll(unsigned char *message, int status, int writesocket)
{
    /*
    1 - Chat
    2 - Screen
    3 - Console
    4 - Crash
    */
    int stringsize = 5 + strlen(message);
    unsigned char *buffer = malloc(stringsize);
    if (buffer == NULL) error_exit("Memory error ( SendChatMessage() )\n");

    int position = 0;

    buffer[position] = 240;
    position++;
    buffer[position] = 0;
    position++;
    buffer[position] = status;
    position++;
    buffer[position] = strlen(message);
    position++;
    buffer[position] = 0;
    position++;
    memcpy(buffer+position, message, strlen(message));
    position += strlen(message);

    SendToAll(buffer, stringsize, 1, writesocket);

    switch(status)
    {
    case 1:
        printf("To All (Chat): %s\n", message);
        break;
    case 2:
        printf("To All (Screen): %s\n", message);
        break;
    case 3:
        printf("To All (Console): %s\n", message);
        break;
    default:
        printf("Unknown status (SendMessageToAll())!\n");
        break;
    }


    free(buffer);
}



void SendJoinMessage(int id, int writesocket)
{
    int stringsize = 4 + strlen(player[id].name);
    unsigned char *buffer = malloc(stringsize);
    if (buffer == NULL) error_exit("Memory error ( SendJoinMessage() )\n");

    int position = 0;

    buffer[position] = 248;
    position++;
    buffer[position] = id;
    position++;
    buffer[position] = strlen(player[id].name);
    position++;

    memcpy(buffer+position, player[id].name, strlen(player[id].name));
    position += strlen(player[id].name);

    buffer[position] = 0; //strlen ACK
    position++;

    SendToAll(buffer, stringsize, 1, writesocket);
    free(buffer);
}

void SendLeaveMessage(int id, int writesocket)
{
    if(player[id].joinstatus >= 4)
    {
        int stringsize = 3;
        unsigned char *buffer = malloc(stringsize);
        if (buffer == NULL) error_exit("Memory error ( SendLeaveMessage() )\n");
        int position = 0;

        buffer[position] = 253;
        position++;
        buffer[position] = id;
        position++;
        buffer[position] = 0; //strlen ACK
        position++;

        SendToAll(buffer, stringsize, 1, writesocket);
        free(buffer);
    }
}

void SendChatMessage(int id, unsigned char *message, int team, int writesocket)
{
    int stringsize = 5 + strlen(message);
    unsigned char *buffer = malloc(stringsize);
    if (buffer == NULL) error_exit("Memory error ( SendChatMessage() )\n");

    int position = 0;

    buffer[position] = 240;
    position++;
    buffer[position] = id;
    position++;
    buffer[position] = team;
    position++;
    buffer[position] = strlen(message);
    position++;
    buffer[position] = 0;
    position++;
    memcpy(buffer+position, message, strlen(message));
    position += strlen(message);
    if(team == 1)
    {
        SendToAll(buffer, stringsize, 1, writesocket);
    }
    else if(team == 2)
    {
        SendToTeam(buffer, stringsize, 1, player[id].team, writesocket);
    }
    free(buffer);
}

void SendTeamChangeMessage(int id, unsigned char team, unsigned char skin, int writesocket)
{
    int stringsize = 4;
    unsigned char *buffer = malloc(stringsize);
    if (buffer == NULL) error_exit("Memory error ( SendJoinMessage() )\n");

    int position = 0;

    buffer[position] = 20;
    position++;
    buffer[position] = id;
    position++;
    buffer[position] = team;
    position++;
    buffer[position] = skin;
    position++;


    SendToAll(buffer, stringsize, 1, writesocket);
    free(buffer);
}

void PingAllPlayer(int writesocket)
{
    time_t actualtime;
    time(&actualtime);
    if(actualtime >= (firsttime + 5))
    {
        firsttime = actualtime;
        int i;
        for(i = 1; i <= sv_maxplayers; i++)
        {
            if(player[i].used == 1 && player[i].joinstatus >= 4)
            {
                int stringsize = 5;
                unsigned char *buffer = malloc(stringsize);
                if (buffer == NULL) error_exit("Memory error ( SendJoinMessage() )\n");

                int position = 0;

                buffer[position] = 249;
                position++;
                buffer[position] = 0;
                position++;
                buffer[position] = 32;
                position++;
                buffer[position] = 191;
                position++;
                buffer[position] = 0;
                position++;

                player[i].start = mtime();

                SendToPlayer(buffer, stringsize, i, 0, writesocket);

                free(buffer);
            }

        }
    }
}
