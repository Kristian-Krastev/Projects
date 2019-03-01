#include "Table.h"
#include <random>
#include <time.h>
#include "Dirt.h"
#include "Tunnel.h"
#include <Windows.h>

using std::queue;


const std::string dirt = "wood.png";
const std::string digg = "face.png";
const std::string digg_r = "face_r.png";
const std::string enemy = "jiren.png";
const std::string tunnel = "square.png";
const std::string currency = "db_";
const std::string proj = "kamehameha1.png";
const std::string game_over = "gameover.png";


const size_t enemy_spawn_x = 19;
const size_t enemy_spawn_y = 0;

void Table::init(size_t random_generator)
{

	if (TTF_Init() == -1) {
		std::cerr << "Failed to initialize SDL_ttf\n";
	}


	srand(time(NULL));

	objects[0][19] = new Tunnel(80, 80, 19, 0, tunnel, renderer);
	objects[1][19] = new Tunnel(80, 80, 19, 1, tunnel, renderer);
	objects[0][18] = new Tunnel(80, 80, 18, 0, tunnel, renderer);
	objects[1][18] = new Tunnel(80, 80, 18, 1, tunnel, renderer);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int random = rand() % random_generator;
			if (random == 0 && !(i == 8 && j == 18) && !(i == enemy_spawn_y && j == enemy_spawn_x) && objects[i][j] == nullptr) {
				objects[i][j] = new Dirt(80, 80, j, i, dirt, renderer);

			}
		}
	}

	Enemy* jiren = new Enemy(80, 80, enemy_spawn_x, enemy_spawn_y, enemy, renderer);
	enemy_collection.push_back(jiren);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (objects[i][j] == nullptr) {
				objects[i][j] = new Tunnel(80, 80, j, i, tunnel, renderer);
			}
		}
	}

	Diamond* diamond_element = nullptr;
	vector<std::pair<int, int>> positions;

	bool already_exists;
	while(positions.size() < 7) {
		already_exists = false;

		int x_pos = rand() % 20;
		int y_pos = rand() % 10;
		if ((x_pos == 0 && y_pos == 19) || (x_pos == 1 && y_pos == 19) || (x_pos == 0 && y_pos == 18)	//so that we dont place diamonds where the enemies are
			|| (x_pos == digger_x && y_pos == digger_y)	|| (x_pos == 1 && y_pos == 18) 
			|| (x_pos == 0 && y_pos == 17) || (x_pos == 1 && y_pos == 17)) {
			continue;
		}
		for (int i = 0; i < positions.size(); i++) {	//so that we dont place two diamonds on the same place
			if (positions[i].first == x_pos && positions[i].second == y_pos) {
				already_exists = true;
				break;
			}
		}
		if (already_exists) {
			continue;
		}
		positions.push_back(std::make_pair(x_pos, y_pos));
	}
	for (int i = 0; i < positions.size(); i++) {

		std::string img = currency;
		img.push_back((i + 1) + '0');
		img.append(".png");

		diamond_element = new Diamond(80, 80, positions[i].first, positions[i].second, img, renderer);
		diamond_collection.push_back(diamond_element);

	}

	text = new Text("GOUDYSTO.ttf", 50, "Score: ", { 0, 0, 0, 255 }, renderer);

}

void Table::reset_game()
{
	//clean
	init(3);
}

void Table::clean()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			delete objects[i][j];
			objects[i][j] = nullptr;
		}
	}
	
	for (int i = enemy_collection.size() - 1; i >= 0; --i) {

		delete enemy_collection[i];
		enemy_collection.pop_back();
	}
	for (int i = diamond_collection.size() - 1; i >= 0; --i) {

		delete diamond_collection[i];
		diamond_collection.pop_back();
	}
	for (int i = projectile_collection.size() - 1; i >= 0; --i) {

		delete projectile_collection[i];
		projectile_collection.pop_back();
	}
	
	digger->change_X(18);
	digger->change_Y(8);
	this->digger_x = digger->get_x();
	this->digger_y = digger->get_y();
	digger->remove_shot();
}

//void Table::spawn_shield()
//{
//	bool** taken = new bool*[rows];
//	for (int i = 0; i < rows; i++) {
//		taken[i] = new bool[cols];
//		for (int j = 0; j < cols; j++) {
//			taken[i][j] = false;
//		}
//	}
//
//	vector<vector<std::string>> vector_directions;
//	int i = 0;
//	for (Enemy* enemy : enemy_collection) {
//		int enemy_x = enemy->get_x();
//		int enemy_y = enemy->get_y();
//		vector_directions.push_back(vector<std::string>(0));
//		while (!(enemy_x == digger_x && enemy_y == digger_y)) {
//
//			queue <std::pair <Object*, const std::string>> wave;
//
//			add_queue(wave, digger, taken, "right");
//			add_queue(wave, digger, taken, "left");
//			add_queue(wave, digger, taken, "down");
//			add_queue(wave, digger, taken, "up");
//
//
//			while (!wave.empty()) {
//				std::pair<Object*, const std::string> front_cell = wave.front();
//				if (front_cell.first->get_x() == enemy_x && front_cell.first->get_y() == enemy_y) {
//					if (front_cell.second == "left") {
//						enemy_x--;
//						vector_directions[i].push_back("left");
//						break;
//					}
//					else if (front_cell.second == "right") {
//						enemy_x++;
//						vector_directions[i].push_back("right");
//						break;
//					}
//					else if (front_cell.second == "up") {
//						enemy_y--;
//						vector_directions[i].push_back("up");
//						break;
//					}
//					else if (front_cell.second == "down") {
//						enemy_y++;
//						vector_directions[i].push_back("down");
//						break;
//					}
//				}
//
//				add_queue(wave, front_cell.first, taken, "right");
//				if (wave.back().first->get_x() == enemy_x && wave.back().first->get_y() == enemy_y) { // if we have found the shortest path to the target
//					vector_directions[i].push_back(wave.back().second);
//					enemy_x++;
//					break;
//				}
//				add_queue(wave, front_cell.first, taken, "left");
//				if (wave.back().first->get_x() == enemy_x && wave.back().first->get_y() == enemy_y) {
//					vector_directions[i].push_back(wave.back().second);
//					enemy_x--;
//					break;
//				}
//				add_queue(wave, front_cell.first, taken, "down");
//				if (wave.back().first->get_x() == enemy_x && wave.back().first->get_y() == enemy_y) {
//					vector_directions[i].push_back(wave.back().second);
//					enemy_y++;
//					break;
//				}
//				add_queue(wave, front_cell.first, taken, "up");
//				if (wave.back().first->get_x() == enemy_x && wave.back().first->get_y() == enemy_y) {
//					vector_directions[i].push_back(wave.back().second);
//					enemy_y--;
//					break;
//				}
//
//				wave.pop();
//			}
//			for (int i = 0; i < rows; i++) {
//				for (int j = 0; j < cols; j++) {
//					taken[i][j] = false;
//				}
//			}
//		}
//		i++;
//	}
//	size_t min = vector_directions[0].size();;
//	size_t index = 0;
//	for (int j = 0; j < vector_directions.size(); j++) {
//		if (vector_directions[j].size() < min) {
//			min = vector_directions[j].size();
//			index = j;
//		}
//	}
//	int temp_dig_x = digger_x;
//	int temp_dig_y = digger_y;
//
//	for (int j = 0; j < vector_directions[index].size(); j++) {
//		if (vector_directions[index][j] == "left") {
//			if(temp_dig_x > 0)
//			temp_dig_x--;
//		}
//		else if (vector_directions[index][j] == "right") {
//			if(temp_dig_x < cols - 1)
//			temp_dig_x++;
//		}
//		else if (vector_directions[index][j] == "down") {
//			if(temp_dig_y < rows - 1)
//			temp_dig_y++;
//		}
//		else if (vector_directions[index][j] == "up") {
//			if(temp_dig_y > 0)
//			temp_dig_y--;
//		}
//	}
//
//	//shield = new Shield(80, 80, temp_dig_x, temp_dig_y, "shield.png", renderer);
//
//}

void Table::is_functioning()
{
	time_t start = time(0);
	Sleep(1000);
	while (!window.is_closed()) {
		if (digger->is_dead()) {
			break;
		}
		double seconds_since_start = difftime(time(0), start);
		std::cout << seconds_since_start << std::endl;
		/*if (text->get_score() >= 1500) {
			this->spawn_shield();
			text->reset_score();
		}*/
		if ((int)seconds_since_start % 20 == 0) {
			--start;
			add_enemy();
		}
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				//move(event, renderer);
				draw(event);
				window.poll_events(event);
				window.draw(renderer);
				continue;
			}
		}

		else {
			draw(event);
			window.draw(renderer);
		}

	}
	SDL_RenderClear(renderer);
	Object* over = new Dirt(800, 600, 0, 0, game_over, renderer);
	SDL_Rect game_over_rect = { 450, 100, 800, 600 };
	SDL_RenderCopy(renderer, over->texture, nullptr, &game_over_rect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);
	SDL_RenderClear(renderer);
}

Table::Table() :
	window("Digger", 1650, 850),
	renderer(SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED)),
	digger(nullptr)
	//shield(nullptr)
{
	digger = new Digger(80, 80, 18, 8, "face_r.png", renderer);
	digger_x = digger->get_x();
	digger_y = digger->get_y();
	init(2);
}


Table::~Table()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			delete objects[i][j];
			objects[i][j] = nullptr;
		}
	}
	
	delete digger;
	digger = nullptr;
	
	for (int i = enemy_collection.size() - 1; i >= 0; --i) {

		delete enemy_collection[i];
		enemy_collection.pop_back();
	}
	for (int i = diamond_collection.size() - 1; i >= 0; --i) {

		delete diamond_collection[i];
		diamond_collection.pop_back();
	}
	for (int i = projectile_collection.size() - 1; i >= 0; --i) {

		delete projectile_collection[i];
		projectile_collection.pop_back();
	}

	delete text;
	text = nullptr;

	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

std::vector<std::string> Table::move_enemies()
{
	bool** taken = new bool*[rows];
	for (int i = 0; i < rows; i++) {
		taken[i] = new bool[cols];
		for (int j = 0; j < cols; j++) {
			taken[i][j] = false;
		}
	}

	vector<std::string> directions;

	bool in_collision_with_diger = false;
	for (Enemy* enemy : enemy_collection) {
		bool path_to_digger = false;
		queue <std::pair <Object*, const std::string>> wave;


		add_queue(wave, digger, taken, "right");
		add_queue(wave, digger, taken, "left");
		add_queue(wave, digger, taken, "down");
		add_queue(wave, digger, taken, "up");


		while (!wave.empty()) {
			std::pair<Object*, const std::string> front_cell = wave.front();

			if (front_cell.first->get_x() == enemy->get_x() && front_cell.first->get_y() == enemy->get_y()) {
				directions.push_back(front_cell.second);
				enemy->move(front_cell.second);
				path_to_digger = true;
				in_collision_with_diger = true;
				break;
			}

			add_queue(wave, front_cell.first, taken, "right");
			if (wave.back().first->get_x() == enemy->get_x() && wave.back().first->get_y() == enemy->get_y()) { // if we have found the shortest path to the target
				directions.push_back(wave.back().second);
				enemy->move(wave.back().second);
				std::cout << "Enemy moving " << front_cell.second << std::endl;
				path_to_digger = true;
				break;
			}
			add_queue(wave, front_cell.first, taken, "left");
			if (wave.back().first->get_x() == enemy->get_x() && wave.back().first->get_y() == enemy->get_y()) {
				directions.push_back(wave.back().second);
				enemy->move(wave.back().second);
				std::cout << "Enemy moving " << front_cell.second << std::endl;

				path_to_digger = true;
				break;
			}
			add_queue(wave, front_cell.first, taken, "down");
			if (wave.back().first->get_x() == enemy->get_x() && wave.back().first->get_y() == enemy->get_y()) {
				directions.push_back(wave.back().second);
				enemy->move(wave.back().second);
				std::cout << "Enemy moving " << front_cell.second << std::endl;

				path_to_digger = true;
				break;
			}
			add_queue(wave, front_cell.first, taken, "up");
			if (wave.back().first->get_x() == enemy->get_x() && wave.back().first->get_y() == enemy->get_y()) {
				directions.push_back(wave.back().second);
				enemy->move(wave.back().second);
				std::cout << "Enemy moving " << front_cell.second << std::endl;

				path_to_digger = true;
				break;
			}

			wave.pop();
		}

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				taken[i][j] = false;
			}
		}
		if (!path_to_digger) { // if there isn't a path to the digger
			if (enemy_canMove_right(enemy)) {
				//render_enemy(enemy, "right");
				directions.push_back("right");
				enemy->move("right");
				continue;
			}
			if (enemy_canMove_down(enemy)) {
				//render_enemy(enemy, "down");
				directions.push_back("down");
				enemy->move("down");
				continue;
			}
			if (enemy_canMove_left(enemy)) {
				//render_enemy(enemy, "left");
				directions.push_back("left");
				enemy->move("left");
				continue;
			}
			if (enemy_canMove_up(enemy)) {
				//render_enemy(enemy, "up");
				directions.push_back("up");
				enemy->move("up");
				continue;
			}
		}
	}
	for (int i = 0; i < rows; i++) {
		delete[] taken[i];
	}
	delete[] taken;

	if (in_collision_with_diger) {

		digger->reduce_lives();
	}

	return directions;
}

void Table::render_everyone(const vector<std::string>& directions, const std::string digger_direction)
{
	bool collision_exists = false;
	for (int i = 0; i < 40; i++) {

		SDL_RenderClear(renderer);

		for (int k = 0; k < rows; k++) {
			for (int j = 0; j < cols; j++) {
				objects[k][j]->draw(renderer);
			}
		}

		bool projectiles_moving = false;
		if (enemy_collection.size() != 0) {
			for (int k = 0; k < enemy_collection.size(); k++) {
				if (projectile_collection.size() != 0) {
					projectiles_moving = true;
					projectile_collection.shrink_to_fit();
					for (Projectile* projectile : projectile_collection) {
						projectile->draw(renderer);
					}
					size_t proj_size = projectile_collection.size();
					for (int k = proj_size - 1; k >= 0; --k) {
						delete projectile_collection[k];
						projectile_collection[k] = nullptr;
						projectile_collection.pop_back();
					}
				}
				SDL_Rect rect = { enemy_collection[k]->get_x(), enemy_collection[k]->get_y(), 80, 80 };
				if (directions.size() != 0 && directions[k] == "left") {
					rect.x = (rect.x + 1) * 80;
					rect.x -= i * 2;
					rect.y *= 80;
				}
				else if (directions.size() != 0 && directions[k] == "right") {
					rect.x = (rect.x - 1) * 80;
					rect.x += i * 2;
					rect.y *= 80;
				}
				else if (directions.size() != 0 && directions[k] == "up") {
					rect.y = (rect.y + 1) * 80;
					rect.y -= i * 2;
					rect.x *= 80;
				}
				else if (directions.size() != 0 && directions[k] == "down") {
					rect.y = (rect.y - 1) * 80;
					rect.y += i * 2;
					rect.x *= 80;
				}
				if (enemy_collection[k]->get_x() == digger_x && enemy_collection[k]->get_y() == digger_y) {
					collision_exists = true;
				}
				SDL_Rect digger_rect = { digger_x * 80, digger_y * 80, 80, 80 };
				if (!collision_exists && (digger_direction == "left" || digger_direction == "right" || digger_direction == "up" || digger_direction == "down")) {
					if (digger_direction == "left") {
						digger_rect.x++;
						digger_rect.x -= i * 2;
					}
					else if (digger_direction == "right") {
						digger_rect.x--;
						digger_rect.x += i * 2;
					}
					else if (digger_direction == "up") {
						digger_rect.y++;
						digger_rect.y -= i * 2;
					}
					else if (digger_direction == "down") {
						digger_rect.y--;
						digger_rect.y += i * 2;
					}
				}
				SDL_RenderCopy(renderer, digger->texture, nullptr, &digger_rect);
				SDL_RenderCopy(renderer, enemy_collection[k]->texture, nullptr, &rect);
			}
		}
		else {
			SDL_Rect digger_rect = { digger_x * 80, digger_y * 80, 80, 80 };
			if (digger_direction == "left" || digger_direction == "right" || digger_direction == "up" || digger_direction == "down") {
				if (digger_direction == "left") {
					digger_rect.x++;
					digger_rect.x -= i * 2;
				}
				else if (digger_direction == "right") {
					digger_rect.x--;
					digger_rect.x += i * 2;
				}
				else if (digger_direction == "up") {
					digger_rect.y++;
					digger_rect.y -= i * 2;
				}
				else if (digger_direction == "down") {
					digger_rect.y--;
					digger_rect.y += i * 2;
				}
			}
			SDL_RenderCopy(renderer, digger->texture, nullptr, &digger_rect);
		}
		for (Diamond* element : diamond_collection) {
			element->draw(renderer);
		}
		/*if (shield != nullptr) {
			shield->draw(renderer);
		}*/
		text->display(100, 790, renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderPresent(renderer);
		if (projectiles_moving) {
			SDL_Delay(300);
		}
	}
	SDL_RenderClear(renderer);
	if (collision_exists) {
		clean();
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderPresent(renderer);
		init(2);
	}
}

void Table::add_enemy()
{
	Enemy* jiren = new Enemy(80, 80, enemy_spawn_x, enemy_spawn_y, enemy, renderer);
	enemy_collection.push_back(jiren);

}

void Table::move(SDL_Event & event, SDL_Renderer* renderer)
{
	for (std::vector<Diamond*>::iterator it = diamond_collection.begin(); it != diamond_collection.end(); ++it) {
		if (digger_x == (*it)->get_x() && digger_y == (*it)->get_y()) {
			diamond_collection.erase(it);
			text->add_to_Score(200);
			break;
		}
	}

	if (diamond_collection.size() == 0) { //if the digger has taken all 7 items he can shoot
		digger->load_shot();
	}

	
	bool moved = false;
	bool moved_d = false;
	bool moved_u = false;
	bool moved_l = false;
	int i = 1;
	int i_d = 1;
	int i_u = 1;
	int i_l = 1;

	size_t lives_before_collision = digger->getLives();
	vector<std::string> directions = move_enemies();
	bool is_moving = false;
	if (lives_before_collision == digger->getLives()) {

		if (event.type == SDL_KEYDOWN) {
			is_moving = true;
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				if (digger->can_shoot()) {
					if (digger->get_name() == digg_r) {
						for (int i = digger_x + 1; i < cols; ++i) {
							if (objects[digger_y][i]->get_name() != tunnel) {
								delete objects[digger_y][i];
								objects[digger_y][i] = new Tunnel(80, 80, i, digger_y, tunnel, renderer);
								text->add_to_Score(50);
							}
						}

						size_t enemy_col_size = enemy_collection.size();
						for (int i = 0; i < enemy_col_size; ++i) {
							for (std::vector<Enemy*>::iterator it = enemy_collection.begin(); it != enemy_collection.end(); ++it) {
								if (digger_y == (*it)->get_y() && (*it)->get_x() >= digger_x) {
									enemy_collection.erase(it);
									text->add_to_Score(200);
									break;
								}
							}
						}
						enemy_collection.shrink_to_fit();
						for (int i = digger_x + 1; i < cols; ++i) {
							Projectile* shot = new Projectile(80, 80, i, digger_y, proj, renderer);
							projectile_collection.push_back(shot);
						}
					}

					else if (digger->get_name() == digg) {
						for (int i = 0; i < digger_x; ++i) {
							if (objects[digger_y][i]->get_name() != tunnel) {
								delete objects[digger_y][i];
								objects[digger_y][i] = new Tunnel(80, 80, i, digger_y, tunnel, renderer);
								text->add_to_Score(50);
							}
						}
						size_t enemy_col_size = enemy_collection.size();
						for (int i = 0; i < enemy_col_size; ++i) {
							for (std::vector<Enemy*>::iterator it = enemy_collection.begin(); it != enemy_collection.end(); ++it) {
								if (digger_y == (*it)->get_y() && (*it)->get_x() <= digger_x) {
									enemy_collection.erase(it);
									text->add_to_Score(100);
									break;
								}
							}
						}
						enemy_collection.shrink_to_fit();
						for (int i = 0; i < digger_x; ++i) {
							Projectile* shot = new Projectile(80, 80, i, digger_y, proj, renderer);
							projectile_collection.push_back(shot);
						}
					}

				}
				break;
			case SDLK_DOWN:
				if (digger_y < rows - 1) {
					//render_digger("down");
					render_everyone(directions, "down");
					this->digger_y++;
					digger->poll_events(event);
					moved_d = true;
				}
				if (moved_d == true) {
					i_d = 0;
				}
				if (moved_d == false) {
					render_everyone(directions, "");
					break;
				}
				if (digger_y < rows && objects[digger_y + i_d][digger_x]->get_name() == dirt) {
					delete[] objects[digger_y + i_d][digger_x];
					objects[digger_y + i_d][digger_x] = new Tunnel(80, 80, digger_x, digger_y + i_d, "square.png", renderer);
					text->add_to_Score(50);
				}
				break;
			case SDLK_UP:
				if (digger_y) {
					//render_digger("up");
					render_everyone(directions, "up");
					this->digger_y--;
					digger->poll_events(event);
					moved_u = true;
				}
				if (moved_u == true) {
					i_u = 0;
				}
				if (moved_u == false) {
					render_everyone(directions, "");
					break;
				}
				if (digger_y >= 0 && objects[digger_y - i_u][digger_x]->get_name() == dirt) {
					delete[] objects[digger_y - i_u][digger_x];
					objects[digger_y - i_u][digger_x] = new Tunnel(80, 80, digger_x, digger_y - i_u, "square.png", renderer);
					text->add_to_Score(50);
				}
				break;
			case SDLK_LEFT:
				if (digger_x) {
					if (digger->is_right_side()) {
						digger->change_side(digg, renderer);
					}
					//render_digger("left");
					render_everyone(directions, "left");
					this->digger_x--;
					digger->poll_events(event);
					moved_l = true;
				}
				if (moved_l == true) {
					i_l = 0;
				}
				if (moved_l == false) {
					render_everyone(directions, "");
					break;
				}
				if (digger_x >= 0 && objects[digger_y][digger_x - i_l]->get_name() == dirt) {
					delete[] objects[digger_y][digger_x - i_l];
					objects[digger_y][digger_x - i_l] = new Tunnel(80, 80, digger_x - i_l, digger_y, "square.png", renderer);
					text->add_to_Score(50);
				}
				break;
			case SDLK_RIGHT:
				if (digger_x < cols - 1) {
					if (digger->is_left_side()) {
						digger->change_side(digg_r, renderer);
					}
					//render_digger("right");
					render_everyone(directions, "right");
					this->digger_x++;
					digger->poll_events(event);
					moved = true;
				}
				if (moved == true) {
					i = 0;
				}
				if (moved == false) {
					render_everyone(directions, "");
					break;
				}
				if (digger_x < cols && objects[digger_y][digger_x + i]->get_name() == dirt) {
					delete[] objects[digger_y][digger_x + i];
					objects[digger_y][digger_x + i] = new Tunnel(80, 80, digger_x + i, digger_y, "square.png", renderer);
					text->add_to_Score(50);
				}
				break;
			default: break;
			}
		}
	}
	if (!is_moving) {

		render_everyone(directions, "");
	}
}

void Table::draw(SDL_Event& event)
{
	SDL_RenderClear(renderer);
	size_t lives_before_collision = digger->getLives();
	move(event, renderer);
	if (lives_before_collision != digger->getLives()) {
		return;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			objects[i][j]->draw(renderer);
		}	
	}
	
	if (enemy_collection.size() != 0) {
		for (Enemy* enemy : enemy_collection) {
			enemy->draw(renderer);
		}
	}
	if (diamond_collection.size() != 0) {
		for (Diamond* diamond : diamond_collection) {
			diamond->draw(renderer);
		}
	}
	bool proj_moveing = false;
	if (projectile_collection.size() != 0) {
		proj_moveing = true;
		projectile_collection.shrink_to_fit();
		for (Projectile* projectile : projectile_collection) {
			projectile->draw(renderer);
		}
		size_t proj_size = projectile_collection.size();
		for (int k = proj_size - 1; k >= 0; --k) {
			delete projectile_collection[k];
			projectile_collection[k] = nullptr;
			projectile_collection.pop_back();
		}
	}

	digger->draw(renderer);
	/*if (shield != nullptr) {
		shield->draw(renderer);
	}*/
	text->display(100, 790, renderer);
	SDL_RenderPresent(renderer);
	if (proj_moveing) {
		SDL_Delay(500);
	}
}

void Table::add_queue(std::queue<std::pair<Object*, const std::string>>& wave, Object * cell, bool ** taken, const std::string & parent)
{
	if (parent == "up") {
		if (cell->get_y() >= 0 && cell->get_y() < rows - 1 && objects[cell->get_y() + 1][cell->get_x()]->get_name() == tunnel) {
			if (!taken[cell->get_y() + 1][cell->get_x()]) {
				//adding the one on the down side
				wave.push(std::make_pair(objects[cell->get_y() + 1][cell->get_x()], parent));
				taken[cell->get_y() + 1][cell->get_x()] = true;
			}
		}
	}
	else if (parent == "down") {
		if (cell->get_y() > 0 && cell->get_y() < rows && objects[cell->get_y() - 1][cell->get_x()]->get_name() == tunnel) {
			if (!taken[cell->get_y() - 1][cell->get_x()]) {
				//adding the one on the upper side
				wave.push(std::make_pair(objects[cell->get_y() - 1][cell->get_x()], parent));
				taken[cell->get_y() - 1][cell->get_x()] = true;
			}
		}
	}
	else if (parent == "left") {
		if (cell->get_x() >= 0 && cell->get_x() < cols - 1 && objects[cell->get_y()][cell->get_x() + 1]->get_name() == tunnel) {
			if (!taken[cell->get_y()][cell->get_x() + 1]) {
				//adding the one on the right
				wave.push(std::make_pair(objects[cell->get_y()][cell->get_x() + 1], parent));
				taken[cell->get_y()][cell->get_x() + 1] = true;
			}
		}
	}
	else if (parent == "right") {
		if (cell->get_x() > 0 && cell->get_x() < cols && objects[cell->get_y()][cell->get_x() - 1]->get_name() == tunnel) {
			if (!taken[cell->get_y()][cell->get_x() - 1]) { //if we haven't traversed this cell
				//adding the one on the left
				wave.push(std::make_pair(objects[cell->get_y()][cell->get_x() - 1], parent));
				taken[cell->get_y()][cell->get_x() - 1] = true;
			}
		}
	}
}

bool Table::enemy_canMove_left(Enemy * enemy)
{
	if (enemy->get_x() > 0 && objects[enemy->get_y()][enemy->get_x() - 1]->get_name() == tunnel) {
		return true;
	}
	return false;
}

bool Table::enemy_canMove_right(Enemy * enemy)
{
	if (enemy->get_x() < cols - 1 && objects[enemy->get_y()][enemy->get_x() + 1]->get_name() == tunnel) {
		return true;
	}
	return false;
}

bool Table::enemy_canMove_up(Enemy * enemy)
{
	if (enemy->get_y() > 0 && objects[enemy->get_y() - 1][enemy->get_x()]->get_name() == tunnel) {
		return true;
	}
	return false;
}

bool Table::enemy_canMove_down(Enemy * enemy)
{
	if (enemy->get_y() < rows - 1 && objects[enemy->get_y() + 1][enemy->get_x()]->get_name() == tunnel) {
		return true;
	}
	return false;
}