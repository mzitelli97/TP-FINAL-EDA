#ifndef NETWORKINGINTERFACE_H
#define NETWORKINGINTERFACE_H
#include <time.h>
#include <stdlib.h>
#include "Networking.h"
#include "StrNmbrFieldToArray.h"

#define MIN_WAITING_TIME 0.2 
#define MAX_WAITING_TIME 10.0

typedef enum {CLIENT, SERVER} CommunicationRole;
typedef struct
{
    PerezProtocolHeader header;
    std::string message;
}NetworkMessage;


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
	/*Recibe un paquete del protocolo establecido, pasando el mensaje a un formato de string. Los unicos dos mensajes que van a ser distintos son
	Guard movement y Name Is, ya que pueden tener caracteres con los que no opera string. Por ejemplo si llega : 5ARIEL (nameis) esta funcion devuelve
	un string con "ARIEL". si llega A2F2(0xFF)A4F2(0xFF)(GUARD_MOV) devuelve A2F2,A4F2,*/
	bool recievePacket(PerezProtocolHeader *headerRecieved, std::string *messageRecieved);
	/*Adapta el mensaje en string al protocolo y lo env�a, as� se puede trabajar con strings todos los mensajes.*/
	bool sendPacket(PerezProtocolHeader header, std::string message);
	~NetworkInterface();
private:
	double timeToBecomeServer;
	clock_t prevClock;
	clock_t currClock;
	bool  firstTimeCalled;
	CommunicationRole currentRole;
	Networking *p2networking;
};



#endif 