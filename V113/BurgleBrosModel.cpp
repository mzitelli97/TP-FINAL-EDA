#include "BurgleBrosModel.h"

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


bool BurgleBrosModel::peek(BurgleBrosPlayer *PlayerEnTurno, CardLocation aux)
{
    bool retVal=false;
    //if(actionisPossible)
    board.setCardVisible(aux);
    PlayerEnTurno->decActions();
    retVal=true;
    return retVal;
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
vector<string> BurgleBrosModel::getPosibleActions(ActionOrigin player, CardLocation tile)
{
    vector<string> aux;
    if(isMovePosible(player, tile))
        aux.push_back("Move");
    if(isPeekPosible(player, tile))
        aux.push_back("Peek");
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




BurgleBrosModel::~BurgleBrosModel()
{
}
