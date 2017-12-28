/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include <stddef.h>

#include "LoginPacketHandler.h"
#include "LoginProcessServerImplementation.h"
#include "server/login/LoginServer.h"

LoginProcessServerImplementation::LoginProcessServerImplementation(LoginServer* serv) {
	server = serv;

	loginPacketHandler = NULL;
}

LoginProcessServerImplementation::~LoginProcessServerImplementation() {
	if (loginPacketHandler != NULL) {
		delete loginPacketHandler;
		loginPacketHandler = NULL;
	}
}

void LoginProcessServerImplementation::initialize() {
	loginPacketHandler = new LoginPacketHandler("LoginPacketHandler", this);
	loginPacketHandler->setLogging(false);
}
