/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSTALLATIONOBJECTMESSAGE7_H_
#define INSTALLATIONOBJECTMESSAGE7_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"

class InstallationObjectMessage7 : public BaseLineMessage {
public:
	InstallationObjectMessage7(InstallationObject * inso)
			: BaseLineMessage(inso->getObjectID(), 0x494E534F, 7, 0x05) {

		if (inso->getObjectSubType() == TangibleObjectImplementation::HARVESTER) {
			HarvesterObject* hino = cast<HarvesterObject*>( inso);
			ResourceManager* resourceManager = inso->getZone()->getZoneServer()->getResourceManager();
			ResourceList* list = resourceManager->getResourceListAtLocation(inso->getZone()->getZoneName(), inso->getPositionX(), inso->getPositionY(), hino->getHarvesterType());

			if (list == NULL)
				System::out << "list was null!" << endl;

			insertByte(1); // ResourcePoolUpdateFlag ?
			insertResourceIDList(list);
			insertResourceIDList(list);
			insertResourceNameList(list);
			insertResourceTypeList(list);
		} else
		{
			insertByte(1);
			// ID
			insertInt(0);
			insertInt(0);
			// ID
			insertInt(0);
			insertInt(0);
			// Name
			insertInt(0);
			insertInt(0);
			// Type
			insertInt(0);
			insertInt(0);
		}

		insertLong(inso->getActiveResourceID());

		insertByte(inso->isOperating());

		insertInt((int)inso->getExtractionRate()); // Extraction Rate Displayed
		insertFloat(inso->getExtractionRate()); // Extract Rate Max

		insertFloat(inso->getActualRate()); // Current Extract Rate

		insertFloat(inso->getHopperSize());
		insertInt((int)inso->getHopperSizeMax());

		//insertByte(0); // Hopper Update Flag
		//insertInt(inso->getHopperSize());

		insertHopperItems(inso);

		insertByte(100); // Percentage of Condition
		setSize();

	}

	//float density = getDensity(player->getZoneIndex(), resourceName, player->getPositionX(), player->getPositionY());
	// .f

	void insertResourceIDList(ResourceList *list) {

		//System::out << "insertResourceIDList size(): " << list->size() << endl;
		insertInt(list->size()); // size
		insertInt(list->size()); // counter
		for (int x = 0; x < list->size(); x++)
		{
			ResourceItem *ri = list->get(x);
			//System::out << "insertResourceIDList() ObjectID: " << hex << ri->getObjectID() << endl;
			insertLong(ri->getObjectID());
		}

	}

	void insertResourceNameList(ResourceList *list) {

		//System::out << "insertResourceNameList size(): " << list->size() << endl;
		insertInt(list->size()); // size
		insertInt(list->size()); // counter
		for (int x = 0; x < list->size(); x++)
		{
			ResourceItem *ri = list->get(x);
			//System::out << "insertResourceNameList() Name: " << ri->getName() << endl;
			insertAscii(ri->getName());
		}
	}

	void insertResourceTypeList(ResourceList *list) {
		//System::out << "insertResourceTypeList size(): " << list->size() << endl;
		insertInt(list->size()); // size
		insertInt(list->size()); // counter
		for (int x = 0; x < list->size(); x++)
		{
			ResourceItem *ri = list->get(x);
			//System::out << "insertResourceTypeList() Type: " << ri->getType() << endl;
			insertAscii(ri->getType());
		}
	}

	void insertHopperItems(InstallationObject *inso) {

		/*insertByte(0);
		insertInt(0);
		insertInt(0);*/


		// Hopper Update Flag
		insertByte(inso->getHopperItemCount() > 0 ? 1 : 0);
		insertInt(inso->getHopperItemCount());
		insertInt(inso->getNewHopperUpdateCounter(1));
		for (int i = 0; i < inso->getHopperItemCount(); i++) {
			uint64 rid = inso->getHopperItemID(i);
			insertLong(rid);
			float quant = inso->getHopperItemQuantity(i);
			insertFloat(quant);
		}
	}
};

#endif /* INSTALLATIONOBJECTMESSAGE7_H_ */
