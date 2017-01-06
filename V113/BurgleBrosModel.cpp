#include "BurgleBrosModel.h"
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
    myPlayer.setTurn(true);
    otherPlayer.setTurn(false);
    for(unsigned int i =0; i <MAX_NMBR_OF_EXTRA_DICES; i++)
        extraDices[i]=0;
}
void BurgleBrosModel::attachView(View * view)
{
    this->view = view;
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
    for(vector<CardLocation>::iterator it=downstairsTokens.begin(); it!=downstairsTokens.end(); it++)
    {
        toPush.position=*it;
        toPush.token=ALARM_TOKEN;
        retVal.push_back(toPush);
    }
    for(list<CardLocation>::iterator it=auxList.begin(); it!=auxList.end(); it++)
    {
        toPush.position=*it;
        toPush.token=DOWNSTAIRS_TOKEN;
        retVal.push_back(toPush);
    }
    auxList = tokens.getCrackedCards();
    for(list<CardLocation>::iterator it=auxList.begin(); it!=auxList.end(); it++)
    {
        toPush.position=*it;
        toPush.token= SAFE_TOKEN;
        retVal.push_back(toPush);
    }
    auxList = tokens.getStealthTokensOnFloor();
    for(list<CardLocation>::iterator it=auxList.begin(); it!=auxList.end(); it++)
    {
        toPush.position=*it;
        toPush.token= STEALTH_TOKEN;
        retVal.push_back(toPush);
    }
    if(tokens.isKeypadOpen())
    {
        toPush.position= tokens.getKeypadOpenLocation();
        toPush.token= KEYPAD_TOKEN;
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
    }
    return info;
}
Info2DrawPlayer BurgleBrosModel:: getInfo2DrawPlayer(ActionOrigin player)
{
    Info2DrawPlayer info;
    BurgleBrosPlayer p;
    
    if(player==THIS_PLAYER_ACTION)        
        p=myPlayer;
    else 
        p=otherPlayer;
    info.name=p.getName();
    info.character=p.getCharacter();
    info.lives=p.getCurrLifes();
    info.position=p.getPosition();
    return info;
}


vector<unsigned int> BurgleBrosModel::getInfo2DrawExtraDices()
{
    vector<unsigned int> aux;
    aux.reserve(MAX_NMBR_OF_EXTRA_DICES);
    for(unsigned int i =0; i <MAX_NMBR_OF_EXTRA_DICES; i++)
        aux.push_back(extraDices[i]);
    return aux;
}


bool BurgleBrosModel::peek(ActionOrigin playerId, CardLocation locationToPeek)
{
    bool retVal=false;
    if(isPeekPosible(playerId, locationToPeek))
    {
        board.setCardVisible(locationToPeek);
        getP2Player(playerId)->decActions();
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
        
        if(!board.isCardVisible(locationToMove))
            board.setCardVisible(locationToMove);
        getP2Player(playerId)->decActions();
        getP2Player(playerId)->setPosition(locationToMove);
        checkTurns();
        view->update(this);
        retVal=true;
    }
    return retVal;
}
void BurgleBrosModel::checkTurns()
{
    if(myPlayer.isItsTurn() && myPlayer.getcurrentActions() == 0)
    {
        myPlayer.setTurn(false);
        myPlayer.setActions(INIT_NMBR_OF_LIVES);
        if(myPlayer.hasLoot(MIRROR))
            myPlayer.setActions(INIT_NMBR_OF_LIVES-1);
        moveGuard(myPlayer.getPosition().floor);
        otherPlayer.setTurn(true);
    }
    if(otherPlayer.isItsTurn() && otherPlayer.getcurrentActions() == 0)
    {
        otherPlayer.setTurn(false);
        myPlayer.setActions(INIT_NMBR_OF_LIVES);
        if(myPlayer.hasLoot(MIRROR))
            myPlayer.setActions(INIT_NMBR_OF_LIVES-1);
        moveGuard(otherPlayer.getPosition().floor);
        myPlayer.setTurn(true);
    }
}

 bool BurgleBrosModel::isMovePosible(ActionOrigin playerId,CardLocation tileToMove)
 {
     BurgleBrosPlayer * playerMoving = getP2Player(playerId);
     CardLocation playerMovingPos= playerMoving->getPosition();
     bool retVal=false;
     if(playerMoving->isItsTurn())
     {
         if(board.isMovePossible(playerMovingPos, tileToMove))
             retVal=true;
         if(board.isCardVisible(playerMovingPos))
         {
             if(board.getCardType(playerMovingPos) == STAIR  && isCardUpstairs(playerMovingPos, tileToMove))
                retVal=true;
             if(board.getCardType(playerMovingPos) == WALKAWAY  &&  isCardDownstairs(playerMovingPos, tileToMove))
                retVal=true;
             if(board.getCardType(playerMovingPos) == SERVICE_DUCT && (board.getOtherServiceDuctPos(playerMovingPos)== tileToMove))
                retVal=true;
         }
         if(board.getCardType(tileToMove) == SECRET_DOOR && board.isAWallBetween(playerMovingPos,tileToMove))
             retVal=true;
         if(tokens.isThereAToken(playerMovingPos, DOWNSTAIRS_TOKEN) && isCardDownstairs(playerMovingPos, tileToMove))
             retVal=true;
         if((playerMoving->getcurrentActions() < 3 )&&(board.getCardType(playerMovingPos) == DEADBOLT )&& !(guards[playerMoving->getPosition().floor].getPosition() == tileToMove) && !(getP2OtherPlayer(playerId)->getPosition() == tileToMove))
             retVal=false;
         if(board.getCardType(playerMovingPos) == SERVICE_DUCT && (board.getOtherServiceDuctPos(playerMovingPos)== tileToMove) && playerMoving->hasLoot(PAINTING))
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
    BurgleBrosPlayer* p;
    p = getP2Player(player);
    if(p->isItsTurn() && (!board.isCardVisible(tile)))
    {
        if(board.isMovePossible(p->getPosition(),tile))
            retVal=true;
        else if(p->getCharacter()==THE_HAWK && board.isAWallBetween(p->getPosition(),tile))//HACER FUNCION WALLLSEPARATES
            retVal=true;
        else if( board.getCardType(p->getPosition())== ATRIUM && ( isCardUpstairs(p->getPosition(),tile) || isCardDownstairs(p->getPosition(),tile) ) )
            retVal=true;
        else if( board.getCardType(p->getPosition())== STAIR && isCardUpstairs(p->getPosition(),tile)  )
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
    while(stepsToMove!=0)
    {
        stepsToMove--;
        targetReached = guards[floor].step();
        if(guards[floor].getPosition() == myPlayer.getPosition())   //Si el guardia entra al tile del player, el mismo pierde una vida.
            myPlayer.decLives();
        if(guards[floor].getPosition() == otherPlayer.getPosition())
            otherPlayer.decLives();
        if(board.isCardVisible(guards[floor].getPosition()))
        {   /*Si el guardia se encuentra sobre un atrium, es visible y un jugador está arriba o debajo del guardia, ese jugador pierde una vida */
            if(board.getCardType(guards[floor].getPosition()) == ATRIUM && (isCardDownstairs(guards[floor].getPosition(), myPlayer.getPosition()) || isCardUpstairs(guards[floor].getPosition(), myPlayer.getPosition())))
                myPlayer.decLives();
            if(board.getCardType(guards[floor].getPosition()) == ATRIUM && (isCardDownstairs(guards[floor].getPosition(), otherPlayer.getPosition()) || isCardUpstairs(guards[floor].getPosition(), otherPlayer.getPosition())))
                otherPlayer.decLives();
        }
        /*Si un player esta sobre un atrium dado vuelta, y el guardia pasa un piso arriba o abajo de ese player, este pierde una vida*/
        if(board.getCardType(myPlayer.getPosition()) == ATRIUM && board.isCardVisible(myPlayer.getPosition()) && (isCardDownstairs(myPlayer.getPosition(), guards[floor].getPosition()) || isCardUpstairs(myPlayer.getPosition(), guards[floor].getPosition())))
            myPlayer.decLives();
        if(board.getCardType(otherPlayer.getPosition()) == ATRIUM && board.isCardVisible(otherPlayer.getPosition()) && (isCardDownstairs(otherPlayer.getPosition(), guards[floor].getPosition()) || isCardUpstairs(otherPlayer.getPosition(), guards[floor].getPosition())))
            otherPlayer.decLives();
        /*Si un player esta sobre un Foyer dado vuelta, y el guardia se encuentra en un tile adyacente, este pierde una vida*/
        if(board.getCardType(myPlayer.getPosition()) == FOYER && board.isCardVisible(myPlayer.getPosition()) && board.isMovePossible(myPlayer.getPosition(), guards[floor].getPosition()))
            myPlayer.decLives();
        if(board.getCardType(otherPlayer.getPosition()) == FOYER && board.isCardVisible(otherPlayer.getPosition()) && board.isMovePossible(otherPlayer.getPosition(), guards[floor].getPosition()))
            otherPlayer.decLives();
        /*Si el guardia llegó a la posición objetivo, busca un nuevo objetivo*/
        if(targetReached)
        {
            if(tokens.isThereAToken(guards[floor].getPosition(), ALARM_TOKEN))
                tokens.turnOffAlarm(guards[floor].getPosition());
            setGuardsNewPath(floor);
        }
        /*Si había un crow token en el tile donde se encuentra*/
        if(tokens.isThereAToken(guards[floor].getPosition(), CROW_TOKEN) && stepsToMove > 1)
            stepsToMove--;
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
    else        //Si no había alarmas, se toma una carta 
        newTargetLocation = guards[floor].drawCardTarget();
    guards[floor].setNewTarget(newTargetLocation);
    guards[floor].setNewPathToTarget(board.getShortestPath(guards[floor].getPosition(), newTargetLocation));
}




BurgleBrosModel::~BurgleBrosModel()
{
}
