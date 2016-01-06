#ifndef RUBIKCOLOR_H
#define	RUBIKCOLOR_H


/*
0: Green
1: Blue
2: Red
3: Orange
4: Yellow
5: White
*/
class RubikColor
{
private:
	int color;

public:
	RubikColor();
	RubikColor(int);
	int getColorName();
	void setColor(int);
};

RubikColor::RubikColor(){

}

RubikColor::RubikColor(int _color){
	this->setColor(_color);
}

void RubikColor::setColor(int _color){
	this->color = _color;
}
int RubikColor::getColorName(){
	return this->color;
}

#endif