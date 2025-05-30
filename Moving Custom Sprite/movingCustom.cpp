//Alexander Young
//Lab 6

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "arrow.h";
#include "bullet.h"

int main(void)
{
	arrowClass arrow;
	bullet mybullet[10];
	int score=0;
	bool redraw=true;
	const int FPS = 60;

	//variables
	int width = 640;
	int height = 520; //Changed height to allow for text to be displayed at the bottom of display
	bool done = false;

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if(!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_font_addon(); //Added font addon to allow for printing time and score to the display
	al_init_ttf_addon(); //Added ttf addon to allow for printing time and score to the display
	arrow.create_arrow_bitmap(display);

	ALLEGRO_FONT* font = al_load_ttf_font("Movistar Text Regular.ttf", 20, 0); //The font for printing score and time during gameplay
	ALLEGRO_FONT* finalfont = al_load_ttf_font("Movistar Text Regular.ttf", 30, 0); //The font for printing score and message at end of the game

	al_set_target_bitmap(al_get_backbuffer(display)); //Tells the program to go to the back buffer for the bitmaps
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_clear_to_color(al_map_rgb(0,0,0));
	arrow.drawArrow();
	al_flip_display();
	al_start_timer(timer);
	int count = 30;
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			//Print the score and current time remaining to the bottom of the display
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_textf(font, al_map_rgb(255, 0, 0), 120, 500, 0, "Score: %i", score);
			al_draw_textf(font, al_map_rgb(255, 0, 0), width / 2, 500, 0, "%i", count);
			if (al_get_timer_count(timer) % 60 == 0) {
				count--;
				if (count == -1) { //When the timer runs out, clear the screen and show the user their score and let them know the game will close automatically
					done = true;
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_textf(finalfont, al_map_rgb(255, 0, 0), 320, 240, ALLEGRO_ALIGN_CENTER, "Final Score: %i", score);
					al_draw_text(finalfont, al_map_rgb(255, 0, 0), 320, 280, ALLEGRO_ALIGN_CENTER, "Game will close in 3 seconds");
					al_flip_display();
					al_rest(3);
				}
			}
			for(int i=0;i<10;i++)
			{
				if (!mybullet[i].getStatus()) {
					mybullet[i].fire();
				}
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				arrow.up();
				break;
			case ALLEGRO_KEY_DOWN:
				arrow.down();
				break;
			case ALLEGRO_KEY_LEFT:
				arrow.left();
				break;
			case ALLEGRO_KEY_RIGHT:
				arrow.right();
				break;
			}
		}
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false; 

			if (arrow.getSpeed()!=0){
				arrow.erase_arrow();
				arrow.move_arrow(width,height);
			}
			arrow.drawArrow();
			for(int i=0;i<10;i++)
			{
				mybullet[i].erase_bullet();
				score+=mybullet[i].move_bullet(arrow.getX(),arrow.getY(),64,64,height); //Modified to account for 64x64 bitmap being used
			}
		}
		al_flip_display();
	}
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font);
	al_destroy_font(finalfont);
	al_destroy_display(display);
	//destroy our display object
	system("pause");
	return 0;
}
