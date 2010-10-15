/*
 * LoginServerImplementation.cpp
 *
 *  Created on: Oct 13, 2010
 *      Author: crush
 */

#include "LoginServer.h"
#include "LoginClient.h"

#include "LoginProcessServerImplementation.h"

#include "server/conf/ConfigManager.h"
#include "server/login/account/AccountManager.h"
#include "server/login/account/Account.h"

#include "LoginHandler.h"

#include "objects.h"

LoginServerImplementation::LoginServerImplementation(ConfigManager* configMan) :
		ManagedServiceImplementation(), Logger("LoginServer") {

	phandler = NULL;

	datagramService = new DatagramServiceThread("LoginServer");
	datagramService->setLogging(false);
	datagramService->setLockName("LoginServerLock");

	configManager = configMan;

	processor = NULL;
	procThreadCount = configManager->getLoginProcessingThreads();

	enumClusterMessage = NULL;
	clusterStatusMessage = NULL;

	accountManager = NULL;
}

void LoginServerImplementation::initializeTransientMembers() {
	phandler = NULL;

	processor = NULL;

	ManagedObjectImplementation::initializeTransientMembers();
}

void LoginServerImplementation::initialize() {
	processor = new LoginProcessServerImplementation(_this, procThreadCount);
	processor->init();

	phandler = new BasePacketHandler("LoginServer", processor->getMessageQueue());
	phandler->setLogging(false);

	startManagers();

	//taskManager->setLogging(false);

	populateGalaxyList();

	return;
}


void LoginServerImplementation::startManagers() {
	info("loading managers..");

	accountManager = new AccountManager(_this);
	accountManager->setAutoRegistrationEnabled(configManager->getAutoReg());
	accountManager->setRequiredVersion(configManager->getLoginRequiredVersion());
	accountManager->setMaxOnlineCharacters(configManager->getZoneOnlineCharactersPerAccount());
}

void LoginServerImplementation::start(int p, int mconn) {
	LoginHandler* loginHandler = new LoginHandler(_this);
	datagramService->setHandler(loginHandler);

	datagramService->start(p, mconn);

	processor->start();
}

void LoginServerImplementation::run() {
	processor->run();

	// recieve messages
	//receiveMessages();

	shutdown();
}


void LoginServerImplementation::stop() {
	datagramService->stop();
}

void LoginServerImplementation::shutdown() {
	processor->stop();

	stopManagers();

	printInfo();

	info("shut down complete", true);
}

void LoginServerImplementation::stopManagers() {
	accountManager = NULL;

	info("managers stopped", true);
}

ServiceClient* LoginServerImplementation::createConnection(Socket* sock, SocketAddress& addr) {
	LoginClient* client = new LoginClient(datagramService, sock, addr);

	info("client connected from \'" + client->getAddress() + "\'");

	return client;
}

void LoginServerImplementation::handleMessage(ServiceClient* client, Packet* message) {
	LoginClient* lclient = (LoginClient*) client;

	try {
		if (lclient->isAvailable())
			phandler->handlePacket(lclient, message);

	} catch (PacketIndexOutOfBoundsException& e) {
		System::out << e.getMessage();

		error("incorrect packet - " + message->toStringData());
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (ArrayIndexOutOfBoundsException& e) {
		error(e.getMessage());
	} catch (...) {
		System::out << "[LoginServer] unreported Exception caught\n";
	}
}

bool LoginServerImplementation::handleError(ServiceClient* client, Exception& e) {
	LoginClient* lclient = (LoginClient*) client;
	lclient->setError();

	lclient->disconnect();

	return true;
}

void LoginServerImplementation::printInfo() {
	lock();

	StringBuffer msg;
	msg << "MessageQueue - size = " << processor->getMessageQueue()->size();
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
}
