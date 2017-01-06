#include "Networking.h"

#define DEF_SOCK_TIMEOUT (APR_USEC_PER_SEC * 5) //TIMEOUT (ver m�s adelante).


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
			retVal = true;
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
	}
	return retVal;
}



Networking::~Networking()
{
	apr_socket_shutdown(principalSocket, APR_SHUTDOWN_READWRITE);
	apr_socket_close(principalSocket);
	apr_terminate();
}
