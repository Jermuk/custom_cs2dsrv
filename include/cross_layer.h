/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#ifndef CROSS_LAYER_H_INCLUDED
#define CROSS_LAYER_H_INCLUDED

#include "main.h"

int create_socket(void);
void error_exit(char *message);
void bind_socket(int *sock, unsigned long adress, unsigned short port);
void cleanup(void);
int udp_recieve(int socket, unsigned char *data, int length,
		struct sockaddr_in *client);
void udp_send(int socket, unsigned char *data, int length,
		struct sockaddr_in *client);
int mtime(void);
#endif // CROSS_LAYER_H_INCLUDED
