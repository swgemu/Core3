/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/login/LoginServer.h"

#include "LoginPacketHandler.h"

#include "LoginProcessServerImplementation.h"

LoginProcessServerImplementation::LoginProcessServerImplementation(LoginServer* serv) {
	server = serv;

	loginPacketHandler = nullptr;
}

LoginProcessServerImplementation::~LoginProcessServerImplementation() {
}

void LoginProcessServerImplementation::initialize() {
	loginPacketHandler = new LoginPacketHandler("LoginPacketHandler", this);
	loginPacketHandler->setLogging(false);
}
