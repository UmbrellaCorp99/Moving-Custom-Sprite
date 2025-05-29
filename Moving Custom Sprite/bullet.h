#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>


class bullet
{
public:
	bullet();
	~bullet();
	void create_bullet_bitmap(ALLEGRO_DISPLAY* display);
	void fire();
	int move_bullet(int arrowX, int arrowY, int width, int length, int height);
	void erase_bullet();
	void drawBullet();
	bool getStatus(); 
	int getX();
	int getY();
private:
	int x,y;
	bool alive;
	ALLEGRO_BITMAP* bullet_bmp[1];
};

