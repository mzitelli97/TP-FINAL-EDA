#ifndef GRAPHIC_MENU_ITME
#define GRAPHIC_MENU_ITME

#include "GraphicItem.h"

using namespace std;

class GraphicMenuItem : public GraphicItem{
public:
    GraphicMenuItem(Point point, CardLocation tile);
    virtual ~GraphicMenuItem();
    void setOption(string option);
    virtual void draw();
    virtual clickItem IAm();
    CardLocation getTile();
    string getOption();
private:
    string option;
    CardLocation tile;
    ALLEGRO_FONT * font;
		
};

#endif //GRAPHIC_MENU_ITME
