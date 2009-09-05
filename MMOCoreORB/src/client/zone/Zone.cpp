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


Zone::Zone(uint64 characterObjectID, uint32 account) : Thread(), Mutex("Zone") {
	//loginSession = login;

	characterID = characterObjectID;
	accountID = account;
	player = NULL;

	objectManager = new ObjectManager();

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

/*
			uint64 playerID = characterID;

			Player * player = createPlayer(playerID);
			player->setPosition(0, 5, 0);

			insertPlayer(player);
		*/
	} catch (sys::lang::Exception& e) {
		System::out << e.getMessage() << "\n";
		exit(0);
	} catch (...) {
		System::out << "unreported exception\n";
	}
}

Player* Zone::createPlayer(uint64 pid) {
	lock();

	Player* pl = new Player(pid);

	objectMap.put(pid, pl);

	playerArray.add(pl);

	unlock();
	return pl;
}

void Zone::insertPlayer() {
	insertPlayer(player);
}

void Zone::insertPlayer(Player* pl) {
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
	return obj;
}

/*void Zone::waitFor() {
	client->join();
}*/
