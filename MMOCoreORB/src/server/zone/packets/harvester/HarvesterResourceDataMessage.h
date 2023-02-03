/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTERRESOURCEDATAMESSAGE_H_
#define HARVESTERRESOURCEDATAMESSAGE_H_

#include "server/zone/packets/object/ObjectControllerMessage.h"

class HarvesterResourceDataMessage : public ObjectControllerMessage {
public:
	HarvesterResourceDataMessage(CreatureObject* player, HarvesterObject* hino, Zone* zone)
		: ObjectControllerMessage(player->getObjectID(), 0x0B, 0xEA) {
			printf("HarvesterResourceDataMessage\n");
		insertLong(hino->getObjectID()); // Harvester Object

		Vector<InstallationResourceData*> data;
		hino->getResourceData(data);

		insertResourceList(data, hino);

	}

	void insertResourceList(Vector<InstallationResourceData*>& list, HarvesterObject* hino) {
		insertInt(list.size()); // list size

/*		LONG:		Resource ID
		ASTRING:	Resource Name
		ASTRING:	Resource Type
		BYTE:		Resource Density
*/
printf("HarvesterResourceDataMessage adding %i resources\n", list.size());
		for (int x = 0; x < list.size(); x++) {
			InstallationResourceData* data = list.get(x);
			hino->info(true) << "id " << data->getId() << ", name " << data->getName() << ", parent " << data->getParentName() << ", efficiency " << (int)data->getEfficiency();
			insertLong(data->getId());
			insertAscii(data->getName());
			insertAscii(data->getParentName());
			insertByte((int)data->getEfficiency());
		}

	}

};

#endif /* HARVESTERRESOURCEDATAMESSAGE_H_ */
