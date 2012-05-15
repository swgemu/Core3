//#include "..\login\LoginSession.h"

#include "Zone.h"

/*#include "packets/zone/SelectCharacterMessage.h"
#include "packets/zone/ClientCreateCharacter.h"
#include "packets/zone/ClientIDMessage.h"*/
#include "ZoneClientThread.h"

#include "engine/service/proto/packets/SessionIDRequestMessage.h"
#include "../../server/zone/packets/zone/ClientIDMessage.h"
#include "../../server/zone/packets/zone/SelectCharacter.h"
#include "../../server/zone/packets/charcreation/ClientCreateCharacter.h"
#include "managers/objectcontroller/ObjectController.h"
#include "managers/object/ObjectManager.h"

int Zone::createdChar = 0;

Zone::Zone(int instance, uint64 characterObjectID, uint32 account, uint32 session) : Thread(), Mutex("Zone") {
	//loginSession = login;

	characterID = characterObjectID;
	accountID = account;
	sessionID = session;
	player = NULL;

	objectManager = new ObjectManager();
	objectManager->setZone(this);

	objectController = new ObjectController(this);

	client = NULL;
	clientThread = NULL;

	Zone::instance = instance;
}

Zone::~Zone() {
	delete objectManager;
	objectManager = NULL;

	clientThread->stop();
}

void Zone::run() {
	try {
		client = new ZoneClient(44463);
		client->setAccountID(accountID);
		client->setZone(this);
		client->getClient()->setLoggingName("ZoneClient" + String::valueOf(instance));
		client->initialize();

		clientThread = new ZoneClientThread(client);
		clientThread->start();

		if (client->connect()) {
			client->getClient()->info("connected", true);
		} else {
			client->getClient()->error("could not connect");
			return;
		}

		startTime.updateToCurrentTime();

		BaseMessage* acc = new ClientIDMessage(accountID, sessionID);
		client->sendMessage(acc);

		client->getClient()->info("sent client id message");

		started = true;

#ifdef WITH_STM
	//TransactionalMemoryManager::commitPureTransaction();
#endif

	} catch (sys::lang::Exception& e) {
		System::out << e.getMessage() << "\n";
		exit(0);
	}
}

void Zone::insertPlayer() {
	insertPlayer(player);
}

void Zone::insertPlayer(PlayerCreature* pl) {
	//lock();

	/*if (player == NULL) {
		player = pl;

		player->insertToZone(this);
	}*/

//	System::out << hex << "inserting Player [" << pl->getObjectID() << "] to (" << dec << pl->getPositionX() << ", "
//		 << pl->getPositionZ() << ", " << pl->getPositionY() << ")\n";


	//unlock();
}

SceneObject* Zone::getObject(uint64 objid) {
	//lock();

	//SceneObject* obj = objectMap.get(objid);

	//unlock();


	SceneObject* obj = objectManager->getObject(objid);

	return obj;
}

PlayerCreature* Zone::getSelfPlayer() {
	return (PlayerCreature*)objectManager->getObject(characterID);
}

void Zone::disconnect() {
	if (client != NULL) {
		client->disconnect();
	}
}

void Zone::sceneStarted() {
	client->getClient()->info("zone started in " + String::valueOf(startTime.miliDifference()) + "ms", true);
}

void Zone::follow(const String& name) {
	SceneObject* object = objectManager->getObject(name);

	if (object == NULL) {
		client->getClient()->error(name + " not found");

		return;
	}

	PlayerCreature* player = getSelfPlayer();

	Locker _locker(player);
	player->setFollow(object);

	client->getClient()->info("started following " + name, true);
}

void Zone::stopFollow() {
	PlayerCreature* player = getSelfPlayer();

	Locker _locker(player);

	player->setFollow(NULL);
	client->getClient()->info("stopped following", true);
}

void Zone::lurk() {
	PlayerCreature* player = getSelfPlayer();

	Locker _locker(player);
}

bool Zone::doCommand(const String& command, const String& arguments) {
	if (command.length() == 0)
		return false;

	return objectController->doCommand(command.hashCode(), arguments);
}

/*void Zone::waitFor() {
	client->join();
}*/
