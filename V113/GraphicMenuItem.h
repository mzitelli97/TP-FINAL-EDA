#ifndef GRAPHIC_MENU_ITME
#define GRAPHIC_MENU_ITME

#include "GraphicItem.h"

using namespace std;

typedef struct
{
    string option;
    CardLocation location;
}auxInfo;

class GraphicMenuItem : public GraphicItem{
public:
    GraphicMenuItem(Point point, CardLocation tile, int number);
    virtual ~GraphicMenuItem();
    void setOption(string option);
    virtual void draw();
    virtual ItemInfo IAm();
    CardLocation getTile();
    string getOption();
private:
    auxInfo properties;
    ALLEGRO_FONT * font;
		
};

#endif //GRAPHIC_MENU_ITME
