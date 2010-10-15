#include "../include/log.h"

/**
 * \fn void myprintf(char *string, ...)
 * \brief prints string with time to stdout and logfile
 * \param *string the string to print out (same syntax as printf)
 * \param ... the other parameters, if necessary
 */
void myprintf(char *string, ...)
{
#ifdef _WIN32
    FILE *logfile;
    time_t rawtime;
    struct tm * timeinfo;

    logfile = fopen("log.txt","a+");
    if(logfile != NULL)
    {
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        //fprintf(logfile, "[%d:%d:%d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
        fprintf(stdout, "[%d:%d:%d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

        va_list argzeiger;
        va_start(argzeiger,string);
        vprintf(string,argzeiger);
        //vfprintf(logfile, string, argzeiger);
        va_end(argzeiger);

        fclose(logfile);
    }
    else
    {
        printf("Cannot open logfile!\n");
    }
#else
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fprintf(stdout, "[%d:%d:%d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    va_list argzeiger;
    va_start(argzeiger,string);
    vprintf(string,argzeiger);
    va_end(argzeiger);
#endif
}

/**
 * \fn void myprintf2(char *string, ...)
 * \brief same as myprintf, just with the difference, that the time won't be printed
 * \param *string the string to print out (same syntax as printf)
 * \param ... the other parameters, if necessary
 */
void myprintf2(char *string, ...)
{
#ifdef _WIN32
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
#else
    va_list argzeiger;
    va_start(argzeiger,string);
    vprintf(string,argzeiger);
    va_end(argzeiger);
#endif
}
