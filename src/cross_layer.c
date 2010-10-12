#include "../include/cross_layer.h"

int create_socket(void)
{
#ifdef _WIN32

    WSADATA wsa;
    if (WSAStartup (MAKEWORD(2,0), &wsa) != 0)
    {
        error_exit("WSAStartup() failed");
    }
    else
    {
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0)
        {
            error_exit("socket() failed");
        }
        return sock;
    }
#else

    const int y = 1;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        error_exit("socket() failed");
    }
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));
    return sock;

#endif
    return 0;
}

void bind_socket(int *sock, unsigned long adress, unsigned short port)
{
#ifdef _WIN32
    struct sockaddr_in server;

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(adress);
    server.sin_port = htons(port);
    if (bind(*sock, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR)
    {
        error_exit("bind() failed");
    }
#else
    struct sockaddr_in server;
    memset(&server, 0, sizeof (server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(adress);
    server.sin_port = htons(port);
    if (bind(*sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        error_exit("bind() failed");
    }
#endif
}

void error_exit(char *message)
{
    printf("%s", message);
    /*
    printf("%s: %d\n", message, WSAGetLastError());
        //debug(stderr);
    #else
        printf("%s: %s\n", message, strerror(errno));
        //debug(stderr);
    */

    exit(EXIT_FAILURE);
}

void cleanup(void)
{
    OnExit();
#ifdef _WIN32
    WSACleanup();
#else
    /* Nichts zu tun */
#endif
}

#ifdef _WIN32
int mtime(void)
{
    return GetTickCount();
}
#else
int mtime(void)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (int)(tv.tv_sec*1000 + (tv.tv_usec / 1000));
}
#endif

void udp_send(int socket, unsigned char *data, int length, struct sockaddr_in *client)
{
    int rc;

    //printf("Try to send message to %s:%d...\n", inet_ntoa(client->sin_addr), client->sin_port);
    rc = sendto(socket, data, length, 0, (struct sockaddr *)client, sizeof(*client));
    /*
    int i;
    for(i = 0; i <= length; i++)
    {
        printf("%d-", data[i]);
    }
    printf("\n");
    */

#ifdef _WIN32
    if (rc == SOCKET_ERROR)
        error_exit("sendto() failed");
#else
    if (rc < 0)
        error_exit("sendto() failed");
#endif
    //else
    //printf("Message sent!\n");
}

int udp_recieve(int socket, unsigned char *data, int length, struct sockaddr_in *client)
{
    struct sockaddr_in newclient;
    unsigned int len;
    int size;
    len = sizeof(struct sockaddr_in);
    size = recvfrom(socket, data, length, 0, (struct sockaddr *)&newclient,&len);
    *client = newclient;
#ifdef _WIN32
    if (size == SOCKET_ERROR)
    {
        error_exit("recvfrom() failed");
    }
#else
    if (size < 0)
    {
        error_exit("recvfrom() failed");
    }
#endif
    else
    {
        return size;
    }
    return 0;
}

