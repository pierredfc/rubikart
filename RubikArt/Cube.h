#ifndef CUBE_H
#define	CUBE_H

#include "Side.h"
#include "IndexOutOfBoundsException.h" 

#include <vector>

/*
Side(0): Front (Blue)
Side(1): Right (Yellow)
Side(2): Back (Green)
Side(3): Left (White)
Side(4): Top (Orange)
Side(5): Down (Red)
*/

class Cube
{
private:
	int size;
	std::vector<Side> sides;

public:
	Cube(int size);
	void setSize(int size);
	void setSide(int sideIndex, Side side);
	void setSide(int side, Square values[]);
	std::vector<Side> getSide();
};

Cube::Cube(int size){
	this->setSize(size);
	this->sides.resize(6);
}

void Cube::setSize(int size){
	this->size = size;
}

void Cube::setSide(int sideIndex, Side side){
	this->sides.at(sideIndex) = side;
}

void Cube::setSide(int sideIndex, Square values[]){
	this->sides.at(sideIndex).setGrid(values);
}

std::vector<Side> Cube::getSide(){
	return this->sides;
}

#endif	/* CUBE_H */