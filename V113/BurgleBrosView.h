/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BurgleBrosView.h
 * Author: javier
 *
 * Created on December 24, 2016, 12:58 PM
 */

#ifndef BURGLEBROSVIEW_H
#define BURGLEBROSVIEW_H
#include "BurgleBrosModel.h"
#include "ImageLoader.h"
#include "View.h"
#include "GraphicItem.h"
#include <list>
typedef enum {FIRST_LAYER, SECOND_LAYER, THIRD_LAYER} Layers;
typedef enum {TILES_LIST, BUTTONS_LIST, CHARACTER_CARDS_LIST, LOOT_SHOW_LIST, EXTRA_DICES_LIST, GUARD_CARDS_LIST} FirstLayerLists;
typedef enum {TOKENS_LIST, GUARD_INFO_LIST, PLAYER_INFO_LIST, STATIC_ITEMS} SecondeLayerLists;
typedef enum {MENU_ITEM_LIST} ThirdLayerLists;
#define DROPDOWNS_MENUS_LIST 0
#define INIT_QUANTITY_LAYERS 3

class BurgleBrosView : public View{
public:
    BurgleBrosView();
    BurgleBrosView(Model * model);
    
    /*Devuelve sobre que item fue el click, junto con informacion del item.
     TILE -> CARDLOCATION
     LOOT_CARD -> OWNER(actionOrigin)
     PLAYER_CARDS -> ACTIONORIGIN
     GUARD_CARD -> FLOOR(unsigned int)
     MENU_ITEM -> AUXINFO (string y cardLocation)*/
    ItemInfo itemFromClick(Point point);
    
    virtual void update(Model * model);
    void ViewInit(BurgleBrosModel* model);
    void showMenu(list<string> options, Point click, CardLocation tile);
    void showMenu(list<string> options, Point click, unsigned int floor);
    void eraseMenu();
    void zoomFloor(unsigned int floor, Model * auxModel);
    void zoomLoot(ActionOrigin owner);
    void zoomPlayerCard(ActionOrigin player);
    void zoomGuardDeck(unsigned int floor);
    string MessageBox(vector<string> &message);
    int yesNoMessageBox(vector<string> &message);
    void cheatCards();
    virtual ~BurgleBrosView();
private:
    list<GraphicItem *>::iterator accessGraphicItems(Layers layer, unsigned int itemType);
    list<list<GraphicItem *>>::iterator deleteList(Layers layer, unsigned int itemList);
    void updateButtons(BurgleBrosModel *model);
    void updateCharacters(BurgleBrosModel *model);
    void updateCharacterCards(BurgleBrosModel *model);
    void updateTiles(BurgleBrosModel * model);
    void updateLoots(BurgleBrosModel * model);
    void updateGuards(BurgleBrosModel * model);
    void updateTokens(BurgleBrosModel * model);
    void updateExtraDices(BurgleBrosModel * model);
    list<list<list<GraphicItem *>>> graphicInterface;                   //layers structure of graphical interface
    vector<GraphicItem*> walls;
    ALLEGRO_DISPLAY * display;
    ALLEGRO_BITMAP * backScreen;
    ALLEGRO_FONT * actionsFont;
    ImageLoader imageLoader;
    bool onZoom;
    int floorZoomed;
    int guardZoomed;
    ActionOrigin lootZoomed;
    ActionOrigin playerZoomed;

};

#endif /* BURGLEBROSVIEW_H */
