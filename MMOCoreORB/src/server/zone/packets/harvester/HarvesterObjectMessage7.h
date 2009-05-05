#ifndef HARVESTEROBJECTMESSAGE7_H_
#define HARVESTEROBJECTMESSAGE7_H_

#include "../BaseLineMessage.h"

#include "../../objects/structure/installation/harvester/HarvesterObject.h"

class HarvesterObjectMessage7 : public BaseLineMessage {
public:
	HarvesterObjectMessage7(HarvesterObject * hino)
			: BaseLineMessage(hino->getObjectID(), 0x48494E4F, 7, 0x05) {

		insertResourceIDList(hino);
		insertResourceNameList(hino);
		insertResourceTypeList(hino);

		insertLong(hino->getActiveResourceID());
		insertByte(hino->isOperating());
		insertFloat(hino->getActualRate());
		insertFloat(hino->getSpecRate());
		insertFloat(hino->getTotalHopperQuantity());
		insertFloat(hino->getCapacity());

		insertInt(hino->getHopperSize());

		insertHopperItems(hino);

		setSize();

	}

	void insertResourceIDList(HarvesterObject * hino) {

		for (int x = 0; x < 2; x++) {
			insertInt(hino->getAvailableResourcesCount());
			insertInt(hino->getAvailableResourcesCount());
			for (int i = 0; i < hino->getAvailableResourcesCount(); i++) {
				insertLong(hino->getAvailableResource(i)->getObjectID());
			}
		}
	}

	void insertResourceNameList(HarvesterObject * hino) {

		for (int x = 0; x < 2; x++) {
			insertInt(hino->getAvailableResourcesCount());
			insertInt(hino->getAvailableResourcesCount());
			for (int i = 0; i < hino->getAvailableResourcesCount(); i++) {
				insertLong(hino->getAvailableResource(i)->getResourceName());
			}
		}
	}

	void insertResourceTypeList(HarvesterObject * hino) {

		for (int x = 0; x < 2; x++) {
			insertInt(hino->getAvailableResourcesCount());
			insertInt(hino->getAvailableResourcesCount());
			for (int i = 0; i < hino->getAvailableResourcesCount(); i++) {
				insertLong(hino->getAvailableResource(i)->getResourceType());
			}
		}
	}

	void insertHopperItems(HarvesterObject * hino) {

		if (getHopperCount() == 0)
			insertByte(0);
		else
			insertByte(getHopperCount() + 1)

		insertInt(hino->getHopperCount());
		insertInt(hino->getHopperCount());
		for (int i = 0; i < hino->getHopperCount(); i++) {
			insertLong(hino->getHopperResource(i)->getObjectID());
			insertFloat(hino->getHopperResource(i)->getQuantity());
		}
	}
};
#endif /*HARVESTEROBJECTMESSAGE7_H_*/
