/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include "main.h"

void myprintf(char *string, ...);
void myprintf2(char *string, ...);

/*
 #define printf(...) file = fopen("log.txt","a+");\
                    time(&rawtime );\
                    timeinfo = localtime(&rawtime);\
                    fprintf(file, "[%d:%d:%d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);\
                    fprintf(file, __VA_ARGS__);\
                    printf("[%d:%d:%d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);\
                    printf(__VA_ARGS__);\
                    fclose(file)

 #define eprintf(...) file = fopen("log.txt","a+");\
                    fprintf(file, __VA_ARGS__);\
                    fprintf(stdout, __VA_ARGS__);\
                    fclose(file)

 extern FILE *file;

 extern time_t rawtime;
 extern struct tm * timeinfo;
 */
#define printf(...) myprintf(__VA_ARGS__)
#define eprintf(...) myprintf2(__VA_ARGS__)

#endif // LOG_H_INCLUDED

/*
 if(player[i].used == 1 && player[i].joinstatus >= 4 && i != id)
 {
 if((player[i].x - player[id].x) != 0 && (player[i].y - player[id].y) != 0)
 {
 float temprot = player[id].rotation;
 double angle = atan2(player[i].x - player[id].x, player[i].y - player[id].y) * 180 / PI;
 double angle2, angle3;
 if(player[id].rotation < 0)
 {
 temprot += 180;
 }
 else if(player[id].rotation > 0)
 {
 temprot -= 180;
 }
 temprot = temprot *-1;
 double victimangle = atan2(player[id].x - player[i].x, player[id].y - player[i].y) * 180 / PI;
 double victimangle2 = victimangle + 90;
 double victimangle3 = victimangle - 90;
 int xPoint1, yPoint1;
 int xPoint2, yPoint2;
 xPoint1 = player[i].x + 16*cos(victimangle2*PI/180);
 yPoint1 = player[i].y + 16*sin(victimangle2*PI/180);
 xPoint2 = player[i].x + 16*cos(victimangle3*PI/180);
 yPoint2 = player[i].y + 16*sin(victimangle3*PI/180);

 angle2 = atan2(xPoint1 - player[id].x, yPoint1 - player[id].y) * 180 / PI;
 angle3 = atan2(xPoint2 - player[id].x, yPoint2 - player[id].y) * 180 / PI;
 printf("(Debug2) %lf: %lf, %lf\n", temprot, angle2, angle3);

 xP = xM + r*cos(ß)
 yP = yM + r*sin(ß)

 if((temprot <= angle2 && temprot >= angle3) || (temprot >= angle2 && temprot <= angle3))
 {
 SendMessageToPlayer(id, "You hit someone!", 1, writesocket);
 SendMessageToPlayer(i, "You were hitted by someone!", 1, writesocket);
 OnHit(id, i, writesocket);
 }
 //SendMessageToPlayer(id, "Shooting not implemented yet!", 1, writesocket);
 }

 }
 */
