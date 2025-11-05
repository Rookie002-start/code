#include "aircraft.hpp"

void game()
{
	object player;
	object bullet;
	object enemy;
	list<object> bullets;
	list<object> enemies;
	IMAGE background;
	bool gamestate = true;
	int twidth = 0;
	int theight = 0;
	int score = 0;

	srand((unsigned)time(NULL));

	initgraph(Width, Height);

	BeginBatchDraw();

	initgame(player, bullet, enemy);

	loadgraph(player, background, bullet, enemy);
	
	playbgm();

	while (gamestate)
	{
		cleardevice();
		drawgraph(score, twidth, theight, player, background, bullets, enemies);
		playermove(player);
		shootbullet(player, bullets, bullet);
		mkenemy(score, enemies, enemy);
		enemymove(enemies);
		clearobject(score, bullets, enemies, gamestate);
		playerlive(player, enemies, gamestate);
		FlushBatchDraw();
		Sleep(10);
	}
	gameover();
}
int main()
{
	game();
	return 0;
}