/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ZoneClient.h"
#include "ZonePacketHandler.h"
#include "ZoneMessageProcessorTask.h"

ZoneClient::ZoneClient(int port) {
	client = new BaseClient("localhost", port);
	client->setHandler(this);

	client->setLogging(true);
	client->setLoggingName("ZoneClient");

	player = NULL;

	key = 0;
	accountID = 0;

	zone = NULL;

	basePacketHandler = new BasePacketHandler("ZoneClient", this);
	zonePacketHandler = NULL;
}

ZoneClient::~ZoneClient() {
	if (player != NULL)
		delete player;

	player = NULL;

	delete basePacketHandler,
	basePacketHandler = NULL;
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
