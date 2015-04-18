/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTCORE_H_
#define CLIENTCORE_H_

#include "system/lang.h"
#include "engine/engine.h"

class Zone;

class ClientCore : public Core, public Logger {
	int instances;

	Vector<Zone*> zones;

public:
	ClientCore(int instances);

	void initialize();

	void run();

	void loginCharacter(int index);
	void logoutCharacter(int index);

	void handleCommands();
};

#endif /*CLIENTCORE_H_*/
