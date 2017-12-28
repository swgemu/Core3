/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "LoginClient.h"
#include "LoginMessageProcessorTask.h"
#include "LoginPacketHandler.h"
#include "engine/core/Core.h"
#include "engine/core/TaskManager.h"
#include "engine/service/proto/BasePacketHandler.h"

namespace engine {
namespace service {
class Message;
class ServiceClient;
}  // namespace service
}  // namespace engine
namespace sys {
namespace net {
class Packet;
}  // namespace net
}  // namespace sys

LoginClient::LoginClient(int port, const String& loggingName) {
	client = new BaseClient("localhost", port);

	client->setLogging(true);
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
