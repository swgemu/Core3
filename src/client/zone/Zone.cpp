//#include "..\login\LoginSession.h"

#include "Zone.h"

/*#include "packets/zone/SelectCharacterMessage.h"
#include "packets/zone/ClientCreateCharacter.h"
#include "packets/zone/ClientIDMessage.h"*/

Zone::Zone(ScheduleManager* sched, LoginSession* login) : Thread(), Mutex("Zone") {
	scheduler = sched;

	loginSession = login;

	player = NULL;

	client = new ZoneClient("127.0.0.1", 44463);
	//client = new ZoneClient("80.99.84.166", 44463);
	client->init(scheduler);

	client->setZone(this);
}

void Zone::run() {
	try {
		characterID = 8; //loginSession->getCharacterID ( );

		if (client != NULL) {
			if (characterID == 0) {
				/*Message * idmsg = new ClientIDMessage ( loginSession->getAccountID ( ) );
				client->sendMessage ( idmsg );*/

				string name;

				cout << "Creating Charater\nName: ";
				cin >> name;

				unicode uname = name;

				/*Message* msg = new ClientCreateCharacter (uname);
				client->sendMessage(msg);*/

				lock();

				characterCreatedCondition.wait(this);

				unlock();
			}

			/*Message* msg = new SelectCharacterMessage(characterID);
			client->sendMessage(msg);*/
		} else {
			/*uint64 playerID = characterID;

			Player * player = createPlayer(playerID);
			player->setPosition(0, 5, 0);

			insertPlayer(player);*/
		}
	} catch (sys::lang::Exception& e) {
		cout << e.getMessage() << "\n";
		exit(0);
	} catch (...) {
		cout << "unreported exception\n";
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

//	cout << hex << "inserting Player [" << pl->getObjectID() << "] to (" << dec << pl->getPositionX() << ", "
//		 << pl->getPositionZ() << ", " << pl->getPositionY() << ")\n";

	unlock();
}

SceneObject* Zone::getObject(uint64 objid) {
	lock();

	SceneObject* obj = objectMap.get(objid);

	unlock();
	return obj;
}

void Zone::waitFor() {
	client->join();
}
