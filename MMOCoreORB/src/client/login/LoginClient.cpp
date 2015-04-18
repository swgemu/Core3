/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "engine/service/proto/packets/SessionIDRequestMessage.h"

//#include "objects/player/Player.h"
#include "LoginMessageProcessorTask.h"

#include "LoginSession.h"

#include "LoginPacketHandler.h"

#include "LoginClient.h"

LoginClient::LoginClient(int port, const String& loggingName) {
	client = new BaseClient("localhost", port);

	client->setLogging(false);
	client->setLoggingName(loggingName);

	loginSession = NULL;

	basePacketHandler = new BasePacketHandler("LoginClient", this);
	loginPacketHandler = NULL;
}

LoginClient::~LoginClient() {
	delete basePacketHandler;
	basePacketHandler = NULL;
}

void LoginClient::initialize() {
	loginPacketHandler = new LoginPacketHandler(loginSession);

	client->setHandler(this);
	client->initialize();
}

void LoginClient::handleMessage(ServiceClient* client, Packet* message) {
	basePacketHandler->handlePacket(LoginClient::client, message);
}

void LoginClient::processMessage(Message* message) {
	LoginMessageProcessorTask* task = new LoginMessageProcessorTask(message, loginPacketHandler);
	Core::getTaskManager()->executeTask(task);
}
