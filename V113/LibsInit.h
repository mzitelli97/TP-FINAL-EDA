
#ifndef ALLEGRO_INIT_SHUTDOWN_H
#define ALLEGRO_INIT_SHUTDOWN_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define AL_STARTUP_ERROR -1
#define AL_STARTUP_SUCCESS 0


int allegro_startup(void);
void allegro_shut_down(void);
#endif /* ALLEGRO_INIT_SHUTDOWN_H */