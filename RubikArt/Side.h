#ifndef SIDE_H
#define	SIDE_H

#include "IndexOutOfBoundsException.h" 
#include "RubikColor.h"
#include "Square.h"

#include <vector>
#include <iostream> // Use for the function draw().

using std::cout;
using std::endl;

/*
Representation of the Side for 2x2 :
| 1    2 |
| 3    4 |

Representation of the Side for 3x3 :
| 1    2    3 |
| 4    5    6 |
| 7    8    9 |

Corners are 1 - 3 - 7 - 9
Edges are 2 - 4 - 6 - 8
Middle are 5
*/

class Side
{
protected:
	std::vector<Square> grid;

public:
	Side();
	Side(int size);
	void display();
	void setGrid(Square values[]);
	Square getValue(int index);
	void setValue(int index, Square value);
};

Side::Side(){

}

Side::Side(int size){
	this->grid.resize(size*size);
}

/*void Side::display(){
for (int i = 0; i < grid.size(); i++){
cout << this->grid.at(i).getColor().getColorName().at(0);

if ((i % (int)sqrt(static_cast<double>(grid.size()))) == 0){
cout << "\n";
}
}
}*/

void Side::setGrid(Square values[]){
	if ((sizeof(values) / sizeof(char)) != grid.size())
		return;

	for (int i = 0; i < grid.size(); i++){
		this->setValue(i, values[i]);
	}
}

void Side::setValue(int index, Square value){
	if (index < 0 || index >= grid.size()){
		throw IndexOutOfBoundsException(index, grid.size() - 1, "setValue: The index is out of bounds.");
	}

	this->grid.at(index) = value;
}

Square Side::getValue(int index){
	if (index < 0 || index >= grid.size()){
		throw IndexOutOfBoundsException(index, grid.size() - 1, "getValue: The index is out of bounds.");
	}

	return this->grid.at(index);
}

#endif	/* SIDE_H */

