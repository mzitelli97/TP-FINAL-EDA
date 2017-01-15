#include "BurgleBrosModel.h"
#include "BurgleBrosView.h"
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
    myPlayer.pickRandomPlayer();
    otherPlayer.pickRandomPlayer(myPlayer.getCharacter());
    myPlayer.setTurn(true);
    myPlayer.setName("PEPE");
    otherPlayer.setTurn(false);
    otherPlayer.setName("COQUI");
    
    guards[0].init();
    list<CardLocation> path = board.getShortestPath(guards[0].getPosition(), guards[0].getTargetPosition());
    guards[0].setNewPathToTarget(path );
    playerSpentFreeAction=false;
    
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
    }
    return info;
}
Info2DrawPlayer BurgleBrosModel:: getInfo2DrawPlayer(ActionOrigin player)
{
    Info2DrawPlayer info;
    BurgleBrosPlayer * p = getP2Player(player);
    info.name=p->getName();
    info.character=p->getCharacter();
    info.lives=p->getCurrLifes();
    info.position=p->getPosition();
    info.currActions=p->getcurrentActions();
    info.turn = p->isItsTurn();
    return info;
}


vector<unsigned int> BurgleBrosModel::getInfo2DrawExtraDices()
{
    return dice.getCurrDice();
}

ActionOrigin BurgleBrosModel::getPlayerOnTurn()
{
    if(myPlayer.isItsTurn())
        return THIS_PLAYER_ACTION;
    else
        return OTHER_PLAYER_ACTION;
}
bool BurgleBrosModel::pass(ActionOrigin playerId)
{
    bool retVal=false;
    BurgleBrosPlayer * p=getP2Player(playerId);
    if(p->isItsTurn())
    {
        while(p->getcurrentActions())
            p->decActions();
        if(board.getCardType(p->getPosition()) == THERMO)
        {   tokens.triggerAlarm(p->getPosition()); setGuardsNewPath(p->getPosition().floor);}
        checkTurns();
        view->update(this);
    }
    return retVal;
}
bool BurgleBrosModel::peek(ActionOrigin playerId, CardLocation locationToPeek)
{
    bool retVal=false;
    BurgleBrosPlayer *p=getP2Player(playerId);
    if(isPeekPosible(playerId, locationToPeek))
    {
        board.setCardVisible(locationToPeek);
        if(p->getCharacter() == THE_HAWK && playerSpentFreeAction==false && board.isAWallBetween(p->getPosition(), locationToPeek))
            playerSpentFreeAction=true;
        else
            p->decActions();
        if(board.getCardType(locationToPeek)==LAVATORY)
            tokens.lavatoryRevealed(locationToPeek); 
        checkTurns();
        view->update(this);
        retVal=true;      
    }
    return retVal;  
}
bool BurgleBrosModel::move(ActionOrigin playerId, CardLocation locationToMove)
{
    bool retVal=false;

    if(isMovePosible(playerId, locationToMove))
    {
        BurgleBrosPlayer* movingPlayer=getP2Player(playerId);
        BurgleBrosPlayer* playerNotMoving=getP2OtherPlayer(playerId);
        CardLocation prevLocation=movingPlayer->getPosition();
        CardName newCardType=board.getCardType(locationToMove);
        bool cardWasVisible=true;
        
        if( !board.isCardVisible(locationToMove) )
        {
            board.setCardVisible(locationToMove);
            cardWasVisible=false;
        }    
        movingPlayer->decActions();
        movingPlayer->setPosition(locationToMove);
        
        /*Si me moví a otro piso y en ese piso el guardia no estaba inicializado, lo inicializo*/
        if(!guards[movingPlayer->getPosition().floor].checkIfInitialized())
        {
            guards[movingPlayer->getPosition().floor].init();
            list<CardLocation> path = board.getShortestPath(guards[movingPlayer->getPosition().floor].getPosition(), guards[movingPlayer->getPosition().floor].getTargetPosition());
            guards[movingPlayer->getPosition().floor].setNewPathToTarget(path);
        }
        
        //Cambios segun el lugar desde el que me muevo
        if(board.getCardType(prevLocation)==MOTION && board.isMotionActivated())
        {
            if(tokens.howManyTokensOnCPURoom(COMPUTER_ROOM_MOTION))
            {
                std::vector<string> msgToShow({MOTION_TEXT,USE_HACK_TOKEN_TEXTB,TRIGGER_ALARM_TEXTB});//STAY????
                string userChoice = controller->askForSpentOK(msgToShow);
                if(userChoice==USE_HACK_TOKEN_TEXTB)
                    tokens.removeOneHackTokenOf(COMPUTER_ROOM_MOTION);
                else if(userChoice==TRIGGER_ALARM_TEXTB)
                    tokens.triggerAlarm(prevLocation);
            }
            else 
                tokens.triggerAlarm(prevLocation);
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
            else 
            {
                std::vector<string> msgToShow({DEADBOLT_TEXT,SPEND_ACTIONS_TEXTB,GET_BACK_TEXTB});
                string userChoice = controller->askForSpentOK(msgToShow);
                if(userChoice==SPEND_ACTIONS_TEXTB)//decide gastar las acciones y entra
                {
                    for(unsigned int i=0;i<2;++i)//PODRIA SER UN DEFINE EL 2
                        movingPlayer->decActions();
                }
                else if(userChoice==GET_BACK_TEXTB)//decide no gastar las acciones y vuelve atras
                    movingPlayer->setPosition(prevLocation);
            }
                
        }    
        //Si quiero entrar a un keypad y no esta abierto tengo que tirar los dados (el numero de dados se corresponde con los intentos en el mismo turno)
        if( newCardType==KEYPAD && !tokens.isThereAKeypadToken(locationToMove))
        {
            bool keyCracked=false;
            if(movingPlayer->getCharacter()==THE_PETERMAN)
                keyCracked=dice.throwDiceForKeypadWithExtraDie(locationToMove);
            else
                keyCracked=dice.throwDiceForKeypad(locationToMove);
            if(keyCracked)
                tokens.putKeyPadToken(locationToMove);
            else
            {
                dice.addDieToKeypad(locationToMove);
                movingPlayer->setPosition(prevLocation);
            }
        }
        
        if(movingPlayer->getCharacter()!=THE_HACKER && ( playerNotMoving->getCharacter()!=THE_HACKER || (playerNotMoving->getCharacter()==THE_HACKER && locationToMove!= playerNotMoving->getPosition() ) ))
        {    
        if( newCardType==FINGERPRINT)//hay que arreglar el tema de cuando hace click en la cruz del native message
        {
               if(tokens.howManyTokensOnCPURoom(COMPUTER_ROOM_FINGERPRINT) )//Si hay tokens disponibles
               {
                  std::vector<string> msgToShow({ENTER_FINGERPRINT_TEXT,USE_HACK_TOKEN_TEXTB,TRIGGER_ALARM_TEXTB});  //Esto contiene el título del cartelito, subtitulo y texto, por eso vector
                  string userChoice = controller->askForSpentOK(msgToShow);
                  if(userChoice==USE_HACK_TOKEN_TEXTB)// clickeo "use hack token" 
                       tokens.removeOneHackTokenOf(COMPUTER_ROOM_FINGERPRINT);
                  else if(userChoice==TRIGGER_ALARM_TEXTB)//clickeo "trigger alarm"
                  {
                        tokens.triggerAlarm(locationToMove);
                        setGuardsNewPath(locationToMove.floor); //Así se pone el dado a donde tiene que ir, este lo necesitaba desde el guardia
                  }
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
            else
            {
                std::vector<string> msgToShow({LASER_TEXT,TRIGGER_ALARM_TEXTB}); 
                if(tokens.howManyTokensOnCPURoom(COMPUTER_ROOM_LASER))
                    msgToShow.push_back(USE_HACK_TOKEN_TEXTB);
                if(movingPlayer->getcurrentActions())
                    msgToShow.push_back(SPEND_ACTION_TEXTB);
                string userChoice=controller->askForSpentOK(msgToShow);
                if(userChoice==TRIGGER_ALARM_TEXTB)
                {    tokens.triggerAlarm(locationToMove); setGuardsNewPath(locationToMove.floor);}
                else if(userChoice==USE_HACK_TOKEN_TEXTB)
                    tokens.removeOneHackTokenOf(COMPUTER_ROOM_LASER);
                else if(userChoice==SPEND_ACTION_TEXTB)
                    movingPlayer->decActions();
            }
        }
        }
        
        if(newCardType==LAVATORY)
        {
            if(!cardWasVisible)
                tokens.lavatoryRevealed(locationToMove);

            if(locationToMove==guards[locationToMove.floor].getPosition() && tokens.isThereAStealthToken(locationToMove))
            {
                vector<string>msgToShow({LAVATORY_TEXT,USE_LAVATORY_TOKEN_TEXTB,USE_MY_STEALTH_TOKEN_TEXTB});
                string userChoice = controller->askForSpentOK(msgToShow);
                if(userChoice ==USE_MY_STEALTH_TOKEN_TEXTB)
                    movingPlayer->decLives();
                else if(userChoice ==USE_LAVATORY_TOKEN_TEXTB)
                    tokens.useLavatoryToken();
            }    
            else if(locationToMove==guards[locationToMove.floor].getPosition() && !tokens.isThereAStealthToken(locationToMove))
                movingPlayer->decLives();
        }    
        
        
        if( newCardType==SCANNER_DETECTOR && movingPlayer->carriesLoot())
            tokens.triggerAlarm(locationToMove);
        
        if(newCardType==THERMO && ( movingPlayer->getcurrentActions()==0 || movingPlayer->hasLoot(ISOTOPE)))
            tokens.triggerAlarm(locationToMove);
        
        if(newCardType==WALKAWAY && !cardWasVisible && locationToMove.floor>0)
        {   
            CardLocation downStairsLocation={locationToMove.floor-1,locationToMove.row,locationToMove.column};
            movingPlayer->setPosition(downStairsLocation);
        }

        checkTurns();
        view->update(this);
        retVal=true;
    }
    return retVal;
}
bool BurgleBrosModel::addToken(ActionOrigin playerId, CardLocation locationToAddToken)
{
    bool retVal=false;
    BurgleBrosPlayer* movingPlayer=getP2Player(playerId);
    if(isAddTokenPosible(playerId, locationToAddToken))
    {
        tokens.addHackTokenOn(board.getCardType(locationToAddToken));
        movingPlayer->decActions();
        checkTurns();
        view->update(this);
        retVal=true;
    }
    return retVal;
}
bool BurgleBrosModel::addDieToSafe(ActionOrigin playerId, CardLocation safe)
{
    bool retVal=false;
    BurgleBrosPlayer* p= getP2Player(playerId);
    if(isAddDieToSafePossible(playerId, safe))
    {
        p->decActions();
        p->decActions();
        dice.addDieToSafe(safe.floor); 
        checkTurns();
        view->update(this);
        retVal=true;
    }
    return retVal;
}
bool BurgleBrosModel::crackSafe(ActionOrigin playerId, CardLocation safe)
{
    bool retVal=false;
    BurgleBrosPlayer* p= getP2Player(playerId);
    if(isCrackSafePossible(playerId,safe))
    {
        p->decActions();                //Cuesta una acción hacer un creack
        vector<unsigned int> aux;
        if(p->getCharacter() == THE_PETERMAN)       //Si es peterman tira con un dado extra
            aux=dice.throwDiceForSafeWithExtraDie(safe.floor);
        else                                        //Sino tira los dados normales
            aux=dice.throwDiceForSafe(safe.floor);
        list<CardLocation> tilesCrackedOnThisAction = board.tilesWithCracked(aux,safe.floor);   //Obtengo las cartas que tienen como safe number uno de los numeros que salio en el dado
        tokens.addCrackTokenOn(tilesCrackedOnThisAction);
        if(tokens.isSafeOpened(safe.floor))
        {
            Loot lootGotten =loots.getLoot(playerId);
            p->attachLoot(lootGotten);
            if(lootGotten==GOLD_BAR)
                loots.setGoldBardLocation(safe);
            if(lootGotten==CURSED_GOBLET && p->getCurrLifes()>1)
                p->decLives();
            board.setSafeCracked(safe.floor);
            triggerSilentAlarm(safe.floor);
        }
        view->update(this);
        checkTurns();
        retVal=true;
    }
    return retVal;        
}

bool BurgleBrosModel::createAlarm(ActionOrigin playerId, CardLocation tile)
{
    bool retVal=false;
    if(isCreateAlarmPossible(playerId,tile))
    {
        playerSpentFreeAction=true;
        tokens.triggerAlarm(tile);
        setGuardsNewPath(tile.floor);
        retVal=true;
    }
    return retVal;
}
bool BurgleBrosModel::placeCrow(ActionOrigin playerId, CardLocation tile)
{
    bool retVal=false;
    if(isPlaceCrowPossible(playerId,tile))
    {
        tokens.placeCrowToken(tile);
        playerSpentFreeAction=true;
    }
    return retVal;
}
bool BurgleBrosModel::pickLoot(ActionOrigin playerId, CardLocation tile, Loot lootToPick)
{
    bool retVal=false;
    BurgleBrosPlayer *p= getP2Player(playerId);
    if(isPickLootPossible(playerId,tile, lootToPick))
    {
        if(lootToPick==PERSIAN_KITTY)          //Si es el persian kitty
        {
            pair<bool, CardLocation> kittyInfo;
            kittyInfo.first= false;
            tokens.placePersianKittyToken(kittyInfo);
            loots.setNewLootOwner(PERSIAN_KITTY, playerId);
            p->attachLoot(PERSIAN_KITTY);
            retVal=true;
        }
        else if(lootToPick==GOLD_BAR)
        {
            loots.pickGoldBarOnFloor(playerId, tile);
            p->attachLoot(GOLD_BAR);
            retVal=true;
        }
    }
    return retVal;
}

bool BurgleBrosModel::askForLoot(ActionOrigin playerId, CardLocation tile, Loot loot)
{
    bool retVal = false;
    if(isAskForLootPossible(playerId,tile,loot))
    {
        std::vector<string> msgToShow({ASK_FOR_LOOT_TEXT+loot2Str(loot),ACCEPT_TEXTB,DECLINE_TEXTB}); 
        string userChoice=controller->askForSpentOK(msgToShow);
        if(userChoice==ACCEPT_TEXTB)
        {    
            getP2Player(playerId)->attachLoot(loot);
            getP2OtherPlayer(playerId)->deattachLoot(loot);
            loots.setNewLootOwner(loot,playerId);
            view->update(this);
        }
    }
}

bool BurgleBrosModel::offerLoot(ActionOrigin playerId, CardLocation tile, Loot loot)
{
    bool retVal = false;
    if(isOfferLootPossible(playerId,tile,loot))
    {
        std::vector<string> msgToShow({OFFER_LOOT_TEXT+loot2Str(loot),ACCEPT_TEXTB,DECLINE_TEXTB}); 
        string userChoice=controller->askForSpentOK(msgToShow);
        if(userChoice==ACCEPT_TEXTB)
        {    
            getP2OtherPlayer(playerId)->attachLoot(loot);
            getP2Player(playerId)->deattachLoot(loot);
            loots.setNewLootOwner(loot,playerId==THIS_PLAYER_ACTION?OTHER_PLAYER_ACTION:THIS_PLAYER_ACTION);
            view->update(this);
        }
    }
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
    if(myPlayer.isItsTurn() && myPlayer.getcurrentActions() == 0)
    {
        if(board.getCardType(myPlayer.getPosition()) == THERMO)
            tokens.triggerAlarm(myPlayer.getPosition());
        myPlayer.setTurn(false);
        myPlayer.setActions(INIT_NMBR_OF_LIVES);
        if(myPlayer.hasLoot(MIRROR))
            myPlayer.setActions(INIT_NMBR_OF_LIVES-1);
        moveGuard(myPlayer.getPosition().floor);
        otherPlayer.setTurn(true);
        handlePersianKittyMove(OTHER_PLAYER_ACTION);
        handleChihuahuaMove(OTHER_PLAYER_ACTION);
        playerSpentFreeAction=false;
        dice.resetKeypadsDice();
        board.deActivateMotion();
    }
    if(otherPlayer.isItsTurn() && otherPlayer.getcurrentActions() == 0)
    {
        if(board.getCardType(myPlayer.getPosition()) == THERMO)
            tokens.triggerAlarm(myPlayer.getPosition());
        otherPlayer.setTurn(false);
        otherPlayer.setActions(INIT_NMBR_OF_LIVES);
        if(otherPlayer.hasLoot(MIRROR))
            otherPlayer.setActions(INIT_NMBR_OF_LIVES-1);
        moveGuard(otherPlayer.getPosition().floor);
        myPlayer.setTurn(true);
        handlePersianKittyMove(THIS_PLAYER_ACTION);
        handleChihuahuaMove(THIS_PLAYER_ACTION);
        playerSpentFreeAction=false;
        dice.resetKeypadsDice();
        board.deActivateMotion();
    }
}

 bool BurgleBrosModel::isMovePosible(ActionOrigin playerId,CardLocation tileToMove)
 {
     BurgleBrosPlayer * playerMoving = getP2Player(playerId);
     CardLocation playerMovingPos= playerMoving->getPosition();
     bool retVal=false;
     if(playerMoving->isItsTurn())
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
 bool BurgleBrosModel:: isPeekPosible(ActionOrigin player, CardLocation tile)
{
    bool retVal=false;
    BurgleBrosPlayer* p=getP2Player(player);
    if(p->isItsTurn() && (!board.isCardVisible(tile)))
    {
        if(board.adjacentCards(p->getPosition(),tile))
            retVal=true;
        else if(p->getCharacter()==THE_HAWK && board.isAWallBetween(p->getPosition(),tile))//HACER FUNCION WALLLSEPARATES
            retVal=true;
        else if( board.getCardType(p->getPosition())== ATRIUM && ( board.isCardUpstairs(p->getPosition(),tile) || board.isCardDownstairs(p->getPosition(),tile) ) )
            retVal=true;
        else if( board.getCardType(p->getPosition())== STAIR && board.isCardUpstairs(p->getPosition(),tile)  )
            retVal=true;
    }
    return retVal;
}
bool BurgleBrosModel::isAddTokenPosible(ActionOrigin player, CardLocation tile)
{
    bool retVal=false;
    BurgleBrosPlayer* p;
    p = getP2Player(player);
    if(p->isItsTurn() && (board.isCardVisible(tile)) && p->getPosition() == tile)
    {
        if(IS_COMPUTER_ROOM(board.getCardType(tile)) && tokens.howManyTokensOnCPURoom(board.getCardType(tile)) < MAX_HACK_TOKENS_ON_COMPUTER_ROOM)
            retVal=true;
    }
    return retVal;
}
bool BurgleBrosModel::isAddDieToSafePossible(ActionOrigin player, CardLocation tile)
{
    bool retVal=false;
    BurgleBrosPlayer* p;
    p = getP2Player(player);
    if(p->isItsTurn() && p->getcurrentActions()>= 2 && board.getCardType(p->getPosition())==SAFE && p->getPosition()==tile)
    {
        if(board.canSafeBeCracked(tile.floor) && !board.isSafeCracked(tile.floor) && dice.getSafeDiceCount(tile.floor) < MAX_NMBR_OF_EXTRA_DICES)
            retVal=true;
    }
    return retVal;
}
bool BurgleBrosModel::isCrackSafePossible(ActionOrigin playerId, CardLocation safe)
{
    bool retVal=false;
    BurgleBrosPlayer* p = getP2Player(playerId);
    if(p->isItsTurn()&& board.getCardType(p->getPosition())==SAFE && p->getPosition()==safe)
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
bool BurgleBrosModel::isCreateAlarmPossible(ActionOrigin playerId, CardLocation tile)
{
    bool retVal=false;
    BurgleBrosPlayer* p=getP2Player(playerId);
    if(p->isItsTurn() && p->getCharacter() == THE_JUICER && playerSpentFreeAction==false && board.adjacentCards(p->getPosition(),tile))
        retVal=true;
    return retVal;
}
bool BurgleBrosModel::isPlaceCrowPossible(ActionOrigin playerId, CardLocation tile)
{
    bool retVal=false;
    BurgleBrosPlayer* p=getP2Player(playerId);
    if(p->getCharacter()== THE_RAVEN && tile.floor == p->getPosition().floor && board.getShortestPathLength(p->getPosition(), tile) <= 2 && playerSpentFreeAction==false)
    {
        retVal=true;
        if(tokens.getCrowToken().first && tokens.getCrowToken().second==tile)
            retVal=false;
    }
    return retVal;
}

bool BurgleBrosModel::isAskForLootPossible(ActionOrigin playerId, CardLocation tile, Loot loot)
{
    bool retVal = false;
    BurgleBrosPlayer * p = getP2Player(playerId);
    BurgleBrosPlayer * o = getP2OtherPlayer(playerId);
    if(p->isItsTurn() && p->getPosition() == tile && o->getPosition() == tile && o->hasLoot(loot))
    {
        retVal = true;
        if(loot == GOLD_BAR && p->hasLoot(loot))
            retVal = false;
    }
    return retVal;
}

bool BurgleBrosModel::isOfferLootPossible(ActionOrigin playerId, CardLocation tile, Loot loot)
{
    bool retVal = false;
    BurgleBrosPlayer * p = getP2Player(playerId);
    BurgleBrosPlayer * o = getP2OtherPlayer(playerId);
    if(p->isItsTurn() && p->getPosition() == tile && o->getPosition() == tile && p->hasLoot(loot))
    {
        retVal = true;
        if(loot == GOLD_BAR && o->hasLoot(loot))
            retVal = false;
    }
    return retVal;
}
bool BurgleBrosModel::isPickLootPossible(ActionOrigin playerId, CardLocation tile , Loot lootToPick)
{
    bool retVal = false;
    BurgleBrosPlayer * p = getP2Player(playerId);
    if(p->isItsTurn() && tokens.isThereAPersianKittyToken(tile) || loots.canPlayerPickUpGoldBarOnFloor(playerId,tile))
    {
        if(lootToPick == PERSIAN_KITTY || lootToPick == GOLD_BAR)
            retVal=true;
    }
    return retVal;
}

list<string> BurgleBrosModel::getPosibleActions(ActionOrigin player, CardLocation tile)
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
    return aux;
}
 
BurgleBrosPlayer * BurgleBrosModel::getP2Player(ActionOrigin playerId)
{
    if(playerId==THIS_PLAYER_ACTION)
        return &myPlayer;
    else
        return &otherPlayer;
}
BurgleBrosPlayer * BurgleBrosModel::getP2OtherPlayer(ActionOrigin playerId)
{
    if(playerId==THIS_PLAYER_ACTION)
        return &otherPlayer;
    else
        return &myPlayer;
}
void BurgleBrosModel::moveGuard(unsigned int floor)
{
    /*Falta camera que tengo una duda.*/
    unsigned int stepsToMove= tokens.howManyAlarmsOnFloor(floor) + guards[floor].getDiceNumber(); //El guardia se mueve en su turno los pasos de sus dados + la cantidad de alarmas en su piso
    bool targetReached=false;
    if(stepsToMove>6)
        stepsToMove=6;  //No puede moverse más de 6 pasos.
    if(tokens.isThereAnAlarmToken(guards[floor].getPosition()))
    {
        tokens.turnOffAlarm(guards[floor].getPosition());
        setGuardsNewPath(floor);
    }
    if(myPlayer.getCharacter()== THE_ACROBAT && myPlayer.getPosition() == guards[floor].getPosition())
        myPlayer.decLives();
    if(otherPlayer.getCharacter()== THE_ACROBAT && otherPlayer.getPosition() == guards[floor].getPosition())
        otherPlayer.decLives();
    while(stepsToMove!=0)
    {
        stepsToMove--;
        targetReached = guards[floor].step();
        
        if(guards[floor].getPosition() == myPlayer.getPosition() && board.getCardType(myPlayer.getPosition())==LAVATORY && tokens.isThereAStealthToken(myPlayer.getPosition()))
        {
            vector<string>msgToShow({LAVATORY_TEXT,USE_LAVATORY_TOKEN_TEXTB,USE_MY_STEALTH_TOKEN_TEXTB});
            string userChoice = controller->askForSpentOK(msgToShow);
            if(userChoice ==USE_MY_STEALTH_TOKEN_TEXTB)
                myPlayer.decLives();
            else if(userChoice ==USE_LAVATORY_TOKEN_TEXTB)
                tokens.useLavatoryToken();
        }
        else if(guards[floor].getPosition() == myPlayer.getPosition())   //Si el guardia entra al tile del player, el mismo pierde una vida.
            myPlayer.decLives();
        if(guards[floor].getPosition() == otherPlayer.getPosition() && board.getCardType(otherPlayer.getPosition())==LAVATORY && tokens.isThereAStealthToken(otherPlayer.getPosition()))
        {
            vector<string>msgToShow({LAVATORY_TEXT,USE_LAVATORY_TOKEN_TEXTB,USE_MY_STEALTH_TOKEN_TEXTB});
            string userChoice = controller->askForSpentOK(msgToShow);
            if(userChoice ==USE_MY_STEALTH_TOKEN_TEXTB)
                otherPlayer.decLives();
            else if(userChoice ==USE_LAVATORY_TOKEN_TEXTB)
                tokens.useLavatoryToken();
        }
        else if(guards[floor].getPosition() == otherPlayer.getPosition())
            otherPlayer.decLives();
        if(board.isCardVisible(guards[floor].getPosition()))
        {   
            if(board.getCardType(guards[floor].getPosition()) == CAMERA && board.getCardType(myPlayer.getPosition()) == CAMERA && board.isCardVisible(myPlayer.getPosition()))
                if(board.getCardType(guards[floor].getPosition()) != board.getCardType(myPlayer.getPosition()))
                {   tokens.triggerAlarm(myPlayer.getPosition()); setGuardsNewPath(myPlayer.getPosition().floor); }
            if(board.getCardType(guards[floor].getPosition()) == CAMERA && board.getCardType(otherPlayer.getPosition()) == CAMERA && board.isCardVisible(otherPlayer.getPosition()))
                if(board.getCardType(guards[floor].getPosition()) != board.getCardType(otherPlayer.getPosition()))
                {   tokens.triggerAlarm(otherPlayer.getPosition()); setGuardsNewPath(otherPlayer.getPosition().floor); }
        }
        /*Si un player esta sobre un atrium dado vuelta, y el guardia pasa un piso arriba o abajo de ese player, este pierde una vida*/
        if(board.getCardType(myPlayer.getPosition()) == ATRIUM && board.isCardVisible(myPlayer.getPosition()) && (board.isCardDownstairs(myPlayer.getPosition(), guards[floor].getPosition()) || board.isCardUpstairs(myPlayer.getPosition(), guards[floor].getPosition())))
            myPlayer.decLives();
        if(board.getCardType(otherPlayer.getPosition()) == ATRIUM && board.isCardVisible(otherPlayer.getPosition()) && (board.isCardDownstairs(otherPlayer.getPosition(), guards[floor].getPosition()) || board.isCardUpstairs(otherPlayer.getPosition(), guards[floor].getPosition())))
            otherPlayer.decLives();
        /*Si un player esta sobre un Foyer dado vuelta, y el guardia se encuentra en un tile adyacente, este pierde una vida*/
        if(board.getCardType(myPlayer.getPosition()) == FOYER && board.isCardVisible(myPlayer.getPosition()) && board.adjacentCards(myPlayer.getPosition(), guards[floor].getPosition()))
            myPlayer.decLives();
        if(board.getCardType(otherPlayer.getPosition()) == FOYER && board.isCardVisible(otherPlayer.getPosition()) && board.adjacentCards(otherPlayer.getPosition(), guards[floor].getPosition()))
            otherPlayer.decLives();
        /*Si el guardia llegó a la posición objetivo, busca un nuevo objetivo*/
        if(targetReached)
        {
            if(tokens.isThereAToken(guards[floor].getPosition(), ALARM_TOKEN))
                tokens.turnOffAlarm(guards[floor].getPosition());
            setGuardsNewPath(floor);
        }
        /*Si había un crow token en el tile donde se encuentra*/
        if(tokens.isThereAToken(guards[floor].getPosition(), CROW_TOKEN) && stepsToMove > 0)
            stepsToMove--;
        view->update(this);
        //sleep(1.0);         //Esto despues cambiará (es bloqueante)
    }
}
void BurgleBrosModel::setGuardsNewPath(unsigned int floor)
{
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
        while((newTargetLocation = guards[floor].drawCardTarget()) == guards[floor].getPosition());
    guards[floor].setNewTarget(newTargetLocation);
    list<CardLocation> temp = board.getShortestPath(guards[floor].getPosition(), newTargetLocation);
    guards[floor].setNewPathToTarget(temp);
}
void BurgleBrosModel::triggerSilentAlarm(unsigned int floor)
{
    for(int i=floor; i >= 0; i--)
    {
        guards[i].incDiceNumber();
    }
}

void BurgleBrosModel::handlePersianKittyMove(ActionOrigin playerId)
{
    BurgleBrosPlayer *p=getP2Player(playerId);
    if(p->isItsTurn() && p->hasLoot(PERSIAN_KITTY) && board.canKittyMove(p->getPosition()) && dice.persianKittyShallMove())   
    {
        p->deattachLoot(PERSIAN_KITTY);
        loots.setNewLootOwner(PERSIAN_KITTY,NON_PLAYER);
        pair<bool, CardLocation> persianKittyToken;
        persianKittyToken.first = true;
        persianKittyToken.second = board.getKittyMovingPos(p->getPosition());
        tokens.placePersianKittyToken(persianKittyToken);
        view->update(this);
    }
}
void BurgleBrosModel::handleChihuahuaMove(ActionOrigin playerId)
{
    BurgleBrosPlayer *p=getP2Player(playerId);
    if(p->isItsTurn() && p->hasLoot(CHIHUAHUA) && dice.chihuahuaBarks())
    {
        tokens.triggerAlarm(p->getPosition());
        setGuardsNewPath(p->getPosition().floor);
        view->update(this);
    }
}
BurgleBrosModel::~BurgleBrosModel()
{
}
