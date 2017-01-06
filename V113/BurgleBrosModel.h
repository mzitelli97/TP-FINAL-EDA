#ifndef BURGLEBROSMODEL_H
#define BURGLEBROSMODEL_H
#include "BurgleBrosBoard.h"
#include "BurgleBrosTokens.h"
#include "BurgleBrosGuard.h"
#include "BurgleBrosLoots.h"
#include "BurgleBrosPlayer.h"
#include "Networking.h"
#include "Model.h"
#include "View.h"

/*typedef enum{OTHER_PLAYER_ACTION, THIS_PLAYER_ACTION} ActionOrigin;
typedef struct{
    //bool guardMovementFinishedEv;  Este siempre es 0 a menos que se haya terminado la animacion del movimiento del guardia.
    ActionOrigin origin;
    NetworkMessage action;
}ModelEvent;*/
#define MAX_NMBR_OF_EXTRA_DICES 6




class BurgleBrosModel : public Model
{
    public:
	BurgleBrosModel();
	vector<Info2DrawCards> getInfo2DrawCards();
        list<Info2DrawLoot> getInfo2DrawLoot();
	Info2DrawPlayer getInfo2DrawPlayer(ActionOrigin player);
        Info2DrawGuard getInfo2DrawGuard(unsigned int floor);
	list<Info2DrawTokens> getInfo2DrawTokens();
        vector<unsigned int> getInfo2DrawExtraDices();
        bool peek(ActionOrigin playerId, CardLocation locationToPeek);
        bool move(ActionOrigin playerId, CardLocation locationToMove);
        bool isMovePosible(ActionOrigin playerId,CardLocation tileToMove);  //Pregunta si una movida es posible
        bool isPeekPosible(ActionOrigin player, CardLocation tile);         //Pregunta si un peek es posible
        list<string> getPosibleActions(ActionOrigin player, CardLocation tile);   //Devuelve que acciones puede realizar el jugador indicado en esa tile
        void moveGuard(unsigned int floor);
        //void attachController(Controller * controller);
        void attachView(View * view);
	~BurgleBrosModel();
    private:
	//RuleManager ruleManager;
        void checkTurns();
        void setGuardsNewPath(unsigned int floor);
        BurgleBrosPlayer * getP2Player(ActionOrigin playerId);
        BurgleBrosPlayer * getP2OtherPlayer(ActionOrigin playerId);
        BurgleBrosPlayer myPlayer;
	BurgleBrosPlayer otherPlayer;
	BurgleBrosBoard board;
	BurgleBrosGuard guards[BOARD_STANDARD_FLOORS];
	BurgleBrosTokens tokens;
	BurgleBrosLoots loots;
	unsigned int extraDices[MAX_NMBR_OF_EXTRA_DICES];
        //Controller * controller;
        View * view;
};
#endif

