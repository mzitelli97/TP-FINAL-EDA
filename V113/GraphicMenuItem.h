#ifndef GRAPHIC_MENU_ITME
#define GRAPHIC_MENU_ITME

#include "GraphicItem.h"

using namespace std;

class GraphicMenuItem : public GraphicItem{
public:
    GraphicMenuItem(Point point);
    virtual ~GraphicMenuItem();
    void setOption(string option);
    virtual void draw();
    virtual clickItem IAm();
private:
    string option;
    ALLEGRO_FONT * font;
		
};

#endif //GRAPHIC_MENU_ITME
