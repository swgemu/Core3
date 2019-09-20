/*
 * TestCore.h
 *
 *  Created on: 03/09/2013
 *      Author: victor
 */

#ifndef TESTCORE_H_
#define TESTCORE_H_

#include "engine/engine.h"

#include "server/db/MySqlDatabase.h"

class TestCore : public Core, public Logger {
public:
	TestCore() : Core(0), Logger("TestCore") {

	}

	~TestCore() {
		finalizeContext();
	}

	void initialize() override {
		 server::db::mysql::MySqlDatabase::initializeLibrary();
	}

	void run() override {

	}

	void finalizeContext() override {
		server::db::mysql::MySqlDatabase::finalizeLibrary();
	}
};


#endif /* TESTCORE_H_ */
