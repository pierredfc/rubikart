#ifndef SQUARE_H
#define	SQUARE_H

#include "RubikColor.h"

class Square
{
private:
	RubikColor color;

public:
	Square();
	Square(RubikColor);
	RubikColor getColor();
	void setColor(RubikColor);
};

Square::Square(){

}

Square::Square(RubikColor _color){
	this->setColor(_color);
}

RubikColor Square::getColor(){
	return this->color;
}

void Square::setColor(RubikColor _color){
	this->color = _color;
}

#endif