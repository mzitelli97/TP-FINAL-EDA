#include <iostream>
#define ALLEGRO_STATICLINK
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "LibsInit.h"

using namespace std;


int allegro_startup(void)
{
	if (al_init())
	{
		if (al_init_primitives_addon())
		{
			if (al_install_keyboard())
			{
				if (al_install_mouse())
				{
					if (al_init_image_addon())
					{
						al_init_font_addon();
						if (al_init_ttf_addon())
						{
                                                    if(al_install_audio())
                                                    {
                                                        if(al_init_acodec_addon())
                                                            return AL_STARTUP_SUCCESS;
                                                        else
                                                            cout << "ERROR: Failed to init acodec addon\n";
                                                        al_shutdown_ttf_addon();
                                                    }
                                                    else
                                                        cout << "ERROR: Failed to install audio\n";
                                                    al_shutdown_ttf_addon();
						}
						else
							cout << "ERROR: Failed to initialize ttf addon\n";
						al_shutdown_font_addon();
						al_shutdown_image_addon();
					}
					else
						cout<<  "ERROR: Failed to initialize image addon\n";
					al_uninstall_mouse();
				}
				else
					cout<<  "ERROR: Failed to initialize mouse\n";
				al_uninstall_keyboard();
			}
			else
				cout << "ERROR: Failed to install keyboard\n";
			al_shutdown_primitives_addon();
		}
		else
			cout <<  "ERROR: Failed to load primitives addon\n";
		al_uninstall_system();
	}
	else
		cout <<  "ERROR: Failed to initialize allegro system\n";
	return AL_STARTUP_ERROR;
}
void allegro_shut_down(void)
{
	al_shutdown_ttf_addon();
	al_shutdown_font_addon();
	al_shutdown_image_addon();
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_shutdown_primitives_addon();
	al_uninstall_system();
}