#pragma once

#include "Object.h"
#include "Digger.h"
#include "Enemy.h"
#include "Window.h"
#include "Diamond.h"
#include "Projectile.h"
#include "Text.h"
#include "Shield.h"

#include <SDL_ttf.h>


#include <vector>
#include <queue>;
using std::vector;

const size_t rows = 10;
const size_t cols = 20;

class Table
{
private:
	size_t digger_x;
	size_t digger_y;

	Digger* digger;
	//Shield* shield;
	Object* objects[rows][cols] = { NULL, };
	vector<Enemy*> enemy_collection;
	vector<Diamond*> diamond_collection;
	vector<Projectile*> projectile_collection;


	Window window;
	SDL_Renderer* renderer;
	Text* text;


private:
	void init(size_t);
	void reset_game();
	void clean();
	//void spawn_shield();

public:
	
	void is_functioning();
	Table();
	~Table();

	void render_everyone(const vector<std::string>& directions, const std::string digger_direction);
	vector<std::string> move_enemies();

	void add_enemy();
	void move(SDL_Event& event, SDL_Renderer* renderer);
	void draw(SDL_Event& event);

	void add_queue(std::queue<std::pair<Object*, const std::string>>&, Object* cell, bool** taken, const std::string& parent);

	bool enemy_canMove_left(Enemy* enemy);
	bool enemy_canMove_right(Enemy* enemy);
	bool enemy_canMove_up(Enemy* enemy);
	bool enemy_canMove_down(Enemy* enemy);

	
};

