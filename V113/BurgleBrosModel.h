#ifndef BURGLEBROSMODEL_H
#define BURGLEBROSMODEL_H
#include "BurgleBrosBoard.h"
#include "BurgleBrosTokens.h"
#include "BurgleBrosGuard.h"
#include "BurgleBrosLoots.h"
#include "BurgleBrosPlayer.h"
#include "Networking.h"
//#include "Rule.h"
//#include "RuleManager.h"

/*typedef enum{OTHER_PLAYER_ACTION, THIS_PLAYER_ACTION} ActionOrigin;
typedef struct{
    //bool guardMovementFinishedEv;  Este siempre es 0 a menos que se haya terminado la animacion del movimiento del guardia.
    ActionOrigin origin;
    NetworkMessage action;
}ModelEvent;*/
#define MAX_NMBR_OF_EXTRA_DICES 6





class BurgleBrosModel
{
    public:
	BurgleBrosModel();
	vector<Info2DrawCards> getInfo2DrawCards();
        list<Info2DrawLoot> getInfo2DrawLoot();
	Info2DrawPlayer getInfo2DrawPlayer(ActionOrigin player);
        Info2DrawGuard getInfo2DrawGuard(unsigned int floor);
	list<Info2DrawTokens> getInfo2DrawTokens();
        vector<unsigned int> getInfo2DrawExtraDices();
        bool peek(BurgleBrosPlayer * PlayerEnTurno, CardLocation aux);
        bool isMovePosible(ActionOrigin playerId,CardLocation tileToMove);
        bool isPeekPosible(ActionOrigin player, CardLocation tile);
        vector<string> getPosibleActions(ActionOrigin player, CardLocation tile);
        //void attachController(Controller * controller);
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
        //View * view;
};
#endif

