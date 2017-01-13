#ifndef BURGLEBROSMODEL_H
#define BURGLEBROSMODEL_H
#include "BurgleBrosBoard.h"
#include "BurgleBrosTokens.h"
#include "BurgleBrosGuard.h"
#include "BurgleBrosLoots.h"
#include "BurgleBrosPlayer.h"
#include "BurgleBrosDices.h"
#include "Networking.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"
#include "SoundManager.h"

/*typedef enum{OTHER_PLAYER_ACTION, THIS_PLAYER_ACTION} ActionOrigin;
typedef struct{
    //bool guardMovementFinishedEv;  Este siempre es 0 a menos que se haya terminado la animacion del movimiento del guardia.
    ActionOrigin origin;
    NetworkMessage action;
}ModelEvent;*/

/*Mensajes para dialog box tienen:  TITULO             SUBTITULO        TEXTO */
#define ENTER_FINGERPRINT_TEXT    "Alert",        "Confirm Action",   "You have entered a Fingerprint tile, so you will trigger an alarm unless you use a hack token"
#define LASER_TEXT   "Alert",        "Confirm Action",   "You have entered a Laser tile, you can either spend and extra action or use a hack token to avoid triggering an alarm"
#define DEADBOLT_TEXT "Alert",  "Confirm action", "You moved to a deadbolt, in order to enter you must spend 3 actions, otherwise you will go back to your previous tile"
#define LAVATORY_TEXT "Alert",        "Confirm Action",   "You have encountered a guard! Luckily you are in the lavatory so you can choose between using one of the stealth tokens in it or one of your own"
#define MOTION_TEXT "Alert",        "Confirm Action",   "You are leaving an activated motion sensor. An alarm will be triggered unless you use a hack token"
#define USE_LAVATORY_TOKEN_TEXTB "Use Lavatory stealth token"
#define USE_MY_STEALTH_TOKEN_TEXTB "Use one of my stealth tokens"
#define SPEND_ACTIONS_TEXTB "Spend actions"
#define GET_BACK_TEXTB  "Go back"
#define SPEND_ACTION_TEXTB "Spend action"
#define USE_HACK_TOKEN_TEXTB "Use hack token"
#define TRIGGER_ALARM_TEXTB "Trigger alarm"

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
        bool pass(ActionOrigin playerId);
        bool peek(ActionOrigin playerId, CardLocation locationToPeek);
        bool move(ActionOrigin playerId, CardLocation locationToMove);
        bool addToken(ActionOrigin playerId, CardLocation locationToAddToken);
        bool crackSafe(ActionOrigin playerId, CardLocation safe);
        bool addDieToSafe(ActionOrigin playerId, CardLocation safe);
        bool createAlarm(ActionOrigin playerId, CardLocation tile);
        bool placeCrow(ActionOrigin playerId, CardLocation tile);
        bool isMovePosible(ActionOrigin playerId,CardLocation tileToMove);  //Pregunta si una movida es posible
        bool isPeekPosible(ActionOrigin player, CardLocation tile);         //Pregunta si un peek es posible
        bool isAddTokenPosible(ActionOrigin player, CardLocation tile);
        bool isAddDieToSafePossible(ActionOrigin player, CardLocation tile);
        bool isCrackSafePossible(ActionOrigin playerId, CardLocation safe);
        bool isCreateAlarmPossible(ActionOrigin playerId, CardLocation tile);
        bool isPlaceCrowPossible(ActionOrigin playerId, CardLocation tile);
        bool isPickLootPossible(ActionOrigin playerId, CardLocation tile);
        list<string> getPosibleActions(ActionOrigin player, CardLocation tile);   //Devuelve que acciones puede realizar el jugador indicado en esa tile
        void moveGuard(unsigned int floor);
        void attachView(View * view);
        void attachController(Controller * controller);
        void attachSoundManager(SoundManager * soundManager);
	~BurgleBrosModel();
    private:
        void checkTurns();
        void triggerSilentAlarm(unsigned int floor);
        bool GuardInCamera();
        void setGuardsNewPath(unsigned int floor);
        bool playerSpentFreeAction;
        BurgleBrosPlayer * getP2Player(ActionOrigin playerId);
        BurgleBrosPlayer * getP2OtherPlayer(ActionOrigin playerId);
        BurgleBrosPlayer myPlayer;
	BurgleBrosPlayer otherPlayer;
	BurgleBrosBoard board;
	BurgleBrosGuard guards[BOARD_STANDARD_FLOORS];
	BurgleBrosTokens tokens;
	BurgleBrosLoots loots;
	BurgleBrosDices dice;
        View * view;
        Controller * controller;
        SoundManager * soundManager;
};
#endif

