#include "BurgleBrosModel.h"
#include "BurgleBrosView.h"
#include "Networking.h"
#include <unistd.h>
#include <vector>
#include <algorithm>

#define KEYPAD_CRACK_NUMBER 6
typedef struct
{
    CardLocation target;
    unsigned int length;
}AuxStruct;
bool sortAuxStruct(AuxStruct &item1, AuxStruct &item2)
{
    return item1.length<item2.length;
}
BurgleBrosModel::BurgleBrosModel()
{
    BurgleBrosGuard aux1(0);
    BurgleBrosGuard aux2(1);
    BurgleBrosGuard aux3(2);
    guards[0]= aux1;
    guards[1]= aux2;
    guards[2]= aux3;
    board.initBoard();
    gameFinished=false;
    playerSpentFreeAction=false;
    status=WAITING_FOR_ACTION;
    guardFinishedMoving=false;
    rollForLootCount=0;
    specialMotionCase=false;
}
void BurgleBrosModel::reset()
{
    BurgleBrosGuard aux1(0);
    BurgleBrosGuard aux2(1);
    BurgleBrosGuard aux3(2);
    BurgleBrosBoard auxBoard;
    BurgleBrosLoots auxLoots;
    BurgleBrosTokens auxTokens;
    BurgleBrosDices auxDice;
    BurgleBrosPlayer auxPlayer;
    guards[0]= aux1;
    guards[1]= aux2;
    guards[2]= aux3;
    board=auxBoard;
    board.initBoard();
    loots=auxLoots;
    tokens=auxTokens;
    dice=auxDice;
    auxPlayer.setName(myPlayer.getName());
    myPlayer=auxPlayer;
    auxPlayer.setName(otherPlayer.getName());
    otherPlayer=auxPlayer;
    gameFinished=false;
    playerSpentFreeAction=false;
    status=WAITING_FOR_ACTION;
    guardFinishedMoving=false;
    rollForLootCount=0;
    specialMotionCase=false;
    finishMsg.clear();
    auxMsgsToShow.clear();
}

void BurgleBrosModel::attachView(View * view)
{
    this->view = view;
}
void BurgleBrosModel::attachController(Controller * controller)
{
    this->controller = controller;
}
void BurgleBrosModel::attachSoundManager(SoundManager * soundManager)
{
    this->soundManager=soundManager;
}
bool BurgleBrosModel::moveRequiresToInitGuard(CardLocation locationToMove)
{
    return !guards[locationToMove.floor].checkIfInitialized();
}
pair<bool,CardLocation> BurgleBrosModel::getGoldBarInfo()
{
    return loots.getGoldBarOnFloor();
}

void BurgleBrosModel::initBoard(vector<CardName> &allTiles)
{
    if(allTiles.empty())
    {
        board.initBoard();
        CardLocation aux;
        for(aux.floor=0;aux.floor<BOARD_STANDARD_FLOORS; aux.floor++ )
        {
            for(aux.row=0;aux.row<FLOOR_RAWS; aux.row++ )
            {
                for(aux.column=0;aux.column<FLOOR_COLUMNS; aux.column++ )
                {
                    allTiles.push_back(board.getCardType(aux));
                }
            }
        }
    }
    else if(allTiles.size()== BOARD_STANDARD_FLOORS * FLOOR_COLUMNS * FLOOR_RAWS)
        board.initBoard(allTiles);
    else
    {
        gameFinished=true;
        finishMsg= "ERROR: BBModel error: Tried to initialize board with an incorrect number of tiles!";
    }
}
void BurgleBrosModel::initPlayer(PlayerId playerId, string playerName, CharacterName playerCharacter, CardLocation playerPos)
{
    BurgleBrosPlayer *p = getP2Player(playerId);
    p->setName(playerName);
    p->setPosition(playerPos);
    //board.setCardVisible(playerPos);
    p->setCharacter(playerCharacter);
    if(!tokens.isThereADownstairToken(playerPos))
        tokens.placeDownstairToken(playerPos);
}
void BurgleBrosModel::setInitTurn(PlayerId playerId)
{
    getP2Player(playerId)->setTurn(true);
}
void BurgleBrosModel::copyGuardInitPos(CardLocation guardPos, CardLocation guardDiePos)
{
    unsigned int i;
    for(i=0; i<BOARD_STANDARD_FLOORS; i++)
    {    
        if(i==BOARD_STANDARD_FLOORS-1 && guards[i].checkIfInitialized())        //Si se llamo a esta función ya habiendo incializado los 3 guardias se cierra el modelo.
            this->gameFinished=true;
        if(!guards[i].checkIfInitialized())     //Si no está inicializado, a ese guardia se va a inicializar.
            break;
    }
    guards[i].init(guardPos, guardDiePos);
    list<CardLocation> path = board.getShortestPath(guardPos, guardDiePos);
    guards[i].setNewPathToTarget(path);
}
void BurgleBrosModel::generateGuardInitPos(CardLocation *guardPos, CardLocation *guardDiePos)
{
    unsigned int i;
    for(i=0; i<BOARD_STANDARD_FLOORS; i++)
    {    
        if(i==BOARD_STANDARD_FLOORS-1 && guards[i].checkIfInitialized())        //Si se llamo a esta función ya habiendo incializado los 3 guardias se cierra el modelo.
            this->gameFinished=true;
        if(!guards[i].checkIfInitialized())     //Si no está inicializado, a ese guardia se va a inicializar.
            break;
    }
    guards[i].init();
    *guardPos = guards[i].getPosition();
    *guardDiePos = guards[i].getTargetPosition();
    list<CardLocation> path = board.getShortestPath(*guardPos, *guardDiePos);
    guards[i].setNewPathToTarget(path);
}
vector<wall> BurgleBrosModel::getInfo2DrawWalls()
{
    vector<wall> aux;
    aux.reserve(BOARD_STANDARD_FLOORS * NUMBER_OF_WALLS);
    board.getWalls(aux);
    return aux;
}
vector<Info2DrawCards> BurgleBrosModel::getInfo2DrawCards()
{
    vector<Info2DrawCards> retVal;
    retVal.reserve(BOARD_STANDARD_FLOORS * FLOOR_RAWS * FLOOR_COLUMNS);
    CardLocation aux;
    for(aux.floor=0; aux.floor < BOARD_STANDARD_FLOORS; aux.floor++)
    {
        for(aux.row=0; aux.row < FLOOR_RAWS; aux.row++)
        {
            for(aux.column=0; aux.column < FLOOR_COLUMNS; aux.column++)
            {
                Info2DrawCards toPush;
                toPush.isVisible = board.isCardVisible(aux);
                toPush.location = aux;
                toPush.safeNumber = board.getCardSafeNumber(aux);
                toPush.type = board.getCardType(aux);
                retVal.push_back(toPush);
            }
        }
    }
    return retVal;
}
list<Info2DrawTokens> BurgleBrosModel::getInfo2DrawTokens()
{
    list<Info2DrawTokens> retVal;
    list<CardLocation> auxList = tokens.getAlarmsList();
    vector<CardLocation> downstairsTokens = tokens.getDownstairs();
    unsigned int aux= tokens.howManyTokensOnCPURoom((CardName)COMPUTER_ROOM_FINGERPRINT);
    unsigned int  i,j;
    Info2DrawTokens toPush;
    
    if(tokens.getCrowToken().first)
    {    
        toPush.token=CROW_TOKEN;
        toPush.position=tokens.getCrowToken().second;
        retVal.push_back(toPush);
    }
    pair<bool, CardLocation> auxiliar= tokens.getPersianKittyToken();
    if(auxiliar.first)
    {
        toPush.token=PERSIAN_KITTY_TOKEN;
        toPush.position=auxiliar.second;
        retVal.push_back(toPush);
    }
    toPush.token=DOWNSTAIRS_TOKEN;
    for(vector<CardLocation>::iterator it=downstairsTokens.begin(); it!=downstairsTokens.end(); it++)
    {
        toPush.position=*it;
        retVal.push_back(toPush);
    }
    
    toPush.token=ALARM_TOKEN;
    for(list<CardLocation>::iterator it=auxList.begin(); it!=auxList.end(); it++)
    {
        toPush.position=*it;
        retVal.push_back(toPush);
    }
    
    auxList = tokens.getCrackedCards();
    toPush.token= SAFE_TOKEN;
    for(list<CardLocation>::iterator it=auxList.begin(); it!=auxList.end(); it++)
    {
        toPush.position=*it;
        retVal.push_back(toPush);
    }
    pair<CardLocation, unsigned int> temp = tokens.getStealthTokensOnFloor();
    for(unsigned int i=0; i < temp.second; i++)
    {
        toPush.position=temp.first;
        toPush.token= STEALTH_TOKEN;
        retVal.push_back(toPush);
    }
    
    //keypad tokens
    auxList= tokens.getKeypadTokens();
    toPush.token= KEYPAD_TOKEN;
    for(list<CardLocation>::iterator it=auxList.begin(); it!=auxList.end(); ++it)    
    {
        toPush.position=*it;
        retVal.push_back(toPush);
    }

    
    for(i=0; i < aux; i++)
    {
        toPush.position = board.getComputerRoomLocation(COMPUTER_ROOM_FINGERPRINT);
        toPush.token= HACK_TOKEN;
        retVal.push_back(toPush);
    }
    aux= tokens.howManyTokensOnCPURoom(COMPUTER_ROOM_LASER);
    for(i= 0; i <  aux; i++)
    {
        toPush.position= board.getComputerRoomLocation(COMPUTER_ROOM_LASER);
        toPush.token= HACK_TOKEN;
        retVal.push_back(toPush);
    }
    aux= tokens.howManyTokensOnCPURoom(COMPUTER_ROOM_MOTION);
    for(i= 0; i <  aux; i++)
    {
        toPush.position= board.getComputerRoomLocation(COMPUTER_ROOM_MOTION);
        toPush.token= HACK_TOKEN;
        retVal.push_back(toPush);
    }
    return retVal;
}
list<Info2DrawLoot> BurgleBrosModel::getInfo2DrawLoot()
{
    list<Info2DrawLoot> retVal;
    unsigned int aux= loots.getCurrentLoots();
    for(unsigned int i =0; i< aux; i++)
    {
        Info2DrawLoot loot = loots.getLootInfo(i);
        retVal.push_back(loot);
    }
    return retVal;
}

Info2DrawGuard BurgleBrosModel::getInfo2DrawGuard(unsigned int floor)
{
    Info2DrawGuard info;//CONTROLAR ERROR
    if(floor<=2)
    { 
        info.dieNumber=guards[floor].getDiceNumber();
        info.diePosition=guards[floor].getTargetPosition();
        info.position=guards[floor].getPosition();
        info.shownDeck=guards[floor].getShownDeck();
        info.initialized=guards[floor].checkIfInitialized();
        info.isTopOfNotShownDeckVisible=guards[floor].isTopOfNotShownDeckVisible();
        info.topOfNotShownDeck=guards[floor].getTopCard();
    }
    return info;
}
Info2DrawPlayer BurgleBrosModel:: getInfo2DrawPlayer(PlayerId player)
{
    Info2DrawPlayer info;
    BurgleBrosPlayer * p = getP2Player(player);
    info.name=p->getName();
    info.character=p->getCharacter();
    info.lives=p->getCurrLifes();
    info.position=p->getPosition();
    info.currActions=p->getcurrentActions();
    info.turn = p->isItsTurn();
    info.isOnHelicopter = p->isOnHelicopter();
    return info;
}


vector<unsigned int> BurgleBrosModel::getInfo2DrawExtraDices()
{
    return dice.getCurrDice();
}

PlayerId BurgleBrosModel::getPlayerOnTurn()
{
    if(myPlayer.isItsTurn())
        return THIS_PLAYER;
    else if(otherPlayer.isItsTurn())
        return OTHER_PLAYER;
    else
        return NON_PLAYER;
}
bool BurgleBrosModel::isGuardsTurn()
{
    return (getPlayerOnTurn()==NON_PLAYER);
}

bool BurgleBrosModel::hasGameFinished()
{
    return gameFinished;
}
string BurgleBrosModel::getFinishMsg()
{
    return finishMsg;
}
CardLocation BurgleBrosModel::locationOfComputerRoomOrLavatory(CardName computerRoomOrLavatory)
{
    if(computerRoomOrLavatory == LAVATORY)
        return board.getLavatoryLocation();
    else
        return board.getComputerRoomLocation(computerRoomOrLavatory);
}
ModelStatus BurgleBrosModel::getModelStatus()
{
    return status;
}
vector<string> BurgleBrosModel::getMsgToShow()
{
    return msgsToShow;
}
bool BurgleBrosModel::userDecidedTo(string userChoice)
{   /*Esta funcion se encarga de procesar la elección del usuario a entrar a tiles especiales, del de este jugador y del otro jugador.*/
    bool guardHasToMove=false;
    BurgleBrosPlayer * movingPlayer= getP2Player(getPlayerOnTurn()); 
    vector<string> fingerPrint({ENTER_FINGERPRINT_TEXT});
    vector<string> lavatory({LAVATORY_TEXT});
    vector<string> laser({LASER_TEXT});
    vector<string> motion({MOTION_TEXT});
    vector<string> deadbolt({DEADBOLT_TEXT});
    vector<string> askForLoot({ASK_FOR_LOOT_TEXT});
    vector<string> offerLoot({OFFER_LOOT_TEXT});
    if(msgsToShow[2]== motion[2])     //Si era una respuesta para un motion
    {
        if(userChoice==USE_HACK_TOKEN_TEXTB)        // y uso hack tokens
            tokens.removeOneHackTokenOf(COMPUTER_ROOM_MOTION);
        else if(userChoice==TRIGGER_ALARM_TEXTB)        //Sino, triggerea la alarma
        {    
            tokens.triggerAlarm(prevLoc); setGuardsNewPath(prevLoc.floor); 
            if(movingPlayer->getcurrentActions() == 0 && getPlayerOnTurn() == THIS_PLAYER && !specialMotionCase) //SI es de este player justo cuando termina su turno, se tiene que enviar el paquete del guardia.
                guardHasToMove=true;
        }
    }
    else if(msgsToShow[2]==deadbolt[2])
    {
        if(userChoice==SPEND_ACTIONS_TEXTB)//decide gastar las acciones y entra
        {
            for(unsigned int i=0;i<2;++i)//PODRIA SER UN DEFINE EL 2
                movingPlayer->decActions();
        }
        else if(userChoice==GET_BACK_TEXTB)//decide no gastar las acciones y vuelve atras
            movingPlayer->setPosition(prevLoc);
    }
    else if(msgsToShow[2]==fingerPrint[2])
    {
        if(userChoice==USE_HACK_TOKEN_TEXTB)// clickeo "use hack token" 
            tokens.removeOneHackTokenOf(COMPUTER_ROOM_FINGERPRINT);
        else if(userChoice==TRIGGER_ALARM_TEXTB)//clickeo "trigger alarm"
        {
              tokens.triggerAlarm(movingPlayer->getPosition());
              setGuardsNewPath(movingPlayer->getPosition().floor); //Así se pone el dado a donde tiene que ir, este lo necesitaba desde el guardia
              if(movingPlayer->getcurrentActions() == 0 && getPlayerOnTurn() == THIS_PLAYER) //SI es de este player justo cuando termina su turno, se tiene que enviar el paquete del guardia.
                    guardHasToMove=true;
        }
    }
    else if(msgsToShow[2]==laser[2])
    {
        if(userChoice==TRIGGER_ALARM_TEXTB)
        {    tokens.triggerAlarm(movingPlayer->getPosition()); setGuardsNewPath(movingPlayer->getPosition().floor);}
        else if(userChoice==USE_HACK_TOKEN_TEXTB)
            tokens.removeOneHackTokenOf(COMPUTER_ROOM_LASER);
        else if(userChoice==SPEND_ACTION_TEXTB)
            movingPlayer->decActions();
        if(movingPlayer->getcurrentActions() == 0 && getPlayerOnTurn() == THIS_PLAYER && msgsToShow.size()==5 && msgsToShow[4]==USE_HACK_TOKEN_TEXTB && userChoice==TRIGGER_ALARM_TEXTB)
            guardHasToMove=true; //En el caso que: this player se mete a un laser y se queda sin acciones, pero tenía token y decide no usar un token, no se manda ningun paquete, por lo cual se tiene que manda el paquete de guardmove.
    }
    else if(msgsToShow[2]==lavatory[2])
    {
        if(userChoice ==USE_MY_STEALTH_TOKEN_TEXTB)
        {
            movingPlayer->decLives();
            if(movingPlayer->getcurrentActions() == 0 && getPlayerOnTurn() == THIS_PLAYER) //SI es de este player justo cuando termina su turno, se tiene que enviar el paquete del guardia.
                    guardHasToMove=true;
        }
        else if(userChoice ==USE_LAVATORY_TOKEN_TEXTB)
            tokens.useLavatoryToken();
    }
    else if(msgsToShow[0]==askForLoot[0])       //Si se estaba esperando por la respuesta a un ask for loot
    {
        if(userChoice==ACCEPT_TEXTB)        //Y se respondió que se acepta
        {   
            PlayerId playerOnTurn = getPlayerOnTurn();
            getP2Player(playerOnTurn)->attachLoot(lootOfferedOrAskedFor);   //Se le pone el loot al player on turn
            getP2OtherPlayer(playerOnTurn)->deattachLoot(lootOfferedOrAskedFor);    //Se le saca al otro jugador
            loots.setNewLootOwner(lootOfferedOrAskedFor,playerOnTurn);
        }
    }
    else if(msgsToShow[0]== offerLoot[0])
    {
        if(userChoice==ACCEPT_TEXTB)
        {    
            PlayerId playerOnTurn = getPlayerOnTurn();
            getP2OtherPlayer(playerOnTurn)->attachLoot(lootOfferedOrAskedFor);
            getP2Player(playerOnTurn)->deattachLoot(lootOfferedOrAskedFor);
            loots.setNewLootOwner(lootOfferedOrAskedFor,playerOnTurn==THIS_PLAYER?OTHER_PLAYER:THIS_PLAYER);
            view->update(this);
        }
    }
    if(msgsToShow[2]== motion[2] && specialMotionCase)      //Si fue el caso especial de motion salen 2 carteles seguidos, o sea se espera por una confirmación más.
    {
        if(!auxMsgsToShow.empty())
        {
            status=WAITING_FOR_USER_CONFIRMATION;
            this->msgsToShow=auxMsgsToShow;
            auxMsgsToShow.clear();
        }
        else        //Si estaba vacía era el caso especial para el keypad.
            status=WAITING_FOR_DICE;
        specialMotionCase=false;
    }   
    else
        status=WAITING_FOR_ACTION;
    view->update(this);
    checkTurns();
    view->update(this);
    return guardHasToMove;
}

void BurgleBrosModel::setDice(vector<unsigned int> &currDice)
{
    bool keyCracked;
    BurgleBrosPlayer * movingPlayer= getP2Player(getPlayerOnTurn());
    if(currDice.empty())        //Si estaba vacío significa que el jugador que hizo el set dice fue el de esta pc
    {       //Entonces se tiran random en este programa
        if(movingPlayer->getCharacter()==THE_PETERMAN)      //Si es el peterman tira 1 dado más
            keyCracked=dice.throwDiceForKeypadWithExtraDie(movingPlayer->getPosition());
        else
            keyCracked=dice.throwDiceForKeypad(movingPlayer->getPosition());    
        currDice=dice.getCurrDice();
    }
    else
    {
        dice.setDice(currDice); //SI los jhizo el otro jugador se copian.
        keyCracked=dice.didDiceUnlockKeypad();
    }
    if(keyCracked)  //SI se crackeo, se pone un token, o sino se lo devuelve a su posición anterior
        tokens.putKeyPadToken(movingPlayer->getPosition());
    else
    {
        dice.addDieToKeypad(movingPlayer->getPosition());
        movingPlayer->setPosition(prevLoc);
    }
    status=WAITING_FOR_ACTION;
    view->update(this);
    checkTurns();
    view->update(this);
}
void BurgleBrosModel::pass(PlayerId playerId)
{
    bool actionOk=false;
    BurgleBrosPlayer * p=getP2Player(playerId);
    if(p->isItsTurn() && !gameFinished)
    {
        while(p->getcurrentActions())
            p->decActions();
        if(board.getCardType(p->getPosition()) == THERMO)
        {   tokens.triggerAlarm(p->getPosition()); setGuardsNewPath(p->getPosition().floor);}
        checkTurns();
        view->update(this);
        actionOk=true;
    }
    if(actionOk==false)
    {   gameFinished=true; finishMsg = "ERROR: BBModel error: A pass action was called when it wasnt possible to do it!"; }
}
unsigned int BurgleBrosModel::peek(PlayerId playerId, CardLocation locationToPeek, int safeNumber)
{
    unsigned int retVal;
    bool actionOk=false;
    BurgleBrosPlayer *p=getP2Player(playerId);
    if(isPeekPosible(playerId, locationToPeek) && !gameFinished)
    {
        if(playerId == THIS_PLAYER)
             retVal=board.setCardVisible(locationToPeek);
        else
             retVal=board.setCardVisible(locationToPeek, safeNumber);
        if(p->getCharacter() == THE_HAWK && playerSpentFreeAction==false && board.isAWallBetween(p->getPosition(), locationToPeek))
            playerSpentFreeAction=true;
        else
            p->decActions();
        if(board.getCardType(locationToPeek)==LAVATORY)
            tokens.lavatoryRevealed(locationToPeek); 
        checkTurns();
        view->update(this);
        actionOk=true;      
    }
    if(actionOk==false)
    {   gameFinished=true; finishMsg = "ERROR: BBModel error :A peek action was called when it wasnt possible to do it!"; }
    return retVal;
}
unsigned int BurgleBrosModel::move(PlayerId playerId, CardLocation locationToMove, int safeNumber)
{
    bool actionOk=false;
    unsigned int retVal;
    if(isMovePosible(playerId, locationToMove) && !gameFinished)
    {
        BurgleBrosPlayer* movingPlayer=getP2Player(playerId);
        BurgleBrosPlayer* playerNotMoving=getP2OtherPlayer(playerId);
        CardLocation prevLocation=movingPlayer->getPosition();
        CardName newCardType=board.getCardType(locationToMove);
        bool cardWasVisible=true;
        
        if( !board.isCardVisible(locationToMove) )
        {
            if(playerId == OTHER_PLAYER)
                retVal=board.setCardVisible(locationToMove, safeNumber);
            else
                retVal=board.setCardVisible(locationToMove);
            cardWasVisible=false;
        }    
        else
            retVal=board.getCardSafeNumber(locationToMove);
        movingPlayer->decActions();
        movingPlayer->setPosition(locationToMove);
        
        
        
        //Cambios segun el lugar desde el que me muevo
        if(board.getCardType(prevLocation)==MOTION && board.isMotionActivated())
        {
            if(tokens.howManyTokensOnCPURoom(COMPUTER_ROOM_MOTION))
            {
                std::vector<string> aux({MOTION_TEXT,USE_HACK_TOKEN_TEXTB,TRIGGER_ALARM_TEXTB});//STAY????
                this->msgsToShow=aux;
                status=WAITING_FOR_USER_CONFIRMATION; //Ahora el modelo va a esperar la respuesta del usuario.
                this->prevLoc=prevLocation;
                handleSpecialMoveFromMotion(locationToMove,&cardWasVisible); //EN el caso en que se mueve a otra carte que pida cartel, se encarga esta función de arreglarlo.
            }
            else 
            {    tokens.triggerAlarm(prevLocation); setGuardsNewPath(prevLocation.floor); }
            board.deActivateMotion();//OJO, SI SE AGREGA LA OPCION STAY ESTO TIENE QUE IR EN LOS OTROS CASOS Y NO ACA
        }
        //cambios segun el charatcer
        if(movingPlayer->getCharacter()==THE_ACROBAT && locationToMove==guards[locationToMove.floor].getPosition())
            movingPlayer->setActions(movingPlayer->getcurrentActions()+1);
        
        //cambios segun loot
        if(movingPlayer->hasLoot(GEMSTONE) && locationToMove==playerNotMoving->getPosition())
            movingPlayer->decActions();
        if(movingPlayer->hasLoot(TIARA) && board.adjacentCards(locationToMove,guards[locationToMove.floor].getPosition()))
            movingPlayer->decLives();
        
        
        view->update(this);
        if(locationToMove==guards[locationToMove.floor].getPosition() && board.getCardType(locationToMove)!= LAVATORY && movingPlayer->getCharacter()!=THE_ACROBAT)
            movingPlayer->decLives();
        
        CardLocation downstairsLocationToMove={locationToMove.floor-1, locationToMove.row, locationToMove.column};
        if(prevLocation==downstairsLocationToMove && !tokens.isThereADownstairToken(locationToMove))
            tokens.placeDownstairToken(locationToMove);
        
        //ver si aca tiene que ir algo mas antes de los cambios por cartas
        
        
        
        

        
        
        //Cambios segun el tipo de carta al que me movi
        
        //Si me movi a un atrium y hay un guard arriba o abajo se activa una alarma
        if(newCardType==ATRIUM &&
                ( (locationToMove.floor>0 && board.isCardDownstairs(locationToMove,guards[locationToMove.floor-1].getPosition()) ) || ( locationToMove.floor<2 && board.isCardUpstairs(locationToMove,guards[locationToMove.floor+1].getPosition()) ) ) )
            movingPlayer->decLives();//OJO SI PIERDE NO HACE NADA POR AHORA!!!!!!!!!!!!!
        //Si me movi a una camara y hay un guardia en otra camara activo una alarma en donde estoy
        if( newCardType==CAMERA && GuardInCamera() && locationToMove!= guards[locationToMove.floor].getPosition() ) 
            {tokens.triggerAlarm(locationToMove); setGuardsNewPath(locationToMove.floor);}
        //Si me movi a un foyer y hay un guardia en un tile adyacente me ve (a menos que haya una pared)
        if( newCardType== FOYER && board.adjacentCards(locationToMove, guards[locationToMove.floor].getPosition() ) )
            movingPlayer->decLives();//OJO SI PIERDE NO HACE NADA POR AHORA!!!!!!!!!!!!!
        //Si me movi a un deadbolt tengo que gastar 3 acciones para entrar o vuelvo a donde estaba
        if( newCardType==DEADBOLT && locationToMove!=guards[locationToMove.floor].getPosition() && locationToMove!=playerNotMoving->getPosition())
        {   
            if(movingPlayer->getcurrentActions()<2 && !cardWasVisible)
                movingPlayer->setPosition(prevLocation);
            else if(!specialMotionCase)
            {
                std::vector<string> aux({DEADBOLT_TEXT,SPEND_ACTIONS_TEXTB,GET_BACK_TEXTB});
                this->msgsToShow=aux;
                this->status=WAITING_FOR_USER_CONFIRMATION; //Pone al modelo en el estado de espera por la respuesta del usuario.
                this->prevLoc=prevLocation;
            }
                
        }    
        //Si quiero entrar a un keypad y no esta abierto tengo que tirar los dados (el numero de dados se corresponde con los intentos en el mismo turno)
        if( newCardType==KEYPAD && !tokens.isThereAKeypadToken(locationToMove) && !specialMotionCase)
        {
            bool keyCracked=false;
            this->status=WAITING_FOR_DICE;
            this->prevLoc=prevLocation;
        }
        
        if(movingPlayer->getCharacter()!=THE_HACKER && ( playerNotMoving->getCharacter()!=THE_HACKER || (playerNotMoving->getCharacter()==THE_HACKER && locationToMove!= playerNotMoving->getPosition() ) ))
        {    
        if( newCardType==FINGERPRINT)//hay que arreglar el tema de cuando hace click en la cruz del native message
        {
               if(tokens.howManyTokensOnCPURoom(COMPUTER_ROOM_FINGERPRINT) && !specialMotionCase )//Si hay tokens disponibles
               {
                  std::vector<string> aux({ENTER_FINGERPRINT_TEXT,USE_HACK_TOKEN_TEXTB,TRIGGER_ALARM_TEXTB});  //Esto contiene el título del cartelito, subtitulo y texto, por eso vector
                  this->msgsToShow=aux;
                  this->status=WAITING_FOR_USER_CONFIRMATION;
               }
               else
               {
                   tokens.triggerAlarm(locationToMove);
                   setGuardsNewPath(locationToMove.floor); //Así se pone el dado a donde tiene que ir, este lo necesitaba desde el guardia
               }
        }   
          
        if( newCardType==MOTION)
            board.activateMotion();//hay que marcar que se entro en este turno y si sale en el mismo turno tiene que gastar un token o activar una alarma, en el proximo ya puede salir
         
        if(newCardType==LASER && !movingPlayer->hasLoot(MIRROR))
        {   
            if( !(tokens.howManyTokensOnCPURoom(COMPUTER_ROOM_LASER)) && !(movingPlayer->getcurrentActions()) )
                {tokens.triggerAlarm(locationToMove); setGuardsNewPath(locationToMove.floor);}
            else if(!specialMotionCase)
            {
                std::vector<string> aux({LASER_TEXT,TRIGGER_ALARM_TEXTB}); 
                if(tokens.howManyTokensOnCPURoom(COMPUTER_ROOM_LASER))
                    aux.push_back(USE_HACK_TOKEN_TEXTB);
                if(movingPlayer->getcurrentActions())
                    aux.push_back(SPEND_ACTION_TEXTB);
                this->msgsToShow=aux;
                this->status=WAITING_FOR_USER_CONFIRMATION;
            }
        }
        }
        
        if(newCardType==LAVATORY)
        {
            if(!cardWasVisible)
                tokens.lavatoryRevealed(locationToMove);

            if(locationToMove==guards[locationToMove.floor].getPosition() && tokens.isThereAStealthToken(locationToMove))
            {
                if(!specialMotionCase)
                {
                    vector<string> aux({LAVATORY_TEXT,USE_LAVATORY_TOKEN_TEXTB,USE_MY_STEALTH_TOKEN_TEXTB});
                    this->msgsToShow=aux;
                    status=WAITING_FOR_USER_CONFIRMATION;
                }
            }    
            else if(locationToMove==guards[locationToMove.floor].getPosition() && !tokens.isThereAStealthToken(locationToMove))
                movingPlayer->decLives();
        }    
        
        
        if( newCardType==SCANNER_DETECTOR && movingPlayer->carriesLoot())
        {    tokens.triggerAlarm(locationToMove); setGuardsNewPath(locationToMove.floor); }
        
        if(newCardType==THERMO && ( movingPlayer->getcurrentActions()==0 || movingPlayer->hasLoot(ISOTOPE)))
        {    tokens.triggerAlarm(locationToMove); setGuardsNewPath(locationToMove.floor); }
        
        if(newCardType==WALKAWAY && !cardWasVisible && locationToMove.floor>0)
        {   
            CardLocation downStairsLocation={locationToMove.floor-1,locationToMove.row,locationToMove.column};
            movingPlayer->setPosition(downStairsLocation);
        }

        checkTurns();
        view->update(this);
        actionOk=true;
    }
    if(actionOk==false)
    {   gameFinished=true; finishMsg = "ERROR: BBModel error: A peek action was called when it wasnt possible to do it!"; }
    return retVal;
}
void BurgleBrosModel::handleSpecialMoveFromMotion(CardLocation movingToTile, bool *cardWasVisible)
{
    CardName moveTo=board.getCardType(movingToTile);
    BurgleBrosPlayer * playerMoving = getP2Player(getPlayerOnTurn());
    BurgleBrosPlayer * playerNotMoving = getP2OtherPlayer(getPlayerOnTurn());
    if(moveTo==FINGERPRINT && tokens.howManyTokensOnCPURoom(COMPUTER_ROOM_FINGERPRINT))
    {
        specialMotionCase=true;
        std::vector<string> aux({ENTER_FINGERPRINT_TEXT,USE_HACK_TOKEN_TEXTB,TRIGGER_ALARM_TEXTB});  //Esto contiene el título del cartelito, subtitulo y texto, por eso vector
        this->auxMsgsToShow=aux;
    }                                                                                                                                   //Mayor igual que dos porque ya se gasto una acción en el move.
    else if(moveTo==DEADBOLT && movingToTile!=guards[movingToTile.floor].getPosition() && movingToTile!=playerNotMoving->getPosition() && playerMoving->getcurrentActions()>=2)
    {   
        specialMotionCase=true;
        std::vector<string> aux({ENTER_FINGERPRINT_TEXT,USE_HACK_TOKEN_TEXTB,TRIGGER_ALARM_TEXTB});  //Esto contiene el título del cartelito, subtitulo y texto, por eso vector
        this->auxMsgsToShow=aux;
    }
    else if(moveTo==KEYPAD && !tokens.isThereAKeypadToken(movingToTile))
    {   
        specialMotionCase=true;
        auxMsgsToShow.clear();      //Para el caso de moverse de un motion que se puede activar y tiene tokens a un keypad que no está abierto:
    }
    else if(moveTo==LAVATORY)
    {
        if(!(*cardWasVisible))
        {   tokens.lavatoryRevealed(movingToTile); *cardWasVisible=true;    }
        if(movingToTile==guards[movingToTile.floor].getPosition() && tokens.isThereAStealthToken(movingToTile))
        {
            specialMotionCase=true;
            vector<string> aux({LAVATORY_TEXT,USE_LAVATORY_TOKEN_TEXTB,USE_MY_STEALTH_TOKEN_TEXTB});
            this->auxMsgsToShow=aux;
        }
    }
    else if(moveTo==LASER &&  !playerMoving->hasLoot(MIRROR) && (tokens.howManyTokensOnCPURoom(COMPUTER_ROOM_LASER) || playerMoving->getcurrentActions()))
    {
        std::vector<string> aux({LASER_TEXT,TRIGGER_ALARM_TEXTB}); 
        if(tokens.howManyTokensOnCPURoom(COMPUTER_ROOM_LASER))
            aux.push_back(USE_HACK_TOKEN_TEXTB);
        if(playerMoving->getcurrentActions())
            aux.push_back(SPEND_ACTION_TEXTB);
        specialMotionCase=true;
        this->auxMsgsToShow=aux;
    }
}



void BurgleBrosModel::addToken(PlayerId playerId, CardLocation locationToAddToken)
{
    bool actionOk=false;
    BurgleBrosPlayer* movingPlayer=getP2Player(playerId);
    if(isAddTokenPosible(playerId, locationToAddToken))
    {
        tokens.addHackTokenOn(board.getCardType(locationToAddToken));
        movingPlayer->decActions();
        checkTurns();
        view->update(this);
        actionOk=true;
    }
    if(actionOk==false)
    {   gameFinished=true; finishMsg = "ERROR: BBModel error: An add token action was called when it wasnt possible to do it!"; }
}
void BurgleBrosModel::addDieToSafe(PlayerId playerId, CardLocation safe)
{
    bool actionOk=false;
    BurgleBrosPlayer* p= getP2Player(playerId);
    if(isAddDieToSafePossible(playerId, safe) && !gameFinished)
    {
        p->decActions();
        p->decActions();
        dice.addDieToSafe(safe.floor); 
        checkTurns();
        view->update(this);
        actionOk=true;
    }
    if(actionOk==false)
    {   gameFinished=true; finishMsg = "ERROR: BBModel error: An add die to safe action was called when it wasnt possible to do it!"; }
}
void BurgleBrosModel::crackSafe(PlayerId playerId,vector<unsigned int> &diceThrown)
{
    bool actionOk=false;
    BurgleBrosPlayer* p= getP2Player(playerId);
    if(isCrackSafePossible(playerId,p->getPosition()) && !gameFinished)
    {
        CardLocation safe= p->getPosition();
        p->decActions();                //Cuesta una acción hacer un creack
        if(playerId==THIS_PLAYER)       //Para este jugador:
        {
            if(p->getCharacter() == THE_PETERMAN)       //Si es peterman tira con un dado extra
                diceThrown=dice.throwDiceForSafeWithExtraDie(safe.floor);
            else                                        //Sino tira los dados normales
                diceThrown=dice.throwDiceForSafe(safe.floor);
        }
        else dice.setDice(diceThrown);  //Si fue el otro jugador se copian
        list<CardLocation> tilesCrackedOnThisAction = board.tilesWithCracked(diceThrown,safe.floor);   //Obtengo las cartas que tienen como safe number uno de los numeros que salio en el dado
        tokens.addCrackTokenOn(tilesCrackedOnThisAction);
        if(tokens.isSafeOpened(safe.floor))
        {
            status=WAITING_FOR_LOOT;    //Espero a que me confirmen el loot.
            prevLoc=safe;           //Guardo a que safe crackeo
        }
        view->update(this);
        checkTurns();
        actionOk=true;
    }
    if(actionOk==false)
    {   gameFinished=true; finishMsg = "ERROR: BBModel error: A crack safe action was called when it wasnt possible to do it!"; }
}
void BurgleBrosModel::setLoot(PlayerId playerId, Loot *loot)
{
    BurgleBrosPlayer *p=getP2Player(playerId);
    CardLocation safe= prevLoc;
    if(tokens.isSafeOpened(safe.floor) && status== WAITING_FOR_LOOT)
    {
        Loot lootGotten;
        if(playerId==THIS_PLAYER)
            lootGotten =loots.getLoot(playerId);
        else if(playerId==OTHER_PLAYER)
            lootGotten =loots.getLoot(playerId, *loot);
        p->attachLoot(lootGotten);
        if(lootGotten==GOLD_BAR)
            loots.setGoldBardLocation(safe);
        if(lootGotten==CURSED_GOBLET && p->getCurrLifes()>1)
            p->decLives();
        board.setSafeCracked(safe.floor);
        triggerSilentAlarm(safe.floor);
        *loot=lootGotten;
        status=WAITING_FOR_ACTION;
        view->update(this);
        checkTurns();
    }
    else
    {   gameFinished=true; finishMsg = "ERROR: BBModel error: A set Loot action was called when it wasnt possible to do it!"; }
}


void BurgleBrosModel::createAlarm(PlayerId playerId, CardLocation tile)
{
    bool actionOk=false;
    if(isCreateAlarmPossible(playerId,tile) && !gameFinished)
    {
        playerSpentFreeAction=true;
        tokens.triggerAlarm(tile);
        setGuardsNewPath(tile.floor);
        actionOk=true;
        view->update(this);
    }
    if(actionOk==false)
    {   gameFinished=true; finishMsg = "ERROR: BBModel error: A create alarm action was called when it wasnt possible to do it!"; }
}
void BurgleBrosModel::placeCrow(PlayerId playerId, CardLocation tile)
{
    bool actionOk=false;
    if(isPlaceCrowPossible(playerId,tile) && !gameFinished)
    {
        tokens.placeCrowToken(tile);
        playerSpentFreeAction=true;
        actionOk=true;
        view->update(this);
    }
    if(actionOk==false)
    {   gameFinished=true; finishMsg = "ERROR: BBModel error: A place crow action was called when it wasnt possible to do it!"; }
}
void BurgleBrosModel::pickLoot(PlayerId playerId, Loot lootToPick)
{
    bool actionOk=false;
    BurgleBrosPlayer *p= getP2Player(playerId);
    if(isPickLootPossible(playerId,p->getPosition(), lootToPick) && !gameFinished)
    {
        if(lootToPick==PERSIAN_KITTY)          //Si es el persian kitty
        {
            pair<bool, CardLocation> kittyInfo;
            kittyInfo.first= false;
            tokens.placePersianKittyToken(kittyInfo);
            loots.setNewLootOwner(PERSIAN_KITTY, playerId);
            p->attachLoot(PERSIAN_KITTY);
            view->update(this);
            actionOk=true;
        }
        else if(lootToPick==GOLD_BAR)
        {
            loots.pickGoldBarOnFloor(playerId, p->getPosition());
            p->attachLoot(GOLD_BAR);
            view->update(this);
            actionOk=true;
        }
    }
    if(actionOk==false)
    {   gameFinished=true; finishMsg = "ERROR: BBModel error: A pick loot action was called when it wasnt possible to do it!"; }
}

string BurgleBrosModel::peekGuardsCard(PlayerId playerId, CardLocation *guardCard, unsigned int guardsFloor, string prevChoice)
{
    bool actionOk = false;
    string userChoice;
    if(isPeekGuardsCardPossible(playerId, guardsFloor) && !gameFinished)
    {
        //unsigned int guardsFloor= guardCard->floor;
        guards[guardsFloor].setTopOfNotShownDeckVisible(true);      //Muestro la carta de arriba
        view->update(this);
        
        if(prevChoice == SPOTTER_NO_PREV_CHOICE && playerId==THIS_PLAYER)   //Para este jugador le pregunta por patalla
        {
            vector<string>msgToShow({SPOTTER_SPECIAL_ACTION_TEXT,SPOTTER_TOP,SPOTTER_BOTTOM});
            userChoice = controller->askForSpentOK(msgToShow);//Le pregunto si la quiere arriba o abajo
        }
        else
        {
            userChoice=prevChoice;      //Sino es lo pasado por argumento.
            sleep(1); //Se duerme un segundo para mostrar la carta que saco el otro pj.
        }    
        *guardCard=guards[guardsFloor].getTopCard();        //tomo la carta sacada
        if(userChoice==SPOTTER_TOP)
        {
            guards[guardsFloor].setTopOfNotShownDeckVisible(false); //Si la quería arriba no hago nada y dejo de mostrarla.
            //*guardCard=guards[guardsFloor].getTopCard();
            guards[guardsFloor].pushCardToTheTop(*guardCard);
        }
        else
        {
            guards[guardsFloor].setTopOfNotShownDeckVisible(false);
            //if(playerId==THIS_PLAYER)
                guards[guardsFloor].pushTopCardToTheBottom();
            //7else
               // guards[guardsFloor].pushCardToTheBottom(*guardCard);
        }
        getP2Player(playerId)->decActions();
        playerSpentFreeAction=true;
        view->update(this);
        actionOk=true;
    }
    if(actionOk==false)
    {   gameFinished=true; finishMsg = "ERROR: BBModel error: A peek guards card action was called when it wasnt possible to do it!"; }
    return userChoice;
}

void BurgleBrosModel::askForLoot(PlayerId playerId, Loot loot)
{
    bool actionOk = false;
    if(isAskForLootPossible(playerId,getP2Player(playerId)->getPosition(),loot) && !gameFinished)
    {
        
        std::vector<string> aux({ASK_FOR_LOOT_TEXT+loot2Str(loot),ACCEPT_TEXTB,DECLINE_TEXTB}); 
        this->msgsToShow=aux;
        this->status=IN_LOOT_EXCHANGE;
        this->lootOfferedOrAskedFor=loot;
        actionOk=true;
    }
    if(actionOk==false)
    {   gameFinished=true; finishMsg = "ERROR: BBModel error: An ask for loot action was called when it wasnt possible to do it!"; }
}

void BurgleBrosModel::offerLoot(PlayerId playerId, Loot loot)
{
    bool actionOk = false;
    if(isOfferLootPossible(playerId,getP2Player(playerId)->getPosition(),loot) && !gameFinished)
    {
        std::vector<string> aux({OFFER_LOOT_TEXT+loot2Str(loot),ACCEPT_TEXTB,DECLINE_TEXTB}); 
        this->msgsToShow=aux;
        this->status=IN_LOOT_EXCHANGE;
        this->lootOfferedOrAskedFor=loot;
        actionOk=true;
    }
    if(actionOk==false)
    {   gameFinished=true; finishMsg = "ERROR: BBModel error: An offer loot action was called when it wasnt possible to do it!"; }
}
void BurgleBrosModel::escape(PlayerId playerId, CardLocation stairTile)
{
    bool actionOk=false;
    BurgleBrosPlayer *p = getP2Player(playerId);
    if(isEscapePossible(playerId,stairTile) && !gameFinished)
    {   
        while(p->getcurrentActions())
            p->decActions();
        p->getToDaChoppa(); 
        view->update(this);
        checkTurns();
        view->update(this);
        actionOk=true;
    }
    if(actionOk==false)
    {   gameFinished=true; finishMsg = "ERROR: BBModel error: An escape action was called when it wasnt possible to do it!"; }
}

bool BurgleBrosModel::GuardInCamera() 
{
    bool GuardOnCamera=false;
    for(unsigned int i=0; i<BOARD_STANDARD_FLOORS; ++i)
    {
        if(guards[i].checkIfInitialized() && board.getCardType(guards[i].getPosition())== CAMERA && board.isCardVisible(guards[i].getPosition()))//chequeo que la camara este dada vuelta
        {    
            GuardOnCamera=true;
            break;
        }    
    }
    return GuardOnCamera;
} 

void BurgleBrosModel::checkTurns()
{
    if(myPlayer.isItsTurn() && myPlayer.getcurrentActions() == 0 && status==WAITING_FOR_ACTION)
    {
        if(board.getCardType(myPlayer.getPosition()) == THERMO && board.isCardVisible(myPlayer.getPosition()))
        {    tokens.triggerAlarm(myPlayer.getPosition()); setGuardsNewPath(myPlayer.getPosition().floor);}
        myPlayer.setTurn(false);
        playerOnTurnBeforeGuardMove=THIS_PLAYER;
      /*  moveGuard(myPlayer.getPosition().floor); //Se comenta para probar los moves entre las 2 pcs
        if(!otherPlayer.isOnHelicopter())
            otherPlayer.setTurn(true);
        else
            myPlayer.setTurn(true);
        handlePersianKittyMove(OTHER_PLAYER);
        handleChihuahuaMove(OTHER_PLAYER);*/
        playerSpentFreeAction=false;
        //dice.resetKeypadsDice();
        board.deActivateMotion();
    }
    else if(otherPlayer.isItsTurn() && otherPlayer.getcurrentActions() == 0 && status==WAITING_FOR_ACTION)
    {
        if(board.getCardType(otherPlayer.getPosition()) == THERMO && board.isCardVisible(otherPlayer.getPosition()))
        {   tokens.triggerAlarm(otherPlayer.getPosition()); setGuardsNewPath(otherPlayer.getPosition().floor);}
        otherPlayer.setTurn(false);
        playerOnTurnBeforeGuardMove=OTHER_PLAYER;
        //moveGuard(otherPlayer.getPosition().floor);
      /*  if(!myPlayer.isOnHelicopter())
            myPlayer.setTurn(true);
        else
            otherPlayer.setTurn(true);
        handlePersianKittyMove(THIS_PLAYER);
        handleChihuahuaMove(THIS_PLAYER);*/
        playerSpentFreeAction=false;
        //dice.resetKeypadsDice();
        board.deActivateMotion();
    }
    else if(isGuardsTurn() && guardFinishedMoving==true)
    {
        BurgleBrosPlayer *nextPlayerOnTurn=getP2OtherPlayer(playerOnTurnBeforeGuardMove); //El jugador que termina ahora el turno va a ser el que no terminó antes que el guardia
        if(nextPlayerOnTurn->isOnHelicopter())
            nextPlayerOnTurn=getP2Player(playerOnTurnBeforeGuardMove);  //Si el otro jugador estaba en el helicopter vuelve a jugar el primero.
        nextPlayerOnTurn->setTurn(true);
        nextPlayerOnTurn->setActions(INIT_NMBR_OF_LIVES);       //Se le resetean las acciones.
        if(nextPlayerOnTurn->hasLoot(MIRROR))
            nextPlayerOnTurn->setActions(INIT_NMBR_OF_LIVES-1);       //SI tenía un mirror pierde 1 acción
        if(nextPlayerOnTurn->hasLoot(CHIHUAHUA) || nextPlayerOnTurn->hasLoot(PERSIAN_KITTY))
            status=WAITING_DICE_FOR_LOOT;
        // handlePersianKittyMove(nextPlayerOnTurn);
       // handleChihuahuaMove(nextPlayerOnTurn);
        guardFinishedMoving=false;
        dice.resetKeypadsDice();
        view->update(this);
    }
    checkIfWonOrLost();
}

void BurgleBrosModel::checkIfWonOrLost()
{
    if(myPlayer.isOnHelicopter() && otherPlayer.isOnHelicopter())
    {
        gameFinished=true;
        finishMsg= "WON";
    }
#ifndef INMORTAL
    else if(myPlayer.getCurrLifes()==0 || otherPlayer.getCurrLifes()==0)
    {
        gameFinished=true;
        finishMsg= "LOST";
    }
    
#endif
}


 bool BurgleBrosModel::isMovePosible(PlayerId playerId,CardLocation tileToMove)
 {
     BurgleBrosPlayer * playerMoving = getP2Player(playerId);
     CardLocation playerMovingPos= playerMoving->getPosition();
     bool retVal=false;
     if(playerMoving->isItsTurn()&& status == WAITING_FOR_ACTION)
     {
         if(board.adjacentCards(playerMovingPos, tileToMove))
             retVal=true;
         if(board.isCardVisible(playerMovingPos))
         {
             if(board.getCardType(playerMovingPos) == STAIR  && board.isCardUpstairs(playerMovingPos, tileToMove))
                retVal=true;
             if(board.isCardVisible(tileToMove) && board.getCardType(playerMovingPos) == WALKAWAY  &&  board.isCardDownstairs(playerMovingPos, tileToMove))
                retVal=true;
             if(board.isCardVisible(tileToMove) && board.getCardType(playerMovingPos) == SERVICE_DUCT && (board.getOtherServiceDuctPos(playerMovingPos)== tileToMove))
                retVal=true;
         }
         if(board.getCardType(tileToMove) == SECRET_DOOR && board.isAWallBetween(playerMovingPos,tileToMove) && board.isCardVisible(tileToMove))//No hay que ver que tambien la card sea visible?
             retVal=true;
         if(tokens.isThereAToken(playerMovingPos, DOWNSTAIRS_TOKEN) && board.isCardDownstairs(playerMovingPos, tileToMove))
             retVal=true;
         if((playerMoving->getcurrentActions() <3 )&& board.isCardVisible(tileToMove) &&(board.getCardType(tileToMove) == DEADBOLT )&& !(guards[playerMoving->getPosition().floor].getPosition() == tileToMove) && !(getP2OtherPlayer(playerId)->getPosition() == tileToMove))
             retVal=false;
         if(board.getCardType(playerMovingPos) == SERVICE_DUCT && (board.getOtherServiceDuctPos(playerMovingPos)== tileToMove) && playerMoving->hasLoot(PAINTING) && board.isCardVisible(tileToMove))
             retVal=false;
         if(board.getCardType(tileToMove) == SECRET_DOOR && board.isAWallBetween(playerMovingPos,tileToMove) && playerMoving->hasLoot(PAINTING))
             retVal=false;
         //Falta la del persian kitty o chihuahua
         if(playerMoving->getcurrentActions() == 1 && playerMoving->hasLoot(GEMSTONE) && (getP2OtherPlayer(playerId)->getPosition() == tileToMove))
            retVal=false;
     }
     return retVal;
 }
 bool BurgleBrosModel:: isPeekPosible(PlayerId player, CardLocation tile)
{
    bool retVal=false;
    BurgleBrosPlayer* p=getP2Player(player);
    if(p->isItsTurn() && (!board.isCardVisible(tile)) && status == WAITING_FOR_ACTION)
    {
        if(board.adjacentCards(p->getPosition(),tile))
            retVal=true;
        else if(p->getCharacter()==THE_HAWK && board.isAWallBetween(p->getPosition(),tile)&& !playerSpentFreeAction)//HACER FUNCION WALLLSEPARATES
            retVal=true;
        else if( board.getCardType(p->getPosition())== ATRIUM && ( board.isCardUpstairs(p->getPosition(),tile) || board.isCardDownstairs(p->getPosition(),tile) ) )
            retVal=true;
        else if( board.getCardType(p->getPosition())== STAIR && board.isCardUpstairs(p->getPosition(),tile)  )
            retVal=true;
    }
    return retVal;
}
bool BurgleBrosModel::isAddTokenPosible(PlayerId player, CardLocation tile)
{
    bool retVal=false;
    BurgleBrosPlayer* p;
    p = getP2Player(player);
    if(p->isItsTurn() && (board.isCardVisible(tile)) && p->getPosition() == tile && status == WAITING_FOR_ACTION)
    {
        if(IS_COMPUTER_ROOM(board.getCardType(tile)) && tokens.howManyTokensOnCPURoom(board.getCardType(tile)) < MAX_HACK_TOKENS_ON_COMPUTER_ROOM)
            retVal=true;
    }
    return retVal;
}
bool BurgleBrosModel::isAddDieToSafePossible(PlayerId player, CardLocation tile)
{
    bool retVal=false;
    BurgleBrosPlayer* p;
    p = getP2Player(player);
    if(p->isItsTurn() && p->getcurrentActions()>= 2 && board.getCardType(p->getPosition())==SAFE && p->getPosition()==tile && status == WAITING_FOR_ACTION)
    {
        if(board.canSafeBeCracked(tile.floor) && !board.isSafeCracked(tile.floor) && dice.getSafeDiceCount(tile.floor) < MAX_NMBR_OF_EXTRA_DICES)
            retVal=true;
    }
    return retVal;
}
bool BurgleBrosModel::isCrackSafePossible(PlayerId playerId,CardLocation safe)
{
    bool retVal=false;
    BurgleBrosPlayer* p = getP2Player(playerId);
    
    if(p->isItsTurn()&& board.getCardType(p->getPosition())==SAFE  && p->getPosition()==safe && status == WAITING_FOR_ACTION)
    {
        if(board.canSafeBeCracked(safe.floor) && !board.isSafeCracked(safe.floor))
        {
            if(dice.getSafeDiceCount(safe.floor)!= 0)
                retVal=true;
            else if (p->getCharacter()==THE_PETERMAN && dice.getSafeDiceCount(safe.floor)==0)
                retVal=true;
            if(getP2OtherPlayer(playerId)->hasLoot(KEYCARD) && getP2OtherPlayer(playerId)->getPosition()!=safe)
                retVal=false;
        }  
    }
    return retVal;
}
bool BurgleBrosModel::isCreateAlarmPossible(PlayerId playerId, CardLocation tile)
{
    bool retVal=false;
    BurgleBrosPlayer* p=getP2Player(playerId);
    if(p->isItsTurn() && p->getCharacter() == THE_JUICER && playerSpentFreeAction==false && board.adjacentCards(p->getPosition(),tile)&& status == WAITING_FOR_ACTION)
        retVal=true;
    return retVal;
}
bool BurgleBrosModel::isPlaceCrowPossible(PlayerId playerId, CardLocation tile)
{
    bool retVal=false;
    BurgleBrosPlayer* p=getP2Player(playerId);
    if(p->isItsTurn() && p->getCharacter()== THE_RAVEN && tile.floor == p->getPosition().floor && board.getShortestPathLength(p->getPosition(), tile) <= 2 && playerSpentFreeAction==false && status == WAITING_FOR_ACTION)
    {
        retVal=true;
        if(tokens.getCrowToken().first && tokens.getCrowToken().second==tile)
            retVal=false;
    }
    return retVal;
}

bool BurgleBrosModel::isAskForLootPossible(PlayerId playerId, CardLocation tile, Loot loot)
{
    bool retVal = false;
    BurgleBrosPlayer * p = getP2Player(playerId);
    BurgleBrosPlayer * o = getP2OtherPlayer(playerId);
    if(p->isItsTurn() && p->getPosition() == tile && o->getPosition() == tile && o->hasLoot(loot) && status == WAITING_FOR_ACTION)
    {
        if(!o->isOnHelicopter())
            retVal = true;
        if(loot == GOLD_BAR && p->hasLoot(loot))
            retVal = false;
    }
    return retVal;
}

bool BurgleBrosModel::isOfferLootPossible(PlayerId playerId, CardLocation tile, Loot loot)
{
    bool retVal = false;
    BurgleBrosPlayer * p = getP2Player(playerId);
    BurgleBrosPlayer * o = getP2OtherPlayer(playerId);
    if(p->isItsTurn() && p->getPosition() == tile && o->getPosition() == tile && p->hasLoot(loot) && status == WAITING_FOR_ACTION)
    {
        if(!o->isOnHelicopter())
            retVal = true;
        if(loot == GOLD_BAR && o->hasLoot(loot))
            retVal = false;
    }
    return retVal;
}
bool BurgleBrosModel::isPickLootPossible(PlayerId playerId, CardLocation tile , Loot lootToPick)
{
    bool retVal = false;
    BurgleBrosPlayer * p = getP2Player(playerId);
    if(p->isItsTurn() && p->getPosition()==tile && status == WAITING_FOR_ACTION)
    {
        if(lootToPick == PERSIAN_KITTY && tokens.isThereAPersianKittyToken(tile))
            retVal=true;
        else if(lootToPick == GOLD_BAR && loots.canPlayerPickUpGoldBarOnFloor(playerId,tile))
            retVal=true;
    }
    return retVal;
}
bool BurgleBrosModel::isEscapePossible(PlayerId playerId, CardLocation tile)
{
    bool retVal = false;
    BurgleBrosPlayer * p = getP2Player(playerId);
    BurgleBrosPlayer * o = getP2OtherPlayer(playerId);
    if(p->isItsTurn() && p->getPosition()==tile && board.getCardType(tile)==STAIR && tile.floor==2 && tokens.areAllSafesOpen() && status == WAITING_FOR_ACTION )
    {
        if(!loots.areLootsOnFloor())    //Si no hay ningun loot en el piso, se puede escapar
            retVal=true;
        else if(p->hasLoot(GOLD_BAR) && !o->hasLoot(GOLD_BAR))  //Si el que se escapar tiene un gold bar y el otro no la agarró todavia, puede escapar.
            retVal=true;
        else if(!o->isOnHelicopter() && tokens.getPersianKittyToken().first)    //Si se quiere escapar, el persian kitty está en el piso, pero el otro jugador todavia no subio al heli, puede.
            retVal=true;
    }
    return retVal;
}
bool BurgleBrosModel::isPeekGuardsCardPossible(PlayerId playerId, unsigned int guardsFloor)
{
    bool retVal = false;
    BurgleBrosPlayer * p = getP2Player(playerId);
    if(p->isItsTurn() && p->getCharacter()== THE_SPOTTER && p->getPosition().floor == guardsFloor && status == WAITING_FOR_ACTION && playerSpentFreeAction==false)
        retVal=true;
    return retVal;
}
list<string> BurgleBrosModel::getPosibleActionsToTile(PlayerId player, CardLocation tile)
{
    list<string> aux;
    if(isMovePosible(player, tile))
        aux.push_back("MOVE");
    if(isPeekPosible(player, tile))
        aux.push_back("PEEK");
    if(isAddTokenPosible(player, tile))
        aux.push_back("ADD TOKEN");
    if(isAddDieToSafePossible(player, tile))
        aux.push_back("ADD DIE");
    if(isCrackSafePossible(player, tile))
        aux.push_back("CRACK");
    if(isCreateAlarmPossible(player,tile))
        aux.push_back("CREATE ALARM");
    if(isPlaceCrowPossible(player,tile))
        aux.push_back("PLACE CROW");
    for(int i = (int)TIARA; i <= (int)GOLD_BAR; i++)
    {
        string ask = "ASK FOR ";
        string offer = "OFFER ";
        ask += loot2Str((Loot)i);
        offer += loot2Str((Loot)i);
        transform(ask.begin(), ask.end(), ask.begin(), ::toupper);
        transform(offer.begin(), offer.end(), offer.begin(), ::toupper);
        if(isAskForLootPossible(player,tile,(Loot)i))
            aux.push_back(ask);
        if(isOfferLootPossible(player,tile,(Loot)i))
            aux.push_back(offer);
    }
    if(isPickLootPossible(player, tile,PERSIAN_KITTY))
        aux.push_back("PICK UP KITTY");
    if(isPickLootPossible(player, tile, GOLD_BAR))
        aux.push_back("PICK UP GOLD BAR");
    if(isEscapePossible(player,tile))
        aux.push_back("ESCAPE");
    return aux;
}
list<string> BurgleBrosModel::getPosibleActionsToGuard(PlayerId player, unsigned int guardsFloor)
{
    list<string> aux;
    if(isPeekGuardsCardPossible(player, guardsFloor))
        aux.push_back("PEEK TOP CARD");
    return aux;
}
 
BurgleBrosPlayer * BurgleBrosModel::getP2Player(PlayerId playerId)
{
    if(playerId==THIS_PLAYER)
        return &myPlayer;
    else
        return &otherPlayer;
}
BurgleBrosPlayer * BurgleBrosModel::getP2OtherPlayer(PlayerId playerId)
{
    if(playerId==THIS_PLAYER)
        return &otherPlayer;
    else
        return &myPlayer;
}
void BurgleBrosModel::guardMove(list<GuardMoveInfo> &guardMovement)
{
    if(guardMovement.empty())//Si se mandó una lista vacía, se hace el movimiento del guardia 
        makeGuardMove(guardMovement);
    else
        copyGuardMove(guardMovement);
    guardFinishedMoving=true;
    checkTurns();
}
void BurgleBrosModel::makeGuardMove(list<GuardMoveInfo> &guardMovement)
{
    GuardMoveInfo auxiliarInfoToReport;
    unsigned int guardFloor= getP2Player(playerOnTurnBeforeGuardMove)->getPosition().floor;   //Obtengo la posición del 
    BurgleBrosGuard *guardMoving = &(guards[guardFloor]);
    unsigned int stepsToMove= tokens.howManyAlarmsOnFloor(guardFloor) + guardMoving->getDiceNumber(); //El guardia se mueve en su turno los pasos de sus dados + la cantidad de alarmas en su piso
    bool targetReached=false;
    if(stepsToMove>6)
        stepsToMove=6;
    if(tokens.isThereAnAlarmToken(guardMoving->getPosition()))     //Si hay una alarma en su posición ya la desactiva y busca un nuevo camino.
    {
        tokens.turnOffAlarm(guardMoving->getPosition());
        setGuardsNewPath(guardFloor);
    }
    /*if(myPlayer.getCharacter()== THE_ACROBAT && myPlayer.getPosition() == guardMoving->getPosition()) // Si un acrobat termina su turno en el tile del guardia PERDERA LA CABEZA! digo un stealth token.
        myPlayer.decLives();
    if(otherPlayer.getCharacter()== THE_ACROBAT && otherPlayer.getPosition() == guardMoving->getPosition())
        otherPlayer.decLives();*/
    if(getP2Player(playerOnTurnBeforeGuardMove)->getCharacter() == THE_ACROBAT && getP2Player(playerOnTurnBeforeGuardMove)->getPosition() == guardMoving->getPosition())
        getP2Player(playerOnTurnBeforeGuardMove)->decLives();
    while(stepsToMove!=0 && !gameFinished)
    {
        stepsToMove--;
        targetReached = guardMoving->step();
        
        /*if(guardMoving->getPosition() == myPlayer.getPosition() && board.getCardType(myPlayer.getPosition())==LAVATORY && tokens.isThereAStealthToken(myPlayer.getPosition()))
        {
            vector<string>msgToShow({LAVATORY_TEXT,USE_LAVATORY_TOKEN_TEXTB,USE_MY_STEALTH_TOKEN_TEXTB});
            string userChoice = controller->askForSpentOK(msgToShow);
            if(userChoice ==USE_MY_STEALTH_TOKEN_TEXTB)
                myPlayer.decLives();
            else if(userChoice ==USE_LAVATORY_TOKEN_TEXTB)
                tokens.useLavatoryToken();
        }
         else*/ if(guardMoving->getPosition() == myPlayer.getPosition() && !myPlayer.isOnHelicopter())   //Si el guardia entra al tile del player y no se encuentra en el helicoptero, el mismo pierde una vida.
            myPlayer.decLives();
        /*if(guards[floor].getPosition() == otherPlayer.getPosition() && board.getCardType(otherPlayer.getPosition())==LAVATORY && tokens.isThereAStealthToken(otherPlayer.getPosition()))
        {
            vector<string>msgToShow({LAVATORY_TEXT,USE_LAVATORY_TOKEN_TEXTB,USE_MY_STEALTH_TOKEN_TEXTB});
            string userChoice = controller->askForSpentOK(msgToShow);
            if(userChoice ==USE_MY_STEALTH_TOKEN_TEXTB)
                otherPlayer.decLives();
            else if(userChoice ==USE_LAVATORY_TOKEN_TEXTB)
                tokens.useLavatoryToken();
        }
         else*/ if(guardMoving->getPosition() == otherPlayer.getPosition() && !otherPlayer.isOnHelicopter())
            otherPlayer.decLives();
        if(board.isCardVisible(guardMoving->getPosition()))
        {   
            if(board.getCardType(guardMoving->getPosition()) == CAMERA && board.getCardType(myPlayer.getPosition()) == CAMERA && board.isCardVisible(myPlayer.getPosition()))   //Si un guardia se mueve a una camara y hay un player en una camara
                if(board.getCardType(guardMoving->getPosition()) != board.getCardType(myPlayer.getPosition()))      //Y ese player no está en la misma camara que el guardia
                {   tokens.triggerAlarm(myPlayer.getPosition()); setGuardsNewPath(myPlayer.getPosition().floor); }  //Triggerea una alarma en el piso que se encuentra 
            if(board.getCardType(guardMoving->getPosition()) == CAMERA && board.getCardType(otherPlayer.getPosition()) == CAMERA && board.isCardVisible(otherPlayer.getPosition()))
                if(guardMoving->getPosition() != otherPlayer.getPosition())
                {   tokens.triggerAlarm(otherPlayer.getPosition()); setGuardsNewPath(otherPlayer.getPosition().floor); }
        }
        /*Si un player esta sobre un atrium dado vuelta, y el guardia pasa un piso arriba o abajo de ese player, este pierde una vida*/
        if(board.getCardType(myPlayer.getPosition()) == ATRIUM && board.isCardVisible(myPlayer.getPosition()) && (board.isCardDownstairs(myPlayer.getPosition(), guardMoving->getPosition()) || board.isCardUpstairs(myPlayer.getPosition(), guardMoving->getPosition())))
            myPlayer.decLives();
        if(board.getCardType(otherPlayer.getPosition()) == ATRIUM && board.isCardVisible(otherPlayer.getPosition()) && (board.isCardDownstairs(otherPlayer.getPosition(), guardMoving->getPosition()) || board.isCardUpstairs(otherPlayer.getPosition(), guardMoving->getPosition())))
            otherPlayer.decLives();
        /*Si un player esta sobre un Foyer dado vuelta, y el guardia se encuentra en un tile adyacente, este pierde una vida*/
        if(board.getCardType(myPlayer.getPosition()) == FOYER && board.isCardVisible(myPlayer.getPosition()) && board.adjacentCards(myPlayer.getPosition(), guardMoving->getPosition()))
            myPlayer.decLives();
        if(board.getCardType(otherPlayer.getPosition()) == FOYER && board.isCardVisible(otherPlayer.getPosition()) && board.adjacentCards(otherPlayer.getPosition(), guardMoving->getPosition()))
            otherPlayer.decLives();
        /*Armo el paquete para informar del movimiento:*/
        auxiliarInfoToReport.meaning=GUARD_STEP_TO;        //Se hizo un movimiento de guardia
        auxiliarInfoToReport.cardLocation=guardMoving->getPosition();   //A la posición que está ahora
        guardMovement.push_back(auxiliarInfoToReport);  //pusheo
        /*Si el guardia llegó a la posición objetivo, busca un nuevo objetivo*/
        if(targetReached)
        {
            if(tokens.isThereAToken(guardMoving->getPosition(), ALARM_TOKEN))
                tokens.turnOffAlarm(guardMoving->getPosition());
            list<CardLocation> cardsTaken=setGuardsNewPath(guardFloor); //Setea un nuevo path y devuelve la lista de cartas que tomó del mazo. ( pueden ser 1 o 2 si tomo una carta que apuntaba a donde estaba parado).
            auxiliarInfoToReport.meaning=GUARD_CARD_PICK;   
            for(list<CardLocation>::iterator it=cardsTaken.begin(); it!=cardsTaken.end();it++)
            {
                auxiliarInfoToReport.cardLocation=*it;
                guardMovement.push_back(auxiliarInfoToReport);  //Guardo que cartas se tomaron del mazo.
            }
        }
        /*Si había un crow token en el tile donde se encuentra*/
        if(tokens.isThereAToken(guardMoving->getPosition(), CROW_TOKEN) && stepsToMove > 0)
            stepsToMove--;
        view->update(this);
        checkIfWonOrLost();
        sleep(0.2);         //Esto despues cambiará (es bloqueante)
    }
    
}
void BurgleBrosModel::copyGuardMove(list<GuardMoveInfo> &guardMovement)
{
    GuardMoveInfo auxiliarInfoToReport;
    unsigned int guardFloor= getP2Player(playerOnTurnBeforeGuardMove)->getPosition().floor;   //Obtengo la posición del 
    BurgleBrosGuard *guardMoving = &(guards[guardFloor]);
    if(tokens.isThereAnAlarmToken(guardMoving->getPosition()))     //Si hay una alarma en su posición ya la desactiva y busca un nuevo camino.
        tokens.turnOffAlarm(guardMoving->getPosition());
    if(myPlayer.getCharacter()== THE_ACROBAT && myPlayer.getPosition() == guardMoving->getPosition()) // Si un acrobat termina su turno en el tile del guardia PERDERA LA CABEZA! digo un stealth token.
        myPlayer.decLives();
    if(otherPlayer.getCharacter()== THE_ACROBAT && otherPlayer.getPosition() == guardMoving->getPosition())
        otherPlayer.decLives();
    for(list<GuardMoveInfo>::iterator it=guardMovement.begin(); it!=guardMovement.end() && !gameFinished; it++)
    {
        if(it->meaning==GUARD_STEP_TO)
        {
            guardMoving->setPosition(it->cardLocation);
            if(tokens.isThereAnAlarmToken(guardMoving->getPosition()))     //Si hay una alarma en su posición ya la desactiva y busca un nuevo camino.
                tokens.turnOffAlarm(guardMoving->getPosition());
            //Se comentó porque hay que ver que pasa con los paquetes.
            /*if(guardMoving->getPosition() == myPlayer.getPosition() && board.getCardType(myPlayer.getPosition())==LAVATORY && tokens.isThereAStealthToken(myPlayer.getPosition()))
            {
                vector<string>msgToShow({LAVATORY_TEXT,USE_LAVATORY_TOKEN_TEXTB,USE_MY_STEALTH_TOKEN_TEXTB});
                string userChoice = controller->askForSpentOK(msgToShow);
                if(userChoice ==USE_MY_STEALTH_TOKEN_TEXTB)
                    myPlayer.decLives();
                else if(userChoice ==USE_LAVATORY_TOKEN_TEXTB)
                    tokens.useLavatoryToken();
            }
            else*/ if(guardMoving->getPosition() == myPlayer.getPosition() && !myPlayer.isOnHelicopter())   //Si el guardia entra al tile del player, el mismo pierde una vida.
                myPlayer.decLives();
            /*if(guards[floor].getPosition() == otherPlayer.getPosition() && board.getCardType(otherPlayer.getPosition())==LAVATORY && tokens.isThereAStealthToken(otherPlayer.getPosition()))
            {
                vector<string>msgToShow({LAVATORY_TEXT,USE_LAVATORY_TOKEN_TEXTB,USE_MY_STEALTH_TOKEN_TEXTB});
                string userChoice = controller->askForSpentOK(msgToShow);
                if(userChoice ==USE_MY_STEALTH_TOKEN_TEXTB)
                    otherPlayer.decLives();
                else if(userChoice ==USE_LAVATORY_TOKEN_TEXTB)
                    tokens.useLavatoryToken();
            }
             else*/ if(guardMoving->getPosition() == otherPlayer.getPosition() && !otherPlayer.isOnHelicopter())
                otherPlayer.decLives();
            if(board.isCardVisible(guardMoving->getPosition()))
            {   
                if(board.getCardType(guardMoving->getPosition()) == CAMERA && board.getCardType(myPlayer.getPosition()) == CAMERA && board.isCardVisible(myPlayer.getPosition()))   //Si un guardia se mueve a una camara y hay un player en una camara
                    if(guardMoving->getPosition() != myPlayer.getPosition())      //Y ese player no está en la misma camara que el guardia
                    {   tokens.triggerAlarm(myPlayer.getPosition()); setGuardsNewPath(myPlayer.getPosition().floor); }  //Triggerea una alarma en el piso que se encuentra 
                if(board.getCardType(guardMoving->getPosition()) == CAMERA && board.getCardType(otherPlayer.getPosition()) == CAMERA && board.isCardVisible(otherPlayer.getPosition()))
                    if(guardMoving->getPosition() != otherPlayer.getPosition())
                    {   tokens.triggerAlarm(otherPlayer.getPosition()); setGuardsNewPath(otherPlayer.getPosition().floor); }
            }
            /*Si un player esta sobre un atrium dado vuelta, y el guardia pasa un piso arriba o abajo de ese player, este pierde una vida*/
            if(board.getCardType(myPlayer.getPosition()) == ATRIUM && board.isCardVisible(myPlayer.getPosition()) && (board.isCardDownstairs(myPlayer.getPosition(), guardMoving->getPosition()) || board.isCardUpstairs(myPlayer.getPosition(), guardMoving->getPosition())))
                myPlayer.decLives();
            if(board.getCardType(otherPlayer.getPosition()) == ATRIUM && board.isCardVisible(otherPlayer.getPosition()) && (board.isCardDownstairs(otherPlayer.getPosition(), guardMoving->getPosition()) || board.isCardUpstairs(otherPlayer.getPosition(), guardMoving->getPosition())))
                otherPlayer.decLives();
            /*Si un player esta sobre un Foyer dado vuelta, y el guardia se encuentra en un tile adyacente, este pierde una vida*/
            if(board.getCardType(myPlayer.getPosition()) == FOYER && board.isCardVisible(myPlayer.getPosition()) && board.adjacentCards(myPlayer.getPosition(), guardMoving->getPosition()))
                myPlayer.decLives();
            if(board.getCardType(otherPlayer.getPosition()) == FOYER && board.isCardVisible(otherPlayer.getPosition()) && board.adjacentCards(otherPlayer.getPosition(), guardMoving->getPosition()))
                otherPlayer.decLives();   
        }
        else if(it->meaning==GUARD_CARD_PICK)
            guardMoving->drawCardTarget(it->cardLocation);
        view->update(this);
        checkIfWonOrLost();
        sleep(0.2);         //Esto despues cambiará (es bloqueante)
    }
    setGuardsNewPath(guardFloor, guardMoving->getTargetPosition());//Para que no quede sin un camino  si la próxima vez se ejecuta desde esta cpu.
}
list<CardLocation> BurgleBrosModel::setGuardsNewPath(unsigned int floor)
{
    list<CardLocation> retVal;
    list<CardLocation> alarmList = tokens.getAlarmsList();
    list<AuxStruct> alarmsOnSameFloor;
    CardLocation newTargetLocation;
    unsigned int aux=0;
    for(list<CardLocation>::iterator it=alarmList.begin(); it !=alarmList.end(); it++)
    {
        AuxStruct aux;
        if(it->floor == floor)
        {
             aux.target=*it;
             alarmsOnSameFloor.push_back(aux);       //Obtengo las alarmas que están en el mismo piso  
        }
    }
    if(!alarmsOnSameFloor.empty())          //Si hay alarmas en su piso
    {
        for(list<AuxStruct>::iterator it=alarmsOnSameFloor.begin(); it !=alarmsOnSameFloor.end(); it++)
            it->length=board.getShortestPathLength(guards[floor].getPosition(), it->target);    //obtengo el largo de cada camino.
        alarmsOnSameFloor.sort(sortAuxStruct);  //las ordeno por el camino mas corto
        for(list<AuxStruct>::iterator it=alarmsOnSameFloor.begin(); it !=alarmsOnSameFloor.end(); it++) 
        {
            if(it->length == alarmsOnSameFloor.front().length)
                aux++;  //Cuento cuantas alarmas estan a la misma distancia.
        }
        if(aux==1)  //Si hay una que este a la minima distancia
            newTargetLocation=alarmsOnSameFloor.front().target; //Esa va a ser el nuevo objetivo
        else
        {
            int temp = rand() % aux;            //Sino, se elige random entre las que tienen el mismo largo de camino
            list<AuxStruct>::iterator it = alarmsOnSameFloor.begin();
            advance(it, temp);
            newTargetLocation = it->target;
        }
    }
    else        //Si no había alarmas, se toma una carta  que no sea en la que esté parado
    {
        do{
            newTargetLocation = guards[floor].drawCardTarget();     //Toma una nueva carta objetivo
            retVal.push_back(newTargetLocation);                //la guarda en el retval
        }while(newTargetLocation == guards[floor].getPosition());      //si era la misma posición que la del guardia, saca otra carta del mazo.
    }
    guards[floor].setNewTarget(newTargetLocation);
    list<CardLocation> temp = board.getShortestPath(guards[floor].getPosition(), newTargetLocation);
    guards[floor].setNewPathToTarget(temp);
    return retVal;
}
list<CardLocation> BurgleBrosModel::setGuardsNewPath(unsigned int floor, CardLocation thisTarget)
{
    list<CardLocation> retVal;
    list<CardLocation> alarmList = tokens.getAlarmsList();
    list<AuxStruct> alarmsOnSameFloor;
    CardLocation newTargetLocation;
    unsigned int aux=0;
    for(list<CardLocation>::iterator it=alarmList.begin(); it !=alarmList.end(); it++)
    {
        AuxStruct aux;
        if(it->floor == floor)
        {
             aux.target=*it;
             alarmsOnSameFloor.push_back(aux);       //Obtengo las alarmas que están en el mismo piso  
        }
    }
    if(!alarmsOnSameFloor.empty())          //Si hay alarmas en su piso
    {
        for(list<AuxStruct>::iterator it=alarmsOnSameFloor.begin(); it !=alarmsOnSameFloor.end(); it++)
            it->length=board.getShortestPathLength(guards[floor].getPosition(), it->target);    //obtengo el largo de cada camino.
        alarmsOnSameFloor.sort(sortAuxStruct);  //las ordeno por el camino mas corto
        for(list<AuxStruct>::iterator it=alarmsOnSameFloor.begin(); it !=alarmsOnSameFloor.end(); it++) 
        {
            if(it->length == alarmsOnSameFloor.front().length)
                aux++;  //Cuento cuantas alarmas estan a la misma distancia.
        }
        if(aux==1)  //Si hay una que este a la minima distancia
            newTargetLocation=alarmsOnSameFloor.front().target; //Esa va a ser el nuevo objetivo
        else
        {
            int temp = rand() % aux;            //Sino, se elige random entre las que tienen el mismo largo de camino
            list<AuxStruct>::iterator it = alarmsOnSameFloor.begin();
            advance(it, temp);
            newTargetLocation = it->target;
        }
    }
    else        //Si no había alarmas, se toma una carta  que no sea en la que esté parado
        newTargetLocation = thisTarget;  //si era la misma posición que la del guardia, saca otra carta del mazo.
    guards[floor].setNewTarget(newTargetLocation);
    list<CardLocation> temp = board.getShortestPath(guards[floor].getPosition(), newTargetLocation);
    guards[floor].setNewPathToTarget(temp);
    return retVal;
}
void BurgleBrosModel::triggerSilentAlarm(unsigned int floor)
{
    for(int i=floor; i >= 0; i--)
    {
        guards[i].incDiceNumber();
    }
}

bool BurgleBrosModel::dieForLootNeeded() //Si es necesario tirar un dado para el chihuahua o persian kitty
{
    bool retVal=false;
    BurgleBrosPlayer *p=getP2Player(getPlayerOnTurn());
    if((p->hasLoot(PERSIAN_KITTY) || p->hasLoot(CHIHUAHUA))  && status==WAITING_DICE_FOR_LOOT && rollForLootCount==0) //Si se esperaba por el dice for loot y todavía no se tiraron los dados si
        retVal=true;
    else if(p->hasLoot(PERSIAN_KITTY) && p->hasLoot(CHIHUAHUA) && status==WAITING_DICE_FOR_LOOT && rollForLootCount==1 && board.canKittyMove(p->getPosition()))
        retVal=true; //Tambien si tenía los dos loots y tiró por el chihuahua, y ahora si el kitty puede moverse se tiene
    return retVal;
}
void BurgleBrosModel::continueGame()        //Si el juego estaba parado por los dados para el loot, se le dice que continúe.
{
    rollForLootCount=0;
    status=WAITING_FOR_ACTION;
}

unsigned int BurgleBrosModel::rollDieForLoot(unsigned int die)
{
    BurgleBrosPlayer *p=getP2Player(getPlayerOnTurn());
    if(p->hasLoot(PERSIAN_KITTY) && !p->hasLoot(CHIHUAHUA))     //Si tiene persian kitty y no chihuahua
        handlePersianKittyMove(die);
    else if(!p->hasLoot(PERSIAN_KITTY) && p->hasLoot(CHIHUAHUA))    //SI tiene chihuahua y no tiene persian kitty
        handleChihuahuaMove(die);
    else if(p->hasLoot(PERSIAN_KITTY) && p->hasLoot(CHIHUAHUA))     //Si tiene los 2.
    {
        if(rollForLootCount==0)
            handleChihuahuaMove(die);
        else
            handlePersianKittyMove(die);
    }
    return dice.getCurrDice().front();
}

void BurgleBrosModel::handlePersianKittyMove(unsigned int die)
{
    BurgleBrosPlayer *p=getP2Player(getPlayerOnTurn());
    if(p->isItsTurn() && p->hasLoot(PERSIAN_KITTY) && board.canKittyMove(p->getPosition()))   
    {
        bool itWillMove;
        if(getPlayerOnTurn()==THIS_PLAYER)      //Si es este jugador tira los dados
            itWillMove=dice.persianKittyShallMove();
        else if(getPlayerOnTurn()==OTHER_PLAYER)    //SIno pone el dado recibido
            itWillMove=dice.persianKittyShallMove(die);
        if(itWillMove)
        {
            p->deattachLoot(PERSIAN_KITTY);
            loots.setNewLootOwner(PERSIAN_KITTY,NON_PLAYER);
            pair<bool, CardLocation> persianKittyToken;
            persianKittyToken.first = true;
            persianKittyToken.second = board.getKittyMovingPos(p->getPosition());
            tokens.placePersianKittyToken(persianKittyToken);
        }
        view->update(this);
    }
    rollForLootCount++;
}
void BurgleBrosModel::handleChihuahuaMove(unsigned int die)
{
    BurgleBrosPlayer *p=getP2Player(getPlayerOnTurn());
    if(p->isItsTurn() && p->hasLoot(CHIHUAHUA))
    {
        bool itWillBark;
        if(getPlayerOnTurn()==THIS_PLAYER)  //SI es este jugador tira los dados
            itWillBark=dice.chihuahuaBarks();
        else if(getPlayerOnTurn()==OTHER_PLAYER)
            itWillBark=dice.chihuahuaBarks(die);    //SIno, tira los dados recibidos.
        if(itWillBark)
        {
            tokens.triggerAlarm(p->getPosition());
            setGuardsNewPath(p->getPosition().floor);
        }
        view->update(this);
    }
    rollForLootCount++;
}
BurgleBrosModel::~BurgleBrosModel()
{
}
