/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ZoneClient.h"
#include "ZonePacketHandler.h"
#include "ZoneMessageProcessorTask.h"

ZoneClient::ZoneClient(const String& address, int port) {
	client = new BaseClient(address, port);
	client->setHandler(this);

	client->setLogging(true);
	client->setLoggingName("ZoneClient");
	client->setInfoLogLevel();

	player = nullptr;

	accountID = 0;

	zone = nullptr;

	basePacketHandler = new BasePacketHandler("ZoneClient", this);
	zonePacketHandler = nullptr;
}

ZoneClient::~ZoneClient() {
	if (player != nullptr)
		delete player;

	player = nullptr;

	delete basePacketHandler,
	basePacketHandler = nullptr;
}

void ZoneClient::handleMessage(ServiceClient* client, Packet* message) {
	basePacketHandler->handlePacket(ZoneClient::client, message);
}

void ZoneClient::initialize() {
	zonePacketHandler = new ZonePacketHandler("ZonePacketHandler", zone);

	client->initialize();
}

void ZoneClient::processMessage(Message* message) {
	ZoneMessageProcessorTask* task = new ZoneMessageProcessorTask(message, zonePacketHandler);
	Core::getTaskManager()->executeTask(task);
}
