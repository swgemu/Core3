#ifndef HARVESTERSPAWNEVENT_H_
#define HARVESTERSPAWNEVENT_H_

//#include "../PlanetManagerImplementation.h"
//#include "../../../objects/installation/harvester/HarvesterObjectImplementation.h"

//#include "../../../../chat/ChatManagerImplementation.h"

class HarvesterSpawnEvent : public Event {
	HarvesterObject* hino;
	Player* player;

public:
	HarvesterSpawnEvent(Player * play, HarvesterObject * inHino) : Event() {

		hino = inHino;
		player = play;

		setKeeping(false);
	}

	bool activate() {

		try {
			cout << "HarvesterSpawnEvent Start" << endl;
			player->wlock();
			// Insert Structure to Zone
			hino->insertToZone(player->getZone());

			// Send Construction Email
			//string mailSender = "Structure Builder";
			//string charNameSender = player->getFirstName();

			//unicode subjectSender("Construction Complete");
			//unicode bodySender("Construction of your " + hino->getName().c_str() + " is now complete.  You have xx lots remaining.");

			//player->sendMail(mailSender, subjectSender, bodySender, charNameSender);
			cout << "HarvesterSpawnEvent::Mail complete" << endl;
			// Create Waypoint to Structure
			WaypointObject* waypoint = new WaypointObject(player, player->getNewItemID());
			waypoint->setName(hino->getName().c_str());
			waypoint->setPosition(hino->getPositionX(), 0.0f, hino->getPositionY());
			waypoint->changeStatus(true);

			player->addWaypoint(waypoint);

			cout << "HarvesterSpawnEvent::Waypoint complete" << endl;

			player->unlock();
		} catch (...) {
			player->unlock();
		}

		return true;
	}

};

#endif /*HARVESTERSPAWNEVENT_H_*/
