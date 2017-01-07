/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BurgleBrosView.cpp
 * Author: javier
 * 
 * Created on December 24, 2016, 12:58 PM
 */

#include "BurgleBrosView.h"
#include "GraphicEDices.h"
#include "GraphicGDie.h"
#include "GraphicGuard.h"
#include "GraphicGuardCards.h"
#include "GraphicLoot.h"
#include "GraphicPlayer.h"
#include "GraphicPlayerCard.h"
#include "GraphicTile.h"
#include "GraphicToken.h"
#include "GraphicMenuItem.h"

#define SCREEN_W 1800
#define SCREEN_H 900
#define TITLE_H al_get_bitmap_height(backScreen)/20.0

BurgleBrosView::BurgleBrosView() {
    imageLoader.initImages();           //Falta checkear.
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    display =al_create_display(SCREEN_W,SCREEN_H);           //Falta checkear.
    backScreen = al_load_bitmap("fondo.jpg");
    al_draw_scaled_bitmap(backScreen,0,0,al_get_bitmap_width(backScreen),al_get_bitmap_height(backScreen),0,0,al_get_display_width(display),al_get_display_height(display),0);
    
    ALLEGRO_FONT * font = al_load_font("title.ttf",TITLE_H,0);
    al_set_target_bitmap(backScreen);
    al_draw_text(font,al_map_rgb(0,0,0),al_get_bitmap_width(backScreen)/2.0,TITLE_H/2,ALLEGRO_ALIGN_CENTER, "EDA BURGLE BROS");
    al_destroy_font(font);
    al_set_target_backbuffer(display);
    
    #ifdef ICON
    ALLEGRO_BITMAP *icon = al_load_bitmap(ICON);                              //Falta checkear.
    al_set_display_icon(display,icon);
    al_destroy_bitmap(icon);
    #endif
    al_set_window_title(display,"EDA Burgle Bros");

}


BurgleBrosView::~BurgleBrosView() {
}
/*void BurgleBrosView::attachModel(BurgleBrosModel *model)
{
    this->model=model;
    board = model->getElements()->getBoard();
}
*/
void BurgleBrosView::ViewInit(BurgleBrosModel* model)
{
    /*VEO SI ANDA ASI O SINO VER CASTEO CON */    
    //creo los info2draw
    vector<Info2DrawCards> info_tiles= model->getInfo2DrawCards();
    Info2DrawGuard infoGuard[3];
    for(int i = 0; i < BOARD_STANDARD_FLOORS; i++)
    {
        infoGuard[i] = model->getInfo2DrawGuard(i);
    }
    list<Info2DrawLoot> infoLoot= model-> getInfo2DrawLoot();
    Info2DrawPlayer infoThisPlayer= model->getInfo2DrawPlayer(THIS_PLAYER_ACTION);
    Info2DrawPlayer infoOtherPlayer= model->getInfo2DrawPlayer(OTHER_PLAYER_ACTION);
    list<Info2DrawTokens> infoTokens= model->getInfo2DrawTokens();
    
    /*************Inicilizo las capas*******************/
    
    list<list<GraphicItem*>> auxLayer;
    list<list<list<GraphicItem *>>>::iterator it_layers;
    
    
    /***************creo las capas y creo un iterador***/
    
    for(int i=0; i<INIT_QUANTITY_LAYERS;i++)
    {
        graphicInterface.push_back(auxLayer);
    }
    it_layers=graphicInterface.begin();
          
    /*********Inicializo la primera capa****************/

    //creo una lista de graphicTiles
    list<GraphicItem*> auxTiles_list;
    for(int i=0; i<info_tiles.size();i++)
    {
         GraphicTile *auxTile_element=new GraphicTile(imageLoader.getImageP(info_tiles[i].type),imageLoader.getImageBackP(info_tiles[i].type),info_tiles[i].location,al_get_display_width(display),al_get_display_height(display));
         auxTiles_list.push_back((GraphicItem *) auxTile_element);
    }
    
    //creo una lista de Buttons
    list<GraphicItem* > auxButtons_list;
    //creo una lista de graphicCharacterscards
    list<GraphicItem* > auxCharactersCards_list;
    
    GraphicPlayerCard *auxCharactersCardsThis_element=new GraphicPlayerCard(imageLoader.getImageP(infoThisPlayer.character,true),imageLoader.getImageP(STEALTH_TOKEN), infoThisPlayer.lives,infoOtherPlayer.name, THIS_PLAYER_ACTION,al_get_display_width(display),al_get_display_height(display)); // con true devuelve la carta
    GraphicPlayerCard *auxCharactersCardsOther_element=new GraphicPlayerCard(imageLoader.getImageP(infoOtherPlayer.character,true),imageLoader.getImageP(STEALTH_TOKEN), infoOtherPlayer.lives,infoOtherPlayer.name, OTHER_PLAYER_ACTION,al_get_display_width(display),al_get_display_height(display)); // con true devuelve la carta
   
    auxCharactersCards_list.push_back((GraphicItem *) auxCharactersCardsThis_element);
    auxCharactersCards_list.push_back((GraphicItem *) auxCharactersCardsOther_element);
            
    //creo una lista para graphicLoots
    list<GraphicItem* > auxLoot_list;
    
    GraphicLoot * auxLoot = new GraphicLoot(imageLoader.getImageBackP(infoLoot.front().loot));
    auxLoot->setScreenDimentions(al_get_display_width(display),al_get_display_height(display));
    auxLoot_list.push_back(auxLoot);
    
    //creo una lista para extra_dies
    list<GraphicItem* > auxExtraDies_list;
    
    //creo una lista de graphicGuardcards 
    list<GraphicItem *> auxGuard_list;
    
    for(int i = 0; i < BOARD_STANDARD_FLOORS; i++)
    {
        GraphicGuardCards *auxGuard_card = new GraphicGuardCards(imageLoader.getImageBackP(infoGuard[i].position),i);
        auxGuard_card->setScreenDimentions(al_get_display_width(display),al_get_display_height(display));
        auxGuard_card->push_top_card(imageLoader.getImageP(infoGuard[i].shownDeck.front()));
        auxGuard_list.push_back((GraphicItem *)auxGuard_card);
    }
    
    //**********push sobre la primera capa 
    it_layers->push_back(auxTiles_list);
    it_layers->push_back(auxButtons_list);
    it_layers->push_back(auxCharactersCards_list);
    it_layers->push_back(auxLoot_list);
    it_layers->push_back(auxExtraDies_list);
    it_layers->push_back(auxGuard_list);
    
    it_layers++; 
    
    /*********Inicializo la segunda capa****************/
    
    //creo una lista de token
    list<GraphicItem *> auxToken_list;
    
    //creo una lista para guardInfo
    list<GraphicItem *> auxGuardInfo_list;
    
    /***********For test***************/
    GraphicGDie * auxGuardDie = new GraphicGDie(imageLoader.getImageP(RED_DICE, 2));
    auxGuardDie->setScreenDimentions(al_get_display_width(display),al_get_display_height(display));
    auxGuardDie->setPosition({2,2,1});
    GraphicGuard * auxGuard = new GraphicGuard(imageLoader.getGuardImage());
    auxGuard->setScreenDimentions(al_get_display_width(display),al_get_display_height(display));
    auxGuard->setPosition({2,2,1});
    auxGuardInfo_list.push_back(auxGuard);
    auxGuardInfo_list.push_back(auxGuardDie);
    /********************************/
    
    //creo una lista de graphicPlayer
    list<GraphicItem *> auxPlayer_list;
    
    GraphicPlayer *auxThisPlayer_element=new GraphicPlayer(imageLoader.getImageP(infoThisPlayer.character,false),infoThisPlayer.position,al_get_display_width(display),al_get_display_height(display)); 
    GraphicPlayer *auxOtherPlayer_element=new GraphicPlayer(imageLoader.getImageP(infoOtherPlayer.character,false),infoOtherPlayer.position,al_get_display_width(display),al_get_display_height(display)); 
    auxPlayer_list.push_back((GraphicItem *)auxThisPlayer_element);
    auxPlayer_list.push_back((GraphicItem *)auxOtherPlayer_element);

    //creo una lista de static item
    list<GraphicItem *> auxStaticItem_list;
    

    //**********push sobre la segunda capa 
    it_layers->push_back(auxToken_list);
    it_layers->push_back(auxGuardInfo_list);
    it_layers->push_back(auxPlayer_list);
    it_layers->push_back(auxStaticItem_list);
    
    it_layers++;
    
    /*********Inicializo la tercer capa****************/
    
    //creo una lista de menu_items
    list<GraphicItem *> auxMenuItem_list;
        
    //**********push sobre la tercer capa 
    it_layers->push_back(auxMenuItem_list);
    
}

void BurgleBrosView::update(Model* auxModel)
{
    /*Update all*/
    BurgleBrosModel * model = (BurgleBrosModel *) auxModel; 
    //string aux;
    updateTiles(model);
    updateTokens(model);
    updateCharacters(model);
    updateCharacterCards(model);
    updateLoots(model);
    updateGuards(model);
    updateExtraDices(model);
    /*Draw all*/
    al_draw_scaled_bitmap(backScreen,0,0,al_get_bitmap_width(backScreen),al_get_bitmap_height(backScreen),0,0,al_get_display_width(display),al_get_display_height(display),0);
    list<list<list<GraphicItem *>>>::iterator it_layers;
    list<list<GraphicItem *>>::iterator it_itemType;
    list<GraphicItem *>::iterator it_items;
    //cout << "hola" << endl;
    for( it_layers = graphicInterface.begin(); it_layers != graphicInterface.end(); it_layers++)
    {
        //cout << "hola1" << endl;
        for( it_itemType = it_layers->begin(); it_itemType != it_layers->end(); it_itemType++)
        {
            //cout << "hola2" << endl;
            for( it_items = it_itemType->begin(); it_items != it_itemType->end(); it_items++)
            {
                //cout << "hola3" << endl;
                (*it_items)->draw();
                
            }
        }
    }
    al_flip_display();
    //cin>>aux;
}
ItemInfo BurgleBrosView::itemFromClick(Point point)
{
    ItemInfo retVal = {NO_ITEM, nullptr};
    bool layer_flag = false;                                                                    //to exit outer loop
    list<list<list<GraphicItem *>>>::reverse_iterator it_layers;
    list<list<GraphicItem *>>::iterator it_itemType;
    list<GraphicItem *>::iterator it_items;
    for( it_layers = graphicInterface.rbegin(); it_layers != graphicInterface.rend() && !layer_flag; it_layers++)
    {
        for( it_itemType = it_layers->begin(); it_itemType != it_layers->end() && !layer_flag; it_itemType++)
        {
            for( it_items = it_itemType->begin(); it_items != it_itemType->end(); it_items++)
            {
                if((*it_items)->isPointIn(point))
                {
                    retVal = (*it_items)->IAm();
                    layer_flag = true;
                    break;
                }
            }
        }
    }
    return retVal;
}
void BurgleBrosView::updateTiles(BurgleBrosModel * model)
{
    vector<Info2DrawCards> aux = model->getInfo2DrawCards();
    list<GraphicItem *>::iterator it = accessGraphicItems(FIRST_LAYER, TILES_LIST);
    for(unsigned int i=0; i < BOARD_STANDARD_FLOORS * FLOOR_RAWS * FLOOR_COLUMNS ; i++, it++)
    {
        GraphicTile *p = dynamic_cast<GraphicTile *>(*it);
        if(p != nullptr)
        {
            if(!(p->isVisible()) && aux[i].isVisible)
                p->setVisible(imageLoader.getImageP(aux[i].safeNumber));
        }
    }
}
void BurgleBrosView::updateTokens(BurgleBrosModel* model)
{
    list<Info2DrawTokens> info_tokens = model->getInfo2DrawTokens();
    list<list<GraphicItem *>>::iterator it_itemType;
    it_itemType = deleteList(SECOND_LAYER, TOKENS_LIST);
    
    /*For test*/
    Info2DrawTokens aux = {ALARM_TOKEN, {1,1,0}};
    info_tokens.push_back(aux);
    aux = {KEYPAD_TOKEN, {2,2,1}};
    info_tokens.push_back(aux);
    /***********/
    
    list<Info2DrawTokens>::iterator it;
    for( it = info_tokens.begin(); it != info_tokens.end(); it++)
    {
        GraphicToken * token = new GraphicToken(imageLoader.getImageP(it->token));
        token->setScreenDimentions(al_get_display_width(display),al_get_display_height(display));
        token->setPosition(it->position);
        it_itemType->push_back(token);
    }
}
void BurgleBrosView::updateLoots(BurgleBrosModel * model)
{
    list<Info2DrawLoot> aux = model->getInfo2DrawLoot();
    Info2DrawLoot loot = {TIARA, THIS_PLAYER_ACTION};
    aux.push_back(loot);
    loot = {PERSIAN_KITTY, OTHER_PLAYER_ACTION};
    aux.push_back(loot);
    
    list<list<GraphicItem *>>::iterator itemsList = deleteList(FIRST_LAYER, LOOT_CARDS);
    for(list<Info2DrawLoot>::iterator newInfo = aux.begin() ; newInfo!= aux.end(); newInfo++)
    {
        GraphicLoot *p = new GraphicLoot(newInfo->owner, imageLoader.getImageP(newInfo->loot));
        p->setScreenDimentions(al_get_display_width(display),al_get_display_height(display));
        itemsList->push_back((GraphicItem *) p);
    }
    
}
void BurgleBrosView::updateCharacters(BurgleBrosModel *model) {
    list<GraphicItem*>::iterator it = accessGraphicItems(SECOND_LAYER, PLAYER_INFO_LIST);
    //First Player
    Info2DrawPlayer player = model->getInfo2DrawPlayer(THIS_PLAYER_ACTION);
    GraphicPlayer* gPlayer = dynamic_cast<GraphicPlayer*> (*it); //ASUMI QUE EL PRIMERO ES THIS_PLAYER
    if(gPlayer!=NULL)//VER EL ORDEN DE LAS COSAS, DEBERIA ANDAR IGUAL
        gPlayer->setLocation(player.position);
    //Second Player
    player = model->getInfo2DrawPlayer(OTHER_PLAYER_ACTION);
    gPlayer = dynamic_cast<GraphicPlayer*> (*(++it));
    if(gPlayer!=NULL)
        gPlayer->setLocation(player.position);
}
 
void BurgleBrosView::updateCharacterCards(BurgleBrosModel *model) {
    Info2DrawPlayer player = model->getInfo2DrawPlayer(THIS_PLAYER_ACTION);
    //FirstPlayer
    list<GraphicItem *>::iterator it = accessGraphicItems(FIRST_LAYER, CHARACTER_CARDS_LIST);
    GraphicPlayerCard* gPlayerCard = dynamic_cast<GraphicPlayerCard *> (*it);
    if(gPlayerCard!=NULL)
        gPlayerCard->setLives(player.lives);
    //SecondPlayer
    player = model->getInfo2DrawPlayer(OTHER_PLAYER_ACTION);
    gPlayerCard = dynamic_cast<GraphicPlayerCard *> (*(++it));
    if(gPlayerCard!=NULL)    
        gPlayerCard->setLives(player.lives);
}
void BurgleBrosView::updateGuards(BurgleBrosModel* model)
{
    for(int i = 0; i < BOARD_STANDARD_FLOORS; i++)
    {
        /*Here update all things related to a guard on a floor*/
        Info2DrawGuard info_guard = model->getInfo2DrawGuard(i);
        list<GraphicItem *>:: iterator guard = accessGraphicItems(SECOND_LAYER, (unsigned int) GUARD_INFO_LIST);
        if(*guard != NULL)
        {
            /*Suppose the first item is the guard item*/
            GraphicGuard * guard_item = dynamic_cast<GraphicGuard*> (*guard);
            GraphicGDie * guard_die = dynamic_cast<GraphicGDie*> (*(++guard));
            if( guard_item == nullptr)
            {
                /*It means the die was the first*/
                guard_item = dynamic_cast<GraphicGuard*>(*guard);
                guard_die = dynamic_cast<GraphicGDie*> (*(--guard));
                guard++;
            }
            guard++;    //point to next floor
            guard_item->setPosition(info_guard.position);
            guard_die->setPosition(info_guard.diePosition);
            guard_die->setNumber(imageLoader.getImageP(RED_DICE, info_guard.dieNumber));

            list<GraphicItem *>::iterator it = accessGraphicItems(FIRST_LAYER, (unsigned int) GUARD_CARDS_LIST);
            GraphicGuardCards * it_cards = dynamic_cast<GraphicGuardCards *> (*it);
            while(!info_guard.shownDeck.empty())
            {          
                it_cards->push_top_card(imageLoader.getImageP(info_guard.shownDeck.back()));
                info_guard.shownDeck.pop_back();
            } 
        }
    }
}
void BurgleBrosView::updateExtraDices(BurgleBrosModel* model)
{
    vector<unsigned int> info_dices = model->getInfo2DrawExtraDices();
    list<list<GraphicItem *>>::iterator it_itemType;
    it_itemType = deleteList(FIRST_LAYER, EXTRA_DICES_LIST);
    
    /*For test*/
    info_dices[0] = 1;
    info_dices[1] = 5;
    info_dices[2] = 2;
    info_dices[3] = 6;
    /**********/
    
    for( int i = 0; i < info_dices.size(); i++)
    {
        if(info_dices[i] != 0)      //if its 0 it means there is no such extra die
        {
            GraphicEDices * dice = new GraphicEDices(imageLoader.getImageP(WHITE_DICE, info_dices[i]));
            dice->setScreenDimentions(al_get_display_width(display),al_get_display_height(display));
            dice->setPosition(i);
            it_itemType->push_back(dice);
        }
        else break;                 //after a die with 0, the following dices are also 0
    }
}

list<GraphicItem *>::iterator BurgleBrosView::accessGraphicItems(Layers layer, unsigned int itemType)
{
    list<list<list<GraphicItem *>>>::iterator it_layers = graphicInterface.begin();
    advance(it_layers, layer);
    list<list<GraphicItem *>>::iterator it_itemType = it_layers->begin();
    advance(it_itemType, itemType);
    list<GraphicItem *>::iterator it_items = it_itemType->begin();
    return it_items;
}
list<list<GraphicItem *>>::iterator BurgleBrosView::deleteList(Layers layer, unsigned int itemList)
{
    list<list<list<GraphicItem *>>>::iterator aux= graphicInterface.begin();
    advance(aux, layer);
    list<list<GraphicItem *>>::iterator aux2 = aux->begin();
    advance(aux2,itemList);
    for(list<GraphicItem *>::iterator it =aux2->begin(); it !=aux2->end(); it++)
        delete *it;
    aux2->clear();
    return aux2;
}
void BurgleBrosView::showMenu(list<string> options, Point click, CardLocation tile)
{
    list<list<GraphicItem *>>::iterator menu_items;
    menu_items = deleteList(THIRD_LAYER,(unsigned int) MENU_ITEM_LIST);
    
    list<string>::iterator it;
    int i = 0;
    for( it = options.begin(); it != options.end(); i++, it++)
    {
        GraphicMenuItem * option_i = new GraphicMenuItem({click.x,click.y+i*20}, tile);
        option_i->setOption(*it);
        option_i->setScreenDimentions(al_get_display_width(display),al_get_display_height(display));
        menu_items->push_back((GraphicItem *) option_i);
    }
}

void BurgleBrosView::eraseMenu()
{
    list<list<GraphicItem *>>::iterator it_itemType;
    it_itemType = deleteList(THIRD_LAYER,(unsigned int) MENU_ITEM_LIST);
}

/*CardLocation BurgleBrosView::getDDMenuLocation()
{
    CardLocation retVal = {3,3,3};
    list<GraphicItem *>::iterator it = accessGraphicItems(THIRD_LAYER, (unsigned int) MENU_ITEM_LIST);
    GraphicMenuItem * menu = dynamic_cast<GraphicMenuItem *> (*it);
    if(menu != nullptr)
        retVal = menu->getTile();
    return retVal;
}

string BurgleBrosView::getDDMenuOption(Point aux)
{
    string retVal = "";
    list<list<list<GraphicItem *>>>::iterator it_layers = graphicInterface.begin();
    advance(it_layers, THIRD_LAYER);
    list<list<GraphicItem *>>::iterator it_itemType = it_layers->begin();
    advance(it_itemType, MENU_ITEM_LIST);
    list<GraphicItem *>::iterator it_items;
    for(it_items = it_itemType->begin(); it_items != it_itemType->end(); it_items++)
    {
        GraphicMenuItem * menu_items = dynamic_cast<GraphicMenuItem *>(*it_items);
        if(menu_items->isPointIn(aux))
        {
            retVal = menu_items->getOption();
            break;
        }
    }
    return retVal;
}

CardLocation BurgleBrosView::point2Location(Point aux)
{
    CardLocation retVal = {3,3,3};
    list<GraphicItem *>::iterator it = accessGraphicItems(FIRST_LAYER, (unsigned int) TILES_LIST);
    for(unsigned int i=0; i < BOARD_STANDARD_FLOORS * FLOOR_RAWS * FLOOR_COLUMNS ; i++, it++)
    {
        GraphicTile * tile = dynamic_cast<GraphicTile *>(*it);
        if(tile->isPointIn(aux))
        {
            retVal = tile->getLocation();
            break;
        }
    }
    return retVal;
}*/