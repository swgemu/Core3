#ifndef TEMPINSTALLATIONDESPAWNEVENT_H_
#define TEMPINSTALLATIONDESPAWNEVENT_H_

#include "../StructureManagerImplementation.h"

class TempInstallationDespawnEvent : public Event {
	InstallationObject * inso;
	DeedObject *deed;
	Player *player;
	float x;
	float z;
	float y;
	float oX;
	float oZ;
	float oY;
	float oW;

public:
	TempInstallationDespawnEvent(InstallationObject * inInso, Player *play, DeedObject *targetDeed, float x, float z, float y, float oX, float oZ, float oY, float oW) : Event() {

		inso = inInso;
		deed = targetDeed;
		player = play;
		this->x = x;
		this->z = z;
		this->y = y;
		this->oX = oX;
		this->oZ = oZ;
		this->oY = oY;
		this->oW = oW;

		setKeeping(false);
	}

	bool activate() {

		//System::out << "TempInstallationDespawnEvent::activate()" << endl;



		inso->removeFromZone();
		inso->finalize();

		PlanetManager *planetManager = player->getZone()->getPlanetManager();
		StructureManager *structureManager = planetManager->getStructureManager();

		//System::out << "TempInstallationDespawnEvent::activate() Deed object type is = " << deed->getObjectType() << " sub object type = " << deed->getObjectType() << endl;
		switch(deed->getObjectSubType()) {
			case TangibleObjectImplementation::INSTALLATIONDEED:

				switch(DeedObjectImplementation::getSubType(deed->getObjectCRC())){
					case TangibleObjectImplementation::HARVESTER:
						structureManager->spawnHarvester(player, deed, x, z, y, oX, oZ, oY, oW);
						break;
					case TangibleObjectImplementation::FACTORY:
						structureManager->spawnFactory(player, deed, x, z, y, oX, oZ, oY, oW);
						break;
					case TangibleObjectImplementation::GENERATOR:
					case TangibleObjectImplementation::TURRET:
					case TangibleObjectImplementation::MINEFIELD:
						structureManager->spawnInstallation(player, deed, x, z, y, oX, oZ, oY, oW);
						break;
				}
				break;
			case TangibleObjectImplementation::BUILDINGDEED:
				structureManager->spawnBuilding(player, deed, x, z, y, oX, oZ, oY, oW);
				break;

			default:
				break;
		}

		//int lots = player->getLotsRemaining();
		//lots -= deed->getLotSize();
		//player->setLotsRemaining(lots);

		return true;
	}

};

#endif /*TEMPINSTALLATIONDESPAWNEVENT_H_*/
