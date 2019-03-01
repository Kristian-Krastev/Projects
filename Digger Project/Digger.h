#pragma once
#include "Object.h"

class Digger : public Object
{
private:
	size_t lives = 3;
	bool fire_shot = false;

public:
	Digger(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer*);
	Digger();
	~Digger();

	const size_t getLives() const { return lives; }
	bool is_dead() const { return (lives == 0) ? true : false; }
	void reduce_lives() { --lives; }

	void change_X(size_t new_x) { this->x = new_x; }
	void change_Y(size_t new_y) { this->y = new_y; }
	bool can_shoot()const { return fire_shot; }
	void load_shot() { fire_shot = true; }
	void remove_shot() { fire_shot = false; }
	bool is_left_side();
	bool is_right_side();
	void change_side(const std::string&, SDL_Renderer*);
	void draw(SDL_Renderer* r);
	virtual void poll_events(SDL_Event& event);


};

