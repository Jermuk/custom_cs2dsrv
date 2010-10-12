#include "../include/log.h"

void myprintf(char *string, ...)
{
    FILE *logfile;
    time_t rawtime;
    struct tm * timeinfo;

    logfile = fopen("log.txt","a+");
    if(logfile != NULL)
    {
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        fprintf(logfile, "[%d:%d:%d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
        fprintf(stdout, "[%d:%d:%d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

        va_list argzeiger;
        va_start(argzeiger,string);
        vprintf(string,argzeiger);
        vfprintf(logfile, string, argzeiger);
        va_end(argzeiger);

        fclose(logfile);
    }
    else
    {
        printf("Cannot open logfile!\n");
    }
}

void myprintf2(char *string, ...)
{
    FILE *logfile;
    logfile = fopen("log.txt","a+");
    if(logfile != NULL)
    {
        va_list argzeiger;
        va_start(argzeiger,string);
        vprintf(string,argzeiger);
        vfprintf(logfile, string, argzeiger);
        va_end(argzeiger);

        fclose(logfile);
    }
    else
    {
        printf("Cannot open logfile!\n");
    }
}
