/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OBJECTDATABASECORE_H_
#define OBJECTDATABASECORE_H_

#include "engine/engine.h"

class ObjectDatabaseCore : public Core, public Logger {

public:
	ObjectDatabaseCore();

	void initialize();

	void run();
};

#endif /*OBJECTDATABASECORE_H_*/
