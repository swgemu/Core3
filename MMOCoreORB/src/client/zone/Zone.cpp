#include "Zone.h"
#include "ZoneClientThread.h"
#include "ClientCore.h"
#include "client/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/zone/ClientIdMessage.h"
#include "client/zone/managers/objectcontroller/ObjectController.h"
#include "client/zone/managers/object/ObjectManager.h"

Zone::Zone(uint32 account, const String& sessionID, const String& galaxyAddress, uint32 galaxyPort) : Thread(), Mutex("Zone"), Logger("Zone") {
	accountID = account;
	this->sessionID = sessionID;
	this->galaxyAddress = galaxyAddress;
	this->galaxyPort = galaxyPort;

	objectManager = new ObjectManager();
	objectManager->setZone(this);

	objectController = new ObjectController(this);

	client = nullptr;
	clientThread = nullptr;

	started = false;
	sceneReady = false;

	characterCreated = false;
	characterCreationFailed = false;
	createdCharacterOID = 0;

	canLogin = false;
	canCreateRegularCharacter = false;
	canCreateJediCharacter = false;
	canSkipTutorial = false;

	lastError = "";
	lastErrorCode = 0;

	setLogLevel(static_cast<Logger::LogLevel>(ClientCore::getLogLevel()));

	info(true) << "Zone connection created to " << galaxyAddress << ":" << galaxyPort;
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
		client->getClient()->setLoggingName("ZoneClient");
		client->getClient()->setLogLevel(static_cast<Logger::LogLevel>(ClientCore::getLogLevel()));
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

JSONSerializationType Zone::collectStats() {
	JSONSerializationType stats;
	stats["elapsedMs"] = startTime.miliDifference();
	stats["packetCount"] = client != nullptr ? client->getPacketCount() : 0;
	stats["sceneReady"] = sceneReady;

	// Add unknown opcodes if any
	if (client != nullptr) {
		auto& unknownOps = client->getZonePacketHandler()->getUnknownOpcodes();
		if (unknownOps.size() > 0) {
			JSONSerializationType unknownStats;
			for (int i = 0; i < unknownOps.size(); i++) {
				StringBuffer key;
				key << "0x" << hex << uppercase << unknownOps.elementAt(i).getKey();
				unknownStats[key.toString().toCharArray()] = unknownOps.elementAt(i).getValue();
			}
			stats["unknownOpcodes"] = unknownStats;
		}
	}

	return stats;
}
