#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <fstream>

static const size_t MAX_HEIGHT = 20;
static const size_t MAX_WIDTH = 80;

class Matrix
{
private:
	char matrix[MAX_HEIGHT][MAX_WIDTH];

public:
	Matrix();
	~Matrix() {};

public:
	void draw() const;
	void gameOver();
	void setPos(size_t, size_t, const char);
	void clean();
};

#endif