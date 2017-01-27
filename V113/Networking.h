#ifndef NETWORKING_H
#define NETWORKING_H

#define APR_DECLARE_STATIC
#include <iostream>
#include <string>
#include <list>
#include <apr_general.h>
#include <apr_file_io.h>
#include <apr_strings.h>
#include <apr_network_io.h>

#define BUFSIZE	516 
#define HEADER_SIZE 1
#define STANDARD_PORT 15251 

//#define HOME_IP "192.168.1.111"
#define HOME_IP "127.0.0.1"
//#define HOME_IP "25.97.249.230"
typedef enum{ACK=0x01, AGREE, DISAGREE, NAME=0x10, NAME_IS, I_AM, INITIAL_G_POS, START_INFO, YOU_START=0x20, I_START,
			 PEEK=0x30, MOVE, SPENT_OK, ADD_TOKEN, USE_TOKEN, THROW_DICE, SAFE_OPENED, CREATE_ALARM, SPY_PATROL,
			 PLACE_CROW, OFFER_LOOT, REQUEST_LOOT, PICK_UP_LOOT, PASS, ROLL_DICE_FOR_LOOT, GUARD_MOVEMENT, WE_WON,
			 WE_LOST, GAME_OVER, PLAY_AGAIN, QUIT=0xFE, ERRORR}PerezProtocolHeader;
using namespace std;
                         
string protocolHeaderToStr(PerezProtocolHeader header);

string getStrRepresentingPacket(PerezProtocolHeader header, const char *packetInfo, unsigned int packetLength);

class Networking
{
public:
	Networking();
	bool prepareToConnect(std::string &ip);
	bool tryToConnect();
	void abortConnecting();
	bool prepareToListen();
	bool listen();
	bool sendPacket(PerezProtocolHeader header, const char *packetInfo, unsigned int packetLength);
	bool recievePacket(PerezProtocolHeader *header,char *buffer, unsigned int *length);					//buffer len >= BUFSIZE!!!
	~Networking();
private:
        list<string> msgsSentNRecieved;
	apr_pool_t *memoryPool;
	apr_socket_t *auxiliarSocket;
	apr_socket_t *principalSocket;
	apr_sockaddr_t *socketAddres;
};



#endif 