#ifndef INDEXOUTOFBOUNDSEXCEPTION_H
#define	INDEXOUTOFBOUNDSEXCEPTION_H

#include <string>
#include <iostream>
#include <exception>

using std::string;
using std::exception;


class IndexOutOfBoundsException : public exception {
private:
	int index;
	int boundIndex;
	string msg;

public:
	IndexOutOfBoundsException(int _index, int _indexBound, string _msg) throw()
		: index(_index), boundIndex(_indexBound), msg(_msg) {
	};

	virtual const char* what() const throw()
	{
		return this->msg.c_str();
	}

	int getIndex() const throw(){
		return this->index;
	}

	int getBound() const throw(){
		return this->boundIndex;
	}

	virtual ~IndexOutOfBoundsException() throw()
	{};

};

#endif	/* INDEXOUTOFBOUNDSEXCEPTION_H */
