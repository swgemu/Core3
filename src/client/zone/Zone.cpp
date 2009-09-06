//#include "..\login\LoginSession.h"

#include "Zone.h"

/*#include "packets/zone/SelectCharacterMessage.h"
#include "packets/zone/ClientCreateCharacter.h"
#include "packets/zone/ClientIDMessage.h"*/
#include "ZoneMessageProcessorThread.h"
#include "ZoneClientThread.h"

#include "engine/service/proto/packets/SessionIDRequestMessage.h"
#include "../../server/zone/packets/zone/ClientIDMessage.h"
#include "../../server/zone/packets/zone/SelectCharacter.h"
#include "../../server/zone/packets/charcreation/ClientCreateCharacter.h"
#include "managers/objectcontroller/ObjectController.h"
#include "managers/object/ObjectManager.h"


Zone::Zone(uint64 characterObjectID, uint32 account) : Thread(), Mutex("Zone") {
	//loginSession = login;

	characterID = characterObjectID;
	accountID = account;
	player = NULL;

	objectManager = new ObjectManager();
	objectManager->setZone(this);

	objectController = ObjectController::instance();
	objectController->setZone(this);

	client = new ZoneClient("127.0.0.1", 44463);
	client->setAccountID(accountID);
	client->setZone(this);
	client->initialize();

	clientThread = new ZoneClientThread(client);
	clientThread->start();

	processor = new ZoneMessageProcessorThread("Zone", client);
	processor->start();
}

void Zone::run() {
	try {
		if (client->connect()) {
			client->info("connected", true);
		} else {
			client->error("could not connect");
			return;
		}

		BaseMessage* acc = new ClientIDMessage(accountID);
		client->sendMessage(acc);

		client->info("sent client id message", true);

		if (characterID == 0) {
			char name[256];
			client->info("enter new Character Name to create", true);
			gets(name);

			BaseMessage* msg = new ClientCreateCharacter(name);
			client->sendMessage(msg);
		} else {
			BaseMessage* selectChar = new SelectCharacter(characterID);
			client->sendMessage(selectChar);
		}

	} catch (sys::lang::Exception& e) {
		System::out << e.getMessage() << "\n";
		exit(0);
	} catch (...) {
		System::out << "unreported exception\n";
	}
}

void Zone::insertPlayer() {
	insertPlayer(player);
}

void Zone::insertPlayer(PlayerCreature* pl) {
	lock();

	if (player == NULL) {
		player = pl;

		player->insertToZone(this);
	}

//	System::out << hex << "inserting Player [" << pl->getObjectID() << "] to (" << dec << pl->getPositionX() << ", "
//		 << pl->getPositionZ() << ", " << pl->getPositionY() << ")\n";

	unlock();
}

SceneObject* Zone::getObject(uint64 objid) {
	lock();

	SceneObject* obj = objectMap.get(objid);

	unlock();

	if (obj == NULL)
		obj = objectManager->getObject(objid);

	return obj;
}

PlayerCreature* Zone::getSelfPlayer() {
	return (PlayerCreature*)objectManager->getObject(characterID);
}

void Zone::disconnect() {
	client->disconnect();
}

void Zone::follow(const String& name) {
	SceneObject* object = objectManager->getObject(name);

	if (object == NULL)
		client->error(name + " not found");

	getSelfPlayer()->setFollow(object);

	client->info("started following " + name, true);
}

void Zone::stopFollow() {
	getSelfPlayer()->setFollow(NULL);
	client->info("stopped following", true);
}

bool Zone::doCommand(const String& command, const String& arguments) {
	return objectController->doCommand(command.hashCode(), arguments);
}

/*void Zone::waitFor() {
	client->join();
}*/
