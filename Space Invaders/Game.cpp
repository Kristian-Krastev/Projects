#include "Game.h"
#include <Windows.h>


Game::Game()
{
	
	hero = Hero::getInstance();
}


Game::~Game()
{
	
}

void Game::start()
{
	while (true) {
		std::cout << "				SPACE INVADERS										\n";
		std::cout << "----------------------------------------------------------------------------------\n";
		std::cout << "1. START\n";
		std::cout << "2. CONTINUE\n";
		std::cout << "3. EXIT\n";
		std::cout << "----------------------------------------------------------------------------------\n";

		char c = 3;
		char buff[32];
		std::cin.getline(buff, 32);

		if (atoi(buff) == 2) {
			try {
				continueGame();
			} catch (std::exception&) {
				continue;
			}
		}
		if (atoi(buff) == 1 || atoi(buff) == 2) {
			while (true) {
				if (hero->getLives() == 0) {
					matrix.clean();
					matrix.gameOver();
					matrix.draw();
					Sleep(100);
					system("CLS");
					matrix.clean();
					projectiles.removeAllProjectiles();
					enemies.removeAllEnemies();
					hero->reset();
					hero->extraLive();	//so that the player can start the game again
					hero->extraLive();
					hero->extraLive();
					score = 0;
					break;
				}
				std::cout << "Lives: ";
				for (int i = 0; i < hero->getLives(); i++) {
					std::cout << ' ' << c;
				}
				std::cout << "                                                           Score: " << score << '\n';
				std::cout << "----------------------------------------------------------------------------------\n";

				int random = rand() % 30 + 1;				
				if (random > 23 && enemies.getSize() < 10){		//to prevent generating enemies all the time
					Enemy* enemy = nullptr;
					int r = rand() % 18 + 1;
					int generateLv = rand() % 3;
					switch (generateLv) {
					case 0: enemy = new EnemyLv1(75, r); break;
					case 1: enemy = new EnemyLv2(75, r); break;
					case 2: enemy = new EnemyLv3(75, r); break;
					}
					enemies.addEnemy(enemy);
				}

				if (GetAsyncKeyState(VK_UP)) {
					hero->moveUp();
				}
				else if (GetAsyncKeyState(VK_DOWN)) {
					hero->moveDown();
				}
				else if (GetAsyncKeyState(VK_LEFT)) {
					hero->moveLeft();
				}
				else if (GetAsyncKeyState(VK_RIGHT)) {
					hero->moveRight();
				}
				else if (GetAsyncKeyState(VK_SPACE)) {
					HeroProjectile h(hero->getX() + 2, hero->getY());
					projectiles.addHeroProjectile(h);
				}
				else if (GetAsyncKeyState(VK_F2)) {
					save();
				}
				else if (GetAsyncKeyState(VK_ESCAPE)) {
					break;
				}
				if ((projectiles.isInCollisionWithEnemyP(hero->getX(), hero->getY()))
					|| (enemies.isInCollisionWIthHero(hero->getX(), hero->getY()))) {

					hero->reduceLives();
					hero->reset();
					projectiles.removeAllProjectiles();
					matrix.clean();
				}

				projectiles.moveAllProj();
				enemies.move(projectiles, hero);

				hero->visualize(matrix);
				projectiles.visualize(matrix);
				enemies.visualize(matrix);


				matrix.draw();

				Sleep(200);
				system("CLS");
				matrix.clean();
			}
		}
		else if (atoi(buff) == 3) {
			system("CLS");
			std::cout << "Goodbye :)\n";
			Sleep(750);
			break;
		}
		else {
			std::cout << "unknown command... \n";
			Sleep(300);
			system("CLS");
			continue;
		}
		system("CLS");
	}
}

void Game::save()
{
	std::ofstream ofs("Saved.txt", std::ios::trunc);
	if (!ofs.is_open()) {

		throw std::exception("Couldn't save the current progress... :(\n");
	}
	hero->write(ofs);
	enemies.write(ofs);
	ofs << "f" << std::endl;
	projectiles.write(ofs);
	ofs << "s" << std::endl;


	ofs.close();
}

void Game::continueGame()
{
	std::ifstream ifs("Saved.txt");
	if (!ifs.is_open()) {

		throw std::exception("Couldn't open the saved game... :(\n");
	}
	char c;
	hero->read(ifs);
	ifs >> c;
	while (c != 'f') {
		Enemy* newEn = nullptr;
		switch (c) {
		case '1': newEn = new EnemyLv1();
			newEn->read(ifs);
			break;
		case '2':newEn = new EnemyLv2();
			newEn->read(ifs);
			break;
		case '3':newEn = new EnemyLv3();
			newEn->read(ifs);
			break;

		default: std::cout << "Error!\n"; break;
		}
		enemies.addEnemy(newEn);

		ifs >> c;
	}
	ifs >> c;
	while (c != 's') {
		
		EnemyProjectile ep;
		HeroProjectile hp;
		switch (c) {
		case 'e': ep.read(ifs);
			projectiles.addEnemyProjectile(ep);
			break;
		case 'h': hp.read(ifs);
			projectiles.addHeroProjectile(hp);
			break;

		default: std::cout << "Error!\n"; break;
		}

		ifs >> c;
	}


	ifs.close();
}
