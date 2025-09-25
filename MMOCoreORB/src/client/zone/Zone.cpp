#include "Zone.h"
#include "ZoneClientThread.h"

#include "server/zone/packets/zone/ClientIdMessage.h"
#include "client/zone/managers/objectcontroller/ObjectController.h"
#include "client/zone/managers/object/ObjectManager.h"

Zone::Zone(int instance, uint64 characterObjectID, uint32 account, const String& sessionID, const String& galaxyAddress, uint32 galaxyPort) : Thread(), Mutex("Zone"), Logger("Zone") {
	characterID = characterObjectID;
	accountID = account;
	this->sessionID = sessionID;
	this->galaxyAddress = galaxyAddress;
	this->galaxyPort = galaxyPort;
	player = nullptr;

	objectManager = new ObjectManager();
	objectManager->setZone(this);

	objectController = new ObjectController(this);

	client = nullptr;
	clientThread = nullptr;

	Zone::instance = instance;
	started = false;
	sceneReady = false;

	info(true) << "Zone created for character " << characterObjectID << " with sessionID: " << sessionID;
}

Zone::~Zone() {
	delete objectManager;
	objectManager = nullptr;
}

void Zone::run() {
	try {
		info(true) << "Zone::run() connecting to " << galaxyAddress << ":" << galaxyPort;

		client = new ZoneClient(galaxyAddress, galaxyPort);
		client->setAccountID(accountID);
		client->setZone(this);
		client->getClient()->setLoggingName("ZoneClient" + String::valueOf(instance));
		client->initialize();

		info(true) << "ZoneClient created and initialized";

		clientThread = new ZoneClientThread(client);
		clientThread->start();

		info(true) << "ZoneClientThread started";

		if (client->connect()) {
			info(true) << "Connected to zone server";
		} else {
			error() << "ERROR: Could not connect to zone server";
			return;
		}

		startTime.updateToCurrentTime();

		// Send ClientIdMessage with sessionID
		info(true) << "Sending ClientIdMessage...";
		BaseMessage* acc = new ClientIdMessage(accountID, sessionID);
		client->sendMessage(acc);
		info(true) << "ClientIdMessage sent";

		started = true;

#ifdef WITH_STM
	//TransactionalMemoryManager::commitPureTransaction();
#endif

	} catch (sys::lang::Exception& e) {
		error() << "Zone::run() exception: " << e.getMessage();
		exit(0);
	}
}

SceneObject* Zone::getObject(uint64 objid) {
	if (objectManager == nullptr)
		return nullptr;

	return objectManager->getObject(objid);
}

PlayerCreature* Zone::getSelfPlayer() {
	return (PlayerCreature*)objectManager->getObject(characterID);
}
