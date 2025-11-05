#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <list>
#include <ctime>
#include <cmath>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

#define Width 480
#define Height 720
#define NWidth 50
#define NHeight 100
#define BSPEED 5
#define OFFSET 10
#define MAX_ENEMY_NUM 10

class object
{
public:
	int x;
	int y;
	int speed;
	bool active;
	IMAGE im1;
	IMAGE im2;
};

void initgame(object& player, object& bullet, object& enemy)
{
	int random = rand() % (Width - NWidth / 2) + NWidth / 2;
	player.x = Width / 2;
	player.y = Height - 100;
	player.speed = BSPEED;
	player.active = true;
	bullet.x = player.x;
	bullet.y = player.y;
	bullet.speed = player.speed * 2;
	bullet.active = true;
	enemy.x = random;
	enemy.y = NHeight / 4;
	enemy.speed = player.speed / 2;
	enemy.active = true;
	mciSendString("open \"D:/little_game/music/bgm.mp3\"", 0, 0, 0);
}
void loadgraph(object& player, IMAGE& background, object& bullet, object& enemy)
{
	loadimage(&background, _T("D:\\little_game\\Í¼Æ¬ËØ²Ä\\±³¾°.png"), Width, Height);
	loadimage(&player.im1, _T("D:\\little_game\\Í¼Æ¬ËØ²Ä\\ÑÚ·É»ú.png"), NWidth, NHeight);
	loadimage(&player.im2, _T("D:\\little_game\\Í¼Æ¬ËØ²Ä\\Ô´·É»ú.png"), NWidth, NHeight);
	loadimage(&bullet.im1, _T("D:\\little_game\\Í¼Æ¬ËØ²Ä\\ÑÚ×Óµ¯.png"), NWidth / 5, NHeight / 5);
	loadimage(&bullet.im2, _T("D:\\little_game\\Í¼Æ¬ËØ²Ä\\×Óµ¯.png"), NWidth / 5, NHeight / 5);
	loadimage(&enemy.im1, _T("D:\\little_game\\Í¼Æ¬ËØ²Ä\\ÑÚµÐ»ú.png"), NWidth / 2 + OFFSET, NHeight / 2 + OFFSET);
	loadimage(&enemy.im2, _T("D:\\little_game\\Í¼Æ¬ËØ²Ä\\Ô´µÐ»ú.png"), NWidth / 2 + OFFSET, NHeight / 2 + OFFSET);
}
void playbgm()
{
	mciSendString("play \"D:/little_game/music/bgm.mp3\" repeat", 0, 0, 0);
}
void drawgraph(int& score, int twidth, int theight, object& player, IMAGE& background, list<object>& bullets, list<object>& enemies)
{
	TCHAR s[4];
	putimage(0, 0, &background);
	outtextxy(0, 0, "·ÖÊý£º");
	twidth = textwidth("·ÖÊý£º");
	_stprintf(s, _T("%d"), score);
	outtextxy(twidth, 0, s);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	putimage(player.x, player.y, &(player.im1), NOTSRCERASE);
	putimage(player.x, player.y, &(player.im2), SRCINVERT);
	for (object& bullet: bullets)
	{
		putimage(bullet.x, bullet.y, &(bullet.im1), NOTSRCERASE);
		putimage(bullet.x, bullet.y, &(bullet.im2), SRCINVERT);
	}
	for(object& enemy: enemies)
	{
		putimage(enemy.x, enemy.y, &(enemy.im1), NOTSRCERASE);
		putimage(enemy.x, enemy.y, &(enemy.im2), SRCINVERT);
	}
}
void playermove(object& player)
{
	if (GetAsyncKeyState(VK_UP)|| GetAsyncKeyState('W'))
	{
		player.y -= player.speed;
	}
	if (GetAsyncKeyState(VK_DOWN)|| GetAsyncKeyState('S'))
	{
		player.y += player.speed;
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
		player.x -= player.speed;
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	{
		player.x += player.speed;
	}
	if (player.x < 0)
	{
		player.x = Width;
	}
	if (player.x > Width)
	{
		player.x = 0;
	}
	if (player.y < 0)
	{
		player.y = Height;
	}
	if (player.y > Height)
	{
		player.y = 0;
	}
}
void makebullet(list<object>& bullets, object& player, const object& bullet)
{
	object b;
	b.x = player.x + NWidth / 2;
	b.y = player.y - NHeight / 2;
	b.speed = bullet.speed;
	b.active = bullet.active;
	b.im1 = bullet.im1;
	b.im2 = bullet.im2;
	bullets.push_back(b);
}
void shootbullet(object& player, list<object>& bullets, const object& bullet)
{
	static DWORD shoottime = GetTickCount();
	if (GetAsyncKeyState(VK_SPACE) && GetTickCount() - shoottime > 200)
	{
		PlaySound("D:/little_game/music/shootingsound.wav", NULL, SND_FILENAME | SND_ASYNC);
		makebullet(bullets, player, bullet);
		shoottime = GetTickCount();
	}
	for (object& b : bullets)
	{
		b.y -= b.speed;
	}
}
void mkenemy(int& score, list<object>& enemies, object& enemy)
{
	clock_t now = clock();
	static int last = 0;
	int interval = 1000 - (score / 20) * 100;
	if (interval < 400)
	{
		interval = 400;
	}
	if (enemies.size() <= MAX_ENEMY_NUM && now - last > interval)
	{
		object e;
		e.x = rand() % (Width - NWidth) + NWidth / 2;
		e.y = enemy.y;
		e.speed = enemy.speed;
		e.active = enemy.active;
		e.im1 = enemy.im1;
		e.im2 = enemy.im2;
		enemies.push_back(e);
		last = now;
	}
}
void enemymove(list<object>& enemies)
{
	for (object& e : enemies)
	{
		e.y += e.speed;
	}
}
void clearobject(int& score, list<object>& bullets, list<object>& enemies, bool& gamestate)
{
	for(object& b: bullets)
	{
		if (b.y <= 0)
		{
			b.active = false;
		}
	}
	for (object& e : enemies)
	{
		if (e.y >= Height)
		{
			e.active = false;
			gamestate = false;
		}
	}
	for (object& b : bullets)
	{
		for (object& e : enemies)
		{
			if (e.active && abs(b.x - e.x) <= NWidth/4 + OFFSET && abs(b.y - e.y) <= NHeight / 4 + OFFSET)
			{
				b.active = false;
				e.active = false;
				score++;
			}
		}
	}
	for (list<object>::iterator it = bullets.begin(); it != bullets.end();)
	{
		if (it->active == false)
		{
			it = bullets.erase(it);
			PlaySound("D:/little_game/music/explosion.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
		else
		{
			it++;
		}
	}
	for (list<object>::iterator ite = enemies.begin(); ite != enemies.end();)
	{
		if (ite->active == false)
		{
			ite = enemies.erase(ite);
		}
		else
		{
			ite++;
		}
	}
}
void playerlive(object& player, list<object> enemies, bool& gamestate)
{
	for (object em : enemies)
	{
		if (abs(em.x - player.x) < NWidth * 3 / 4 && abs(em.y - player.y) < NHeight * 3 / 4)
		{
			player.active = false;
			gamestate = false;
		}
	}
}
void gameover()
{
	mciSendString("stop \"D:/little_game/music/bgm.mp3\"", 0, 0, 0);
	if (IDOK == MessageBox(GetHWnd(), "ÓÎÏ·½áÊø", "ÌáÊ¾", MB_OK))
	{
		closegraph();
		exit(0);
	}
}