/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include <stddef.h>

#include "LoginHandler.h"
#include "LoginMessageProcessorTask.h"
#include "LoginProcessServerImplementation.h"
#include "conf/ConfigManager.h"
#include "engine/core/Core.h"
#include "engine/core/ManagedObject.h"
#include "engine/core/ManagedService.h"
#include "engine/core/Task.h"
#include "engine/core/TaskManager.h"
#include "engine/log/Logger.h"
#include "engine/service/DatagramServiceThread.h"
#include "engine/service/MessageQueue.h"
#include "engine/service/proto/BaseClientProxy.h"
#include "engine/service/proto/BasePacketHandler.h"
#include "server/login/LoginClient.h"
#include "server/login/LoginServer.h"
#include "server/login/account/AccountManager.h"
#include "server/login/objects/GalaxyList.h"
#include "server/login/packets/LoginClusterStatus.h"
#include "server/login/packets/LoginEnumCluster.h"
#include "system/io/PrintStream.h"
#include "system/lang/Exception.h"
#include "system/lang/String.h"
#include "system/lang/StringBuffer.h"
#include "system/lang/System.h"
#include "system/lang/ref/Reference.h"
#include "system/lang/ref/WeakReference.h"
#include "system/net/Packet.h"
#include "system/net/PacketIndexOutOfBoundsException.h"
#include "system/platform.h"

namespace engine {
namespace service {
class Message;
class ServiceClient;
}  // namespace service
}  // namespace engine
namespace sys {
namespace net {
class Socket;
class SocketAddress;
}  // namespace net
}  // namespace sys

LoginServerImplementation::LoginServerImplementation(ConfigManager* configMan) :
		ManagedServiceImplementation(), Logger("LoginServer") {

	phandler = NULL;

	datagramService = new DatagramServiceThread("LoginDatagramService");
	datagramService->setLogging(false);
	datagramService->setLockName("LoginServerLock");

	loginHandler = new LoginHandler();
	datagramService->setHandler(loginHandler);

	configManager = configMan;

	processor = NULL;

	enumClusterMessage = NULL;
	clusterStatusMessage = NULL;

	accountManager = NULL;

	setLogging(false);
}

void LoginServerImplementation::initializeTransientMembers() {
	phandler = NULL;

	processor = NULL;

	ManagedObjectImplementation::initializeTransientMembers();
}

void LoginServerImplementation::initialize() {
	processor = new LoginProcessServerImplementation(_this.getReferenceUnsafeStaticCast());
	processor->initialize();

	phandler = new BasePacketHandler("LoginServer", loginHandler);
	phandler->setLogging(false);

	startManagers();

	//taskManager->setLogging(false);

	populateGalaxyList();

	return;
}


void LoginServerImplementation::startManagers() {
	info("loading managers..");

	accountManager = new AccountManager(_this.getReferenceUnsafeStaticCast());
	accountManager->setAutoRegistrationEnabled(configManager->getAutoReg());
	accountManager->setRequiredVersion(configManager->getLoginRequiredVersion());
	accountManager->setMaxOnlineCharacters(configManager->getZoneOnlineCharactersPerAccount());
	accountManager->setDBSecret(configManager->getDBSecret());
}

void LoginServerImplementation::start(int p, int mconn) {
	loginHandler->setLoginSerrver(_this.getReferenceUnsafeStaticCast());

	datagramService->start(p, mconn);
}

void LoginServerImplementation::stop() {
	shutdown();

	datagramService->stop();
	datagramService = NULL;
}

void LoginServerImplementation::shutdown() {
	stopManagers();
	loginHandler = NULL;
	phandler = NULL;
	processor = NULL;
	enumClusterMessage = NULL;
	clusterStatusMessage = NULL;

	printInfo();

	info("shut down complete", true);
}

void LoginServerImplementation::stopManagers() {
	accountManager = NULL;
	configManager = NULL;

	info("managers stopped", true);
}

LoginClient* LoginServerImplementation::createConnection(Socket* sock, SocketAddress& addr) {
	BaseClientProxy* session = new BaseClientProxy(sock, addr);

	session->setLoggingName("LoginClient " + session->getIPAddress());
	session->setLogging(false);

	session->init(datagramService);

	LoginClient* client = new LoginClient(session);

	info("client connected from \'" + session->getAddress() + "\'");

	return client;
}

void LoginServerImplementation::handleMessage(LoginClient* client, Packet* message) {
	if (phandler == NULL)
		return;

	BaseClientProxy* session = cast<BaseClientProxy*>(client->getSession());

	try {
		if (session != NULL && session->isAvailable())
			phandler->handlePacket(session, message);

	} catch (PacketIndexOutOfBoundsException& e) {
		System::out << e.getMessage();

		error("incorrect packet - " + message->toStringData());
	} catch (Exception& e) {
		error(e.getMessage());
	}
}

void LoginServerImplementation::processMessage(Message* message) {
	//info("processing message " + message->toStringData());

	Reference<Task*> task = new LoginMessageProcessorTask(message, processor->getPacketHandler());

	Core::getTaskManager()->executeTask(task);
}

LoginClient* LoginServerImplementation::getLoginClient(ServiceClient* session) {
	return loginHandler->getClient(session);
}

bool LoginServerImplementation::handleError(ServiceClient* client, Exception& e) {
	BaseClientProxy* bclient = cast<BaseClientProxy*>(client);

	if (bclient != NULL) {
		bclient->setError();

		bclient->disconnect();
	}

	return true;
}

void LoginServerImplementation::printInfo() {
	lock();

	StringBuffer msg;
	msg << "MessageQueue - size = " << datagramService->getMessageQueue()->size();
	info(msg, true);

	unlock();
}

void LoginServerImplementation::populateGalaxyList() {
	//Populate the galaxies list for the login server.
	GalaxyList galaxies;
	uint32 galaxyCount = galaxies.size();

	//In case we want to add the functionality to update the lists while the server is running...
	if (enumClusterMessage != NULL) {
		delete enumClusterMessage;
		enumClusterMessage = NULL;
	}

	if (clusterStatusMessage != NULL) {
		delete enumClusterMessage;
		enumClusterMessage = NULL;
	}

	enumClusterMessage = new LoginEnumCluster(galaxyCount);
	clusterStatusMessage = new LoginClusterStatus(galaxyCount);

    while (galaxies.next()) {
    	uint32 galaxyID = galaxies.getGalaxyID();

    	String name;
    	galaxies.getGalaxyName(name);

    	enumClusterMessage->addGalaxy(galaxyID, name);

		String address;
    	galaxies.getGalaxyAddress(address);

    	clusterStatusMessage->addGalaxy(galaxyID, address, galaxies.getGalaxyPort(), galaxies.getGalaxyPingPort());
    }

    enumClusterMessage->finish();
}
