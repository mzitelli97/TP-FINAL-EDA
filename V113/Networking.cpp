#include "Networking.h"
#include "BurgleBrosModel.h"
#include <cctype>

#define DEF_SOCK_TIMEOUT (APR_USEC_PER_SEC * 5) //TIMEOUT (ver m�s adelante).


string protocolHeaderToStr(PerezProtocolHeader header)
{
    string retVal;
    switch(header)
    {
        case ACK: retVal="Ack";break;
        case AGREE:retVal="Agree";break;
        case DISAGREE:retVal="Disagree";break;
        case NAME:retVal="Name";break;
        case NAME_IS:retVal="Name is";break;
        case I_AM:retVal="I am";break;
        case INITIAL_G_POS:retVal="Initial g pos";break;
        case START_INFO:retVal="Start info";break;
        case YOU_START:retVal="You start";break;
        case I_START:retVal="I start";break;
        case PEEK:retVal="Peek";break;
        case MOVE:retVal="Move";break;
        case SPENT_OK:retVal="Spent OK";break;
        case ADD_TOKEN:retVal="Add token";break;
        case USE_TOKEN:retVal="Use token";break;
        case THROW_DICE:retVal="Throw dice";break;
        case SAFE_OPENED:retVal="Safe Opened";break;
        case CREATE_ALARM:retVal="Create alarm";break;
        case SPY_PATROL:retVal="Spy Patrol";break;
        case PLACE_CROW:retVal="Place Crow";break;
        case OFFER_LOOT:retVal="Offer Loot";break;
        case REQUEST_LOOT:retVal="Request Loot";break;
        case PICK_UP_LOOT:retVal="Pick up Loot";break;
        case PASS:retVal="Pass";break;
        case ROLL_DICE_FOR_LOOT:retVal="Roll dice for loot";break;
        case GUARD_MOVEMENT:retVal="Guard movement";break;
        case WE_WON:retVal="We won";break;
        case WE_LOST:retVal="We lost";break;
        case GAME_OVER:retVal="Game over";break;
        case QUIT:retVal="Quit";break;
        case ERRORR:retVal="Error";break;
        default: retVal="Unknown header";break;
    }
    return retVal;
}

string getStrRepresentingPacket(PerezProtocolHeader header, const char *packetInfo, unsigned int packetLength)
{
    string retVal= "Header: " + protocolHeaderToStr(header);
    char buffer[BUFSIZE];
    unsigned int i,j; //J indice para el buffer auxiliar
    for(i=0,j=0; i<packetLength;i++,j++)
    {
        if(isalnum(packetInfo[i]))
            buffer[j]= packetInfo[i];
        else
        {
            sprintf(&(buffer[j]), "(0x%X)",(unsigned int)packetInfo[i]);    //Si no es algo imprimible, pone el valor en hexa entre parentesis.
            while(buffer[j+1]!='\0')        //Avanzo i hasta llegar al ), luego el for lo incrementa en 1
                j++;
        }
    }
    buffer[j+1]='\0'; // Le pongo terminador para que sea string.
    retVal+= " Packet: ";
    retVal+= buffer;       
    
    return retVal;
}


Networking::Networking()
{
	apr_initialize();
	apr_pool_create(&memoryPool, NULL);
	auxiliarSocket = NULL;
	principalSocket = NULL;
}

bool Networking::prepareToConnect(std::string &ip)
{
	bool retVal = false;
	apr_status_t rv;
	apr_pool_create(&memoryPool, NULL);
	rv = apr_sockaddr_info_get(&socketAddres, ip.c_str() , APR_INET, STANDARD_PORT, 0, memoryPool);
	if (rv == APR_SUCCESS)
	{
		rv = apr_socket_create(&principalSocket, APR_INET, SOCK_STREAM, APR_PROTO_TCP, memoryPool); //cambiar UNSPEC por APR_INET
		if (rv == APR_SUCCESS)
		{
			apr_socket_opt_set(principalSocket, APR_SO_NONBLOCK, 1);
			apr_socket_timeout_set(principalSocket, DEF_SOCK_TIMEOUT);
			retVal = true;
			
		}
		else
			printf("\nCANNOT CREATE SOCKET TO CONNECT");
	}
	else
		printf("\nCANNOT GET SERVER INFO\n");
	return retVal;
}
bool Networking::tryToConnect()
{
	bool retVal=false;
	apr_status_t rv;
	rv = apr_socket_connect(principalSocket, socketAddres);
	if (rv == APR_SUCCESS)
	{
		apr_socket_opt_set(principalSocket, APR_SO_NONBLOCK, 1);
		apr_socket_timeout_set(principalSocket, 0);
		retVal = true;
	}
	return retVal;
}
void Networking::abortConnecting()
{
	apr_socket_shutdown(principalSocket, APR_SHUTDOWN_READWRITE);
	apr_socket_close(principalSocket);
	principalSocket = NULL;
}


bool Networking::prepareToListen()
{
	bool retVal = false;
	apr_status_t rv;
	apr_socket_t *news;
	rv = apr_sockaddr_info_get(&socketAddres, HOME_IP, APR_INET, STANDARD_PORT, 0, memoryPool);
	if (rv == APR_SUCCESS)
	{
		rv = apr_socket_create(&news, APR_INET, SOCK_STREAM, APR_PROTO_TCP, memoryPool);
		if (rv == APR_SUCCESS)
		{
			apr_socket_opt_set(news, APR_SO_NONBLOCK, 1);
			apr_socket_timeout_set(news, 0);
			apr_socket_opt_set(news, APR_SO_REUSEADDR, 1);
			rv = apr_socket_bind(news, socketAddres);
			if (rv == APR_SUCCESS)
			{
				rv = apr_socket_listen(news, SOMAXCONN);
				if (rv == APR_SUCCESS)
				{
					auxiliarSocket = news;
					retVal = true;
				}
				else
					printf("\nNOT LISTENING");
			}
			else
				printf("\nfailed to bind socket");

		}
		else
			printf("\ncannot create socket");

	}
	else
		printf("\ncannot get info?");

	return retVal;
}
bool Networking::listen()
{
	bool retVal=false;
	apr_socket_accept(&principalSocket, auxiliarSocket, memoryPool);
	if (principalSocket != NULL)
	{
		apr_socket_shutdown(auxiliarSocket, APR_SHUTDOWN_READWRITE);
		apr_socket_opt_set(principalSocket, APR_SO_NONBLOCK, 1);
		apr_socket_timeout_set(principalSocket, 0);
		retVal = true;
	}
	return retVal;
}
bool Networking::sendPacket(PerezProtocolHeader header, const char *packetInfo, unsigned int packetLength)
{
	bool retVal = false;
	if (packetLength < (BUFSIZE - HEADER_SIZE))
	{
		unsigned char buffer[BUFSIZE];
		apr_size_t totalSize = packetLength + HEADER_SIZE;	
		apr_status_t rv;
		buffer[0] = header;
		if (packetLength != 0)
			memcpy(&(buffer[1]), packetInfo, packetLength);
		rv = apr_socket_send(principalSocket, (const char *)buffer, &totalSize);
		if (rv == APR_SUCCESS)
		{
                    retVal = true;
                    string aux= "Sent-> " + getStrRepresentingPacket(header,packetInfo, packetLength) + "\n";
                    cout << aux;
                    msgsSentNRecieved.push_back(aux);
                }
	}
	return retVal;
}
bool Networking::recievePacket(PerezProtocolHeader *header, char *buffer, unsigned int *length)
{
	apr_size_t totalSize = BUFSIZE;
	bool retVal = false;
	unsigned char auxBuffer[BUFSIZE];
	apr_status_t rv;
	rv = apr_socket_recv(principalSocket,(char *) auxBuffer, &totalSize);	//Recieves the paquet and saves the length recieved.
	if (APR_STATUS_IS_EOF(rv) || (totalSize == 0))
		retVal = false;
	else
	{
		*header = (PerezProtocolHeader)auxBuffer[0];
		*length = totalSize - HEADER_SIZE;
		if (*length != 0)
			memcpy(buffer, (&(auxBuffer[1])), *length);
		retVal = true;
                string aux= "Recieved <- " + getStrRepresentingPacket(*header,buffer, *length) + "\n";
                cout << aux;
                msgsSentNRecieved.push_back(aux);
	}
	return retVal;
}



Networking::~Networking()
{
	apr_socket_shutdown(principalSocket, APR_SHUTDOWN_READWRITE);
	apr_socket_close(principalSocket);
	apr_terminate();
}


