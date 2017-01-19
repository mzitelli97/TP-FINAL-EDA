#ifndef BURGLEBROSMODEL_H
#define BURGLEBROSMODEL_H
#include "BurgleBrosBoard.h"
#include "BurgleBrosTokens.h"
#include "BurgleBrosGuard.h"
#include "BurgleBrosLoots.h"
#include "BurgleBrosPlayer.h"
#include "BurgleBrosDices.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"
#include "SoundManager.h"

#define NUMBER_OF_PLAYERS 2
#define NO_SAFE_NUMBER -1

/*Mensajes para dialog box tienen:  TITULO                  SUBTITULO               TEXTO */
#define ENTER_FINGERPRINT_TEXT      "Alert",            "Confirm Action", "You have entered a Fingerprint tile, so you will trigger an alarm unless you use a hack token"
#define LASER_TEXT                  "Alert",            "Confirm Action", "You have entered a Laser tile, you can either spend and extra action or use a hack token to avoid triggering an alarm"
#define DEADBOLT_TEXT               "Alert",            "Confirm action", "You moved to a deadbolt, in order to enter you must spend 3 actions, otherwise you will go back to your previous tile"
#define LAVATORY_TEXT               "Alert",            "Confirm Action", "You have encountered a guard! Luckily you are in the lavatory so you can choose between using one of the stealth tokens in it or one of your own"
#define MOTION_TEXT                 "Alert",            "Confirm Action", "You are leaving an activated motion sensor. An alarm will be triggered unless you use a hack token"
#define OFFER_LOOT_TEXT             "Loot Offer",       "Confirm Offer",  "The other player offers you the loot: "
#define ASK_FOR_LOOT_TEXT           "Loot Request",     "Confirm Request","The other player ask you for the loot: "
#define SPOTTER_SPECIAL_ACTION_TEXT "Spotter guard peek", "Complete action", "You have spotted the top of the guard deck. Would you like to let it on the top or put it at the bottom?"
/*Botones de los dialog box:*/
#define ACCEPT_TEXTB "Accept"
#define DECLINE_TEXTB "Decline"
#define USE_LAVATORY_TOKEN_TEXTB "Use Lavatory stealth token"
#define USE_MY_STEALTH_TOKEN_TEXTB "Use one of my stealth tokens"
#define SPEND_ACTIONS_TEXTB "Spend actions"
#define GET_BACK_TEXTB  "Go back"
#define SPEND_ACTION_TEXTB "Spend action"
#define USE_HACK_TOKEN_TEXTB "Use hack token"
#define TRIGGER_ALARM_TEXTB "Trigger alarm"
#define SPOTTER_TOP         "Top"
#define SPOTTER_BOTTOM      "Bottom"

class BurgleBrosModel : public Model
{
    public:
	BurgleBrosModel();
        PlayerId getPlayerOnTurn();
        bool hasGameFinished();
        string getFinishMsg();
        /* Funciones para inicializar al modelo.*/
        void initBoard(vector<CardName> &allTiles);     //Dado un vector de cardNames: Si está vacío, se genera el board y se le pasa toda la información, si tiene 48 cartas, se copian las cartas, sino genera un error.
        void initPlayer(PlayerId playerId, string playerName, CharacterName playerCharacter, CardLocation playerPos);   
        void setInitTurn(PlayerId playerId);
        void copyGuardInitPos(CardLocation guardPos, CardLocation guardDiePos);
        void generateGuardInitPos(CardLocation *guardPos, CardLocation *guardDiePos);
        /* Funciones para obtener información para dibujar. */
        vector<wall> getInfo2DrawWalls();
	vector<Info2DrawCards> getInfo2DrawCards();
        list<Info2DrawLoot> getInfo2DrawLoot();
	Info2DrawPlayer getInfo2DrawPlayer(PlayerId player);
        Info2DrawGuard getInfo2DrawGuard(unsigned int floor);
	list<Info2DrawTokens> getInfo2DrawTokens();
        vector<unsigned int> getInfo2DrawExtraDices();
        /* Acciones que se puede llamar públicamente*/
        void pass(PlayerId playerId);
        unsigned int peek(PlayerId playerId, CardLocation locationToPeek,int safeNumber); //Recibe que jugador a que tile va a mirar, y si se sabe de antemano el número de safe, se lo asigna a la carta que estaba dada vuelta. devuelve el numero de safe de esa carta.
        unsigned int move(PlayerId playerId, CardLocation locationToMove, int safeNumber); //Si es del otro jugador, recibe el safeNumber desde afuera, devuelve el safe number de la carta a la que se mueve.
        void addToken(PlayerId playerId, CardLocation locationToAddToken);
        void crackSafe(PlayerId playerId, CardLocation safe);
        void addDieToSafe(PlayerId playerId, CardLocation safe);
        void createAlarm(PlayerId playerId, CardLocation tile);
        void placeCrow(PlayerId playerId, CardLocation tile);
        void pickLoot(PlayerId playerId, CardLocation tile, Loot loot);
        void askForLoot(PlayerId playerId, CardLocation tile, Loot loot);
        void offerLoot(PlayerId playerId, CardLocation tile, Loot loot);
        void escape(PlayerId playerId, CardLocation stairTile);
        void peekGuardsCard(PlayerId playerId, unsigned int guardsFloor);
        /*Prueba para ver si se pueden realizar ciertas acciones*/
        bool isMovePosible(PlayerId playerId,CardLocation tileToMove);  //Pregunta si una movida es posible
        bool isPeekPosible(PlayerId player, CardLocation tile);         //Pregunta si un peek es posible
        bool isAddTokenPosible(PlayerId player, CardLocation tile);
        bool isAddDieToSafePossible(PlayerId player, CardLocation tile);
        bool isCrackSafePossible(PlayerId playerId, CardLocation safe);
        bool isCreateAlarmPossible(PlayerId playerId, CardLocation tile);
        bool isPlaceCrowPossible(PlayerId playerId, CardLocation tile);
        bool isPickLootPossible(PlayerId playerId, CardLocation tile, Loot loot);
        bool isAskForLootPossible(PlayerId playerId, CardLocation tile, Loot loot);
        bool isOfferLootPossible(PlayerId playerId, CardLocation tile, Loot loot);
        bool isEscapePossible(PlayerId playerId, CardLocation tile);
        bool isPeekGuardsCardPossible(PlayerId playerId, unsigned int guardsFloor);
        list<string> getPosibleActionsToTile(PlayerId player, CardLocation tile);   //Devuelve que acciones puede realizar el jugador indicado en esa tile
        list<string> getPosibleActionsToGuard(PlayerId player, unsigned int guardsFloor); 
        void moveGuard(unsigned int floor);
        void attachView(View * view);
        void attachController(Controller * controller);
        void attachSoundManager(SoundManager * soundManager);
	~BurgleBrosModel();
    private:
        void checkTurns();
        void checkIfWonOrLost();
        void handlePersianKittyMove(PlayerId playerId);
        void handleChihuahuaMove(PlayerId playerId);
        void triggerSilentAlarm(unsigned int floor);
        bool GuardInCamera();
        void setGuardsNewPath(unsigned int floor);
        bool playerSpentFreeAction;
        BurgleBrosPlayer * getP2Player(PlayerId playerId);
        BurgleBrosPlayer * getP2OtherPlayer(PlayerId playerId);
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
        bool gameFinished;
        string finishMsg;       //Si el juego terminó indica como termino (por ejemplo WON, LOST o MODEL ERROR:"(errormsg)"
};
#endif

