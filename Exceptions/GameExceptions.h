#ifndef GAMEEXCEPTIONS_H
#define GAMEEXCEPTIONS_H

#include "BaseException.h"

class GameException : public BaseException {
public:
	using BaseException::BaseException;
};

class SaveException : public BaseException {
public:
	using BaseException::BaseException;
};

class LoadException : public BaseException {
public:
	using BaseException::BaseException;
};

#endif //GAMEEXCEPTIONS_H
