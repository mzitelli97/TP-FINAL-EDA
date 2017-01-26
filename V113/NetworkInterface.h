#ifndef NETWORKINGINTERFACE_H
#define NETWORKINGINTERFACE_H
#include <time.h>
#include <stdlib.h>
#include "Networking.h"
#include "ProtocolFunctions.h"
#include "BurgleBrosModel.h"

#define MIN_WAITING_TIME 0.2 
#define MAX_WAITING_TIME 10.0

typedef enum {CLIENT, SERVER} CommunicationRole;
typedef struct
{
    PerezProtocolHeader header;
    std::string message;
}NetworkMessage;
using namespace std;

bool packetHasNoDataField(PerezProtocolHeader header); //Devuelve si el header no requiere ningún dato extra, por ejemplo ack

class NetworkInterface
{
public:
	NetworkInterface(Networking &networking);
        NetworkInterface();
        //IMPORTANTE PONER EL RANDOM SEED EN EL MAIN.
	/*Intenta conectarse con un server, y despues con un tiempo random entre las 2 macros definidas arriba
	se vuelve en servidor y espera que alguien se conecte. Es no bloqueante, devuelve 1 si se pudo establecer una conexion (se tiene que llamar
	a getcomunicationrole para saber si quedo como server o como cliente.*/
	bool standardConnectionStart(std::string &ip);	
	/*Devuelve si se conect� como server o cliente */
	CommunicationRole getCommunicationRole();
	bool recievePacket(PerezProtocolHeader *header, unsigned char * msg, unsigned int *len);
        bool sendPacket(PerezProtocolHeader header);    //Para los que no mandan datos.
        bool sendName(string name);         //El largo del nombre debe ser menor que bufsize - 1
        bool sendChar(CharacterName characterName);
        bool sendInitGPos(CardLocation guardPos, CardLocation guardDiePos);
        bool sendStartInfo(vector<CardName> &tiles, CardLocation &initTile);
        bool sendPeek(CardLocation tileToPeek, unsigned int safeNumber);
        bool sendMove(CardLocation tileToPeek, unsigned int safeNumber);
        bool sendDice(vector<unsigned int> &dice);
        bool sendUseToken(CardLocation location);
        bool sendAddToken(CardLocation location);
        bool sendSpent(bool YesOrNo);       //Yes == true, no == false;
        bool sendGMove(list<GuardMoveInfo> guardMovement);
	bool sendPlaceCrow(CardLocation location);
        bool sendCreateAlarm(CardLocation location);
        bool sendSafeOpened(Loot loot);
        bool sendRequestLoot(Loot i);
        bool sendOfferLoot(Loot i);
        bool sendPickUpLoot(Loot loot);
        bool sendRollDiceForLoot(unsigned int die);
        bool sendSpyPatrol(CardLocation topOfNotShown,string userChoice);
	~NetworkInterface();
private:
	double timeToBecomeServer;
        bool error;
        string errorMsg;
	clock_t prevClock;
	clock_t currClock;
	bool  firstTimeCalled;
	CommunicationRole currentRole;
	Networking *p2networking;
};



#endif 
