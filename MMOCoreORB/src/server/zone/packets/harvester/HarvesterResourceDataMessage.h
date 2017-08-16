/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTERRESOURCEDATAMESSAGE_H_
#define HARVESTERRESOURCEDATAMESSAGE_H_

#include "server/zone/packets/object/ObjectControllerMessage.h"

class HarvesterResourceDataMessage : public ObjectControllerMessage {
public:
	HarvesterResourceDataMessage(CreatureObject* player, InstallationObject* hino, Zone* zone)
		: ObjectControllerMessage(player->getObjectID(), 0x0B, 0xEA) {

		insertLong(hino->getObjectID()); // Harvester Object

		Vector<ManagedReference<ResourceSpawn*> > resourceList;

		ResourceManager* resourceManager = hino->getZoneServer()->getResourceManager();
		resourceManager->getResourceListByType(resourceList, hino->getInstallationType(), zone->getZoneName());

		/*StringBuffer msg;
		msg << "resource list for type " << hino->getInstallationType() << " with size " << resourceList.size();
		hino->info(msg.toString(), true);*/

		insertResourceList(&resourceList, hino);

	}

	void insertResourceList(Vector<ManagedReference<ResourceSpawn*> >* list, InstallationObject* hino) {

		//System::out << "insertResourceList size(): " << list->size() << endl;
		insertInt(list->size()); // list size

/*		LONG:		Resource ID
		ASTRING:	Resource Name
		ASTRING:	Resource Type
		BYTE:		Resource Density
*/
		for (int x = 0; x < list->size(); x++) {
			ResourceSpawn* ri = list->get(x);
			//System::out << "insertResourceList() ObjectID: " << hex << ri->getObjectID() << endl;
			insertLong(ri->getObjectID());
			insertAscii(ri->getName());
			insertAscii(ri->getType());
			auto zone = hino->getZone();

			if (zone != nullptr) {
				insertByte((int) (ri->getDensityAt(zone->getZoneName(), hino->getPositionX(), hino->getPositionY()) * 100.f));
			} else {
				insertByte((int) 0);
			}
		}

	}

};

/*

if (list == NULL)
	System::out << "list was null!" << endl;
*/


#endif /* HARVESTERRESOURCEDATAMESSAGE_H_ */
