#include "bullet.h"

bullet::bullet()
{
	alive = false;;
	srand(time(0));
	bullet_bmp[1] = NULL;
}
bullet::~bullet()
{
	al_destroy_bitmap(bullet_bmp[1]);
}
void bullet::drawBullet()
{
	al_draw_bitmap(bullet_bmp[1], getX(), getY(), 0);
}
void bullet::create_bullet_bitmap(ALLEGRO_DISPLAY* display)
{
	bullet_bmp[1] = al_create_bitmap(8, 8);
	if (!bullet_bmp[1]) {
		exit(1);
		al_destroy_display(display);

	}
	al_set_target_bitmap(bullet_bmp[1]);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	int x = 0;
	int y = 0;
	al_draw_filled_rectangle(x, y, x + 8, y + 8, al_map_rgb(255, 0, 0));
	al_draw_filled_circle(x + 4, y + 4, 3, al_map_rgb(0, 255, 0));
}
bool bullet::getStatus()
{
	return alive;
}

void bullet::fire()
{
	x=rand()%615+10;
	y = 10;
	alive=true;

}
void bullet::erase_bullet()
{
	al_draw_filled_rectangle(x, y, x + 8, y + 8, al_map_rgb(0, 0, 0));
	al_draw_filled_circle(x + 4, y + 4, 3, al_map_rgb(0, 0, 0));
}
int bullet::move_bullet (int arrowX, int arrowY, int width, int length, int height)
{
	y++;
	al_draw_filled_rectangle(x, y, x + 8, y + 8, al_map_rgb(255, 0, 0));
	al_draw_filled_circle(x + 4, y + 4, 3, al_map_rgb(0, 255, 0));


	if (x > arrowX && x < arrowX+width && y > arrowY && y < arrowY+length) {
		al_draw_filled_rectangle(x,y,x+8,y+8,al_map_rgb(0,0,0)); //BLACK
		al_draw_filled_circle(x + 4, y + 4, 3, al_map_rgb(0, 0, 0));
		alive=false;
		return 1;
	}
	if (y> height-40)
		alive = false;
	return 0;


}
int bullet::getX()
{
	return x;
}
int bullet::getY()
{
	return y;
}


