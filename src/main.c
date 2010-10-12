#include "../include/main.h"

time_t firsttime;

int main()
{
    int readsocket;
    struct sockaddr_in newclient;
    unsigned char buffer[MAX_BUF];
    int size;
    fd_set descriptor; //I don't know

    ClearAllPlayer();
    WeaponInit();

    readsocket = create_socket();
    bind_socket(&readsocket, INADDR_ANY, LOCAL_PORT);
    atexit(cleanup);

    FD_ZERO(&descriptor);
    FD_SET(readsocket, &descriptor);

    OnServerStart();
    ReadMap();
    time(&firsttime);
    while(1)
    {

        CheckForTimeout();
        PingAllPlayer(readsocket);

        select(readsocket+1, &descriptor, NULL, NULL, NULL);

        if(FD_ISSET(readsocket, &descriptor))
        {
            size = udp_recieve(readsocket, buffer, MAX_BUF, &newclient);
            //printf("(Debug) Recieved data from %s:%d\n", inet_ntoa(newclient.sin_addr), newclient.sin_port);

            if (size < 3)
            {
                printf("Invalid paket! (size < 3)\n");
            }
            else
            {
                int id = IsPlayerKnown(newclient.sin_addr, newclient.sin_port);
                if(id != -1)
                {
                    if (ValidatePaket(buffer, id))
                    {
                        PaketConfirmation(buffer, id, readsocket);
                        time(&player[id].lastpaket);
                        int control = 1;
                        int position = 2;
                        while(control)
                        {
                            int tempsize = size - position;

                            unsigned char *message = malloc(tempsize);
                            memcpy(message, buffer+position, tempsize);
                            int rtn = 0;

                            switch(message[0]) //payload
                            {
                            case 1:
                                rtn = confirmation_known(message, tempsize, id, readsocket);
                                break;
                            case 3:
                                rtn = connection_setup_known(message, tempsize, newclient.sin_addr, newclient.sin_port, id);
                                break;
                            case 7:
                                rtn = fire(message, tempsize, id, readsocket);
                                break;
                            case 9:
                                rtn = weaponchange(message, tempsize, id, readsocket);
                                break;
                            case 10:
                                rtn = posupdaterun(message, tempsize, id, readsocket);
                                break;
                            case 11:
                                rtn = posupdatewalk(message, tempsize, id, readsocket);
                                break;
                            case 12:
                                rtn = rotupdate(message, tempsize, id, readsocket);
                                break;
                            case 13:
                                rtn = posrotupdaterun(message, tempsize, id, readsocket);
                                break;
                            case 14:
                                rtn = posrotupdatewalk(message, tempsize, id, readsocket);
                                break;
                            case 17:
                                rtn = buy(message, tempsize, id, readsocket);
                                break;
                            case 20:
                                rtn = teamchange(message, tempsize, id, readsocket);
                                break;
                            case 32:
                                rtn = specpos(message, tempsize, id, readsocket);
                                break;
                            case 39:
                                rtn = respawnrequest(message, tempsize, id, readsocket);
                                break;
                            case 240:
                                rtn = chatmessage(message, tempsize, id, readsocket);
                                break;
                            case 249:
                                rtn = ping_ingame(message, tempsize, id, readsocket);
                                break;
                            case 252:
                                rtn = joinroutine_known(message, tempsize, id, readsocket);
                                break;
                            case 253:
                                rtn = leave(id, readsocket);
                                break;
                            default:
                                SendMessageToPlayer(id, "Not implemented yet!", 1, readsocket);
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
                    while(control)
                    {
                        int tempsize = size - position;

                        unsigned char *message = malloc(tempsize);
                        memcpy(message, buffer+position, tempsize);
                        int rtn = 0;

                        switch(message[0]) //payload
                        {
                        case 1:
                            rtn = confirmation_unknown(message, tempsize, newclient.sin_addr, newclient.sin_port);
                            break;
                        case 3:
                            rtn = connection_setup_unknown(message, tempsize, newclient.sin_addr, newclient.sin_port);
                            break;
                        case 250:
                            rtn = ping_serverlist(message, tempsize, &newclient, readsocket);
                            break;
                        case 251:
                            rtn = serverinfo_request(message, tempsize, &newclient, readsocket);
                            break;
                        case 252:
                            rtn = joinroutine_unknown(message, tempsize, &newclient, readsocket);
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
    }
    return 0;
}
