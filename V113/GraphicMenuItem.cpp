#include "GraphicMenuItem.h"

#define WHITE al_map_rgb(255,255,255)
#define BLACK al_map_rgb(0,0,0)

GraphicMenuItem::GraphicMenuItem(Point point, CardLocation tile)
{
	min = point;
        this->tile = tile;
        font = al_load_font("fonts.ttf",10,0);
        //definir alto y ancho del cuadrado
        width = 100;
        height = 20;
        max.x = min.x + width;
        max.y = min.y + height;
}

void GraphicMenuItem::draw()
{
	//dibujo un cuadrado con las dimesiones del objeto
	al_draw_filled_rectangle(min.x, min.y, max.x, max.y, WHITE);
        al_draw_rectangle(min.x, min.y, max.x, max.y, BLACK, 0);
	//escribo el string option en este cuadrado
	al_draw_text(font, BLACK, min.x + 5, min.y + 5, 0, option.c_str());
}

void GraphicMenuItem::setOption(string option)
{
	this->option = option;
}

clickItem GraphicMenuItem::IAm()
{
	return MENU_ITEM;
}

string GraphicMenuItem::getOption()
{
    return option;
}

CardLocation GraphicMenuItem::getTile()
{
    return tile;
}

GraphicMenuItem::~GraphicMenuItem()
{
    al_destroy_font(font);
}

