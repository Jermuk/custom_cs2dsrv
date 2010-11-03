/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk, FloooD
 */

#include "../include/main.h"

/**
 * \fn int main()
 * \brief initialize sockets and if a message was recieved, give it to the right function.
 * \return EXIT_SUCCESS or EXIT_FAILURE
 */
int main()
{
	/**
	 * Initalize variables, weapons, players and sockets
	 */
	int readsocket;
	struct sockaddr_in newclient;
	unsigned char buffer[MAX_BUF];
	int size;
	fd_set descriptor; //I don't know

	ClearAllPlayer();
	WeaponInit();
	ReadCfg();

	readsocket = create_socket();
	bind_socket(&readsocket, INADDR_ANY, sv_hostport);
	atexit(cleanup);

	//struct in_addr usgnip = GetIp("usgn.de");
	/*
	 FD_ZERO(&descriptor);
	 FD_SET(readsocket, &descriptor);
	 */
	OnServerStart();
	ReadMap();
	UsgnRegister(readsocket);

	/**
	 * \var needed for ExecuteFunctionsWithTime()
	 */
	time_t checktime;
	time(&checktime);

	int mstime = mtime();
	int timecounter = mtime();
	int tickcounter = 0;
	const int fps = 1000 / sv_fps;

	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0; //1ms = 1000
	while (1)
	{
		if ((timecounter + 1000 - (int) mtime()) <= 0)
		{
			fpsnow = (int) tickcounter;
			tickcounter = 0;
			timecounter = mtime();
		}
		tickcounter++;

		UpdateBuffer();
		CheckForTimeout(readsocket);
		ExecuteFunctionsWithTime(&checktime, readsocket);
		CheckAllPlayerForReload(readsocket);

		FD_ZERO(&descriptor);
		FD_SET(readsocket, &descriptor);
		select(readsocket + 1, &descriptor, NULL, NULL, &timeout);

		if (FD_ISSET(readsocket, &descriptor))
		{
			size = udp_recieve(readsocket, buffer, MAX_BUF, &newclient);

			if (size < 3)
			{
				printf("Invalid paket! (size < 3)\n");
			}
			else
			{
				int id = IsPlayerKnown(newclient.sin_addr, newclient.sin_port); /// Function returns id or -1 if unknown
				if (id != -1)///When the player is known execute other commands as when the player is unknown
				{
					if (ValidatePaket(buffer, id)) ///Checks and raise the packet numbering if necessary
					{
						PaketConfirmation(buffer, id, readsocket); ///If the numbering is even, send a confirmation
						player[id].lastpaket = mtime();
						int control = 1;
						int position = 2;
						/**
						 * This while construct splits the recieved UDP-message
						 * into cs2d-messages.
						 * Every packet function returns the count of read bytes.
						 */
						while (control)
						{
							int tempsize = size - position;

							unsigned char *message = malloc(tempsize);
							memcpy(message, buffer + position, tempsize);
							int rtn = 0;

							switch (message[0])
							//payload
							{
							case 1:
								rtn = confirmation_known(message, tempsize, id,
										readsocket);
								break;
							case 3:
								rtn = connection_setup_known(message, tempsize,
										newclient.sin_addr, newclient.sin_port,
										id);
								break;
							case 7:
								rtn = fire(message, tempsize, id, readsocket);
								break;
							case 8:
								rtn = advanced_fire(message, tempsize, id,
										readsocket);
								break;
							case 9:
								rtn = weaponchange(message, tempsize, id,
										readsocket);
								break;
							case 10:
								rtn = posupdaterun(message, tempsize, id,
										readsocket);
								break;
							case 11:
								rtn = posupdatewalk(message, tempsize, id,
										readsocket);
								break;
							case 12:
								rtn = rotupdate(message, tempsize, id,
										readsocket);
								break;
							case 13:
								rtn = posrotupdaterun(message, tempsize, id,
										readsocket);
								break;
							case 14:
								rtn = posrotupdatewalk(message, tempsize, id,
										readsocket);
								break;
							case 16:
								rtn = reload(message, tempsize, id, readsocket);
								break;
							case 20:
								rtn = teamchange(message, tempsize, id,
										readsocket);
								break;
							case 23:
								rtn = buy(message, tempsize, id, readsocket);
								break;
							case 24:
								rtn = drop(message, tempsize, id, readsocket);
								break;
							case 28:
								// Spray 28 - 0 - x x - y y - color
								rtn = spray(message, tempsize, id, readsocket);
								break;
							case 32:
								rtn
										= specpos(message, tempsize, id,
												readsocket);
								break;
							case 39:
								rtn = respawnrequest(message, tempsize, id,
										readsocket);
								break;
							case 240:
								rtn = chatmessage(message, tempsize, id,
										readsocket);
								break;
							case 249:
								rtn = ping_ingame(message, tempsize, id,
										readsocket);
								break;
							case 252:
								rtn = joinroutine_known(message, tempsize, id,
										readsocket);
								break;
							case 253:
								rtn = leave(id, readsocket);
								break;
							default:
								SendMessageToPlayer(id, "Not implemented yet!",
										1, readsocket);
								unknown(message, tempsize, buffer, size,
										position);
								rtn = tempsize;
								break;
							}

							position = position + rtn;
							if (position == size)
							{
								free(message);
								break;
							}
							/**
							 * Security check (Buffer Overflow)
							 */
							else if (position > size)
							{
								printf("Error while reading packet: position(%d) > size(%d)\n", position, size);
								free(message);
							}
							free(message);
						}
					}
				}
				else
				{
					int control = 1;
					int position = 2;
					while (control)
					{
						int tempsize = size - position;

						unsigned char *message = malloc(tempsize);
						memcpy(message, buffer + position, tempsize);
						int rtn = 0;

						switch (message[0])
						//payload
						{
						case 1:
							rtn = confirmation_unknown(message, tempsize,
									newclient.sin_addr, newclient.sin_port);
							break;
						case 3:
							rtn = connection_setup_unknown(message, tempsize,
									newclient.sin_addr, newclient.sin_port);
							break;
						case 27:
							rtn = UsgnPacket(27, message, tempsize, readsocket);
							break;
						case 28:
							rtn = UsgnPacket(28, message, tempsize, readsocket);
							break;
						case 250:
							rtn = ping_serverlist(message, tempsize,
									&newclient, readsocket);
							break;
						case 251:
							rtn = serverinfo_request(message, tempsize,
									&newclient, readsocket);
							break;
						case 252:
							rtn = joinroutine_unknown(message, tempsize,
									&newclient, readsocket);
							break;
						default:
							unknown(message, tempsize, buffer, size, position);
							rtn = tempsize;
							break;
						}

						position = position + rtn;
						if (position == size)
						{
							free(message);
							break;
						}
						/**
						 * Security check (Buffer Overflow)
						 */
						else if (position > size)
						{
							printf("Error while reading packet: position(%d) > size(%d)\n", position, size);
							free(message);
						}
						free(message);
					}
				}
			}

		}
#ifdef _WIN32
		Sleep(fps + mstime - mtime());
#else
		sleep(fps + mstime - mtime());
#endif
		mstime = mtime();
	}
	return EXIT_SUCCESS;
}
