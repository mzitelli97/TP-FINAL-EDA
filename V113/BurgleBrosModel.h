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
#include "Controller.h"

/*typedef enum{OTHER_PLAYER_ACTION, THIS_PLAYER_ACTION} ActionOrigin;
typedef struct{
    //bool guardMovementFinishedEv;  Este siempre es 0 a menos que se haya terminado la animacion del movimiento del guardia.
    ActionOrigin origin;
    NetworkMessage action;
}ModelEvent;*/
#define MAX_NMBR_OF_EXTRA_DICES 6
/*Mensajes para dialog box tienen:  TITULO             SUBTITULO        TEXTO */
#define ENTER_FINGERPRINT_TEXT  ({  "Alert",        "Confirm Action",   "You have entered a Fingerprint tile, so you will trigger an alarm unless you use a hack token. Use token?"})
#define ENTER_LASER_ACTION_TEXT ({  "Alert",        "Confirm Action",   "You have entered a Laser tile, so you can spend and extra action to avoid triggering an alarm. Spend another action?"})
#define ENTER_LASER_TOKEN_TEXT  ({  "Alert",        "Confirm Action",   "You have entered a Laser tile, so you can use a hack token to avoid triggering an alarm. Use token?"})


class BurgleBrosModel : public Model
{
    public:
	BurgleBrosModel();
        vector<wall> getInfo2DrawWalls();
	vector<Info2DrawCards> getInfo2DrawCards();
        list<Info2DrawLoot> getInfo2DrawLoot();
	Info2DrawPlayer getInfo2DrawPlayer(ActionOrigin player);
        Info2DrawGuard getInfo2DrawGuard(unsigned int floor);
	list<Info2DrawTokens> getInfo2DrawTokens();
        vector<unsigned int> getInfo2DrawExtraDices();
        ActionOrigin getPlayerOnTurn();
        bool peek(ActionOrigin playerId, CardLocation locationToPeek);
        bool move(ActionOrigin playerId, CardLocation locationToMove);
        bool isMovePosible(ActionOrigin playerId,CardLocation tileToMove);  //Pregunta si una movida es posible
        bool isPeekPosible(ActionOrigin player, CardLocation tile);         //Pregunta si un peek es posible
        list<string> getPosibleActions(ActionOrigin player, CardLocation tile);   //Devuelve que acciones puede realizar el jugador indicado en esa tile
        void moveGuard(unsigned int floor);
        void attachView(View * view);
        void attachController(Controller * controller);
	~BurgleBrosModel();
    private:
        void checkTurns();
        bool GuardInCamera();
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
        View * view;
        Controller * controller;
};
#endif

