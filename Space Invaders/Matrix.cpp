#include "Matrix.h"



Matrix::Matrix()
{
	for (int i = 0; i < MAX_HEIGHT; i++) {
		for (int j = 0; j < MAX_WIDTH; j++) {
			matrix[i][j] = ' ';
		}
	}

}

void Matrix::draw() const
{
	for (int i = 0; i < MAX_HEIGHT; i++) {
		for (int j = 0; j < MAX_WIDTH; j++) {
			std::cout << matrix[i][j];
		}
		std::cout << '\n';
	}

}

void Matrix::gameOver()
{
	setPos(10, 35, 'G');
	setPos(10, 36, 'A');
	setPos(10, 37, 'M');
	setPos(10, 38, 'E');
	setPos(10, 39, ' ');
	setPos(10, 40, 'O');
	setPos(10, 41, 'V');
	setPos(10, 42, 'E');
	setPos(10, 43, 'R');
	setPos(10, 44, '!');
}

void Matrix::setPos(size_t i, size_t j, const char symb)
{
	matrix[i][j] = symb;
}

void Matrix::clean()
{
	for (int i = 0; i < MAX_HEIGHT; i++) {
		for (int j = 0; j < MAX_WIDTH; j++) {
			matrix[i][j] = ' ';
		}
	}
}
